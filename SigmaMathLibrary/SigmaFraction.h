/*****************************************************************
 * \file   SigmaFraction.h
 * \brief  分数
 * 
 * \author Lenovo
 * \date   April 2023
 ******************************************************************/

#ifndef  SIGMA_FRACTION_H
#define SIGMA__FRACTION_H

#define SIGMAFRACTION_EXPORTS
#define SIGMAFRACTION_API __declspec(dllexport)
#else
#define SIGMAFRACTION_API __declspec(dllimport)
#endif

namespace SigmaMath {
	class SIGMAFRACTION_API Fraction {
	public:
		explicit Fraction(int numerator_value, int denominator_value) :numerator(numerator_value), denominator(denominator_value) {};

		Fraction(const Fraction& F1);
		
		Fraction(int n);
		
		//化简
		Fraction& Simplify();
		//通分
		static void Reduction(Fraction& a, Fraction& b);
		
		friend std::ostream& operator<<(std::ostream& out, const Fraction& F);
		// Fraction + Fraction
		Fraction operator+(Fraction& F2);
		//Fraction + n
		Fraction operator+(int n);
		//n + Fraction
		friend Fraction operator+(int n, const Fraction& F);
		//Fraction - Fraction
		Fraction operator-(Fraction& F2);
		//Fraction - n
		Fraction operator-(int n);
		//n - Fraction
		friend  Fraction operator-(int n, const Fraction& F);
		//Fraction * Fraction
		Fraction operator*(Fraction& F2);
		//Fraction * n
		Fraction operator*(int n);
		//n * Fraction 
		friend Fraction operator*(int n, const Fraction& F);
		//Fraction / Fraction
		Fraction operator/(Fraction& F2);
		//Fraction / n
		Fraction operator/(int n);
		//n / Fraction 
		friend Fraction operator/(int n, const Fraction& F);
		Fraction& operator=(int n);

		private:
		int numerator;//分子
		int denominator;//分母
	};
	std::ostream& operator<<(std::ostream& out, const Fraction & F)
	{
		out << F.numerator << "/" << F.denominator;
		return out;
	}

	Fraction operator+(int n, const Fraction& F)
	{
		int numerator_value = n * F.denominator + F.numerator;
		int denominator_value = F.denominator;
		return Fraction(numerator_value, denominator_value).Simplify();
	}

	Fraction operator-(int n, const Fraction& F)
	{
		int numerator_value = n * F.denominator - F.numerator;
		int denominator_value = F.denominator;
		return Fraction(numerator_value, denominator_value).Simplify();
	}

	Fraction operator*(int n, const Fraction& F)
	{
		int numerator_value = n * F.numerator;
		int denominator_value = F.denominator;
		return Fraction(numerator_value, denominator_value).Simplify();
	}

	Fraction operator/(int  n, const Fraction& F)
	{
		int numerator_value = n * F.denominator;
		int denominator_value = F.numerator;
		return Fraction(numerator_value, denominator_value).Simplify();
	}
};





