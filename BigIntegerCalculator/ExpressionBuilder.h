#pragma once

#include <string>
#include <list>
#include <map>

#include "ExpressionRule.h"

class Expression;

class ExpressionBuilder
{
public:
	ExpressionBuilder& AddRule(const ExpressionRule& rule);

	Expression BuildExpression(const TokenList& tokenList);

private:
	std::map<std::string, ExpressionRule> m_ExprRuleMap;

};