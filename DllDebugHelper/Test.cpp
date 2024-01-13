#include <iostream>
#include "SigmaMathLibrary.h"
#include "SigmaComplexNumber.h"
#include "SigmaFraction.h"
#include "SigmaMatrix.h"
int main(void)
{
	
	//std::cout << SigmaMath::IsNearlyEqual(1.0, 2.0) << std::endl;
	SigmaMath::ComplexNumber<double> a(1.0, 2.0);
	SigmaMath::ComplexNumber<double> a1(1.0, -2.0);

	SigmaMath::ComplexNumber<int> b(5, 12);
	SigmaMath::ComplexNumber<int> c;
	c = 1;

	SigmaMath::Fraction f(1, 2);
	SigmaMath::Fraction f2(1, 2);
	
	SigmaMath::Matrix<int, 2, 2> M = { {1, 2}, {2, 3} };
	//SigmaMath::Vector2dd V ;

	try
	{
		SigmaMath::Matrix3d M1 = { {1, 0, -2}, {0, 3, -1}, {-1, 2, 1} };
		SigmaMath::Matrix3d M2 = { {1, 0, 0}, {0, -1, 0}, {0, 0, 0} };
		SigmaMath::Matrix3d M3 = { {-5, 4, -6}, {-1, 1, -1}, {-3, 2, -3} };


		SigmaMath::Matrix3d M4 = { {1, 1, 1}, {2, -1, 3}, {4,1,9} };
		SigmaMath::Vector3dd V1 = { {1}, {-2}, {4} };
		//std::cout << M4 * V1 << std::endl;
		std::cout << SigmaMath::pow(M3, -1) << std::endl;
		//std::cout << V1.transport() << std::endl;
		//std::cout << M1.submatrix(M1, 1, 0) << std::endl;
		//std::cout << M1.inverse() << std::endl;
		//std::cout << M1*M1.inverse() << std::endl;


	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	//SigmaMath::Matrix2d M = it;

	//std::cout << SigmaMath::pow<SigmaMath::Fraction>(f, 10) << std::endl;
	//SigmaMath::Fraction::Reduction(f, f2);
	//std::cout << 2 * f;
	//std::cout << f << std::endl;
	//std::cout << SigmaMath::pow<SigmaMath::ComplexNumber<int>>(b, 100) << std::endl;
	//std::cout << SigmaMath::pow<double>(2, -2) << std::endl;
	return 0;
}
