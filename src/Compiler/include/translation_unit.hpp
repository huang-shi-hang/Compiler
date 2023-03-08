#ifndef TRANSLATION_UNIT_HPP
#define TRANSLATION_UNIT_HPP

#include "bindings.hpp"
#include "node.hpp"

#include <memory>
#include <vector>

typedef std::shared_ptr<Node> NodePtr;


class TranslationUnit : public Node {
protected:
	std::vector<NodePtr> translation_unit_;
    
public:
	TranslationUnit(Node* external_declaration);

	virtual void print() const;
	virtual void printIR() const;
	virtual Bindings printAsm(Bindings bindings, int& label_count) const;

	void push(Node* external_declaration);
};


#endif
