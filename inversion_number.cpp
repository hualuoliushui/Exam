///*
//ÄæĞòÊı
//*/
//#include <vector>
//#include <iostream>
//#include <math.h>
//using namespace std;
//
//class Solution{
//public:
//	long solve(vector<int>& nums){
//		vector<int> nums_helper;
//		for (int i = 0; i < nums.size(); i++)
//		{
//			nums_helper.push_back(nums[i]);
//		}
//
//		return merge_sort(nums, nums_helper, 0, nums.size() - 1);
//	}
//
//
//	long merge_sort(vector<int>& nums,vector<int>& nums_helper, int start, int end){
//		if (start < end)
//		{
//			long counter = 0;
//			int mid = (start + end) / 2;
//			counter += merge_sort(nums, nums_helper, start, mid);
//			counter += merge_sort(nums, nums_helper, mid + 1, end);
//			counter += merge(nums, nums_helper, start, mid, end);
//
//			return counter;
//		}
//		return 0;
//	}
//
//	long merge(vector<int>& nums, vector<int>& nums_helper, int start, int mid, int end){
//		int i = start, j = mid + 1;
//		long counter = 0;
//		int cur = start;
//		while (i <= mid && j <= end)
//		{
//			if (nums[i] <= nums[j])
//			{
//				nums_helper[cur++] = nums[i++];
//			}
//			else
//			{
//				nums_helper[cur++] = nums[j++];
//				counter += j - cur;
//			}
//		}
//
//		while (i <= mid)
//		{
//			nums_helper[cur++] = nums[i++];
//		}
//		while (j <= end)
//		{
//			nums_helper[cur++] = nums[j++];
//		}
//
//		for (int k = start; k < cur; k++)
//		{
//			nums[k] = nums_helper[k];
//		}
//
//		return counter;
//	}
//};
//
//int main(){
//	Solution s;
//	vector<int> testData = { };
//	cout << s.solve(testData) << endl;
//
//	return 0;
//}