#pragma once

#include <list>

#include "ExpressionItem.h"

class Expression
{
public:
	BigInteger Eval() const;

	void Push(const ExpressionItem& item);
	void Push(const Expression& expr);

private:
	std::list<ExpressionItem> m_ItemList;
};