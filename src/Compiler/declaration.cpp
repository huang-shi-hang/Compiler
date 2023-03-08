#include "declaration.hpp"
#include "bindings.hpp"
#include "type.hpp"
#include "expression.hpp"

#include <algorithm>
#include <cstdio>
#include <memory>
#include <vector>

// Declaration

Declaration::Declaration(Expression *initializer)
	: initializer_(initializer), extern_declaration_(false)
{}

Declaration::Declaration(ExpressionPtr initializer)
	: initializer_(initializer), extern_declaration_(false)
{}

void Declaration::linkDeclaration(Declaration* next_declaration)
{
	DeclarationPtr decl_ptr(next_declaration);
	next_declaration_ = decl_ptr;
}

void Declaration::linkListDeclaration(Declaration* next_declaration)
{
	DeclarationPtr decl_ptr(next_declaration);
	next_list_declaration_ = decl_ptr;
}

void Declaration::setType(TypePtr type)
{
	type_ = type;
}

void Declaration::setInitializer(Expression* initializer)
{
	ExpressionPtr expression_ptr(initializer);
	initializer_ = expression_ptr;
}

void Declaration::setExternDeclaration(bool is_extern)
{
	extern_declaration_ = is_extern;
}

DeclarationPtr Declaration::getNext() const
{
	return next_declaration_;
}

DeclarationPtr Declaration::getNextListItem() const
{
	return next_list_declaration_;
}

ExpressionPtr Declaration::getInitializer() const
{
	return initializer_;
}

TypePtr Declaration::getType() const
{
	return type_;
}


// IdentifierDeclaration

IdentifierDeclaration::IdentifierDeclaration(const std::string &id, Expression *initializer)
	: Declaration(initializer), id_(id)
{}

IdentifierDeclaration::IdentifierDeclaration(const std::string &id, ExpressionPtr initializer)
	: Declaration(initializer), id_(id)
{}

void IdentifierDeclaration::print() const
{
	if(next_declaration_ != nullptr)
		next_declaration_->print();
    
	if(id_ != "")
		printf("%s\n", id_.c_str());
}

void IdentifierDeclaration::printIR() const{}

Bindings IdentifierDeclaration::printAsm(Bindings bindings, int& label_count) const
{
	(void)label_count;
	if(!extern_declaration_)
	{
		if(initializer_ == nullptr)
			printf("\t.globl\t%s\n\t.section\t.sdata\n\t.align\t2\n\t.type %s, @object\n\t.size\t%s, 4\n%s:\n\t.zero\t4\n",
					id_.c_str(),id_.c_str(),id_.c_str(),id_.c_str());
		else
			printf("\t.globl\t%s\n\t.section\t.sdata\n\t.align\t2\n\t.type\t%s, @object\n\t.size\t%s, 4\n%s:\n\t.word %d\n",
				id_.c_str(), id_.c_str(),id_.c_str(),id_.c_str(),initializer_->constantFold());
	}
	bindings.insertBinding(id_, type_, -1);
	return bindings;
}


Bindings IdentifierDeclaration::localAsm(Bindings bindings, int& label_count) const
{
	if(next_declaration_ != nullptr)
		bindings = next_declaration_->localAsm(bindings, label_count);

	if(next_list_declaration_ != nullptr)
		bindings = next_list_declaration_->localAsm(bindings, label_count);
		//声明表的最后面，生命表应该是有多个，相互链接，形成作用域
    
	if(id_ != "")
	{
		int stack_position = bindings.currentStackPosition();
		if(initializer_ != nullptr)
		{
			initializer_->printAsm(bindings, label_count);
			type_->store(stack_position);
		}
		bindings.insertBinding(id_, type_, stack_position);//记录id
		type_->increaseStackPosition(bindings);
	}//如果被初始化，就要生成相关的指令
	
	return bindings;
}

void IdentifierDeclaration::countDeclarations(int &declaration_count) const
{
	if(next_declaration_ != nullptr)
		next_declaration_->countDeclarations(declaration_count);

	if(next_list_declaration_ != nullptr)
		next_list_declaration_->countDeclarations(declaration_count);

	++declaration_count;
}

std::string IdentifierDeclaration::getId() const
{
	return id_;
}


// Array

ArrayDeclaration::ArrayDeclaration(Declaration *declarator, ExpressionPtr initializer, const int &size)
	: Declaration(initializer), size_(size), declarator_(declarator)
{}

void ArrayDeclaration::print() const
{
	if(next_declaration_ != nullptr)
		next_declaration_->print();
	if(next_list_declaration_ != nullptr)
		next_list_declaration_->print();
    
	printf("Array Declaration\n");
	declarator_->print();
}

void ArrayDeclaration::printIR() const{}

Bindings ArrayDeclaration::printAsm(Bindings bindings, int &label_count) const
{
	if(next_declaration_ != nullptr)
		bindings = next_declaration_->printAsm(bindings, label_count);
	if(next_list_declaration_ != nullptr)
		bindings = next_list_declaration_->printAsm(bindings, label_count);
	bindings = declarator_->printAsm(bindings, label_count);
    
	return bindings;
}

Bindings ArrayDeclaration::localAsm(Bindings bindings, int &label_count) const
{
	if(next_declaration_ != nullptr)
		bindings = next_declaration_->localAsm(bindings, label_count);
	if(next_list_declaration_ != nullptr)
		bindings = next_list_declaration_->localAsm(bindings, label_count);

	if(getId() != "")
	{
		int stack_position = bindings.currentStackPosition();
		std::shared_ptr<ArrayDeclaration> array_declaration(
			std::dynamic_pointer_cast<ArrayDeclaration>(declarator_));
		std::vector<int> array_sizes = { size_ };
		while(array_declaration != nullptr)
		{
			array_sizes.push_back(array_declaration->getSize());
			array_declaration = std::dynamic_pointer_cast<ArrayDeclaration>
				(array_declaration->getNextArrayDeclaration());
		}
		//array_sizes是数组，用来数组的维数和大小
		std::shared_ptr<Initializer> initializer;
		if(initializer_ != nullptr)
		{
			initializer = std::static_pointer_cast<Initializer>(initializer_);
			initializer->printInitializerAsm(bindings, label_count, array_sizes.size()-1, array_sizes, type_->type());
		}
		else
		{
			int sum = 1;
			std::for_each(array_sizes.begin(), array_sizes.end(), [&] (int n) {
					sum *= n;
				});
			sum *= getType()->getSize();
			bindings.increaseStackPosition(sum);
		}
		
		std::reverse(array_sizes.begin(), array_sizes.end());
		bindings.insertBinding(getId(), type_, stack_position, array_sizes);
	}
    
	return bindings;
}

void ArrayDeclaration::countDeclarations(int &declaration_count) const
{
	if(next_declaration_ != nullptr)
		next_declaration_->countDeclarations(declaration_count);
	if(next_list_declaration_ != nullptr)
		next_list_declaration_->countDeclarations(declaration_count);

	std::shared_ptr<ArrayDeclaration> array_declaration(
		std::dynamic_pointer_cast<ArrayDeclaration>(declarator_));
	int size = size_;
	while(array_declaration != nullptr)
	{
		size *= array_declaration->getSize();
		array_declaration = std::dynamic_pointer_cast<ArrayDeclaration>(
			array_declaration->getNextArrayDeclaration());
	}

	declaration_count += size;
}

std::string ArrayDeclaration::getId() const
{
	return declarator_->getId();
}

int ArrayDeclaration::getSize() const
{
	return size_;
}

DeclarationPtr ArrayDeclaration::getNextArrayDeclaration() const
{
	return declarator_;
}
