/*****************************************************************
 * \file   SigmaComplexNumber.h
 * \brief  复数
 *
 * \author OwODarkness
 * \date   April 2023
 *********************************************************************/
#ifndef SIGMA_COMPLEX_NUMBER_H
#define SIGMA_COMPLEX_NUMBER_H


#ifdef SIGMACOMPLEXNUMBER_EXPORTS
#define SIGMA_COMPLEX_NUMBER_API __declspec(dllexport)
#define SIGMA_COMPLEX_NUMBER_TEMPLATE __declspec(dllexport)
#else
#define SIGMA_COMPLEX_NUMBER_API __declspec(dllimport)
#define SIGMA_COMPLEX_NUMBER_TEMPLATE 
#endif



namespace SigmaMath {
	template<typename T>
	using RealValidType = std::enable_if_t<std::is_convertible<T, double>::value >;
	template<typename T, typename = RealValidType<T>>
	class SIGMA_COMPLEX_NUMBER_TEMPLATE ComplexNumber {
	public:
		ComplexNumber() :real(0.0), imaginary(0.0), size(0.0) {};
		ComplexNumber(T real_number, T imaginary_number) :real(real_number), imaginary(imaginary_number) 
		{
			size = std::sqrt(real_number * real_number + imaginary * imaginary);
		};

		ComplexNumber(const ComplexNumber& C)
		{
			real = C.real;
			imaginary = C.imaginary;
			size = C.size;
		}
		ComplexNumber(double real_num)
		{
			this->real = real_num;
			this->imaginary = 0.0;
			size = std::fabs(real_num);
		}
		//Complex_Number + Complex_Number
		template<typename U>
		ComplexNumber<T> operator+(const ComplexNumber<U>& C1)
		{
			T real_num = this->real + (T)C1.real;
			T imaginary_num = this->imaginary + (T)C1.imaginary;
			return ComplexNumber<T>(real_num, imaginary_num);
		}
		//Complex_Number + Real_Number
		ComplexNumber<T> operator+(double real_number)
		{
			T real_num = this->real + (T)real_number;
			T imaginary_num = this->imaginary;
			return ComplexNumber<T>(real_num, imaginary_num);
		}
		//Complex_Number - Complex_Number
		template<typename U>
		ComplexNumber<T> operator-(const ComplexNumber<U>& C1)
		{
			T real_num = this->real - (T)C1.real;
			T imaginary_num = this->imaginary - (T)C1.imaginary;
			return ComplexNumber<T>(real_num, imaginary_num);
		}
		//Complex_Number - Real_Number
		ComplexNumber<T> operator-(double real_number)
		{
			T real_num = this->real - (T)real_number;
			T imaginary_num = this->imaginary;
			return ComplexNumber<T>(real_num, imaginary_num);
		}
		//Real_Number - Complex_Number 
		template<typename U>
		friend ComplexNumber<U> operator-(double real_number, const ComplexNumber<U>& C);
		//Complex_Number*Complex_Number
		template<typename U>
		ComplexNumber<T> operator*(const ComplexNumber<U>& C1)
		{
			//(a+bi)(c+di) = (ac - bd) + (bc + ad)i
			T real_num = this->real * (T)C1.real - this->imaginary*(T)C1.imaginary;
			T imaginary_num = this->imaginary* (T)C1.real + this->real * (T)C1.imaginary;
			return ComplexNumber<T>(real_num, imaginary_num);
		}
		//Complex_Number * Real_Number
		ComplexNumber<T> operator*(double real_number)
		{
			T real_num = this->real * (T)real_number;
			T imaginary_num = this->imaginary * (T)real_number;
			return ComplexNumber<T>(real_num, imaginary_num);
		}
		//Real_Number * Complex_Number
		template<typename U>
		friend ComplexNumber<U> operator*(double real_number, const ComplexNumber<U>& C);
		//Complex_Number / Complex_Number
		template<typename U>
		ComplexNumber<T> operator/(const ComplexNumber<U>& C1)
		{
			T bottom = (T)C1.real * (T)C1.real + (T)C1.imaginary * (T)C1.imaginary;
			T real_num = (this->real * (T)C1.real + this->imaginary * (T)C1.imaginary) / bottom;
			T imaginary_num = (this->imaginary * (T)C1.real - this->real * (T)C1.imaginary) / bottom;
			return ComplexNumber<T>(real_num, imaginary_num);
		}
		ComplexNumber<T> operator/(double real_number)
		{
			return  *this/ ComplexNumber<double>(real_number, 0.0);
		}
		template<typename U>
		friend ComplexNumber<U> operator/(double, const ComplexNumber<U>& C);

		template<typename U>
		friend std::ostream& operator<<(std::ostream& out, const ComplexNumber<U>& C);

		ComplexNumber<T>& operator=(double a)
		{
			this->real = a;
			return *this;
		}

		ComplexNumber<T> getConjugateComplex()
		{
			return ComplexNumber<T>(this->real, -1 * this->imaginary);
		}



		T real;//实数
		T imaginary;//虚数
		T size;//模
		~ComplexNumber() {};
	};
	template<typename U>
	std::ostream& operator<< (std::ostream& out, const SigmaMath::ComplexNumber<U>& C)
	{
		if (C.real == 0 && C.imaginary != 0)
		{
			if (C.imaginary == 1 || C.imaginary == -1)
			{
				out << ((C.imaginary > 0) ? "i" : "-i");
			}
			else
			{
				out << C.imaginary << "i";
			}
		}
		else if (C.imaginary == 0)
		{
			out << C.real;
		}
		else
		{
			if (C.imaginary == 1 || C.imaginary == -1)
			{
				out << C.real  << ((C.imaginary > 0) ? "+i" : "-i");
			}
			else
			{
				out << C.real << ((C.imaginary>0) ? "+":"") << C.imaginary << "i";
			}
		}
		return out;
	}
	template<typename U>
	ComplexNumber<U> operator-(double real_number, const ComplexNumber<U>& C)
	{
		U real_num = (U)real_number - C.real;
		U imaginary_num = -1*C.imaginary;
		return ComplexNumber<U>(real_num, imaginary_num);
	}
	template<typename U>
	ComplexNumber<U> operator*(double real_number, const ComplexNumber<U>& C)
	{
		U real_num = C.real * (U)real_number;
		U imaginary_num = C.imaginary * (U)real_number;
		return ComplexNumber<U>(real_num, imaginary_num);
	}
	template<typename U>
	ComplexNumber<U> operator/(double real_number, const ComplexNumber<U>& C)
	{
		return ComplexNumber<U>(real_number, 0.0) / C;
	}

	template<typename T1, typename T2>
	static bool isConjugate(const ComplexNumber<T1>& C1, const ComplexNumber<T2>& C2)
	{
		return (C1.real == C2.real) && (C1.imaginary + C2.imaginary) == 0;
	}
};

extern "C"
{
	SIGMA_COMPLEX_NUMBER_API SigmaMath::ComplexNumber<double>* ComplexNumberClass(double real, double imaginary);

	SIGMA_COMPLEX_NUMBER_API SigmaMath::ComplexNumber<double>* pow_Complex(SigmaMath::ComplexNumber<double>* C, int n);
}

#endif