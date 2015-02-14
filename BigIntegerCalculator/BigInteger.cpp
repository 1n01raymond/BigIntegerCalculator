#include "BigInteger.h"

#include <sstream>
#include <cassert>

BigInteger::BigInteger(const int value)
	:m_Negative(value < 0)
{
	std::stringstream ss;

	if (m_Negative)
		ss << -value;
	else
		ss << value;
	m_Data = ss.str();

	std::reverse(m_Data.begin(), m_Data.end());
}

BigInteger::BigInteger(const std::string value)
	:m_Data(value), m_Negative(value[0] == '-')
{
	if (m_Negative)
		m_Data = m_Data.substr(1);

	std::reverse(m_Data.begin(), m_Data.end());

	TrimZero();
}

const BigInteger BigInteger::operator - () const
{
	BigInteger out = *this;
	out.m_Negative = !m_Negative;
	return out;
}

const BigInteger operator +(const BigInteger& a, const BigInteger& b)
{
	std::string resultData;
	int carry = 0;
	for (size_t i = 0; i < a.m_Data.length() || i < b.m_Data.length(); ++i)
	{
		int digitA = i < a.m_Data.length() ? a.m_Data[i] - '0' : 0;
		int digitB = i < b.m_Data.length() ? b.m_Data[i] - '0' : 0;

		if (a.m_Negative) digitA = -digitA;
		if (b.m_Negative) digitB = -digitB;

		int digitSum = digitA + digitB + carry;

		// 음수인 경우 == 음수인 10의 자리 + 양수인 1의 자리
		// ex) -7 -> -10 + 3
		// ex) -16 -> -20 + 4
		// ex) -10 -> -10 + 0
		if (digitSum < 0)
		{
			resultData += static_cast<char>((digitSum + 20) % 10 + '0');
			carry = (digitSum - 9) / 10;
		}
		else
		{
			resultData += static_cast<char>(digitSum % 10 + '0');
			carry = digitSum / 10;
		}
	}

	BigInteger result;
	if (carry < 0)
	{
		/*
			ex)
			-20000000
			+ 1234567
			==
			-10000000
			- 9999999
			+ 1234567
			-       1
			9의 보수를 구하고 1을 더한다.
			더하는 이유는, 음수에 -1을 더하기 때문에 절댓값으로 보면 양수 + 1
		*/

		result.m_Negative = true;
		for (char& ch : resultData)
			ch = 9 - (ch - '0') + '0';
		resultData += static_cast<char>(-(carry + 1) + '0');
	}
	else if (carry > 0)
	{
		resultData += static_cast<char>(carry + '0');
	}
	result.m_Data = resultData;

	if (carry < 0)
		result.AddOne();

	result.TrimZero();

	return result;
}

const BigInteger operator -(const BigInteger& a, const BigInteger& b)
{
	return a + -b;
}

const BigInteger operator *(const BigInteger& a, const BigInteger& b)
{
	BigInteger result;
	for (size_t i = 0; i < b.m_Data.length(); ++i)
	{
		if (i > 0)
			result.ShiftLeft();

		char ch = b.m_Data[b.m_Data.length() - i - 1];
		if (ch == '0')
			continue;

		BigInteger middleResult = a;
		middleResult.m_Negative = false;
		middleResult.MultiplyByOneDigit(ch - '0');

		result = result + middleResult;
	}
	result.m_Negative = a.m_Negative != b.m_Negative;
	return result;
}

const BigInteger operator %(const BigInteger& a, const BigInteger& b)
{
	if (b.IsZero())
		throw "Divide by zero";

	BigInteger result = a;
	BigInteger remover = b;

	result.m_Negative = false;
	remover.m_Negative = false;

	int shiftTimes = a.m_Data.length() - b.m_Data.length();
	shiftTimes = shiftTimes < 0 ? 0 : shiftTimes;

	for (int i = 0; i < shiftTimes; ++i)
		remover.ShiftLeft();

	while (true)
	{
		if (result >= remover)
		{
			result = result - remover;
		}
		else if (shiftTimes > 0)
		{
			remover.ShiftRight();
			--shiftTimes;
		}
		else
			break;
	}

	result.m_Negative = a.m_Negative;

	return result;
}

const BigInteger BigInteger::Power(const BigInteger& other) const
{
	BigInteger result = 1;
	BigInteger base = *this;
	BigInteger exp = other;
	
	while (!exp.IsZero())
	{
		if (exp % 2 == 1)
			result = result * base;

		base = base * base;

		exp.DivideByOneDigit(2);
	}

	return result;
}


bool operator <(const BigInteger& a, const BigInteger& b)
{
	return (a - b).m_Negative;
}

bool operator <=(const BigInteger& a, const BigInteger& b)
{
	return !(a > b);
}

bool operator >(const BigInteger& a, const BigInteger& b)
{
	return !(a - b).m_Negative;
}

bool operator >=(const BigInteger& a, const BigInteger& b)
{
	return !(a < b);
}

bool operator ==(const BigInteger& a, const BigInteger& b)
{
	return (a - b).IsZero();
}



std::string BigInteger::AsString() const
{
	std::string str = m_Data;
	std::reverse(str.begin(), str.end());
	if (m_Negative)
		str = '-' + str;
	return str;
}


bool BigInteger::IsZero() const
{
	return m_Data == "0";
}

bool BigInteger::IsNegative() const
{
	return m_Negative;
}


void BigInteger::MultiplyByOneDigit(const int value)
{
	assert(value < 10 && value >= 0);
	int carry = 0;
	for (char& ch : m_Data)
	{
		int digit = ch - '0';
		digit = digit * value + carry;
		carry = digit / 10;
		ch = digit % 10 + '0';
	}
	if (carry > 0)
		m_Data += static_cast<char>(carry + '0');
	TrimZero();
}

void BigInteger::DivideByOneDigit(const int value)
{
	assert(value < 10 && value >= 0);
	if (value == 0)
		throw "Divide by zero";
	std::string quotient;
	int divisor = 0;
	for (size_t i = 0; i < m_Data.length(); ++i)
	{
		divisor *= 10;
		divisor += m_Data[m_Data.length() - i - 1] - '0';
		quotient = static_cast<char>(divisor / value + '0') + quotient;
		divisor %= value;
	}
	m_Data = quotient;
	TrimZero();
}

void BigInteger::TrimZero()
{
	int realLength = m_Data.length();
	for (; realLength > 1; --realLength)
	{
		if (m_Data[realLength - 1] != '0')
			break;
	}
	m_Data = m_Data.substr(0, realLength);

	if (realLength == 1 && m_Data[0] == '0')
		m_Negative = false;
}

void BigInteger::AddOne()
{
	bool carry = false;
	for (char& ch : m_Data)
	{
		carry = ch == '9';
		ch = (ch - '0' + 1) % 10 + '0';
		if (!carry)
			break;
	}
}

void BigInteger::ShiftLeft()
{
	m_Data = "0" + m_Data;
}

void BigInteger::ShiftRight()
{
	m_Data = m_Data.substr(1);
}
