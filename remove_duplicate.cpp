////С����һ������Ϊn���У�
////С�����Ƴ���������ظ�Ԫ�أ�
////����С�����Ƕ���ÿ��Ԫ�ر��������ֵ��Ǹ���
////С������������, ϣ��������������
//
////==============================================
////�������� :
////����������У�
////��һ��Ϊ���г���n(1 �� n �� 50)
////�ڶ���Ϊn����sequence[i](1 �� sequence[i] �� 1000)���Կո�ָ�
////
////������� :
////��������ظ�Ԫ��֮������У��Կո�ָ�����ĩ�޿ո�
//
////**********************************************
////�������� :
////9
////100 100 100 99 99 99 100 100 100
////
////������� :
////	 99 100
//
//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//#include <iostream>
//#include <string>
//#include <vector>
//#include <map>
//
//using namespace std;
//
//int main(){
//	int n;
//	cin >> n;
//	if (n == 0){
//		return 0;
//	}
//
//	vector<int> nums;
//	int temp;
//	for (int i = 0; i < n; i++){
//		cin >> temp;
//		nums.push_back(temp);
//	}
//
//	vector<int> ret;
//	map<int, int> nums_map;
//	map<int, int>::iterator it;
//	for (int i = nums.size() - 1; i >= 0; i--)
//	{
//		int temp = nums[i];
//		it = nums_map.find(temp);
//		if (it == nums_map.end())
//		{
//			ret.push_back(temp);
//			nums_map.insert(make_pair(temp, 100));
//		}
//	}
//
//	for (int i = ret.size() - 1; i > 0; i--){
//		cout << ret[i] << " ";
//	}
//	cout << ret[0];
//}