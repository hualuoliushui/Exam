//#include <iostream>
//#include <vector>
//#include <cstdio>
//#include <algorithm>
//
//using namespace std;
//
///*������������������ʵ����ĿҪ��Ĺ���*/
///*��Ȼ����Ҳ���Բ������������ģ����������ȫ�����Լ����뷨�� ^-^ */
///******************************��ʼд����******************************/
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
///******************************����д����******************************/
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