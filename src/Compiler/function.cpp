#include "function.hpp"

#include <cstdio>
#include <vector>


// Function

Function::Function(const std::string& id, Statement* statement, DeclarationPtr parameter_list)
	: id_(id), statement_(statement), parameter_list_(parameter_list)
{}

void Function::print() const
{
	printf("%s\n", id_.c_str());
    
	if(parameter_list_ != nullptr)
		parameter_list_->print();
    
	if(statement_ != nullptr)
		statement_->print();
}

void Function::printIR() const{}

Bindings Function::printAsm(Bindings bindings, int& label_count) const
{
	Bindings original_bindings = bindings;
	//计算变量数量
	int variable_count = 0;
	if(statement_ != nullptr)
		statement_->countVariables(variable_count);

	int max_argument_count = 0;
	// 计算参数数量
	statement_->countArguments(max_argument_count);

	int max_depth = 0;
	statement_->countExpressionDepth(max_depth);

	if(max_argument_count < 6)
		max_argument_count = 6;

	int parameter_count = 0;
	countParameters(parameter_count);
    
	int memory_needed = 4*(variable_count+max_argument_count+max_depth+2);
    
	printf("\t.text\n\t.align\t2\n\t.globl\t%s\n\t.type\t%s,@function\n%s:\n\taddi\tsp,sp,-%d\n\tsw\t",
	       id_.c_str(), id_.c_str(),id_.c_str(), memory_needed);
	printf("ra,%d(sp)\n\tsw\tfp,%d(sp)\n\tmv\tfp,sp\n", memory_needed-4, memory_needed-8);

	bindings.setStackPosition(max_argument_count*4);
	bindings.setExpressionStackPosition((max_argument_count+variable_count)*4);
	bindings.setFunName(id_.c_str());
	//打印参数
	printParameterAsm(bindings, memory_needed);
    
	//打印语句的汇编
	statement_->printAsm(bindings, label_count);
    
	printf("\tmv\ta0,zero\n%s_0:\n\tmv\tsp,fp\n\tlw\tra,%d(sp)\n", id_.c_str(),memory_needed-4);
	printf("\tlw\tfp,%d", memory_needed-8);
	printf("(sp)\n\taddi\tsp,sp,%d\n\tjr\tra\n\tnop\n", memory_needed);

	auto string_lit_iterator = bindings.getStringLiteralIterator();
	if(string_lit_iterator.first != string_lit_iterator.second)
	{
		printf("\n\t.rodata\n\t.align\t2\n");
		for(auto itr = string_lit_iterator.first; itr != string_lit_iterator.second; ++itr)
		{
			printf("x%d_string:\n\t.string\t", int(itr-string_lit_iterator.first));
			printf("\"%s\\000\"", (*itr).c_str());
		}
	}

	return original_bindings;
}

void Function::printParameterAsm(Bindings& bindings, int& frame_offset) const
{
	std::vector<DeclarationPtr> parameter_vector;
	DeclarationPtr parameter_list = parameter_list_;

	while(parameter_list != nullptr)
	{
		parameter_vector.push_back(parameter_list);
		parameter_list = parameter_list->getNext();
	}

	for(auto itr = parameter_vector.rbegin(); itr != parameter_vector.rend(); ++itr)
	{
		int i = itr-parameter_vector.rbegin();
		bindings.insertBinding((*itr)->getId(), (*itr)->getType(), i*4+frame_offset);
		TypePtr parameter_type = (*itr)->getType();
		if(i < 6)
		{    
			parameter_type->store(12+i, 4*i+frame_offset);
		}
		else
		{
			if(std::dynamic_pointer_cast<TypeContainer>(parameter_type) != nullptr)
			{
				if(std::dynamic_pointer_cast<Char>(parameter_type->type()) != nullptr)
				{    
					printf("\tlw\ta0,%d(fp)\n", i*4+frame_offset);
					printf("\tsb\ta0,%d(fp)\n", i*4+frame_offset);
				}
				else if(std::dynamic_pointer_cast<Short>(parameter_type->type()) != nullptr)
				{
					printf("\tlw\ta0,%d(fp)\n", i*4+frame_offset);
					printf("\tsh\ta0,%d(fp)\n", i*4+frame_offset);
				}
			}
		}
	}
}

void Function::countParameters(int& parameter_count) const
{
	DeclarationPtr parameter_list = parameter_list_;

	while(parameter_list != nullptr)
	{
		parameter_count++;
		parameter_list = parameter_list->getNext();
	}
}
