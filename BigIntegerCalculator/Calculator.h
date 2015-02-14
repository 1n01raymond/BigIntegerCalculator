#pragma once

#include <string>

#include "Tokenizer.h"
#include "ExpressionBuilder.h"

class Calculator
{
public:
	Calculator();
	BigInteger Calculate(const std::string& expression);

private:
	Tokenizer m_Tokenizer;
	ExpressionBuilder m_ExprBuilder;
};