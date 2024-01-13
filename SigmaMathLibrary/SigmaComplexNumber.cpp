#include "pch.h"
#include <utility>
#include <limits.h>
#include <iostream>
#include "SigmaMathLibrary.h"
#include "SigmaComplexNumber.h"


SigmaMath::ComplexNumber<double>* ComplexNumberClass(double real, double imaginary)
{
	return new SigmaMath::ComplexNumber<double>(real, imaginary);
}

SigmaMath::ComplexNumber<double>* pow_Complex(SigmaMath::ComplexNumber<double>* C, int n)
{
	return new SigmaMath::ComplexNumber<double>(SigmaMath::pow<SigmaMath::ComplexNumber<double>>(*C, n));
}

