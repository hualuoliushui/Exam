//#include <iostream>
//#include <vector>
//#include <cstdio>
//#include <algorithm>
//
//using namespace std;
//
///*请完成下面这个函数，实现题目要求的功能*/
///*当然，你也可以不按照下面这个模板来作答，完全按照自己的想法来 ^-^ */
///******************************开始写代码******************************/
//double StockGod(int n, int m, double p, const vector<vector<double>>& prices)
//{
//	double ret = 1.0;
//	double max_dif = 0.0;
//	double _p = 1 - p;
//
//	for (int i = 0; i < m - 1; i++){
//		max_dif = 0.0;
//		for (int j = 0; j < n; j++){
//			double temp = ret*(prices[i + 1][j] / prices[i][j])*_p;
//			if (temp > max_dif){
//				max_dif = temp;
//			}
//		}
//		if (ret < max_dif) ret = max_dif;
//	}
//	return ret;
//}
///******************************结束写代码******************************/
//
//
//int main()
//{
//	int n = 0;
//	int m = 0;
//	double p = 0;
//	cin >> n >> m >> p;
//
//	vector<vector<double>> prices;
//	for (int i = 0; i < m; ++i) {
//		prices.push_back(vector<double>());
//		for (int j = 0; j < n; ++j) {
//			double x = 0;
//			cin >> x;
//			prices.back().push_back(x);
//		}
//	}
//
//	double final = StockGod(n, m, p, prices);
//	printf("%.1f\n", final);
//
//	return 0;
//}