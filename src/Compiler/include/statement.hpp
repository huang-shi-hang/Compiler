#ifndef STATEMENT_HPP
#define STATEMENT_HPP

#include "bindings.hpp"
#include "declaration.hpp"
#include "expression.hpp"
#include "node.hpp"

#include <memory>

class Statement;

typedef std::shared_ptr<Statement> StatementPtr;


class Statement : public Node
{
protected:
	StatementPtr next_statement_;
    
public:
	Statement(Statement *statement = nullptr);

	virtual void print() const = 0;
	virtual void printIR() const = 0;
	virtual Bindings printAsm(Bindings bindings, int &label_count) const = 0;
	
	//计算变量个数
	virtual void countVariables(int &var_count) const = 0;
	//计算参数个数
	virtual void countArguments(int &argument_count) const = 0;
	virtual void countExpressionDepth(int &depth_count) const = 0;

	virtual int constantFold() const;
	virtual ExpressionPtr getExpression() const;
	virtual bool isDefault() const;
    
	void linkStatement(Statement *next);
	StatementPtr getNext() const;
};

class LabelStatement : public Statement
{
private:
	std::string label_;
	StatementPtr statement_;

public:
	LabelStatement(const std::string &label, Statement *statement);

	virtual void print() const;
	virtual void printIR() const;
	virtual Bindings printAsm(Bindings bindings, int &label_count) const;

	virtual void countVariables(int &var_count) const;
	virtual void countArguments(int &argument_count) const;
	virtual void countExpressionDepth(int &depth_count) const;
};

class CaseStatement : public Statement
{
private:
	ExpressionPtr constant_expression_;
	StatementPtr statement_;
	bool default_;

public:
	CaseStatement(Statement *statement, Expression *constant_expression_ = nullptr, const bool &_default = false);

	virtual void print() const;
	virtual void printIR() const;
	virtual Bindings printAsm(Bindings bindings, int &label_count) const;

	virtual void countVariables(int &var_count) const;
	virtual void countArguments(int &argument_count) const;
	virtual void countExpressionDepth(int &depth_count) const;
	virtual int constantFold() const;
	virtual ExpressionPtr getExpression() const;
	virtual bool isDefault() const;
};

class CompoundStatement : public Statement
{
protected:
	DeclarationPtr declaration_;
	StatementPtr statement_;
    
public:
	CompoundStatement(Declaration *declaration = nullptr, Statement *statement = nullptr);
	CompoundStatement(Statement *statement);

	virtual void print() const;
	virtual void printIR() const;
	virtual Bindings printAsm(Bindings bindings, int &label_count) const;

	virtual void countVariables(int &var_count) const;
	virtual void countArguments(int &argument_count) const;
	virtual void countExpressionDepth(int &depth_count) const;

	StatementPtr getStatementList() const;
};

class IfElseStatement : public Statement
{
private:
	ExpressionPtr condition_;
	StatementPtr if_;
	StatementPtr else_;
public:
	IfElseStatement(Expression *condition, Statement *_if, Statement *_else = nullptr);

	virtual void print() const;
	virtual void printIR() const;
	virtual Bindings printAsm(Bindings bindings, int &label_count) const;

	virtual void countVariables(int &var_count) const;
	virtual void countArguments(int &argument_count) const;
	virtual void countExpressionDepth(int &depth_count) const;
};

class SwitchStatement : public Statement
{
private:
	ExpressionPtr condition_;
	StatementPtr statement_;
public:
	SwitchStatement(Expression *condition, Statement *statement);
	virtual void print() const;
	virtual void printIR() const;
	virtual Bindings printAsm(Bindings bindings, int &label_count) const;

	virtual void countVariables(int &var_count) const;
	virtual void countArguments(int &argument_count) const;
	virtual void countExpressionDepth(int &depth_count) const;
};

class ExpressionStatement : public Statement
{
protected:
	ExpressionPtr expression_;
public:
	ExpressionStatement(Expression *expression = nullptr);

	virtual void print() const;
	virtual void printIR() const;
	virtual Bindings printAsm(Bindings bindings, int &label_count) const;

	virtual void countVariables(int &var_count) const;
	virtual void countArguments(int &argument_count) const;
	virtual void countExpressionDepth(int &depth_count) const;    
};

class JumpStatement : public Statement
{
public:
	virtual Bindings printAsm(Bindings bindings, int &label_count) const = 0;
    
	virtual void print() const;
	virtual void printIR() const;

	virtual void countVariables(int &var_count) const;
	virtual void countArguments(int &argument_count) const;
	virtual void countExpressionDepth(int &depth_count) const;
};

class ReturnStatement : public JumpStatement
{
private:
	ExpressionPtr expression_;
public:
	ReturnStatement(Expression *expression = nullptr);

	virtual Bindings printAsm(Bindings bindings, int &label_count) const;

	virtual void countVariables(int &var_count) const;
	virtual void countArguments(int &argument_count) const;
	virtual void countExpressionDepth(int &depth_count) const;    
};

class BreakStatement : public JumpStatement
{
public:
	BreakStatement();

	virtual Bindings printAsm(Bindings bindings, int &) const;
};

class ContinueStatement : public JumpStatement
{
public:
	ContinueStatement();

	virtual Bindings printAsm(Bindings bindings, int &) const;
};

class GotoStatement : public JumpStatement
{
private:
	std::string label_;
public:
	GotoStatement(const std::string &label);

	virtual Bindings printAsm(Bindings bindings, int &) const;
};

class IterationStatement : public Statement
{
protected:
	ExpressionPtr condition_;
	StatementPtr statement_;
public:
	IterationStatement(Expression *condition, Statement *statement);

	virtual void print() const;
	virtual void printIR() const;
	virtual Bindings printAsm(Bindings bindings, int &label_count) const = 0;

	virtual void countVariables(int &var_count) const;
	virtual void countArguments(int &argument_count) const;
	virtual void countExpressionDepth(int &depth_count) const;
};

class WhileLoop : public IterationStatement
{
private:
	bool is_while_;
public:
	WhileLoop(Expression *condition, Statement *statement, const bool &is_while = true);

	virtual Bindings printAsm(Bindings bindings, int &label_count) const;
};

class ForLoop : public IterationStatement
{
private:
	ExpressionPtr initializer_;
	ExpressionPtr incrementer_;
public:
	ForLoop(Expression *initializer, Expression *condition, Expression *incrementer, Statement *statement);

	virtual Bindings printAsm(Bindings bindings, int &label_count) const;
};

#endif
