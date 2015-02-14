#pragma once

#include <string>

class BigInteger
{
public:
	BigInteger(const int value = 0);
	explicit BigInteger(const std::string value);

	const BigInteger operator -() const;
	friend const BigInteger operator +(const BigInteger& a, const BigInteger& b);
	friend const BigInteger operator -(const BigInteger& a, const BigInteger& b);
	friend const BigInteger operator *(const BigInteger& a, const BigInteger& b);
	friend const BigInteger operator %(const BigInteger& a, const BigInteger& b);

	const BigInteger Power(const BigInteger& other) const;

	friend bool operator <(const BigInteger& a, const BigInteger& b);
	friend bool operator <=(const BigInteger& a, const BigInteger& b);
	friend bool operator >(const BigInteger& a, const BigInteger& b);
	friend bool operator >=(const BigInteger& a, const BigInteger& b);
	friend bool operator ==(const BigInteger& a, const BigInteger& b);

	std::string AsString() const;

	bool IsZero() const;
	bool IsNegative() const;

private:
	void MultiplyByOneDigit(const int value);
	void DivideByOneDigit(const int value);
	void TrimZero();
	void AddOne();

	void ShiftLeft();
	void ShiftRight();

private:
	// index 0: 1의 자리, index 1: 10의 자리 ...
	std::string m_Data;
	bool m_Negative;
};