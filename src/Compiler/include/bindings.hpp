#ifndef BINDINGS_HPP
#define BINDINGS_HPP

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

class Type;

typedef std::shared_ptr<Type> TypePtr;

/**
 * @brief 声明结构，存储相应的声明语句，其实是符号表
 * 
 */
struct DeclarationData
{
	/**
	 * @brief 类型，栈位置，数组
	 * 
	 */
	TypePtr type;
	int stack_position;
	std::vector<int> array_sizes;
};

/**
 * @brief 保存当前作用域与堆栈的绑定关系
 * 
 */
class Bindings
{
private:
	static std::vector<std::string> string_literals;
    
	std::unordered_map<std::string, DeclarationData> bindings_;//key是string，符号表作为value
	std::string break_label_;//break语句的标志
	std::string continue_label_;//continue的标志
	int stack_counter_;//栈计数
	int expression_stack_;//表达式的栈
	int global_stack_counter_;//全局栈计数
	std::string fun_name_;//函数名
public:
	Bindings();
	//将符号插入符号表中，普通符号和数组分开
	void insertBinding(const std::string &id, const TypePtr &type, const int &stack_position);
	void insertBinding(const std::string &id, const TypePtr &type, const int &stack_position, const std::vector<int> array_sizes);
	//将符号名放入栈中，并且返回插入的位置
	int insertStringLiteral(const std::string &string_literal);
	//增大栈
	void increaseStackPosition();
	//增加指定的栈大小
	void increaseStackPosition(const int &position);
	//增加全局栈
	void increaseGlobalStackPosition();

	void increaseGlobalStackPosition(const int &position);
	//更改栈的个数
	void setStackPosition(const int &stack_counter);
	//找到下一个表达式的位置
	void nextExpressionStackPosition();
	//设置表达式栈的位置
	void setExpressionStackPosition(const int &stack_counter);
	//设置函数的名称
	void setFunName(const std::string &name);

	//找到种类
	TypePtr getType(const std::string &id) const;
	//找到数组的大小
	const std::vector<int> &getArraySizes(const std::string &id) const;
	//找到函数的名字
	std::string getFunName();

	//返回break和continue
	std::string breakLabel();
	std::string breakLabel(const std::string &label);
	std::string continueLabel();
	std::string continueLabel(const std::string &label);

	//返回当前的栈的位置
	int currentStackPosition() const;
	//返回对应key的位置
	int stackPosition(const std::string &id) const;
	int currentGlobalStackPosition() const;
	int currentExpressionStackPosition() const;

	std::pair<std::vector<std::string>::const_iterator, std::vector<std::string>::const_iterator>
	getStringLiteralIterator() const;

	bool bindingExists(const std::string &id) const;
};


#endif
