#include "statement.hpp"

#include <cstdio>
#include <vector>
#include <stdexcept>


// General base Statement definition

Statement::Statement(Statement *statement)
	: next_statement_(statement)
{}

int Statement::constantFold() const
{
	throw std::runtime_error("Error : not implemented");
}

ExpressionPtr Statement::getExpression() const
{
	return nullptr;  
}

bool Statement::isDefault() const
{
	return false;
}

void Statement::linkStatement(Statement *next)
{
	StatementPtr statement_ptr(next);
	next_statement_ = statement_ptr;
}

StatementPtr Statement::getNext() const
{
	return next_statement_;
}


// LabelStatement

LabelStatement::LabelStatement(const std::string &label, Statement *statement)
	: label_(label), statement_(statement)
{}

void LabelStatement::print() const
{
	if(next_statement_ != nullptr)
		next_statement_->print();
    
	printf("Label Statement\n");
}

void LabelStatement::printIR() const{}

Bindings LabelStatement::printAsm(Bindings bindings, int &label_count) const
{
	if(next_statement_ != nullptr)
		next_statement_->printAsm(bindings, label_count);

	printf("%s:\n", label_.c_str());

	statement_->printAsm(bindings, label_count);

	return bindings;
}

void LabelStatement::countVariables(int &var_count) const
{
	if(next_statement_ != nullptr)
		next_statement_->countVariables(var_count);

	statement_->countVariables(var_count);
}

void LabelStatement::countArguments(int &argument_count) const
{
	if(next_statement_ != nullptr)
		next_statement_->countArguments(argument_count);

	statement_->countArguments(argument_count);
}

void LabelStatement::countExpressionDepth(int &depth_count) const
{
	int previous_depth_count = depth_count;
	if(next_statement_ != nullptr)
	{
		next_statement_->countExpressionDepth(depth_count);
		if(previous_depth_count > depth_count)
			depth_count = previous_depth_count;
		previous_depth_count = depth_count;
	}
    
	statement_->countExpressionDepth(depth_count);
	if(previous_depth_count > depth_count)
		depth_count = previous_depth_count;
}


// CaseStatement

CaseStatement::CaseStatement(Statement *statement, Expression *constant_expression, const bool &_default)
	: constant_expression_(constant_expression), statement_(statement), default_(_default)
{}

void CaseStatement::print() const
{
	if(next_statement_ != nullptr)
		next_statement_->print();
    
	printf("Case Statement\n");
}

void CaseStatement::printIR() const{}

Bindings CaseStatement::printAsm(Bindings bindings, int &label_count) const
{
	if(next_statement_ != nullptr)
		next_statement_->printAsm(bindings, label_count);

	statement_->printAsm(bindings, label_count);

	return bindings;
}

void CaseStatement::countVariables(int &var_count) const
{
	if(next_statement_ != nullptr)
		next_statement_->countVariables(var_count);

	statement_->countVariables(var_count);
}

void CaseStatement::countArguments(int &argument_count) const
{
	if(next_statement_ != nullptr)
		next_statement_->countArguments(argument_count);

	statement_->countArguments(argument_count);
}

void CaseStatement::countExpressionDepth(int &depth_count) const
{
	int previous_depth_count = depth_count;
	if(next_statement_ != nullptr)
	{
		next_statement_->countExpressionDepth(depth_count);
		if(previous_depth_count > depth_count)
			depth_count = previous_depth_count;
		previous_depth_count = depth_count;
	}
    
	statement_->countExpressionDepth(depth_count);
	if(previous_depth_count > depth_count)
		depth_count = previous_depth_count;    
}

int CaseStatement::constantFold() const
{
	return constant_expression_->constantFold();
}

ExpressionPtr CaseStatement::getExpression() const
{
	return constant_expression_;
}

bool CaseStatement::isDefault() const
{
	return default_;
}


// CompoundStatement

CompoundStatement::CompoundStatement(Declaration *declaration, Statement *statement)
	: Statement(), declaration_(declaration), statement_(statement)
{}

CompoundStatement::CompoundStatement(Statement *statement)
	: statement_(statement)
{}

void CompoundStatement::print() const
{
	if(declaration_ != nullptr)
		declaration_->print();
    
	if(statement_ != nullptr)
		statement_->print();
}

void CompoundStatement::printIR() const{}

Bindings CompoundStatement::printAsm(Bindings bindings, int &label_count) const
{
	Bindings outer_scope_bindings = bindings;
    
	if(next_statement_ != nullptr)
		next_statement_->printAsm(bindings, label_count);
    
	if(declaration_ != nullptr)
		bindings = declaration_->localAsm(bindings, label_count);

	if(statement_ != nullptr)
		statement_->printAsm(bindings, label_count);

	return outer_scope_bindings;
}

void CompoundStatement::countVariables(int &var_count) const
{
	if(next_statement_ != nullptr)
		next_statement_->countVariables(var_count);
    
	if(declaration_ != nullptr)
		declaration_->countDeclarations(var_count);

	if(statement_ != nullptr)
		statement_->countVariables(var_count);
}

void CompoundStatement::countArguments(int &argument_count) const
{
	if(next_statement_ != nullptr)
		next_statement_->countArguments(argument_count);

	if(statement_ != nullptr)
		statement_->countArguments(argument_count);
}

void CompoundStatement::countExpressionDepth(int &depth_count) const
{
	int previous_depth_count = depth_count;
	if(next_statement_ != nullptr)
	{
		next_statement_->countExpressionDepth(depth_count);
		if(previous_depth_count > depth_count)
			depth_count = previous_depth_count;
		previous_depth_count = depth_count;
	}

	if(statement_ != nullptr)
	{
		statement_->countExpressionDepth(depth_count);
		if(previous_depth_count > depth_count)
			depth_count = previous_depth_count;
	}
}

StatementPtr CompoundStatement::getStatementList() const
{
	return statement_;
}


// IfElseStatement

IfElseStatement::IfElseStatement(Expression *condition, Statement *_if, Statement *_else)
	: Statement(), condition_(condition), if_(_if), else_(_else) {}

void IfElseStatement::print() const
{
	condition_->print();
	if_->print();
	if(else_ != nullptr)
		else_->print();
}

void IfElseStatement::printIR() const{}

Bindings IfElseStatement::printAsm(Bindings bindings, int &label_count) const
{
	if(next_statement_ != nullptr)
		next_statement_->printAsm(bindings, label_count);
    
	int if_label = label_count++;
	
	condition_->printAsm(bindings, label_count);
	printf("\tbeq\ta0,zero,x%d_else\n\tnop\n", if_label);
    
	if_->printAsm(bindings, label_count);

	printf("\tj\tx%d_if_end\n\tnop\nx%d_else:\n", if_label, if_label);

	if(else_ != nullptr)
		else_->printAsm(bindings, label_count);

	printf("x%d_if_end:\n", if_label);

	return bindings;
}

void IfElseStatement::countVariables(int &var_count) const
{
	if(next_statement_ != nullptr)
		next_statement_->countVariables(var_count);

	if(if_ != nullptr)
		if_->countVariables(var_count);

	if(else_ != nullptr)
		else_->countVariables(var_count);
}

void IfElseStatement::countArguments(int &argument_count) const
{
	if(next_statement_ != nullptr)
		next_statement_->countArguments(argument_count);

	if(if_ != nullptr)
		if_->countArguments(argument_count);

	if(else_ != nullptr)
		else_->countArguments(argument_count);
}

void IfElseStatement::countExpressionDepth(int &depth_count) const
{
	int previous_depth_count = depth_count;

	if(next_statement_ != nullptr)
	{
		next_statement_->countExpressionDepth(depth_count);
		if(previous_depth_count > depth_count)
			depth_count = previous_depth_count;
		previous_depth_count = depth_count;
	}

	depth_count = 1;
	condition_->expressionDepth(depth_count);
	if(previous_depth_count > depth_count)
		depth_count = previous_depth_count;
	previous_depth_count = depth_count;
    
	if_->countExpressionDepth(depth_count);
	if(previous_depth_count > depth_count)
		depth_count = previous_depth_count;
	previous_depth_count = depth_count;

	if(else_ != nullptr)
	{
		else_->countExpressionDepth(depth_count);
		if(previous_depth_count > depth_count)
			depth_count = previous_depth_count;
	}
}


// SwitchStatement

SwitchStatement::SwitchStatement(Expression *condition, Statement *statement)
	: condition_(condition), statement_(statement)
{}

void SwitchStatement::print() const
{
	if(next_statement_ != nullptr)
		next_statement_->print();
    
	printf("Switch Statement\n");
	condition_->print();
	statement_->print();
}

void SwitchStatement::printIR() const{}

Bindings SwitchStatement::printAsm(Bindings bindings, int &label_count) const
{
	int switch_count = label_count++;
	std::shared_ptr<CompoundStatement> comp_statement;
	StatementPtr case_statement_list;
	std::vector<StatementPtr> case_statement_vector;
    
	if(next_statement_ != nullptr)
		next_statement_->printAsm(bindings, label_count);

	condition_->printAsm(bindings, label_count);

	comp_statement = std::dynamic_pointer_cast<CompoundStatement>(statement_);
	if(comp_statement == nullptr)
		throw std::runtime_error("Error : not implemented");

	bindings.breakLabel("x"+std::to_string(switch_count)+"_break_switch");

	case_statement_list = comp_statement->getStatementList();
	while(case_statement_list != nullptr)
	{
		case_statement_vector.push_back(case_statement_list);
		case_statement_list = case_statement_list->getNext();
	}

	bool is_default = false;

	for(auto itr = case_statement_vector.rbegin(); itr != case_statement_vector.rend(); ++itr)
	{
		if((*itr)->getExpression() != nullptr)
		{
			int jump_label = (*itr)->constantFold();
			printf("\tli\ta1,%d\n\tbeq\ta0,a1,x%d_%d_switch\n\tnop\n",
			       jump_label, switch_count, jump_label);
		}
		if(!is_default)
		{
			is_default = (*itr)->isDefault();
		}
	}

	if(is_default)
		printf("\tj\tx%d_default_switch\n\tnop\n", switch_count);

	for(auto itr = case_statement_vector.rbegin(); itr != case_statement_vector.rend(); ++itr)
	{
		if((*itr)->getExpression() != nullptr)
			printf("x%d_%d_switch:\n", switch_count, (*itr)->constantFold());
	
		if((*itr)->isDefault())
			printf("x%d_default_switch:\n", switch_count);
		(*itr)->linkStatement(nullptr);
		(*itr)->printAsm(bindings, label_count);
	}

	printf("x%d_break_switch:\n", switch_count);
	return bindings;
}

void SwitchStatement::countVariables(int &label_count) const
{
	if(next_statement_ != nullptr)
		next_statement_->countVariables(label_count);

	statement_->countVariables(label_count);
}

void SwitchStatement::countArguments(int &argument_count) const
{
	if(next_statement_ != nullptr)
		next_statement_->countArguments(argument_count);

	statement_->countArguments(argument_count);
	int previous_argument_count = argument_count;
	condition_->countArguments(argument_count);

	if(previous_argument_count > argument_count)
		argument_count = previous_argument_count;
}

void SwitchStatement::countExpressionDepth(int &depth_count) const
{
	int previous_depth_count = depth_count;

	if(next_statement_ != nullptr)
	{
		next_statement_->countExpressionDepth(depth_count);
		if(previous_depth_count > depth_count)
			depth_count = previous_depth_count;
		previous_depth_count = depth_count;
	}

	depth_count = 1;
	statement_->countExpressionDepth(depth_count);
	if(previous_depth_count > depth_count)
		depth_count = previous_depth_count;
	previous_depth_count = depth_count;
    
	depth_count = 1;
	condition_->expressionDepth(depth_count);
	if(previous_depth_count > depth_count)
		depth_count = previous_depth_count;   
}


// ExpressionStatement

ExpressionStatement::ExpressionStatement(Expression *expr)
	: Statement(), expression_(expr)
{}

void ExpressionStatement::print() const
{
	if(next_statement_ != nullptr)
		next_statement_->print();

	printf("Expression Statement\n");
	if(expression_ != nullptr)
		expression_->print();
}

void ExpressionStatement::printIR() const{}

Bindings ExpressionStatement::printAsm(Bindings bindings, int &label_count) const
{
	if(next_statement_ != nullptr)
		next_statement_->printAsm(bindings, label_count);
    
	if(expression_ != nullptr)
		expression_->printAsm(bindings, label_count);
    
	return bindings;
}

void ExpressionStatement::countVariables(int &var_count) const
{
	if(next_statement_ != nullptr)
		next_statement_->countVariables(var_count);
}

void ExpressionStatement::countArguments(int &argument_count) const
{
	if(next_statement_ != nullptr)
		next_statement_->countArguments(argument_count);

	int tmp_argument_count = argument_count;

	if(expression_ != nullptr)
		expression_->countArguments(argument_count);

	if(tmp_argument_count > argument_count)
		argument_count = tmp_argument_count;
}

void ExpressionStatement::countExpressionDepth(int &depth_count) const
{
	int previous_depth_count = depth_count;

	if(next_statement_ != nullptr)
	{
		next_statement_->countExpressionDepth(depth_count);
		if(previous_depth_count > depth_count)
			depth_count = previous_depth_count;
		previous_depth_count = depth_count;
	}

	if(expression_ != nullptr)
	{
		depth_count = 1;
		expression_->expressionDepth(depth_count);
		if(previous_depth_count > depth_count)
			depth_count = previous_depth_count;
	}
}


// JumpStatement

void JumpStatement::print() const
{}

void JumpStatement::printIR() const{}

void JumpStatement::countVariables(int &var_count) const
{
	if(next_statement_ != nullptr)
		next_statement_->countVariables(var_count);
}

void JumpStatement::countArguments(int &argument_count) const
{
	if(next_statement_ != nullptr)
		next_statement_->countArguments(argument_count);
}

void JumpStatement::countExpressionDepth(int &depth_count) const
{
	if(next_statement_ != nullptr)
		next_statement_->countExpressionDepth(depth_count);
}


// Returnstatement

ReturnStatement::ReturnStatement(Expression *expression)
	: expression_(expression)
{}

Bindings ReturnStatement::printAsm(Bindings bindings, int &label_count) const
{
	if(next_statement_ != nullptr)
		next_statement_->printAsm(bindings, label_count);
    
	if(expression_ != nullptr)
		expression_->printAsm(bindings, label_count);

	printf("\tj\t%s_0\n\tnop\n",bindings.getFunName().c_str());
    
	return bindings;
}

void ReturnStatement::countVariables(int &var_count) const
{
	if(next_statement_ != nullptr)
		next_statement_->countVariables(var_count);
}

void ReturnStatement::countArguments(int &argument_count) const
{
	if(next_statement_ != nullptr)
		next_statement_->countArguments(argument_count);

	int tmp_argument_count = argument_count;

	if(expression_ != nullptr)
		expression_->countArguments(argument_count);

	if(tmp_argument_count > argument_count)
		argument_count = tmp_argument_count;
}

void ReturnStatement::countExpressionDepth(int &depth_count) const
{
	int previous_depth_count = depth_count;

	if(next_statement_ != nullptr)
	{
		next_statement_->countExpressionDepth(depth_count);
		if(previous_depth_count > depth_count)
			depth_count = previous_depth_count;
		previous_depth_count = depth_count;
	}

	if(expression_ != nullptr)
	{
		depth_count = 1;
		expression_->expressionDepth(depth_count);
		if(previous_depth_count > depth_count)
			depth_count = previous_depth_count;
	}
}


// Breakstatement
BreakStatement::BreakStatement()
{}

Bindings BreakStatement::printAsm(Bindings bindings, int &label_count) const
{
	if(next_statement_ != nullptr)
		next_statement_->printAsm(bindings, label_count);
    
	printf("\tj\t%s\n\tnop\n", bindings.breakLabel().c_str());
	return bindings;
}


// Continuestatement

ContinueStatement::ContinueStatement()
{}

Bindings ContinueStatement::printAsm(Bindings bindings, int &label_count) const
{
	if(next_statement_ != nullptr)
		next_statement_->printAsm(bindings, label_count);
    
	printf("\tj\t%s\n\tnop\n", bindings.continueLabel().c_str());
	return bindings;
}


// Goto statement

GotoStatement::GotoStatement(const std::string &label)
	: label_(label)
{}

Bindings GotoStatement::printAsm(Bindings bindings, int &label_count) const
{
	if(next_statement_ != nullptr)
		next_statement_->printAsm(bindings, label_count);
    
	printf("\tj\t%s\n\tnop\n", label_.c_str());
	return bindings;
}


// IterationStatement

IterationStatement::IterationStatement(Expression *condition, Statement *statement)
	: condition_(condition), statement_(statement)
{}

void IterationStatement::print() const
{}

void IterationStatement::printIR() const{}

void IterationStatement::countVariables(int &var_count) const
{
	if(next_statement_ != nullptr)
		next_statement_->countVariables(var_count);

	if(statement_ != nullptr)
		statement_->countVariables(var_count);
}

void IterationStatement::countArguments(int &argument_count) const
{
	if(next_statement_ != nullptr)
		next_statement_->countArguments(argument_count);

	if(statement_ != nullptr)
		statement_->countArguments(argument_count);
}

void IterationStatement::countExpressionDepth(int &depth_count) const
{
	int previous_depth_count = depth_count;

	if(next_statement_ != nullptr)
	{
		next_statement_->countExpressionDepth(depth_count);
		if(previous_depth_count > depth_count)
			depth_count = previous_depth_count;
		previous_depth_count = depth_count;
	}
    
	depth_count = 1;
	condition_->expressionDepth(depth_count);
	if(previous_depth_count > depth_count)
		depth_count = previous_depth_count;
	previous_depth_count = depth_count;

	statement_->countExpressionDepth(depth_count);
	if(previous_depth_count > depth_count)
		depth_count = previous_depth_count;
}


// WhileLoop

WhileLoop::WhileLoop(Expression *condition, Statement *statement, const bool &is_while)
	: IterationStatement(condition, statement), is_while_(is_while)
{}

Bindings WhileLoop::printAsm(Bindings bindings, int &label_count) const
{
	if(next_statement_ != nullptr)
		next_statement_->printAsm(bindings, label_count);

	Bindings initial_bindings = bindings;
    
	int while_label = label_count++;

	bindings.continueLabel("x"+std::to_string(while_label)+"_while_cond");
	bindings.breakLabel("x"+std::to_string(while_label)+"_while_break");

	if(is_while_)
		printf("\tj\tx%d_while_cond\n\tnop\n", while_label);
	printf("x%d_while_body:\n", while_label);
	statement_->printAsm(bindings, label_count);
	printf("x%d_while_cond:\n", while_label);
	condition_->printAsm(bindings, label_count);
	printf("\tbne\ta0,zero,x%d_while_body\n\tnop\nx%d_while_break:\n", while_label, while_label);
	return initial_bindings;
}

ForLoop::ForLoop(Expression *initializer, Expression *condition, Expression *incrementer, Statement *statement)
	: IterationStatement(condition, statement), initializer_(initializer), incrementer_(incrementer)
{}

Bindings ForLoop::printAsm(Bindings bindings, int &label_count) const
{
	if(next_statement_ != nullptr)
		next_statement_->printAsm(bindings, label_count);

	Bindings initial_bindings = bindings;
    
	int for_label = label_count++;

	bindings.continueLabel("x"+std::to_string(for_label)+"_for_cond");
	bindings.breakLabel("x"+std::to_string(for_label)+"_for_break");
    
	initializer_->printAsm(bindings, label_count);
	printf("\tj\tx%d_for_cond\n\tnop\nx%d_for_body:\n", for_label, for_label);
	statement_->printAsm(bindings, label_count);
	incrementer_->printAsm(bindings, label_count);
	printf("x%d_for_cond:\n", for_label);
	condition_->printAsm(bindings, label_count);
	printf("\tbne\ta0,zero,x%d_for_body\n\tnop\nx%d_for_break:\n", for_label, for_label);

	return initial_bindings;
}
