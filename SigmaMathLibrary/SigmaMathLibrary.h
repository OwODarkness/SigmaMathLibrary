/*****************************************************************
 * \file   SigmaMathLibrary.h
 * \brief  
 * 
 * \author OwODarkness
 * \date   April 2023
 *********************************************************************/
#ifndef  SIGMA_MATH_LIBRARY_H
#define SIGMA_MATH_LIBRARY_H


#ifdef SIGMAMATHLIBRARY_EXPORTS
#define SIGMAMATHLIBRARY_API __declspec(dllexport)
#else
#define SIGMAMATHLIBRARY_API __declspec(dllimport)
#endif



namespace SigmaMath{

	extern"C" 
	{
		/**
		* .判断两个数是否相等
		* parma error 误差值
		*/
		SIGMAMATHLIBRARY_API bool IsNearlyEqual(double a, double b, double error = 1e-6);
	}

	//extern "C"
	
		/**
		 * .最大公约数
		 */
	extern "C"
	{
		SIGMAMATHLIBRARY_API int GCD(int a, int b);
	}

		/**
		 * 最小公倍数.
		 */
	extern "C"
	{
		SIGMAMATHLIBRARY_API int LCM(int a, int b);
	}
	
	extern "C"
	{
		SIGMAMATHLIBRARY_API int Round(double a);
	}

	//幂次
	template<typename T>
	SIGMAMATHLIBRARY_API T pow(T C, int n);
	template<typename T>
	T pow(T x, int n)
	{
		if (n < 0)
		{
			try
			{
				x = 1.0 / x;
			}
			catch (const std::exception& e)
			{
				std::cout << e.what() << std::endl;
			}
			n = -1 * n;
		}
		T ans = 1;
		while (n)
		{
			if (n & 1)
			{
				ans = ans * x;
			}
			n >>= 1;
			x = x * x;
		}
		return ans;
	}



	extern"C"
	{
		SIGMAMATHLIBRARY_API int Pow_Integer(int x, int n);

		SIGMAMATHLIBRARY_API double Pow_double(double x, int n);
		
	}



}

#endif