//#include "RBT.h"
//#include "Heap.h"
//#include <vector>
//#include <iostream>
//#include <iomanip>
//#include "timing.h"
//#include "Fibonacci.h"
//#include "StringMatcher.h"
//#include "FloodAttack.h"
//
//#define SOURCE_TEST
//
////#define STRING_MATCHER_TEST
////#define FLOODATTACK_TEST
//
//template<typename T1, typename T2>
//void printT(T1& t)
//{
//	T1::iterator its;
//	for (its = t.begin(); its != t.end(); ++its)
//	{
//		T2::iterator it;
//		for (it = (*its).begin(); it != (*its).end(); ++it)
//		{
//			std::cout << *it << " ";
//		}
//		std::cout << std::endl;
//	}
//}
//
//template<typename T>
//void check(T num, std::vector<std::vector<T>> t)
//{
//	std::vector<std::vector<T>>::iterator its;
//	for (its = t.begin(); its != t.end(); ++its)
//	{
//		T sum = 0;
//		std::vector<T>::iterator it;
//		//std::cout << "num(" << num << ") == ";
//		for (it = (*its).begin(); it != (*its).end(); ++it)
//		{
//			sum += *it;
//			//std::cout << *it << " + ";
//		}
//		//std::cout << "\b\b\b    \n";
//
//		if (sum != num)
//		{
//			std::cout << "错误：num(" << num << ") != ";
//			for (it = (*its).begin(); it != (*its).end(); ++it)
//			{
//				sum += *it;
//				std::cout << *it << "+";
//			}
//			std::cout << "\b\n";
//			exit(0);
//		}
//	}
//}
//
///*
//求连续整数和等于 num 的序列
//*/
//std::vector<std::vector<long long>> solve(int num)
//{
//	bool isOdd = num % 2 == 1 ? true : false;
//
//	std::vector<std::vector<long long>> ret;
//	for (long long i = 3; i < num; ++i)
//	{
//		std::vector<long long> temp;
//		long long x = num / i;
//		long long y = num%i;
//
//		if (y == 0)
//		{
//			if (i % 2 == 1)
//			{
//				long long z = i / 2;
//				for (long m = -z; m <= z && m + x>0; ++m)
//				{
//					temp.push_back(m + x);
//				}
//				if (temp.size() == i)
//					ret.push_back(temp);
//			}
//		}
//		else
//		{
//			temp.push_back(x);
//			int step = 1;
//			while (y > 0)
//			{
//				temp.push_back(x + step);
//				y -= step;
//				++step;
//			}
//			if (y == 0 && temp.size() == i)
//				ret.push_back(temp);
//		}
//	}
//	return ret;
//}
//
//
//#include <iostream>
//
//using namespace std;
//
//int solve(int n, int cur)
//{
//	if (n < 0) return 0;
//	if (n == 0) return 1;
//	if (n == 1)
//	{
//		cin >> cur;
//		return 1;
//	}
//	int next;
//	int add_min;
//	
//	int i = 0;
//	for (i = 1; i < n;)
//	{
//		cin >> next;
//		++i;
//		if (cur < next)
//		{
//			add_min = 1;
//			break;
//		}
//		else if (cur>next)
//		{
//			add_min = -1;
//			break;
//		}
//	}
//	if (i == n)
//		return 1;
//	cur = next;
//
//	for (; i < n; ++i)
//	{
//		cin >> next;
//		if ((cur < next && (add_min < 0) || (cur > next && (add_min > 0))))
//		{
//			return 1+solve(n - i, next);
//		}
//		cur = next;
//	}
//	return 1;
//}
//
//#ifdef SOURCE_TEST
//
//#define MATCHER_NUM 4
//int main(int argc,char* argv[]){
//	gss::Timing t;
//
//#ifdef STRING_MATCHER_TEST
//	gss::StringMatcher* matchers[MATCHER_NUM];
//	int index_matchers = 0;
//	matchers[index_matchers++] = new gss::KMPMatcher();
//	matchers[index_matchers++] = new gss::HorspoolMatcher();
//	matchers[index_matchers++] = new gss::BoyerMooreMatcher();
//	matchers[index_matchers++] = new gss::SundayMatcher();
//
//	char *pattern = "abcdabd";
//	char *test = "bbc abcdab abcdabcdabde";
//
//	for (int i = 0; i < MATCHER_NUM; ++i)
//	{
//		t.start();
//		std::cout << matchers[i]->getName() << " : " << matchers[i]->matching(pattern, test) << "\n";
//		t.end();
//	}
//#endif
//
//#ifdef FLOODATTACK_TEST
//	FloodAttack fa;
//	fa.run(argc,argv);
//#endif
//
//	int n;
//	int ret = 1;
//	int cur;
//
//	int add_min;
//	cin >> n;
//	if (n<0)
//	{
//		cout << -1;
//		return 0;
//	}
//	if (n <= 1)
//	{
//		cout << n;
//		return 0;
//	}
//
//	cin >> cur;
//	ret = solve(n - 1, cur);
//	cout << ret;
//
//	return 0;
//}
//#endif

//============================================================


#include <iostream>

using namespace std;

int solve(int n)
{
	int nums[3];
	int changeIndex;
	int tempIndex;
	int index;
	int com_10 = INT_MIN;
	int ret = 0;





	return ret;
}

int main()
{
	int n, ret = 0;
	cin >> n;
	if (n <= 0)
	{
		cout << 0;
		return 0;
	}
	ret = solve(n);
	cout << ret;
	return 0;
}