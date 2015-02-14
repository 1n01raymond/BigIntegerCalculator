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
		// ������
		auto it = m_ExprRuleMap.find(token);
		if (it != m_ExprRuleMap.end())
		{
			auto& rule = it->second;

			// �������� �켱���� ���� ������
			// �ڽź��� ���ų� ���� �����ڸ� ���� ������ �̱�
			while (!operatorStack.empty()
				&& operatorStack.top().priority > rule.priority)
			{
				expr.Push(ExpressionItem::MakeOperatorItem(operatorStack.top().function));
				operatorStack.pop();
			}

			// �������� �켱���� ���� �����ڴ� �׳� ����
			// �������� �켱���� ���� �����ڴ�
			if (!operatorStack.empty()
				&& operatorStack.top().priority == rule.priority)
			{
				// ������̸� �̰� �ֱ�
				if (rule.direction == ExpressionRule::RIGHT)
				{
					expr.Push(ExpressionItem::MakeOperatorItem(operatorStack.top().function));
					operatorStack.pop();
				}
				// �°����̸� �׳� �ֱ�
			}

			operatorStack.push(rule);
		}
		// ����
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

