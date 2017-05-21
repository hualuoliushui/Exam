#ifndef GSS_FIBONACCI_H
#define GSS_FIBONACCI_H

/*
	斐波那契（Fibonacci）数列
	1、递归
	2、递推关系式的优化（空间换时间），时间复杂度 O(N)，空间复杂度 O(N)
	3、求解通项公式（无法保证结果精度），时间复杂度 O(1)
	4、分治策略，时间复杂度 O（logN)
		Fibonacci数列是二阶递推数列，所以存在一个2*2的矩阵A，使得 （ F(n)	F(n-1) ) = ( F(n-1)	 F(n-2) )*A
		求解，可得：A = { { 1,1 } ,{ 1,0 } }
		则：
			( F(n)	F(n-1) ) = ( F(n-1)  F(n-2) )*A = ( F(n-2)  F(n-3) )*A^2 = ... = ( F(1)  F(0) )*A^(n-1)
		剩下的问题就是求解矩阵A的方幂。
*/
#include "Matrix.h"
namespace gss
{
	/*
		T 为数值类型，如 int,long long,float,double等，只是为了不同的取值范围而选择不同的类型
		同时某些类型的返回值格式也需要额外设置
	*/
	template<typename T = int>
	class Fibonacci
	{
	private:
		Matrix<T> _matrixPow(const Matrix<T>& m, int n)
		{
			Matrix<T> ret = Matrix<T>::getIdentity();
			Matrix<T> temp = m;
			for (; n; n >>= 1)
			{
				if (n & 1)
					ret = ret * temp;
				temp = temp*temp;
			}
			return ret;
		}

		T F0 = 0;
		T F1 = 1;
		
	public:
		T get(int n)
		{
			if (n == 0)
				return F0;
			if (n == 1)
				return F1;

			Matrix<T> A;
			A.set(0, 0, 1);
			A.set(0, 1, 1);
			A.set(1, 0, 1);
			A.set(1, 1, 0);
			Matrix<T> An = _matrixPow(A, n - 1);
			
			Matrix<T,1,2> F10;
			F10.set(0, 0, F1);
			F10.set(0, 1, F0);

			Matrix<T, 1, 2> Fnn_1 = F10*An;

			return Fnn_1.get(0, 0);
		}

		std::vector<T> get(int start, int end)
		{
			std::vector<T> ret;

			if (start < 0 || end < 0)
				return ret;
			if (start > end)
			{
				int temp = start;
				start = end;
				end = temp;
			}
			else if (start == end)
			{
				ret.push_back(get(start));
				return ret;
			}

			T start_value = get(start);
			ret.push_back(start_value);
			T start_plus_1_value = get(start + 1);
			ret.push_back(start_plus_1_value);

			for (int index = start + 2; index <= end; ++index)
			{
				T temp = start_value + start_plus_1_value;
				ret.push_back(temp);

				start_value = start_plus_1_value;
				start_plus_1_value = temp;
			}
			return ret;
		}
	};

}

#endif