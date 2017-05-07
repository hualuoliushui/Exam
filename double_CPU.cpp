////一种双核CPU的两个核能够同时的处理任务，
////现在有n个已知数据量的任务需要交给CPU处理，
////假设已知CPU的每个核1秒可以处理1kb，每个核同时只能处理一项任务。
////n个任务可以按照任意顺序放入CPU进行处理，
////现在需要设计一个方案让CPU处理完这批任务所需的时间最少，求这个最小的时间。
//
////=========================================================
////输入描述:
////输入包括两行：
////第一行为整数n(1 ≤ n ≤ 50)
////第二行为n个整数length[i](1024 ≤ length[i] ≤ 4194304)，表示每个任务的长度为length[i]kb，每个数均为1024的倍数。
//
////输出描述:
////输出一个整数，表示最少需要处理的时间
//
////*********************************************************
////输入例子 :
////5
////3072 3072 7168 3072 1024
////
////输出例子 :
////	 9216
//
//#include <iostream>
//#include <vector>
//#include <algorithm>
//#include <queue>
//using namespace std;
//
////求数组中 分成两个子数组，使得他们之差最小
////输入：
////5
////3072 3072 7168 3072 1024
////输出：
////9216
//
//void main(){
//	int n;
//	vector<int> nums;
//
//	cin >> n;
//
//	if (n == 0){
//		cout << "0" << endl;
//	}
//
//	int sum = 0;
//	int half_sum = 0;
//
//	int temp;
//	for (int i = 0; i < n; i++){
//		cin >> temp;
//		temp >>= 10;
//		sum += temp;
//		nums.push_back(temp);
//	}
//
//	sort(nums.begin(), nums.end());
//
//	half_sum = sum / 2;
//
//	int* f = new int[half_sum + 1]();
//
//	for (int i = 0; i < n; i++)
//	{
//		//cout << "i========:: " << i << " value : " << nums[i] << endl;
//			//01背包
//		for (int j = half_sum; j >= nums[i]; j--) 
//			//完全背包
//		/*for (int j = nums[i]; j <= half_sum;j++)*/
//		{
//			f[j] = max(f[j], f[j - nums[i]] + nums[i]);
//		}
//		/*for (int k = 0; k <= half_sum; k++){
//			cout << f[k] << " ";
//		}
//		cout << "\n\n";*/
//	}
//
//	int ret = max(f[half_sum], sum - f[half_sum]);
//	ret <<= 10;
//	cout << ret << endl;
//
//	delete[] f;
//}
