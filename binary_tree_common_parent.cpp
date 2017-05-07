//#include <vector>
//#include <iostream>
//using namespace std;
//
//
//class Node{
//public:
//	int val;
//	int level;
//	Node(int _val,int _k){
//		val = _val;
//		level = 0;
//		while (_val % 2 == 0){
//			_val >>= 1;
//			level++;
//		}
//		level = _k - level;
//	}
//
//	bool operator<(const Node& right) const{
//		return this->level < right.level;
//	}
//};
//
//bool isSame(vector<Node>& nums,int mid){
//	for (int i = 0; i < nums.size(); i++){
//		if (mid == nums[i].val){
//			return true;
//		}
//	}
//
//	for (int i = 0; i < nums.size() - 1; i++){
//		if (nums[i].val != nums[i + 1].val){
//			return false;
//		}
//	}
//	return true;
//}
//
//int max(int a, int b, int c)
//{
//	if (a < b)
//	{
//		a = b;
//	}
//	if (a < c)
//	{
//		a = c;
//	}
//	return a;
//}
//
//// 4 10 15 13 
//// 12
//int main(){
//	int k, n1, n2, n3;
//	vector<Node> nums;
//	cin >> k >> n1 >> n2 >> n3;
//
//	nums.push_back(Node(n1,k));
//	nums.push_back(Node(n2,k));
//	nums.push_back(Node(n3,k));
//
//	int N = 1 << k;
//
//	while (!isSame(nums,N>>1)){
//		int max_level = max(nums[0].level, nums[1].level, nums[2].level);
//		for (int i = 0; i < nums.size(); i++){
//			int temp = nums[i].val;
//			
//			if (max_level > nums[i].level){
//				continue;
//			}
//
//			int counter =(k - nums[i].level);
//			nums[i].level--;
//
//			if ((temp >> (counter+1)) % 2 == 0){
//				nums[i].val = temp + (1 << counter);
//			}
//			else{
//				nums[i].val = temp - (1 << counter);
//			}
//
//		}
//	}
//
//	cout << nums[0].val;
//	return 0;
//}