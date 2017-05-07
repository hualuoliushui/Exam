////小易有一个长度为n序列，
////小易想移除掉里面的重复元素，
////但是小易想是对于每种元素保留最后出现的那个。
////小易遇到了困难, 希望你来帮助他。
//
////==============================================
////输入描述 :
////输入包括两行：
////第一行为序列长度n(1 ≤ n ≤ 50)
////第二行为n个数sequence[i](1 ≤ sequence[i] ≤ 1000)，以空格分隔
////
////输出描述 :
////输出消除重复元素之后的序列，以空格分隔，行末无空格
//
////**********************************************
////输入例子 :
////9
////100 100 100 99 99 99 100 100 100
////
////输出例子 :
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