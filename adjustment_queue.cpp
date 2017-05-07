////在幼儿园有n个小朋友排列为一个队伍，
////从左到右一个挨着一个编号为(0~n - 1)。
////其中有一些是男生，有一些是女生，
////男生用'B'表示，女生用'G'表示。
////小朋友们都很顽皮，当一个男生挨着的是女生的时候就会发生矛盾。
////作为幼儿园的老师，你需要让男生挨着女生或者女生挨着男生的情况最少。
////你只能在原队形上进行调整，每次调整只能让相邻的两个小朋友交换位置，
////现在需要尽快完成队伍调整，你需要计算出最少需要调整多少次可以让上述情况最少。
////例如：
////GGBBG->GGBGB->GGGBB
////这样就使之前的两处男女相邻变为一处相邻，需要调整队形2次
//
////===============================================
////输入描述:
////输入数据包括一个长度为n且只包含G和B的字符串.n不超过50.
////
////输出描述 :
////	 输出一个整数，表示最少需要的调整队伍的次数
//
////***********************************************
//// 输入例子 :
////GGBBG
////
////输出例子 :
////2
//
////测试用例:
////BGBGBGBGGGBBGBGBGG
////
////对应输出应该为 :
////33
//
////测试用例:
////BBGGGBGGBGBBGBBBBBBBGGGBBBBGBBBBBGBBBGBGBBGBG
////
////对应输出应该为 :
////208
//
//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//#include <iostream>
//#include <string>
//#include <vector>
//
//using namespace std;
//
//int min(int a, int b){
//	return a < b ? a : b;
//}
//
//int solve(char gbs[], int n, int start, int index, bool begin)
//{
//	int ret = 0;
//
//	if (begin)
//	{
//		for (int i = index + 1; i < n; i++)
//		{
//			if (gbs[start] == gbs[i])
//			{
//				/*char temp = gbs[i];
//				gbs[i] = gbs[leftIndex];
//				gbs[leftIndex] = temp;
//				cout << "== " << gbs << " leftIndex = " << leftIndex << "; i = " << i << endl;*/
//
//				ret += i - index;
//				index++;
//			}
//		}
//	}
//	else
//	{
//		for (int i = index - 1; i >= 0; i--)
//		{
//			if (gbs[start] == gbs[i])
//			{
//				/*char temp = gbs[i];
//				gbs[i] = gbs[rightIndex];
//				gbs[rightIndex] = temp;
//				cout << "== " << gbs << " rightIndex = " << rightIndex << "; i = " << i << endl;*/
//
//				ret += index - i;
//				index--;
//			}
//		}
//	}
//
//	return ret;
//}
//
//int main()
//{
//	char gbs[55];
//	
//	while (cin >> gbs)
//	{
//		int n = strlen(gbs);
//
//		if (n == 0 || n == 1){
//			cout << "0" << endl;
//			return 0;
//		}
//
//		int leftIndex = 0;
//		for (int i = 1; i < n; i++,leftIndex++)
//		{
//			if (gbs[leftIndex] != gbs[i])
//			{
//				break;
//			}
//		}
//		leftIndex++;
//
//		int rightIndex = n - 1;
//		for (int i = n - 2; i >= 0; i--,rightIndex--){
//			if (gbs[rightIndex] != gbs[i])
//			{
//				break;
//			}
//		}
//		rightIndex--;
//
//		int num1 = solve(gbs, n, 0, leftIndex, true);
//		int num2 = solve(gbs, n, leftIndex, 0, true);
//		int num3 = solve(gbs, n, n - 1, rightIndex, false);
//		int num4 = solve(gbs, n, rightIndex, n - 1, false);
//
//		cout << min(min(num1, num2), min(num3, num4)) << endl;
//
//		break;
//	}
//	return 0;
//}