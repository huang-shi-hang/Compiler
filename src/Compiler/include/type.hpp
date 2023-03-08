#ifndef TYPE_HPP
#define TYPE_HPP

#include "bindings.hpp"
#include "node.hpp"

#include <memory>
#include <string>

class Type;
typedef std::shared_ptr<Type> TypePtr;

class Type : public Node
{
public:
	virtual void print() const = 0;
	virtual void printIR() const = 0;
	virtual Bindings printAsm(Bindings bindings, int &label_count) const = 0;
    
	//返回类型
	virtual TypePtr type() = 0;
	virtual TypePtr type(Type *type_ptr) = 0;
	virtual TypePtr type(TypePtr type_ptr) = 0;
	//分配空间
	virtual void increaseStackPosition(Bindings &bindings) const = 0;
	virtual void increaseGlobalStackPosition(Bindings &bindings) const = 0;
	//加载此类型的动作
	virtual void load() const = 0;
	virtual void load(const int &reg, const int &position) const = 0;

	//储存此类型的动作
	virtual void store() const = 0;    
	virtual void store(const int &position) const = 0;
	virtual void store(const int &reg, const int &position) const = 0;

	//类型所占空间
	virtual int getSize() const = 0;
    
	//设置正负号，设置各种特性
	virtual void setStatic(bool _static);
	virtual void setConst(bool _const);
	virtual void setSize(int size);
};

class Array : public Type
{
private:
	int size_;
	TypePtr type_;
public:
	Array(const int &size, TypePtr type_ = nullptr);

	virtual void print() const;
	virtual void printIR() const;
	virtual Bindings printAsm(Bindings bindings, int &label_count) const;
    
	virtual TypePtr type();
	virtual TypePtr type(Type *type_ptr);
	virtual TypePtr type(TypePtr type_ptr);

	virtual void increaseStackPosition(Bindings &bindings) const;
	virtual void increaseGlobalStackPosition(Bindings &bindings) const;
	virtual void load() const;
	virtual void load(const int &reg, const int &position) const;
	virtual void store() const;    
	virtual void store(const int &position) const;
	virtual void store(const int &reg, const int &position) const;
	virtual int getSize() const;
};

class TypeContainer : public Type
{
protected:
	TypePtr type_;
	int size_;
	bool static_;
	bool const_;

public:
	TypeContainer();

	virtual void print() const;
	virtual void printIR() const;
	virtual Bindings printAsm(Bindings bindings, int &label_count) const;
    
	virtual TypePtr type();    
	virtual TypePtr type(Type *type_ptr);
	virtual TypePtr type(TypePtr type_ptr);

	virtual void increaseStackPosition(Bindings &bindings) const;
	virtual void increaseGlobalStackPosition(Bindings &bindings) const;
	virtual void load() const;
	virtual void load(const int &reg, const int &position) const;
	virtual void store() const;    
	virtual void store(const int &position) const;
	virtual void store(const int &reg, const int &position) const;
	virtual int getSize() const;
    
	virtual void setStatic(bool _static);
	virtual void setConst(bool _const);
	virtual void setSize(int size);
};

class Specifier : public Type
{
public:
	virtual void print() const = 0;
	virtual void printIR() const = 0;
	virtual Bindings printAsm(Bindings bindings, int &label_count) const = 0;

	virtual void increaseStackPosition(Bindings &bindings) const = 0;
	virtual void increaseGlobalStackPosition(Bindings &bindings) const = 0;
	virtual void load() const = 0;
	virtual void load(const int &reg, const int &position) const = 0;
	virtual void store() const = 0;    
	virtual void store(const int &position) const = 0;
	virtual void store(const int &reg, const int &position) const = 0;
	virtual int getSize() const = 0;
    
	virtual TypePtr type();
	virtual TypePtr type(Type *type_ptr);
	virtual TypePtr type(TypePtr type_ptr);
};

class Int : public Specifier
{
public:
	Int();

	virtual void print() const;
	virtual void printIR() const;
	virtual Bindings printAsm(Bindings bindings, int &label_count) const;
	virtual void increaseStackPosition(Bindings &bindings) const;
	virtual void increaseGlobalStackPosition(Bindings &bindings) const;
	virtual void load() const;
	virtual void load(const int &reg, const int &position) const;
	virtual void store() const;
	virtual void store(const int &position) const;
	virtual void store(const int &reg, const int &position) const;
	virtual int getSize() const;
};

class Short : public Specifier
{
public:
	Short();

	virtual void print() const;
	virtual void printIR() const;
	virtual Bindings printAsm(Bindings bindings, int &label_count) const;
	virtual void increaseStackPosition(Bindings &bindings) const;
	virtual void increaseGlobalStackPosition(Bindings &bindings) const;
	virtual void load() const;    
	virtual void load(const int &reg, const int &position) const;
	virtual void store() const;
	virtual void store(const int &position) const;
	virtual void store(const int &reg, const int &position) const;
	virtual int getSize() const;
};

class Void : public Specifier
{
public:
	Void();

	virtual void print() const;
	virtual void printIR() const;
	virtual Bindings printAsm(Bindings bindings, int &label_count) const;
	virtual void increaseStackPosition(Bindings &bindings) const;
	virtual void increaseGlobalStackPosition(Bindings &bindings) const;
	virtual void load() const;    
	virtual void load(const int &reg, const int &position) const;
	virtual void store() const;
	virtual void store(const int &position) const;
	virtual void store(const int &reg, const int &position) const;
	virtual int getSize() const;
};

class Char : public Specifier
{
public:
	Char();

	virtual void print() const;
	virtual void printIR() const;
	virtual Bindings printAsm(Bindings bindings, int &label_count) const;
	virtual void increaseStackPosition(Bindings &bindings) const;
	virtual void increaseGlobalStackPosition(Bindings &bindings) const;
	virtual void load() const;    
	virtual void load(const int &reg, const int &position) const;
	virtual void store() const;
	virtual void store(const int &position) const;
	virtual void store(const int &reg, const int &position) const;
	virtual int getSize() const;
};

#endif
