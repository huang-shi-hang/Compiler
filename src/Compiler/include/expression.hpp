#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

#include "bindings.hpp"
#include "node.hpp"
#include "type.hpp"

#include <cstdint>
#include <memory>
#include <string>

class Expression;
typedef std::shared_ptr<Expression> ExpressionPtr;

class Expression : public Node
{
protected:
	ExpressionPtr next_expression_;//指向下一个表达式
    
public:
	virtual Bindings printAsm(Bindings bindings, int& label_count) const = 0;
    //数组
	virtual int constantFold() const;
	
	virtual void print() const;
	virtual void printIR() const;

	//计算参数个数
	virtual void countArguments(int &argument_count) const;

	//确定表达式的深度
	virtual void expressionDepth(int &depth_count) const;
	//返回id
	virtual std::string id() const;
	//表达式类型
	virtual TypePtr getType(const Bindings &bindings) const = 0;
    //链接到下一个语句
	void linkExpression(Expression* next_expression);
	//找到下一个语句
	ExpressionPtr nextExpression() const;
};

class OperationExpression : public Expression
{
protected:
	ExpressionPtr lhs_;
	ExpressionPtr rhs_;
public:
	OperationExpression(Expression *lhs, Expression *rhs);
	OperationExpression(ExpressionPtr lhs, Expression *rhs);

	virtual Bindings printAsm(Bindings bindings, int &label_count) const = 0;
    
	virtual int constantFold() const;
	virtual void expressionDepth(int &depth_count) const;
	virtual TypePtr getType(const Bindings &bindings) const;

	ExpressionPtr getLhs() const;
	ExpressionPtr getRhs() const;
    
	void evaluateExpression(Bindings bindings, int &label_count) const;
};

class UnaryExpression : public Expression
{
public:
	virtual void expressionDepth(int &depth_count) const;
	virtual void pointerPosition(Bindings bindings) const;
	virtual void stackPosition(Bindings bindings, int &depth_count) const;
};

class PostfixArrayElement : public UnaryExpression
{
private:
	ExpressionPtr postfix_expression_;
	ExpressionPtr index_expression_;
    
public:
	PostfixArrayElement(Expression *postfix_expression, Expression *index_expression);

	virtual Bindings printAsm(Bindings bindings, int &label_count) const;
	virtual void expressionDepth(int &depth_count) const;
	virtual void stackPosition(Bindings bindings, int &depth_count) const;
	virtual TypePtr getType(const Bindings &bindings) const;
	virtual std::string id() const;

	ExpressionPtr getIndex() const;
	ExpressionPtr getPostfix() const;    
};

class PostfixFunctionCall : public UnaryExpression
{
private:
	ExpressionPtr postfix_expression_;
	ExpressionPtr argument_expression_list_;
    
public:
	PostfixFunctionCall(Expression *argument_expression_list = nullptr);

	virtual Bindings printAsm(Bindings bindings, int &label_count) const;
	virtual void countArguments(int &argument_count) const;
	virtual void expressionDepth(int &depth_count) const;
	virtual TypePtr getType(const Bindings &bindings) const;
    
	void setPostfixExpression(Expression *postfix_expression);
};

class PostfixPostIncDecExpression : public UnaryExpression
{
private:
	std::string operator_;
	ExpressionPtr postfix_expression_;

public:
	PostfixPostIncDecExpression(const std::string &_operator, Expression *postfix_expression);

	virtual Bindings printAsm(Bindings bindings, int &label_count) const;
	virtual TypePtr getType(const Bindings &bindings) const;
    
};

class UnaryPreIncDecExpression : public UnaryExpression
{
private:
	std::string operator_;
	ExpressionPtr unary_expression_;
    
public:
	UnaryPreIncDecExpression(const std::string &_operator, Expression *unary_expression);

	virtual Bindings printAsm(Bindings bindings, int &label_count) const;
	virtual TypePtr getType(const Bindings &bindings) const;
};

class OperatorUnaryExpression : public UnaryExpression
{
private:
	std::string operator_;
	ExpressionPtr cast_expression_;

public:
	OperatorUnaryExpression(const std::string &_operator, Expression *cast_expression);

	virtual Bindings printAsm(Bindings bindings, int &label_count) const;
	virtual void stackPosition(Bindings bindings, int &depth_count) const;
	virtual TypePtr getType(const Bindings &bindings) const;
	std::string getOperator() const;
};


class CastExpression : public Expression
{
private:
	TypePtr type_;
	ExpressionPtr expression_;

public:
	CastExpression(Type *type, Expression *expression);

	virtual Bindings printAsm(Bindings bindings, int &label_count) const;
	virtual void expressionDepth(int &depth_count) const;
	virtual TypePtr getType(const Bindings &bindings) const;
};

class AdditiveExpression : public OperationExpression
{
private:
	std::string operator_;

public:
	AdditiveExpression(Expression *lhs, const std::string &_operator, Expression *rhs);

	virtual Bindings printAsm(Bindings bindings, int &label_count) const;
	virtual int constantFold() const;
};

class MultiplicativeExpression : public OperationExpression
{
private:
	std::string operator_;

public:
	MultiplicativeExpression(Expression *lhs, const std::string &_operator, Expression *rhs);

	virtual Bindings printAsm(Bindings bindings, int &label_count) const;
	virtual int constantFold() const;
};

class ShiftExpression : public OperationExpression
{
private:
	std::string operator_;
public:
	ShiftExpression(Expression *lhs, const std::string &_operator, Expression *rhs);

	virtual Bindings printAsm(Bindings bindings, int &label_count) const;
	virtual int constantFold() const;
};

class RelationalExpression : public OperationExpression
{
private:
	std::string operator_;
public:
	RelationalExpression(Expression *lhs, const std::string &_operator, Expression *rhs);

	virtual Bindings printAsm(Bindings bindings, int &label_count) const;
	virtual int constantFold() const;
};

class EqualityExpression : public OperationExpression
{
private:
	std::string operator_;
public:
	EqualityExpression(Expression *lhs, const std::string &_operator, Expression *rhs);

	virtual Bindings printAsm(Bindings bindings, int &label_count) const;
	virtual int constantFold() const;
};

class AndExpression : public OperationExpression
{
public:
	AndExpression(Expression *lhs, Expression *rhs);

	virtual Bindings printAsm(Bindings bindings, int &label_count) const;
	virtual int constantFold() const;
};

class ExclusiveOrExpression : public OperationExpression
{
public:
	ExclusiveOrExpression(Expression *lhs, Expression *rhs);

	virtual Bindings printAsm(Bindings bindings, int &label_count) const;
	virtual int constantFold() const;
};

class InclusiveOrExpression : public OperationExpression
{
public:
	InclusiveOrExpression(Expression *lhs, Expression *rhs);

	virtual Bindings printAsm(Bindings bindings, int &label_count) const;
	virtual int constantFold() const; 
};

class LogicalAndExpression : public OperationExpression
{
public:
	LogicalAndExpression(Expression *lhs, Expression *rhs);

	virtual Bindings printAsm(Bindings bindings, int &label_count) const;
	virtual int constantFold() const;
};

class LogicalOrExpression : public OperationExpression
{
public:
	LogicalOrExpression(Expression *lhs, Expression *rhs);

	virtual Bindings printAsm(Bindings bindings, int &label_count) const;
	virtual int constantFold() const;    
};

class ConditionalExpression : public Expression
{
private:
	ExpressionPtr logical_or_;
	ExpressionPtr expression_;
	ExpressionPtr conditional_expression_;

public:
	ConditionalExpression(Expression *logical_or, Expression *expression,
	                      Expression *conditional_expression);
    
	virtual Bindings printAsm(Bindings bindings, int &label_count) const;
	virtual TypePtr getType(const Bindings &bindings) const;
};

class AssignmentExpression : public OperationExpression
{
public:
	AssignmentExpression(Expression *lhs, Expression *rhs);
	AssignmentExpression(ExpressionPtr lhs, Expression *rhs);

	virtual Bindings printAsm(Bindings bindings, int &label_count) const;
};

class Identifier : public UnaryExpression
{
private:
	std::string id_;
public:
	Identifier(const std::string &id);

	virtual Bindings printAsm(Bindings bindings, int &label_count) const;
	virtual void pointerPosition(Bindings bindings) const;
	virtual void stackPosition(Bindings bindings, int &depth_count) const;
	virtual std::string id() const;
	virtual TypePtr getType(const Bindings &bindings) const;
};

class StringLiteral : public UnaryExpression
{
private:
	std::string string_content_;
public:
	StringLiteral(const std::string &string_content);

	virtual Bindings printAsm(Bindings bindings, int &label_count) const;
	virtual TypePtr getType(const Bindings &bindings) const;
};

class Constant : public UnaryExpression
{
private:
	int32_t constant_;
public:
	Constant(const int32_t &constant);

	virtual Bindings printAsm(Bindings bindings, int &label_count) const;
	virtual int constantFold() const;
	virtual TypePtr getType(const Bindings &bindings) const;
};

class Initializer : public Expression
{
private:
	ExpressionPtr next_initializer_;
public:
	Initializer(Expression *next_initializer);

	virtual Bindings printAsm(Bindings bindings, int &label_count) const;
	virtual TypePtr getType(const Bindings &bindings) const;

	void printInitializerAsm(Bindings &bindings, int &label_count, int position, const std::vector<int> &iteration_vector, const TypePtr &type) const;
	ExpressionPtr getNext() const;
};

#endif
