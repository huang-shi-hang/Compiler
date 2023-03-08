#ifndef DECLARATION_HPP
#define DECLARATION_HPP

#include "node.hpp"
#include "type.hpp"
#include "expression.hpp"

#include <memory>

class Declaration;
typedef std::shared_ptr<Declaration> DeclarationPtr;

class Declaration : public Node {
protected:
	DeclarationPtr next_declaration_;//指向下一个
	DeclarationPtr next_list_declaration_; //指向下一个声明表   
	ExpressionPtr initializer_;//初始化语句 
	TypePtr type_;//类型
	bool extern_declaration_;   
public:
	Declaration(Expression *initializer);
	Declaration(ExpressionPtr initializer);
    
	virtual void print() const = 0;
	virtual void printIR() const = 0;
	virtual Bindings printAsm(Bindings bindings, int &label_count) const = 0;
	
	//存储此声明语句
	virtual Bindings localAsm(Bindings bindings, int &label_count) const = 0;
	//计算到现在为止一共有多少个声明
	virtual void countDeclarations(int &declaration_count) const = 0;
	
	virtual std::string getId() const = 0;

	void linkDeclaration(Declaration *next_declaration);    
	void linkListDeclaration(Declaration *next_list_declaration);

	void setType(TypePtr type);
	void setInitializer(Expression *initializer);
	void setExternDeclaration(bool is_extern);

	DeclarationPtr getNext() const;
	DeclarationPtr getNextListItem() const;
	ExpressionPtr getInitializer() const;
	TypePtr getType() const;
};

class IdentifierDeclaration : public Declaration {
private:
	std::string id_;
public:
	IdentifierDeclaration(const std::string &id="", Expression *initializer=nullptr);
	IdentifierDeclaration(const std::string &id, ExpressionPtr initializer);

	virtual void print() const;
	virtual void printIR() const;
	virtual Bindings printAsm(Bindings bindings, int &label_count) const;
	virtual Bindings localAsm(Bindings bindings, int &label_count) const;
	virtual void countDeclarations(int &declaration_count) const;
	virtual std::string getId() const;
};

class ArrayDeclaration : public Declaration
{
private:
	int size_;
	DeclarationPtr declarator_;
public:
	ArrayDeclaration(Declaration *declarator, ExpressionPtr initializer, const int &size=0);

	virtual void print() const;
	virtual void printIR() const;
	virtual Bindings printAsm(Bindings bindings, int &label_count) const;
	virtual Bindings localAsm(Bindings bindings, int &label_count) const;
	virtual void countDeclarations(int &declaration_count) const;
	virtual std::string getId() const;

	int getSize() const;
	DeclarationPtr getNextArrayDeclaration() const;
};

#endif
