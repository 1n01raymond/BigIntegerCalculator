#include <iostream>

#include "Calculator.h"
#include "BigInteger.h"

void main(const int argc, const char* const * const argv)
{
	Calculator calc;

//	auto result = calc.Calculate("7**10+6**5");
	auto result = calc.Calculate(argv[1]);

	std::cout << result.AsString() << std::endl;
	return;
}