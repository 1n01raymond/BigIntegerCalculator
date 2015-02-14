#include "Expression.h"

#include <stack>
#include <string>
#include <cmath>

BigInteger Expression::Eval() const
{
	std::stack<BigInteger> valueStack;

	for (auto& item : m_ItemList)
	{
		switch (item.GetType())
		{
		case ExpressionItem::NUMBER:
			valueStack.push(item.AsNumber());
			break;
		case ExpressionItem::OPERATOR:
		{
			BigInteger rightValue = valueStack.top();
			valueStack.pop();

			BigInteger leftValue = valueStack.top();
			valueStack.pop();

			BigInteger resultValue = item.AsOperator()(leftValue, rightValue);
			valueStack.push(resultValue);
			break;
		}
		default:
			throw "Unexpected item type " + item.GetType();
			break;
		}
	}

	return valueStack.top();
}

void Expression::Push(const ExpressionItem& item)
{
	m_ItemList.push_back(item);
}

void Expression::Push(const Expression& expr)
{
	m_ItemList.insert(m_ItemList.end(), expr.m_ItemList.begin(), expr.m_ItemList.end());
}
