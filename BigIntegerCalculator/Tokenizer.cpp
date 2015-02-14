#include "Tokenizer.h"

Tokenizer::Tokenizer()
{

}

Tokenizer& Tokenizer::AddTokenRule(const std::string& token)
{
	auto it = m_TokenRules.begin();
	for (; it != m_TokenRules.end(); ++it)
	{
		if (token.length() >= it->length())
			break;
	}
	m_TokenRules.insert(it, token);

	return *this;
}


TokenList Tokenizer::Tokenize(const std::string& expression)
{
	TokenList tokenList;
	std::string buf;

	for (size_t i = 0; i < expression.length(); )
	{
		if (expression[i] == ' ')
			continue;

		bool metToken = false;
		for (auto rule : m_TokenRules)
		{
			if (rule == expression.substr(i, rule.length()))
			{
				metToken = true;
				if (!buf.empty())
				{
					tokenList.push_back(buf);
					buf.clear();
				}
				tokenList.push_back(rule);
				i += rule.length();
				break;
			}
		}

		if (!metToken)
		{
			buf += expression[i++];
		}
	}

	if (!buf.empty())
	{
		tokenList.push_back(buf);
		buf.clear();
	}

	return tokenList;
}
