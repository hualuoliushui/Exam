////终于到周末啦！小易走在市区的街道上准备找朋友聚会，突然服务器发来警报, 
////小易需要立即回公司修复这个紧急bug。假设市区是一个无限大的区域，
////每条街道假设坐标是(X，Y)，小易当前在(0，0)街道，办公室在(gx, gy)街道上。
////小易周围有多个出租车打车点，小易赶去办公室有两种选择，
////一种就是走路去公司，
////另外一种就是走到一个出租车打车点，然后从打车点的位置坐出租车去公司。
////每次移动到相邻的街道(横向或者纵向)走路将会花费walkTime时间，打车将花费taxiTime时间。
////小易需要尽快赶到公司去，现在小易想知道他最快需要花费多少时间去公司。
//
////=============================================================
////输入数据包括五行:
////
////第一行为周围出租车打车点的个数n(1 ≤ n ≤ 50)
////
////第二行为每个出租车打车点的横坐标tX[i](-10000 ≤ tX[i] ≤ 10000)
////
////第三行为每个出租车打车点的纵坐标tY[i](-10000 ≤ tY[i] ≤ 10000)
////
////第四行为办公室坐标gx, gy(-10000 ≤ gx, gy ≤ 10000), 以空格分隔
////
////第五行为走路时间walkTime(1 ≤ walkTime ≤ 1000)和taxiTime(1 ≤ taxiTime ≤ 1000), 以空格分隔
//
////输出描述:
////输出一个整数表示，小易最快能赶到办公室的时间
//
////***************************************************************
////输入例子:
////2
////-2 -2
////0 -2
////-4 -2
////15 3
////输出例子:
////42
//
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
//
//template<class T>
//class Point{
//private:
//	T _x;
//	T _y;
//public:
//	Point(T x = 0, T y = 0)
//		:_x(x), _y(y)
//	{
//
//	};
//
//	Point(const Point<T>& origin){
//		_x = origin.x();
//		_y = origin.y();
//	}
//
//	T x() const{
//		return _x;
//	}
//
//	void x(T val){
//		_x = val;
//	}
//
//	T y() const{
//		return _y;
//	}
//	
//	void y(T val){
//		_y = val;
//	}
//
//	Point<T>* operator -(const Point<T>& right){
//		return new Point<T>(this->x() - right.x(), this->y() - right.y());
//	}
//
//	Point<T>* operator =(const Point<T>& origin){
//		return new Point<T>(origin.x(), origin.y());
//	}
//
//	~Point(){
//
//	};
//
//
//};
//
//class Solution{
//public:
//	int ntexis;
//	vector<Point<int>> texis;
//	Point<int> office;
//	int eachWalkTime;
//	int eachTexiTime;
//
//	Solution(){
//
//	};
//
//	~Solution(){
//
//	}
//
//	int run(){
//		int min;
//
//		Point<int>* temp;
//		temp = &office;
//		min = (abs(temp->x()) + abs(temp->y()))*eachWalkTime;
//		
//		int eachTime;
//		for (int i = 0; i < ntexis; i++){
//			eachTime = 0;
//			temp = (texis[i] - office);
//			eachTime = (abs(texis[i].x()) + abs(texis[i].y()))*eachWalkTime + (abs(temp->x()) + abs(temp->y()))*eachTexiTime;
//			delete temp;
//
//			min = min > eachTime ? eachTime : min;
//		}
//		return min;
//	}
//
//};
//
//#include <iostream>
//#include <vector>
//#include <algorithm>
//#include <queue>
//using namespace std;
//
//int main(){
//	Solution s;
//	//输入出租车 打车点的数量
//	cin >> s.ntexis;
//
//	vector<int> Xs;
//	vector<int> Ys;
//	int temp;
//
//	for (int i = 0; i < s.ntexis; i++){
//		cin >> temp;
//		Xs.push_back(temp);
//	}
//	for (int i = 0; i < s.ntexis; i++){
//		cin >> temp;
//		Ys.push_back(temp);
//	}
//	
//	// 输入打车点的坐标
//	for (int i = 0; i < s.ntexis; i++){
//		s.texis.push_back(Point<int>(Xs[i], Ys[i]));
//	}
//
//	//输入办公室坐标
//	cin >> temp;
//	s.office.x(temp);
//	cin >> temp;
//	s.office.y(temp);
//
//	//输入走路、坐车的单位时间
//
//	cin >> s.eachWalkTime >> s.eachTexiTime;
//
//	//输出结果
//	cout << s.run() << endl;
//
//	return 0;
//}