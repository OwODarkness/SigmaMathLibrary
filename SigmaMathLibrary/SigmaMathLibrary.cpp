#include "pch.h"
#include <utility>
#include <limits.h>
#include <cmath>
#include <iostream>
#include "SigmaMathLibrary.h"

bool SigmaMath::IsNearlyEqual(double a, double b, double error)
{
	return fabs(a-b) <= error;
}

int SigmaMath::GCD(int a, int b)
{
		if (b == 0)
		{
			return a;
		}
		return GCD(b, a % b);
}

int  SigmaMath::LCM(int a, int b)
{
	return a * b / GCD(a, b);
}

int SigmaMath::Round(double a)
{
	return (int)(a + 0.5);
}

int SigmaMath::Pow_Integer(int x, int n)
{
	return SigmaMath::pow<int>(x, n);
}

double SigmaMath::Pow_double(double x, int n)
{
	return SigmaMath::pow<double>(x, n);

}




