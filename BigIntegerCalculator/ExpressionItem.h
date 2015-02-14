#pragma once

#include <string>

#include "typedef.h"
#include "BigInteger.h"

class ExpressionItem
{
public:
	enum ItemType {
		NUMBER
		, OPERATOR
	};

public:
	static ExpressionItem MakeNumberItem(const std::string& data);
	static ExpressionItem MakeOperatorItem(const OperatorFunction& function);

	ExpressionItem(const ExpressionItem& other);
	ExpressionItem& operator =(const ExpressionItem& other);

	BigInteger AsNumber() const;
	OperatorFunction AsOperator() const;

	ItemType GetType() const;

private:
	ExpressionItem();

private:
	ItemType m_Type;

	BigInteger m_Number;
	OperatorFunction m_Function;

};
