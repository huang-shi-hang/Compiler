#include "type.hpp"

#include <cstdio>
#include <exception>
#include <stdexcept>


// Type

void Type::setStatic(bool)
{
	throw std::runtime_error("Error : cannot set static");
}

void Type::setConst(bool)
{
	throw std::runtime_error("Error : cannot set const");
}

void Type::setSize(int)
{
	throw std::runtime_error("Error : cannot set size");
}


// Array

Array::Array(const int &size, TypePtr type)
	: size_(size), type_(type)
{}

void Array::print() const
{
	printf("Array\n");
}

void Array::printIR() const{}

Bindings Array::printAsm(Bindings bindings, int &) const
{
	return bindings;
}

TypePtr Array::type()
{
	return type_;
}

TypePtr Array::type(Type *type_ptr)
{
	TypePtr sh_type_ptr(type_ptr);
	type_ = sh_type_ptr;
	return type_;
}

TypePtr Array::type(TypePtr type_ptr)
{
	type_ = type_ptr;
	return type_;
}

void Array::increaseStackPosition(Bindings &bindings) const
{
	for(int i = 0; i < size_; ++i)
	{
		type_->increaseStackPosition(bindings);
	}
}

void Array::increaseGlobalStackPosition(Bindings &bindings) const
{
	for(int i = 0; i < size_; ++i)
	{
		type_->increaseGlobalStackPosition(bindings);
	}
}

void Array::load() const
{
	type_->load();
}

void Array::load(const int &reg, const int &position) const
{
	type_->load(reg, position);
}

void Array::store() const
{
	type_->store();
}

void Array::store(const int &position) const
{
	type_->store(position);
}

void Array::store(const int &reg, const int &position) const
{
	type_->store(reg, position);
}

int Array::getSize() const
{
	return type_->getSize();
}

// TypeContainer

TypeContainer::TypeContainer()
	: type_(nullptr), size_(32), static_(false), const_(false)
{}

void TypeContainer::print() const
{
	printf("TypeContainer : ");
	type_->print();
}

void TypeContainer::printIR() const{}

Bindings TypeContainer::printAsm(Bindings bindings, int &) const
{
	return bindings;
}

TypePtr TypeContainer::type()
{
	return type_;
}

TypePtr TypeContainer::type(Type *type_ptr)
{
	TypePtr new_type_ptr(type_ptr);
	type_ = new_type_ptr;

	return type_;
}

TypePtr TypeContainer::type(TypePtr type_ptr)
{
	type_ = type_ptr;
    
	return type_;
}

void TypeContainer::increaseStackPosition(Bindings &bindings) const
{
	type_->increaseStackPosition(bindings);
}

void TypeContainer::increaseGlobalStackPosition(Bindings &bindings) const
{
	type_->increaseGlobalStackPosition(bindings);
}


void TypeContainer::load() const
{
	type_->load();
}

void TypeContainer::load(const int &reg, const int &position) const
{
	type_->load(reg, position);
}

void TypeContainer::store() const
{
	type_->store();
}

void TypeContainer::store(const int &position) const
{
	type_->store(position);
}

void TypeContainer::store(const int &reg, const int &position) const
{
	type_->store(reg, position);
}

int TypeContainer::getSize() const
{
	return type_->getSize();
}

void TypeContainer::setStatic(bool _static)
{
	static_ = _static;
}

void TypeContainer::setConst(bool _const)
{
	const_ = _const;
}

void TypeContainer::setSize(int size)
{
	size_ = size;
}


// Specifier 

TypePtr Specifier::type()
{
	throw std::runtime_error("Error : Cannot get type");
}

TypePtr Specifier::type(Type *)
{
	throw std::runtime_error("Error : Cannot get type");
}

TypePtr Specifier::type(TypePtr)
{
	throw std::runtime_error("Error : Cannot get type");
}


// Int 

Int::Int()
{}

void Int::print() const
{
	printf("Int\n");
}

void Int::printIR() const{}

Bindings Int::printAsm(Bindings bindings, int &) const
{
	return bindings;
}

void Int::increaseStackPosition(Bindings &bindings) const
{
	bindings.increaseStackPosition(4);
}

void Int::increaseGlobalStackPosition(Bindings &bindings) const
{
	bindings.increaseGlobalStackPosition(4);
}

void Int::load() const
{
	printf("\tlw\ta0,0(t0)\n");
}

void Int::load(const int &reg, const int &position) const
{
	printf("\tlw\tx%d,%d(fp)\n", reg, position);
	// printf("\tlw\ta0,%d(fp)\n", position);
}

void Int::store() const
{
	printf("\tsw\ta0,0(t0)\n");
}

void Int::store(const int &position) const
{
	printf("\tsw\ta0,%d(fp)\n", position);
}

void Int::store(const int &reg, const int &position) const
{
	printf("\tsw\tx%d,%d(fp)\n", reg, position);
}

int Int::getSize() const
{
	return 4;
}


// Void

Void::Void()
{}

void Void::print() const
{
	printf("Void\n");
}

void Void::printIR() const{}

Bindings Void::printAsm(Bindings bindings, int &) const
{
	return bindings;
}

void Void::increaseStackPosition(Bindings &) const
{}
void Void::increaseGlobalStackPosition(Bindings &) const
{}
void Void::load() const
{}

void Void::load(const int &, const int &) const
{}

void Void::store() const
{}

void Void::store(const int &) const
{}

void Void::store(const int &, const int &) const
{}

int Void::getSize() const
{
	return 0;
}


// Short

Short::Short()
{}

void Short::print() const
{
	printf("Short\n");
}

void Short::printIR() const{}

Bindings Short::printAsm(Bindings bindings, int &) const
{
	return bindings;
}

void Short::increaseStackPosition(Bindings &bindings) const
{
	bindings.increaseStackPosition(2);
}

void Short::increaseGlobalStackPosition(Bindings &bindings) const
{
	bindings.increaseGlobalStackPosition(2);
}

void Short::load() const
{
	printf("\tlhu\ta0,0(t0)\n");
}

void Short::load(const int &reg, const int &position) const
{
	printf("\tlhu\tx%d,%d(fp)\n", reg, position);
}

void Short::store() const
{
	printf("\tsh\ta0,0(t0)\n");
}

void Short::store(const int &position) const
{
	printf("\tsh\ta0,%d(fp)\n", position);
}

void Short::store(const int &reg, const int &position) const
{
	printf("\tsh\tx%d,%d(fp)\n", reg, position);
}

int Short::getSize() const
{
	return 2;
}


// Char

Char::Char()
{}

void Char::print() const
{
	printf("Char\n");
}

void Char::printIR() const{}

Bindings Char::printAsm(Bindings bindings, int &) const
{
	return bindings;
}

void Char::increaseStackPosition(Bindings &bindings) const
{
	bindings.increaseStackPosition(1);
}

void Char::increaseGlobalStackPosition(Bindings &bindings) const
{
	bindings.increaseGlobalStackPosition(1);
}

void Char::load() const
{
	printf("\tlbu\ta0,0(t0)\n");
}

void Char::load(const int &reg, const int &position) const
{
	printf("\tlbu\tx%d,%d(fp)\n", reg, position);
}

void Char::store() const
{
	printf("\tsb\ta0,0(t0)\n");
}

void Char::store(const int &position) const
{
	printf("\tsb\ta0,%d(fp)\n", position);
}

void Char::store(const int &reg, const int &position) const
{
	printf("\tsb\tx%d,%d(fp)\n", reg, position);
}

int Char::getSize() const
{
	return 1;
}
