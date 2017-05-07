//// 计算连续正数和为sum的序列
//// (l+r)n/2 = sum ; n = r-l+1;
//// (l+r)(r-l+1) = 2*sum = m*k;
//// m = l+r; k = r-l+1;
//// l = m-k+1; r = m+k-1;
//
//#include <vector>
//#include <stack>
//#include <iostream>
//using namespace std;
//
//class Solution {
//public:
//	vector<vector<int> > FindContinuousSequence(int sum) {
//		vector<vector<int>> ret;
//		int doubleSum = 2 * sum;
//		for (int k = sqrt(doubleSum); k > 1; k--){
//			vector<int> temp;
//
//			if (doubleSum%k == 0){
//				int m = doubleSum / k;
//
//				if ((m + k - 1) % 2 != 0 || (m - k + 1) % 2 != 0 || (m + k - 1) == 0 || (m - k + 1) == 0){
//					continue;
//				}
//
//				int l = (m - k + 1) / 2;
//				int r = (m + k - 1) / 2;
//
//				for (int i = l; i <= r; i++){
//					temp.push_back(i);
//				}
//
//				if (temp.size()>1){
//					ret.push_back(temp);
//				}
//			}
//		}
//		return ret;
//	}
//}; 
//
//class Test{
//public:
//	static Solution s;
//	static vector<Test> v;
//};
//Solution Test::s = Solution();
//vector<Test> Test::v = vector<Test>();
//
//int main(){
//	Solution s;
//	vector<int> testdata = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };
//	vector<vector<int>> ret;
//	ret = Test::s.FindContinuousSequence(9);
//	for (int i = 0; i < ret.size(); i++)
//	{
//		for (int j = 0; j < ret[i].size(); j++)
//			cout << ret[i][j] << " ";
//		cout << endl;
//	}
//}