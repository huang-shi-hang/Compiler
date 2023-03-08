#ifndef NODE_HPP
#define NODE_HPP

#include <cstdint>
#include <map>
#include <string>

class Type;
class Bindings; 


// base node class
/**
 * @brief 
 * node作为基类，其中print打印出所需要的ast树，printAsm打印出所需要的汇编代码
 */
class Node
{
public:
	virtual ~Node() {}

	virtual void print() const = 0;
	virtual void printIR() const = 0;
	virtual Bindings printAsm(Bindings bindings, int& label_count) const = 0;
};


#endif
