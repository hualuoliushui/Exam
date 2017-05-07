//#include<vector>
//#include<iostream>
//using namespace std;
//
//class Solution {
//public:
//	int min_self(int a, int b, int c){
//		if (a > b){
//			a = b;
//		}
//		if (a > c){
//			a = c;
//		}
//		return a;
//	}
//
//	int GetUglyNumber_Solution(int index) {
//		vector<int> ret;
//		ret.push_back(0);
//		ret.push_back(1);
//		int top = 1;
//
//		int index_2 = 1, index_3 = 1, index_5 = 1;
//		while(top <=index){
//			int min = min_self(2 * ret[index_2], 3 * ret[index_3], 5 * ret[index_5]);
//			
//			ret.push_back(min);
//			top++;
//			while (ret[index_2] * 2 <= ret[top])
//				index_2++;
//			while (ret[index_3] * 3 <= ret[top])
//				index_3++;
//			while (ret[index_5] * 5 <= ret[top])
//				index_5++;
//		}
//		/*for (int i = 0; i <= index; i++){
//			cout << ret[i] << " ";
//		}*/
//		return ret[index];
//	}
//};
//
//int main(){
//	Solution s;
//	s.GetUglyNumber_Solution(100);
//	return 0;
//}