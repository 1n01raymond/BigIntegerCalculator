#include "ExpressionBuilder.h"

#include <stack>

#include "Expression.h"
#include "ExpressionItem.h"


ExpressionBuilder& ExpressionBuilder::AddRule(const ExpressionRule& rule)
{
	m_ExprRuleMap[rule.str] = rule;
	return *this;
}


Expression ExpressionBuilder::BuildExpression(const TokenList& tokenList)
{
	Expression expr;

	std::stack<ExpressionRule> operatorStack;

	for (auto token : tokenList)
	{
		// 연산자
		auto it = m_ExprRuleMap.find(token);
		if (it != m_ExprRuleMap.end())
		{
			auto& rule = it->second;

			// 기존보다 우선순위 낮은 연산자
			// 자신보다 높거나 같은 연산자를 만날 때까지 뽑기
			while (!operatorStack.empty()
				&& operatorStack.top().priority > rule.priority)
			{
				expr.Push(ExpressionItem::MakeOperatorItem(operatorStack.top().function));
				operatorStack.pop();
			}

			// 기존보다 우선순위 높은 연산자는 그냥 넣음
			// 기존보다 우선순위 같은 연산자는
			if (!operatorStack.empty()
				&& operatorStack.top().priority == rule.priority)
			{
				// 우결합이면 뽑고 넣기
				if (rule.direction == ExpressionRule::RIGHT)
				{
					expr.Push(ExpressionItem::MakeOperatorItem(operatorStack.top().function));
					operatorStack.pop();
				}
				// 좌결합이면 그냥 넣기
			}

			operatorStack.push(rule);
		}
		// 숫자
		else
		{
			expr.Push(ExpressionItem::MakeNumberItem(token));
		}
	}

	while (!operatorStack.empty())
	{
		expr.Push(ExpressionItem::MakeOperatorItem(operatorStack.top().function));
		operatorStack.pop();
	}

	return expr;
}

