#include "Calculator.h"

#include <cmath>

#include "Expression.h"
#include "BigInteger.h"

Calculator::Calculator()
{
	m_Tokenizer
		.AddTokenRule("+")
		.AddTokenRule("*")
		.AddTokenRule("%")
		.AddTokenRule("**");

	m_ExprBuilder
		.AddRule(ExpressionRule(
			"+"
			, 1
			, ExpressionRule::RIGHT
			, [](const BigInteger& a, const BigInteger& b){ return a + b; }
			))
		.AddRule(ExpressionRule(
			"*"
			, 2
			, ExpressionRule::RIGHT
			, [](const BigInteger& a, const BigInteger& b){ return a * b; }
			))
		.AddRule(ExpressionRule(
			"%"
			, 2
			, ExpressionRule::RIGHT
			, [](const BigInteger& a, const BigInteger& b){ return a % b; }
			))
		.AddRule(ExpressionRule(
			"**"
			, 3
			, ExpressionRule::LEFT
			, [](const BigInteger& a, const BigInteger& b){ return a.Power(b); }
	));
}

BigInteger Calculator::Calculate(const std::string& expression)
{
	auto tokenList = m_Tokenizer.Tokenize(expression);
	auto expr = m_ExprBuilder.BuildExpression(tokenList);
	return expr.Eval();
}
