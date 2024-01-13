/*****************************************************************
 * \file   SigmaMatrix.h
 * \brief  ¾ØÕó
 * 
 * \author Lenovo
 * \date   April 2023
 *********************************************************************/

#pragma once

#ifndef SIGMA_MATRIX_H
#define SIGMA_MATRIX_H

#include <array>
#include "SigmaCommonDefs.h"

#ifdef SIGMAMATRIX_EXPORTS
#define SIGMAMATRIX_API __declspec(dllexport)
#define SIGMAMATRIX_TEMPLATE __declspec(dllexport)
#else 
#define SIGMAMATRIX_API __declspec(dllimport)
#define SIGMAMATRIX_TEMPLATE 
#endif // !SIGMAMATRIX_EXPORTS


namespace SigmaMath {
	using INDEX = SigmaType::INDEX;
	template<typename T, int RowsAtCompileTime, int ColsAtCompileTime>
	class SIGMAMATRIX_TEMPLATE Matrix {
	private:
		std::array<std::array<T, ColsAtCompileTime>, RowsAtCompileTime> data;

	public:
		Matrix() = default;
		Matrix(T n)
		{
			if (RowsAtCompileTime != ColsAtCompileTime)
			{
				throw std::invalid_argument("The Matrix must be a square matrix");
			}
			T zero = (T)0;
			for (INDEX i = 0; i < rows(); i++)
			{
				for (INDEX j = 0; j < cols(); j++)
				{
					if (i == j)
					{
						data[i][j] = n;
					}
					else
					{
						data[i][j] = zero;
					}
				}
			}

		}
		Matrix(const std::initializer_list<std::initializer_list<T>>& input)
		{
			//±ß½ç¼ì²â
			if (input.size() != RowsAtCompileTime || input.begin()->size() != ColsAtCompileTime)
			{
				throw std::invalid_argument("size error, please check your rows and cols");
			}
			INDEX i = 0;
			for (const auto& item : input)
			{
				INDEX j = 0;
				for (const auto& item2 : item)
				{
					data[i][j] = item2;
					j++;
				}
				i++;
			}

		}
		Matrix(const Matrix& M) = default;
	public:

		template<typename U, int Rows, int Cols>
		friend std::ostream& operator<<(std::ostream& out, const Matrix<U, Rows, Cols>& M);

		Matrix operator+(const Matrix& M) const
		{
			Matrix res;
			for (INDEX i = 0; i < rows(); i++)
			{
				for (INDEX j = 0; j < cols(); j++)
				{
					res.data[i][j] = this->data[i][j] + M.data[i][j];
				}
			}
			return res;
		}

		Matrix operator+(T value) const
		{
			if (!IsSquareMatrix())
			{
				throw std::invalid_argument("The Matrix must be a square matrix");
			}
			Matrix M;
			for (INDEX i = 0; i < rows(); i++)
			{
				for (INDEX j = 0; j < cols(); j++)
				{
					if (i == j)
					{
						M.set(i, j, data[i][j] + value);
					}
					else
					{
						M.set(i, j, data[i][j]);
					}
				}
			}
			return M;
		}

		Matrix operator-(const Matrix& M) const
		{
			Matrix res;
			for (INDEX i = 0; i < rows(); i++)
			{
				for (INDEX j = 0; j < cols(); j++)
				{
					res.data[i][j] = this->data[i][j] - M.data[i][j];
				}
			}
			return res;
		}

		Matrix operator-(T value) const
		{
			if (!IsSquareMatrix())
			{
				throw std::invalid_argument("The Matrix must be a square matrix");
			}
			Matrix M;
			for (INDEX i = 0; i < rows(); i++)
			{
				for (INDEX j = 0; j < cols(); j++)
				{
					if (i == j)
					{
						M.set(i, j, data[i][j]-value);
					}
					else
					{
						M.set(i, j, data[i][j]);
					}
				}
			}	
		}

		template<INDEX ROWS, INDEX COLS>
		Matrix<T, RowsAtCompileTime, COLS> operator*(const Matrix<T, ROWS, COLS>& M)
		{
			Matrix<T, RowsAtCompileTime, COLS> res;
			for (INDEX i = 0; i < this->rows(); i++)
			{
				for (INDEX k = 0; k < COLS; k++)
				{
					T sum = (T)0;
					for (int j = 0; j < ROWS; j++)
					{
						sum += this->data[i][j] * M(j, k);
					}
					res.set(i, k, sum);
				}
			}
			return res;
		}

		Matrix operator*(T value)
		{
			Matrix M;
			for (INDEX i = 0; i < this->rows(); i++)
			{
				for (INDEX j = 0; j < M.cols(); j++)
				{
					M.set(i, j, value * data[i][j]);
				}
			}
			return  M;
		}

		template<typename U, INDEX ROWS, INDEX COLS>
		friend Matrix<U, ROWS, COLS> operator/(U value, const Matrix<U, ROWS, COLS>& M);

		Matrix& operator=(T n)
		{
			if (!IsSquareMatrix())
			{
				throw std::invalid_argument("The Matrix must be a square matrix");
			}
			for (INDEX i = 0; i < RowsAtCompileTime; i++)
			{
				data[i][i] += n;
			}
		}

		T operator()(INDEX i, INDEX j) const
		{
			return data[i][j];
		}

		//Óà×ÓÊ½
		template <INDEX N>
		Matrix<T, N - 1, N - 1> submatrix(const Matrix<T, N, N>& mat, INDEX row, INDEX col)  const{
			Matrix<T, N - 1, N - 1> sub_mat;
			int m = 0;
			int n = 0;
			for (INDEX i = 0; i < N; i++)
			{
				n = 0;
				for (INDEX j = 0; j < N; j++)
				{
					if (row != i && col != j)
					{
						sub_mat.set(m, n, mat(i, j));
						n++;
					}
				}
				if (n > 0)
				{
					m++;
				}
			}
			
			return sub_mat;
		}

		//ÐÐÁÐÊ½
		template <INDEX N>
		T determinant(const Matrix<T, N, N>& mat) const {
			T det = 0;

			if constexpr (N == 1) {
				det = mat(0, 0);
			}
			else if constexpr (N == 2) {
				det = mat(0, 0) * mat(1, 1) - mat(0, 1) * mat(1, 0);
			}
			else {
				for (INDEX col = 0; col < N; ++col) {
					Matrix<T, N - 1, N - 1> sub_mat = submatrix(mat, 0, col);
					T sub_det = determinant(sub_mat);
					T sign = (col % 2 == 0) ? 1 : -1;
					det += sign * mat(0, col) * sub_det;
				}
			}

			return det;
		}

		T determinant() const
		{
			return determinant(*this);
		}

		//×ªÖÃ¾ØÕó
		Matrix<T, ColsAtCompileTime, RowsAtCompileTime> transport() 
		{
			Matrix<T, ColsAtCompileTime, RowsAtCompileTime> M;
			for (int i = 0; i < RowsAtCompileTime; i++) {
				for (int j = 0; j < ColsAtCompileTime; j++) {
					M.set(j, i, data[i][j]);
				}
			}
			return M;
		}

		//°éËæ¾ØÕó
		template <INDEX N>
		Matrix adjoint(const Matrix<T, N, N>& mat) const
		{
			Matrix M;
			for (int i = 0; i < RowsAtCompileTime; i++)
			{
				for (int j = 0; j < ColsAtCompileTime; j++)
				{
					Matrix<T, N - 1, N - 1> sub_mat = submatrix(mat, j, i);
					M.set(i, j, (((i+j) % 2 == 0) ? 1 : -1)*sub_mat.determinant());
				}
			}
			return M;
		}

		//Äæ¾ØÕó
		Matrix inverse() const
		{
			return adjoint(*this) * (1.0/determinant());
		}
		//ÅÐ¶ÏÊÇ·ñÎª·½Õý
		bool IsSquareMatrix() const
		{
			return  rows() == cols();
		}

		void set(INDEX index_row, INDEX index_col, T value)
		{
			data[index_row][index_col] = value;
		}
		inline INDEX rows() const { return RowsAtCompileTime; }
		inline INDEX cols() const { return ColsAtCompileTime; }


	};
	typedef Matrix<double, 2, 1> Vector2dd;// 2*1 double
	typedef Matrix<float, 2, 1> Vector2df;// 2*1 float
	typedef Matrix<double, 3, 1> Vector3dd;// 3*1 double
	typedef Matrix<float, 3, 1> Vector3df;// 3*1 float
	typedef Matrix<double, 2, 2> Matrix2d;//2*2 double
	typedef Matrix<float, 2, 2> Matrix2f;//2*2 float
	typedef Matrix<double, 3, 3> Matrix3d;//3*3 double
	typedef Matrix<float, 3, 3> Matrix3f;//3*3 float
	typedef Matrix<double, 4, 4> Matrix4d;//4*4 double
	typedef Matrix<float, 4, 4> Matrix4f;//4*4 float

	template<typename U, int Rows, int Cols>
	std::ostream& operator<<(std::ostream& out, const Matrix<U, Rows, Cols>& M)
	{
		for (const auto& item : M.data)
		{
			for (const auto& item2 : item)
			{
				out << item2 << " ";
			}
			out << std::endl;
		}
		return out;
	}

	template<typename U, INDEX ROWS, INDEX COLS>
	Matrix<U, ROWS, COLS> operator/(U value, const Matrix<U, ROWS, COLS>& M)
	{
		return M.inverse()*value;
	}
}


#endif // DEBUG



