#include "ExpressionItem.h"
#include "BigInteger.h"

ExpressionItem ExpressionItem::MakeNumberItem(const std::string& data)
{
	ExpressionItem item;
	item.m_Type = NUMBER;
	item.m_Number = BigInteger(data);
	return item;
}

ExpressionItem ExpressionItem::MakeOperatorItem(const OperatorFunction& function)
{
	ExpressionItem item;
	item.m_Type = OPERATOR;
	item.m_Function = function;
	return item;
}


ExpressionItem::ExpressionItem()
	:m_Type(NUMBER)
{}

ExpressionItem::ExpressionItem(const ExpressionItem& other)
	: m_Type(other.m_Type), m_Number(other.m_Number), m_Function(other.m_Function)
{}

ExpressionItem& ExpressionItem::operator = (const ExpressionItem& other)
{
	m_Type = other.m_Type;
	m_Number = other.m_Number;
	m_Function = other.m_Function;
	return *this;
}

BigInteger ExpressionItem::AsNumber() const
{
	return m_Number;
}

OperatorFunction ExpressionItem::AsOperator() const
{
	return m_Function;
}


ExpressionItem::ItemType ExpressionItem::GetType() const
{
	return m_Type;
}
