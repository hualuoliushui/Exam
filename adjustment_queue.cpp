////���׶�԰��n��С��������Ϊһ�����飬
////������һ������һ�����Ϊ(0~n - 1)��
////������һЩ����������һЩ��Ů����
////������'B'��ʾ��Ů����'G'��ʾ��
////С�����Ƕ�����Ƥ����һ���������ŵ���Ů����ʱ��ͻᷢ��ì�ܡ�
////��Ϊ�׶�԰����ʦ������Ҫ����������Ů������Ů������������������١�
////��ֻ����ԭ�����Ͻ��е�����ÿ�ε���ֻ�������ڵ�����С���ѽ���λ�ã�
////������Ҫ������ɶ������������Ҫ�����������Ҫ�������ٴο���������������١�
////���磺
////GGBBG->GGBGB->GGGBB
////������ʹ֮ǰ��������Ů���ڱ�Ϊһ�����ڣ���Ҫ��������2��
//
////===============================================
////��������:
////�������ݰ���һ������Ϊn��ֻ����G��B���ַ���.n������50.
////
////������� :
////	 ���һ����������ʾ������Ҫ�ĵ�������Ĵ���
//
////***********************************************
//// �������� :
////GGBBG
////
////������� :
////2
//
////��������:
////BGBGBGBGGGBBGBGBGG
////
////��Ӧ���Ӧ��Ϊ :
////33
//
////��������:
////BBGGGBGGBGBBGBBBBBBBGGGBBBBGBBBBBGBBBGBGBBGBG
////
////��Ӧ���Ӧ��Ϊ :
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