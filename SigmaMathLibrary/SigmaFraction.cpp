#include "pch.h"
#include <utility>
#include <limits.h>
#include <iostream>
#include <cmath>
#include "SigmaMathLibrary.h"
#include "SigmaFraction.h"

SigmaMath::Fraction::Fraction(const Fraction& F1)
{
	this->numerator = F1.numerator;
	this->denominator = F1.denominator;
}

SigmaMath::Fraction::Fraction(int n)
{
	this->numerator = n;
	this->denominator = 1;
}

SigmaMath::Fraction& SigmaMath::Fraction::Simplify()
{
	int num = std::abs(SigmaMath::GCD(this->numerator, this->denominator));
	this->numerator = this->numerator / num;
	this->denominator = this->denominator / num;
	return *this;
}

void SigmaMath::Fraction::Reduction(Fraction& a, Fraction& b)
{
	int bottom = SigmaMath::LCM(a.denominator, b.denominator);
	a.numerator = a.numerator * bottom / a.denominator;
	b.numerator = b.numerator * bottom / b.denominator;
	a.denominator = b.denominator = bottom;

}

SigmaMath::Fraction SigmaMath::Fraction::operator+(Fraction& F2)
{
	{
		Reduction(*this, F2);
		int numerator_value = this->numerator + F2.numerator;
		return Fraction(numerator_value, this->denominator).Simplify();
	}
}

SigmaMath::Fraction SigmaMath::Fraction::operator+(int n)
{
	int numerator_value = n * this->denominator + this->numerator;
	int denominator_value = this->denominator;
	return Fraction(numerator_value, denominator_value).Simplify();
}

SigmaMath::Fraction SigmaMath::Fraction::operator-(Fraction& F2)
{
	Reduction(*this, F2);
	int numerator_value = this->numerator - F2.numerator;
	return Fraction(numerator_value, this->denominator).Simplify();
}

SigmaMath::Fraction SigmaMath::Fraction::operator-(int n)
{
	int numerator_value = this->numerator - n * this->denominator;
	int denominator_value = this->denominator;
	return Fraction(numerator_value, denominator_value).Simplify();
}

SigmaMath::Fraction SigmaMath::Fraction::operator*(Fraction& F2)
{
	int numerator_value = this->numerator * F2.numerator;
	int denominator_value = this->denominator * F2.denominator;
	return Fraction(numerator_value, denominator_value).Simplify();
}

SigmaMath::Fraction SigmaMath::Fraction::operator*(int n)
{
	int numerator_value = this->numerator * n;
	int denominator_value = this->denominator;
	return Fraction(numerator_value, denominator_value).Simplify();
}

SigmaMath::Fraction SigmaMath::Fraction::operator/(Fraction& F2)
{
	int numerator_value = this->numerator * F2.denominator;
	int denominator_value = this->denominator * F2.numerator;
	return Fraction(numerator_value, denominator_value).Simplify();
}

SigmaMath::Fraction SigmaMath::Fraction::operator/(int n)
{
	int numerator_value = this->numerator;
	int denominator_value = this->denominator / n;
	return Fraction(numerator_value, denominator_value).Simplify();
}

SigmaMath::Fraction& SigmaMath::Fraction::operator=(int n)
{
	this->numerator = n;
	this->denominator = 1;
	return *this;
}
