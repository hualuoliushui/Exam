#ifndef GSS_GCD_H
#define GSS_GCD_H
#include <iostream>
#include <vector>
#include <random>


//#define GSS_MAIN_GCD_TEST
#ifdef GSS_MAIN_GCD_TEST
#include "timing.h"
#endif

namespace gss{
	/*
		求 T 类型的最大公约数，
		T 必须为正整数，
		T 需提供 &、<、>>、<<、- 、== 等操作符
		T&1 必须返回 0 或 1
	*/
	template<typename T>
	class GreatestCommonDivisor{
	private:
		static bool isEven(T value){
			return !(value & 1);
		}
	public:
		static T solve(T x, T y){
			if (x < y)
				return solve(y, x);
			if (y == 0)
				return x;
			else{
				if (isEven(x)){
					if (isEven(y))
						return (solve(x >> 1, y >> 1) << 1);
					else
						return solve(x >> 1, y);
				}
				else{
					if (isEven(y))
						return solve(x, y >> 1);
					else
						return solve(y, x - y);
				}
			}
		}
	};
}
#endif

#ifdef GSS_MAIN_GCD_TEST
int main(){
	gss::Timing timing;

	timing.start();
	for (int i = 0; i < 100; ++i){
		gss::cout << i << std::endl;
	}
	timing.start();
	timing.end();
	timing.start();

	return 0;
}
#endif