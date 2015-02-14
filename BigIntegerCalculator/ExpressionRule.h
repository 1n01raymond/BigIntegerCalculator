#pragma once

#include <string>
#include <functional>

#include "typedef.h"

struct ExpressionRule
{
	enum Direction
	{
		RIGHT
		, LEFT
	};

	ExpressionRule()
		:priority(0), direction(RIGHT)
	{}

	ExpressionRule(const std::string& str, const int priority, const Direction direction, const OperatorFunction& function)
		:str(str), priority(priority), direction(direction), function(function)
	{}

	ExpressionRule(const ExpressionRule& other)
		:str(other.str), priority(other.priority), direction(other.direction), function(other.function)
	{}

	ExpressionRule& operator =(const ExpressionRule& other)
	{
		str = other.str;
		priority = other.priority;
		direction = other.direction;
		function = other.function;
		return *this;
	}

	std::string str;
	int priority;
	Direction direction;
	OperatorFunction function;
};