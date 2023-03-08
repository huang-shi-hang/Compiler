#include "expression.hpp"

#include <algorithm>
#include <cstdio>
#include <exception>
#include <vector>
#include <stdexcept>

// Expression definition

int Expression::constantFold() const
{
	throw std::runtime_error("Error : Cannot constant fold this expression");
}

void Expression::print() const
{
	if(next_expression_ != nullptr)
		next_expression_->print();

	printf("Expression\n");
}

void Expression::printIR() const{}

void Expression::countArguments(int &) const
{
}

void Expression::expressionDepth(int &depth_count) const
{
	if(next_expression_ != nullptr)
		next_expression_->expressionDepth(depth_count);
}

std::string Expression::id() const
{
	return "";
}

TypePtr Expression::getType(const Bindings &) const
{
	return std::make_shared<Int>();
}


void Expression::linkExpression(Expression *next_expression)
{
	ExpressionPtr expression_ptr(next_expression);
	next_expression_ = expression_ptr;
}

ExpressionPtr Expression::nextExpression() const
{
	return next_expression_;
}


// OperationExpression

OperationExpression::OperationExpression(Expression *lhs, Expression *rhs)
	: lhs_(lhs), rhs_(rhs)
{}

OperationExpression::OperationExpression(ExpressionPtr lhs, Expression *rhs)
	: lhs_(lhs), rhs_(rhs)
{}

int OperationExpression::constantFold() const
{
	throw std::runtime_error("Error : Cannot constant fold expression");
}

void OperationExpression::expressionDepth(int &depth_count) const
{
	int lhs_depth_count = depth_count;
	int rhs_depth_count = depth_count+1;

	lhs_->expressionDepth(lhs_depth_count);
	rhs_->expressionDepth(rhs_depth_count);

	if(lhs_depth_count > rhs_depth_count)
		depth_count = lhs_depth_count;
	else
		depth_count = rhs_depth_count;
}//确定运算表达式的深度

TypePtr OperationExpression::getType(const Bindings &bindings) const
{
	return lhs_->getType(bindings);
}

ExpressionPtr OperationExpression::getLhs() const
{
	return lhs_;
}

ExpressionPtr OperationExpression::getRhs() const
{
	return rhs_;
}

void OperationExpression::evaluateExpression(Bindings bindings, int &label_count) const
{
	//打印左式
	lhs_->printAsm(bindings, label_count);

	int lhs_stack_position = bindings.currentExpressionStackPosition();

	bindings.nextExpressionStackPosition();
	rhs_->printAsm(bindings, label_count);

	int rhs_stack_position = bindings.currentExpressionStackPosition();

	printf("\tlw\ta0,%d(fp)\n", lhs_stack_position);
	printf("\tlw\ta1,%d(fp)\n", rhs_stack_position);
}


// Unary

void UnaryExpression::expressionDepth(int &depth_count) const
{
	++depth_count;
}

void UnaryExpression::pointerPosition(Bindings bindings) const
{
	throw std::runtime_error("Error : Cannot get pointer position");
}

void UnaryExpression::stackPosition(Bindings, int &) const
{
	throw std::runtime_error("Error : Cannot get stack position of expression");
}


// PostfixArrayElement

PostfixArrayElement::PostfixArrayElement(Expression *postfix_expression, Expression *index_expression)
	: postfix_expression_(postfix_expression), index_expression_(index_expression)
{}

Bindings PostfixArrayElement::printAsm(Bindings bindings, int &label_count) const
{
	stackPosition(bindings, label_count);
    
	TypePtr type_ptr = postfix_expression_->getType(bindings);
	type_ptr->load();
	printf("\tsw\ta0,%d(fp)\n", bindings.currentExpressionStackPosition());
	return bindings;
}

void PostfixArrayElement::stackPosition(Bindings bindings, int &label_count) const
{
	std::shared_ptr<PostfixArrayElement> array_element
		(std::dynamic_pointer_cast<PostfixArrayElement>(postfix_expression_));
    
	std::vector<int> array_sizes = bindings.getArraySizes(postfix_expression_->id());
    
	int counter = 1;
	printf("\tmv\tt1,zero\n");
	index_expression_->printAsm(bindings, label_count);
	printf("\tadd\tt1,t1,a0\n"); 
	while(array_element != nullptr)
	{
		array_element->getIndex()->printAsm(bindings, label_count);
		int sum = 0;
		std::for_each(array_sizes.end()-counter, array_sizes.end(), [&] (int n) {
				sum += n;
			});
		printf("\tli\ta1,%d\n",sum);
		printf("\tmul\ta0,a0,a1\n");
		printf("\tadd\tt1,t1,a0\n");
		array_element = std::dynamic_pointer_cast<PostfixArrayElement>(array_element->getPostfix());
		counter++;
	}
	auto identifier_expression = std::make_shared<Identifier>(postfix_expression_->id());
	identifier_expression->stackPosition(bindings, label_count);
	printf("\tslli\tt1,t1,%d\n", postfix_expression_->getType(bindings)->getSize()/2);
	printf("\tadd\tt0,t0,t1\n");
}

void PostfixArrayElement::expressionDepth(int &depth_count) const
{
	if(nextExpression() != nullptr)
		nextExpression()->expressionDepth(depth_count);

	if(index_expression_ != nullptr)
		index_expression_->expressionDepth(depth_count);
}

TypePtr PostfixArrayElement::getType(const Bindings &bindings) const
{
	return postfix_expression_->getType(bindings);
}

std::string PostfixArrayElement::id() const
{
	return postfix_expression_->id();
}

ExpressionPtr PostfixArrayElement::getIndex() const
{
	if(index_expression_ == nullptr)
		throw std::runtime_error("Error : No index expression found");
	return index_expression_;
}

ExpressionPtr PostfixArrayElement::getPostfix() const
{
	if(postfix_expression_ == nullptr)
		throw std::runtime_error("Error : No index expression postfix");
	return postfix_expression_;
}


// PostfixFunctionCall

PostfixFunctionCall::PostfixFunctionCall(Expression *argument_expression_list)
	: argument_expression_list_(argument_expression_list)
{}

Bindings PostfixFunctionCall::printAsm(Bindings bindings, int &label_count) const
{
	std::vector<ExpressionPtr> argument_vector;
	ExpressionPtr current_argument = argument_expression_list_;
	int argument_counter = 0;
	int start_register = 10;
	if((postfix_expression_->id() != "getint") && (postfix_expression_->id() != "getch")
	&&(postfix_expression_->id() != "getarray")&&(postfix_expression_->id() != "putint")
	&&(postfix_expression_->id() != "putch")&&(postfix_expression_->id() != "starttime")
	&&(postfix_expression_->id() != "stoptime"))
		start_register = 12;
	while(current_argument != nullptr)
	{
		argument_vector.push_back(current_argument);
		current_argument = current_argument->nextExpression();
	}

	for(auto itr = argument_vector.rbegin(); itr != argument_vector.rend(); ++itr)
	{
		(*itr)->printAsm(bindings, label_count);

		if(argument_counter < 6)
			printf("\tmv\tx%d,a0\n", start_register+argument_counter);
		else
			(*itr)->getType(bindings)->store(4*argument_counter);
		argument_counter++;
	}
	printf("\tcall\t%s\n\tnop\n\tsw\ta0,%d(fp)\n",
	       postfix_expression_->id().c_str(), bindings.currentExpressionStackPosition());
	return bindings;
}

void PostfixFunctionCall::countArguments(int &argument_count) const
{
	ExpressionPtr current_argument = argument_expression_list_;

	argument_count = 0;
    
	while(current_argument != nullptr)
	{
		argument_count++;
		current_argument = current_argument->nextExpression();
	}
}

void PostfixFunctionCall::setPostfixExpression(Expression *postfix_expression)
{
	ExpressionPtr expression_ptr(postfix_expression);
	postfix_expression_ = expression_ptr;
}

void PostfixFunctionCall::expressionDepth(int &depth_count) const
{
	if(argument_expression_list_ != nullptr)
		argument_expression_list_->expressionDepth(depth_count);
}

TypePtr PostfixFunctionCall::getType(const Bindings &) const
{
	return std::make_shared<Int>();
}


// PostfixPostIncDecExpression

PostfixPostIncDecExpression::PostfixPostIncDecExpression(const std::string &_operator, Expression *postfix_expression)
	: operator_(_operator), postfix_expression_(postfix_expression)
{}

Bindings PostfixPostIncDecExpression::printAsm(Bindings bindings, int &label_count) const
{
	postfix_expression_->printAsm(bindings, label_count);
	if(operator_ == "++")
		printf("\taddi\ta1,a0,1\n");
	else if(operator_ == "--")
		printf("\taddi\ta1,a0,4294967295\n");
	else
		throw std::runtime_error("Error : '"+operator_+"' not recognized");

	std::shared_ptr<UnaryExpression> unary_expression;
	unary_expression = std::static_pointer_cast<UnaryExpression>(postfix_expression_);

	printf("\tsw\ta0,%d(fp)\n", bindings.currentExpressionStackPosition());
	unary_expression->stackPosition(bindings, label_count);
	TypePtr tmp_ptr = postfix_expression_->getType(bindings);
	if(std::dynamic_pointer_cast<Char>(tmp_ptr))
	{	
		printf("\tsb\ta1,0(t0)\n");
	}
	else if(std::dynamic_pointer_cast<Short>(tmp_ptr))
	{
		printf("\tsh\ta1,0(t0)\n");
	}
	else
	{
		printf("\tsw\ta1,0(t0)\n");
	}
    
	return bindings;
}

TypePtr PostfixPostIncDecExpression::getType(const Bindings &bindings) const
{
	return postfix_expression_->getType(bindings);
}


//UnaryPreIncDecExpression

UnaryPreIncDecExpression::UnaryPreIncDecExpression(const std::string &_operator, Expression *unary_expression)
	: operator_(_operator), unary_expression_(unary_expression)
{}

Bindings UnaryPreIncDecExpression::printAsm(Bindings bindings, int &label_count) const
{
	unary_expression_->printAsm(bindings, label_count);
	if(operator_ == "++")
		printf("\taddi\ta0,a0,1\n");
	else if(operator_ == "--")
		printf("\taddi\ta0,a0,4294967295\n");
	else
		throw std::runtime_error("Error : '"+operator_+"' not recognized");

	std::shared_ptr<UnaryExpression> unary_expression;
	unary_expression = std::static_pointer_cast<UnaryExpression>(unary_expression_);

	printf("\tsw\ta0,%d(fp)\n", bindings.currentExpressionStackPosition());
	unary_expression->stackPosition(bindings, label_count);
	unary_expression_->getType(bindings)->store();
	return bindings;
}

TypePtr UnaryPreIncDecExpression::getType(const Bindings &bindings) const
{
	return unary_expression_->getType(bindings);
}


// Operatorunarydefinition

OperatorUnaryExpression::OperatorUnaryExpression(const std::string &_operator, Expression *cast_expression)
	: operator_(_operator), cast_expression_(cast_expression)
{}

Bindings OperatorUnaryExpression::printAsm(Bindings bindings, int &label_count) const
{

	if(operator_ == "!")
	{
		cast_expression_->printAsm(bindings, label_count);	
		// printf("\tsltiu\ta0,a0,1\n\tandi\ta0,a0,0x0000ffff\n");
		printf("\tsltiu\ta0,a0,1\n");
	}
	else if(operator_ == "~")
	{
		cast_expression_->printAsm(bindings, label_count);	
		printf("\tnot\ta0,a0\n");
	}
	else if(operator_ == "&")
	{
		std::shared_ptr<UnaryExpression> unary_expression;
		unary_expression = std::static_pointer_cast<UnaryExpression>(cast_expression_);
		unary_expression->stackPosition(bindings, label_count);
		printf("\tmv\ta0,t0\n");
	}
	else if(operator_ == "-")
	{
		cast_expression_->printAsm(bindings, label_count);	
		printf("\tsub\ta0,zero,a0\n");
	}
	else if(operator_ == "*")
	{
		cast_expression_->printAsm(bindings, label_count);	
		printf("\tlw\ta0,0(a0)\n");
	}

	printf("\tsw\ta0,%d(fp)\n", bindings.currentExpressionStackPosition());

	return bindings;
}

void OperatorUnaryExpression::stackPosition(Bindings bindings, int &label_count) const
{
	if(operator_ == "*")
	{	
		std::shared_ptr<UnaryExpression> unary_expression;
		unary_expression = std::static_pointer_cast<UnaryExpression>(cast_expression_);
		unary_expression->stackPosition(bindings, label_count);
	}
}

TypePtr OperatorUnaryExpression::getType(const Bindings &bindings) const
{
	return cast_expression_->getType(bindings);
}

std::string OperatorUnaryExpression::getOperator() const
{
	return operator_;
}


// CastExpression

CastExpression::CastExpression(Type *type, Expression *expression)
	: type_(type), expression_(expression)
{}

Bindings CastExpression::printAsm(Bindings bindings, int &label_count) const
{
	return bindings;
}

void CastExpression::expressionDepth(int &depth_count) const
{
	if(nextExpression() != nullptr)
		nextExpression()->expressionDepth(depth_count);

	expression_->expressionDepth(depth_count);
}

TypePtr CastExpression::getType(const Bindings &) const
{
	return type_;
}


// AdditiveExpression

AdditiveExpression::AdditiveExpression(Expression *lhs, const std::string &_operator, Expression *rhs)
	: OperationExpression(lhs, rhs), operator_(_operator)
{}

Bindings AdditiveExpression::printAsm(Bindings bindings, int &label_count) const
{
	evaluateExpression(bindings, label_count);
    
	if(operator_ == "+")
		printf("\tadd\ta0,a0,a1\n");
	else if(operator_ == "-")
		printf("\tsub\ta0,a0,a1\n");
	else
		throw std::runtime_error("Error : '"+operator_+"' not recognized");

	printf("\tsw\ta0,%d(fp)\n", bindings.currentExpressionStackPosition());

	return bindings;
}

int AdditiveExpression::constantFold() const
{
	if(operator_ == "+")
		return lhs_->constantFold()+rhs_->constantFold();
	return lhs_->constantFold()-rhs_->constantFold();
}


// MultiplicativeExpression


MultiplicativeExpression::MultiplicativeExpression(Expression *lhs, const std::string &_operator, Expression *rhs)
	: OperationExpression(lhs, rhs), operator_(_operator)
{}

Bindings MultiplicativeExpression::printAsm(Bindings bindings, int &label_count) const
{
	evaluateExpression(bindings, label_count);

	if(operator_ == "*")
	{
		printf("\tmul\ta0,a0,a1\n");	
	}
	else if(operator_ == "/")
	{
		printf("\tdiv\ta0,a0,a1\n");
	}
	else if(operator_ == "%")
	{
		printf("\trem\ta0,a0,a1\n");
	}
	else
	{
		throw std::runtime_error("Error : '"+operator_+"' not recognized");
	}
	printf("\tsw\ta0,%d(fp)\n", bindings.currentExpressionStackPosition());

	return bindings;
}

int MultiplicativeExpression::constantFold() const
{
	if(operator_ == "*")
		return lhs_->constantFold()*rhs_->constantFold();
	else if(operator_ == "/")
		return lhs_->constantFold()/rhs_->constantFold();
	return lhs_->constantFold()%rhs_->constantFold();
}


// ShiftExpression

ShiftExpression::ShiftExpression(Expression* lhs, const std::string &_operator, Expression *rhs)
	: OperationExpression(lhs, rhs), operator_(_operator)
{}

Bindings ShiftExpression::printAsm(Bindings bindings, int &label_count) const
{
	evaluateExpression(bindings, label_count);

	if(operator_ == "<<")
	{
		printf("\tsll\ta0,a0,a1\n");
	}
	else if(operator_ == ">>")
	{
		printf("\tsra\ta0,a0,a1\n");
	}
	else
	{
		throw std::runtime_error("Error : '"+operator_+"' not recognized");
	}

	printf("\tsw\ta0,%d(fp)\n", bindings.currentExpressionStackPosition());

	return bindings;
}

int ShiftExpression::constantFold() const
{
	if(operator_ == "<<")
		return lhs_->constantFold()<<rhs_->constantFold();
	return lhs_->constantFold()>>rhs_->constantFold();
}


// RelationalExpression

RelationalExpression::RelationalExpression(Expression* lhs, const std::string &_operator, Expression *rhs)
	: OperationExpression(lhs, rhs), operator_(_operator)
{}

Bindings RelationalExpression::printAsm(Bindings bindings, int &label_count) const
{
	evaluateExpression(bindings, label_count);

	if(operator_ == "<")
	{
		printf("\tslt\ta0,a0,a1\n");
	}
	else if(operator_ == ">")
	{
		printf("\tslt\ta0,a1,a0\n");
	}
	else if(operator_ == "<=")
	{
		printf("\tslt\ta0,a1,a0\n\txori\ta0,a0,0x1\n");
	}
	else if(operator_ == ">=")
	{
		printf("\tslt\ta0,a0,a1\n\txori\ta0,a0,0x1\n");
	}
	else
	{
		throw std::runtime_error("Error : '"+operator_+"' not recognized");
	}

	printf("\tsw\ta0,%d(fp)\n", bindings.currentExpressionStackPosition());
	return bindings;
}

int RelationalExpression::constantFold() const
{
	if(operator_ == "<")
	{
		return lhs_->constantFold()<rhs_->constantFold();
	}
	else if(operator_ == ">")
	{
		return lhs_->constantFold()>rhs_->constantFold();
	}
	else if(operator_ == "<=")
	{
		return lhs_->constantFold()<=rhs_->constantFold();
	}
    
	return lhs_->constantFold()>=rhs_->constantFold();
}


// EqualityExpression

EqualityExpression::EqualityExpression(Expression *lhs, const std::string &_operator, Expression *rhs)
	: OperationExpression(lhs, rhs), operator_(_operator)
{}

Bindings EqualityExpression::printAsm(Bindings bindings, int &label_count) const
{
	evaluateExpression(bindings, label_count);
	printf("\txor\ta0,a0,a1\n");

	if(operator_ == "==")
	{
		printf("\tsltiu\ta0,a0,1\n");
	}
	else if(operator_ == "!=")
	{
		printf("\tsltu\ta0,zero,a0\n");
	}
	else
	{
		throw std::runtime_error("Error : '"+operator_+"' not recognized");
	}

	// printf("\tandi\ta0,a0,0x0000ffff\n\tsw\ta0,%d(fp)\n", bindings.currentExpressionStackPosition());
	printf("\tsw\ta0,%d(fp)\n", bindings.currentExpressionStackPosition());
	return bindings;
}

int EqualityExpression::constantFold() const
{
	if(operator_ == "==")
		return lhs_->constantFold()==rhs_->constantFold();
	return lhs_->constantFold()!=rhs_->constantFold();
}


// AndExpression

AndExpression::AndExpression(Expression *lhs, Expression *rhs)
	: OperationExpression(lhs, rhs)
{}

Bindings AndExpression::printAsm(Bindings bindings, int &label_count) const
{
	evaluateExpression(bindings, label_count);
	printf("\tand\ta0,a0,a1\n\tsw\ta0,%d(fp)\n", bindings.currentExpressionStackPosition());
	return bindings;
}

int AndExpression::constantFold() const
{
	return lhs_->constantFold()&rhs_->constantFold();
}


// ExclusiveOrExpression

ExclusiveOrExpression::ExclusiveOrExpression(Expression *lhs, Expression *rhs)
	: OperationExpression(lhs, rhs)
{}

Bindings ExclusiveOrExpression::printAsm(Bindings bindings, int &label_count) const
{
	evaluateExpression(bindings, label_count);
	printf("\txor\ta0,a0,a1\n\tsw\ta0,%d(fp)\n", bindings.currentExpressionStackPosition());
	return bindings;
}

int ExclusiveOrExpression::constantFold() const
{
	return lhs_->constantFold()^rhs_->constantFold();
}


// InclusiveOrExpression

InclusiveOrExpression::InclusiveOrExpression(Expression *lhs, Expression *rhs)
	: OperationExpression(lhs, rhs)
{}

Bindings InclusiveOrExpression::printAsm(Bindings bindings, int &label_count) const
{
	evaluateExpression(bindings, label_count);
	printf("\tor\ta0,a0,a1\n\tsw\ta0,%d(fp)\n", bindings.currentExpressionStackPosition());
	return bindings;
}

int InclusiveOrExpression::constantFold() const
{
	return lhs_->constantFold()|rhs_->constantFold();
}


// LogicalAndExpression

LogicalAndExpression::LogicalAndExpression(Expression *lhs, Expression *rhs)
	: OperationExpression(lhs, rhs)
{}

Bindings LogicalAndExpression::printAsm(Bindings bindings, int &label_count) const
{
	int log_and = label_count++;
	lhs_->printAsm(bindings, label_count);
	printf("\tbeq\ta0,zero,x%d_log_and_load_0\n\tnop\n", log_and);
	rhs_->printAsm(bindings, label_count);
	printf("\tbeq\ta0,zero,x%d_log_and_load_0\n\tnop\n", log_and);
	printf("\tli\ta0,1\n\tj\tx%d_log_and_end\n\tnop\n", log_and);
	printf("x%d_log_and_load_0:\n\tmv\ta0,zero\nx%d_log_and_end:\n", log_and, log_and);
	printf("\tsw\ta0,%d(fp)\n", bindings.currentExpressionStackPosition());
	return bindings;
}

int LogicalAndExpression::constantFold() const
{
	return lhs_->constantFold()&&rhs_->constantFold();
}


// LogicalOrExpression

LogicalOrExpression::LogicalOrExpression(Expression *lhs, Expression *rhs)
	: OperationExpression(lhs, rhs)
{}

Bindings LogicalOrExpression::printAsm(Bindings bindings, int &label_count) const
{
	int log_or = label_count++;
	lhs_->printAsm(bindings, label_count);
	printf("\tbne\ta0,zero,x%d_log_or_load_1\n\tnop\n", log_or);
	rhs_->printAsm(bindings, label_count);
	printf("\tbeq\ta0,zero,x%d_log_or_load_0\n\tnop\n", log_or);
	printf("x%d_log_or_load_1:\n\tli\ta0,1\n\tj\tx%d_log_or_end\n\tnop\n", log_or, log_or);
	printf("x%d_log_or_load_0:\n\tmv\ta0,zero\nx%d_log_or_end:\n", log_or, log_or);
	printf("\tsw\ta0,%d(fp)\n", bindings.currentExpressionStackPosition());
	return bindings;
}

int LogicalOrExpression::constantFold() const
{
	return lhs_->constantFold()&&rhs_->constantFold();
}


// ConditionalExpression

ConditionalExpression::ConditionalExpression(Expression *logical_or,
                                             Expression *expression,
                                             Expression *conditional_expression)
	: logical_or_(logical_or), expression_(expression),
	  conditional_expression_(conditional_expression)
{}

Bindings ConditionalExpression::printAsm(Bindings bindings, int &label_count) const
{
	return bindings;
}

TypePtr ConditionalExpression::getType(const Bindings &bindings) const
{
	return std::make_shared<Int>();
}


// Assignment

AssignmentExpression::AssignmentExpression(Expression *lhs, Expression *rhs)
	: OperationExpression(lhs, rhs)
{}

AssignmentExpression::AssignmentExpression(ExpressionPtr lhs, Expression *rhs)
	: OperationExpression(lhs, rhs)
{}



/////HSH 有问题 已改正////////////////////////////
Bindings AssignmentExpression::printAsm(Bindings bindings, int &label_count) const
{
	//判断左式是否为全局变量
	std::shared_ptr<Identifier> lhs_tmp;
	lhs_tmp = std::dynamic_pointer_cast<Identifier>(lhs_);
	if(lhs_tmp != nullptr)
	{
		std::string id = lhs_tmp->id();
		if(bindings.bindingExists(id))
		{
			int stack_position = bindings.stackPosition(id);
			if(stack_position == -1)
			{
				printf("\tlui\ta1,%%hi(%s)\n",id.c_str());
				rhs_->printAsm(bindings, label_count);
				printf("\tsw\ta0,%%lo(%s)(a1)\n",id.c_str());
				return bindings;
			}
		}	
	}

	std::shared_ptr<UnaryExpression> lhs_postfix;
	lhs_postfix = std::static_pointer_cast<UnaryExpression>(lhs_);

	int expression_stack_position = bindings.currentExpressionStackPosition();


	rhs_->printAsm(bindings, label_count);
	bindings.nextExpressionStackPosition();
    
	std::shared_ptr<StringLiteral> rhs_tmp_string;
	std::shared_ptr<OperatorUnaryExpression> rhs_tmp_address;
	rhs_tmp_string = std::dynamic_pointer_cast<StringLiteral>(rhs_);
	rhs_tmp_address = std::dynamic_pointer_cast<OperatorUnaryExpression>(rhs_);
    
	if(rhs_tmp_string != nullptr)
	{
		lhs_postfix->pointerPosition(bindings);
	}
	else if(rhs_tmp_address != nullptr && rhs_tmp_address->getOperator() == "&")
	{
		lhs_postfix->pointerPosition(bindings);
	}
	else
	{
		lhs_postfix->stackPosition(bindings, label_count);
	}
    
	printf("\tlw\ta0,%d(fp)\n", expression_stack_position);
    
	TypePtr lhs_type = lhs_->getType(bindings);
	lhs_type->store();
	return bindings;
}


// Identifier

Identifier::Identifier(const std::string &id)
	: id_(id)
{}

Bindings Identifier::printAsm(Bindings bindings, int &) const
{///////////////////////HSH//////////////////////////
	if(bindings.bindingExists(id_))
	{
		int stack_position = bindings.stackPosition(id_);
		if(stack_position == -1)
		{
			printf("\tlui\ta0,%%hi(%s)\n\tlw\ta0,%%lo(%s)(a0)\n", id_.c_str(), id_.c_str());   
		}
		else
		{
			if(std::dynamic_pointer_cast<Array>(bindings.getType(id_)) != nullptr)
			{
				printf("\taddi\ta0,fp,%d\n", stack_position);
			}
			else
			{
				bindings.getType(id_)->load(10, stack_position);
			}
		}
	}
	else
	{
		throw std::runtime_error("Error : Can't find '"+id_+"' in current scope binding");
	}

	printf("\tsw\ta0,%d(fp)\n", bindings.currentExpressionStackPosition());
	return bindings;
}

void Identifier::pointerPosition(Bindings bindings) const
{
	if(bindings.bindingExists(id_))
	{
		printf("\taddi\tt0,fp,%d\n", bindings.stackPosition(id_));
		return;
	}

	throw std::runtime_error("Error : '"+id_+"' not yet declared");
}

void Identifier::stackPosition(Bindings bindings, int &) const
{
	if(bindings.bindingExists(id_))
	{
		if(bindings.stackPosition(id_) != -1)
			printf("\taddi\tt0,fp,%d\n", bindings.stackPosition(id_));
		return;
	}

	throw std::runtime_error("Error : '"+id_+"' not yet declared");
}

std::string Identifier::id() const
{
	return id_;
}

TypePtr Identifier::getType(const Bindings &bindings) const
{
	return bindings.getType(id_);
}


// String

StringLiteral::StringLiteral(const std::string &string_content)
	: string_content_(string_content)
{}

Bindings StringLiteral::printAsm(Bindings bindings, int &) const
{
	int label = bindings.insertStringLiteral(string_content_);
	printf("\tlui\ta0,%%hi(x%d_string)\n\taddi\ta0,a0,%%lo(x%d_string)\n", label, label);
	printf("\tsw\ta0,%d(fp)\n", bindings.currentExpressionStackPosition());
	return bindings;
}

TypePtr StringLiteral::getType(const Bindings &) const
{
	std::shared_ptr<Char> tmp_pointer_ptr;
	tmp_pointer_ptr->type(std::make_shared<Char>());
	return tmp_pointer_ptr;
}

// Constant
Constant::Constant(const int32_t &constant)
	: constant_(constant)
{}

Bindings Constant::printAsm(Bindings bindings, int &) const
{
	printf("\tli\ta0,%d\n", constant_);
	printf("\tsw\ta0,%d(fp)\n", bindings.currentExpressionStackPosition());
	return bindings;
}

int Constant::constantFold() const
{
	return constant_;
}

TypePtr Constant::getType(const Bindings &) const
{
	return std::make_shared<Int>();
}

// Initializer

Initializer::Initializer(Expression *next_initializer)
	: next_initializer_(next_initializer)
{}

Bindings Initializer::printAsm(Bindings bindings, int &) const
{
	return bindings;
}

TypePtr Initializer::getType(const Bindings &bindings) const
{
	return next_initializer_->getType(bindings);
}

void Initializer::printInitializerAsm(Bindings &bindings, int &label_count, int position, const
                                      std::vector<int> &iteration_vector, const TypePtr &type) const
{
	std::shared_ptr<Initializer> next_initializer
		(std::dynamic_pointer_cast<Initializer>(next_initializer_));
	ExpressionPtr current_expression = next_initializer_;
	std::vector<ExpressionPtr> expression_vector;

	while(current_expression != nullptr)
	{
		expression_vector.push_back(current_expression);
		current_expression = current_expression->nextExpression();
	}

	std::reverse(expression_vector.begin(), expression_vector.end());
	int size = (int)expression_vector.size();
	for(int i = size; i < iteration_vector[position]; ++i)
	{
		expression_vector.emplace_back(nullptr);
	}

	for(int i = 0; i < iteration_vector[position]; ++i)
	{
		next_initializer = std::dynamic_pointer_cast<Initializer>(expression_vector[i]);
		if(next_initializer != nullptr)
		{
			next_initializer->printInitializerAsm(bindings, label_count,
			                                      position-1, iteration_vector, type);
		}
		else
		{
			if(expression_vector[i] != nullptr)
			{
				Bindings temp_bindings = bindings;
				expression_vector[i]->printAsm(temp_bindings, label_count);
				type->store(bindings.currentStackPosition());
			}
			type->increaseStackPosition(bindings);
		}
	}
}

ExpressionPtr Initializer::getNext() const
{
	return next_initializer_;
}
