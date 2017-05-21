#ifndef GSS_FIBONACCI_H
#define GSS_FIBONACCI_H

/*
	쳲�������Fibonacci������
	1���ݹ�
	2�����ƹ�ϵʽ���Ż����ռ任ʱ�䣩��ʱ�临�Ӷ� O(N)���ռ临�Ӷ� O(N)
	3�����ͨ�ʽ���޷���֤������ȣ���ʱ�临�Ӷ� O(1)
	4�����β��ԣ�ʱ�临�Ӷ� O��logN)
		Fibonacci�����Ƕ��׵������У����Դ���һ��2*2�ľ���A��ʹ�� �� F(n)	F(n-1) ) = ( F(n-1)	 F(n-2) )*A
		��⣬�ɵã�A = { { 1,1 } ,{ 1,0 } }
		��
			( F(n)	F(n-1) ) = ( F(n-1)  F(n-2) )*A = ( F(n-2)  F(n-3) )*A^2 = ... = ( F(1)  F(0) )*A^(n-1)
		ʣ�µ��������������A�ķ��ݡ�
*/
#include "Matrix.h"
namespace gss
{
	/*
		T Ϊ��ֵ���ͣ��� int,long long,float,double�ȣ�ֻ��Ϊ�˲�ͬ��ȡֵ��Χ��ѡ��ͬ������
		ͬʱĳЩ���͵ķ���ֵ��ʽҲ��Ҫ��������
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