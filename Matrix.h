#ifndef GSS_MATRIX_H
#define GSS_MATRIX_H

#include <vector>
namespace gss
{
	template<typename T,size_t rows=2,size_t cols=2>
	class Matrix
	{
	public:
		std::vector<std::vector<T>> _matrix;

	public:
		Matrix(){
			for (int i = 0; i < rows; ++i)
			{
				std::vector<T> temp(cols, 0);
				if (i < cols)
					temp[i] = 1.0;
				_matrix.push_back(temp);
			}
		}

		//µ¥Î»¾ØÕó
		static Matrix<T,rows,cols> getIdentity()
		{
			Matrix<T, rows, cols> ret;
			for (int i = 0; i < rows; ++i)
			{
				std::vector<T> temp(cols, 0);
				if (i < cols)
					temp[i] = 1.0;
				ret._matrix.push_back(temp);
			}
			return ret;
		}

		void set(int x, int y, T t)
		{
			_matrix[x][y] = t;
		}

		T get(int x, int y) const
		{
			return _matrix[x][y];
		}

		template<size_t cols2>
		Matrix<T, rows, cols2> operator*(const Matrix<T, cols, cols2>& right)
		{
			Matrix<T, rows, cols2> ret;
			for (int i = 0; i < rows; ++i)
			{
				for (int j = 0; j < cols2; ++j)
				{
					ret._matrix[i][j] = 0;
					for (int k = 0; k < cols; ++k)
					{
						ret._matrix[i][j] += this->_matrix[i][k] * right._matrix[k][j];
					}
				}
			}
			return ret;
		}
	};
}

#endif