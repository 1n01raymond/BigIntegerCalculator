#pragma once

#include <list>
#include <memory>
#include <functional>

typedef std::list<std::string> TokenList;

class BigInteger;
typedef std::function<BigInteger(const BigInteger&, const BigInteger&)> OperatorFunction;

