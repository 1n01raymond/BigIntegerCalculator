#pragma once

#include <string>
#include <list>

#include "typedef.h"

class Tokenizer
{
public:
	Tokenizer();
	Tokenizer& AddTokenRule(const std::string& token);

	TokenList Tokenize(const std::string& expression);

private:
	std::list<std::string> m_TokenRules;

};