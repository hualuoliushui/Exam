////���ڵ���ĩ����С�����������Ľֵ���׼�������ѾۻᣬͻȻ��������������, 
////С����Ҫ�����ع�˾�޸��������bug������������һ�����޴������
////ÿ���ֵ�����������(X��Y)��С�׵�ǰ��(0��0)�ֵ����칫����(gx, gy)�ֵ��ϡ�
////С����Χ�ж�����⳵�򳵵㣬С�׸�ȥ�칫��������ѡ��
////һ�־�����·ȥ��˾��
////����һ�־����ߵ�һ�����⳵�򳵵㣬Ȼ��Ӵ򳵵��λ�������⳵ȥ��˾��
////ÿ���ƶ������ڵĽֵ�(�����������)��·���Ứ��walkTimeʱ�䣬�򳵽�����taxiTimeʱ�䡣
////С����Ҫ����ϵ���˾ȥ������С����֪���������Ҫ���Ѷ���ʱ��ȥ��˾��
//
////=============================================================
////�������ݰ�������:
////
////��һ��Ϊ��Χ���⳵�򳵵�ĸ���n(1 �� n �� 50)
////
////�ڶ���Ϊÿ�����⳵�򳵵�ĺ�����tX[i](-10000 �� tX[i] �� 10000)
////
////������Ϊÿ�����⳵�򳵵��������tY[i](-10000 �� tY[i] �� 10000)
////
////������Ϊ�칫������gx, gy(-10000 �� gx, gy �� 10000), �Կո�ָ�
////
////������Ϊ��·ʱ��walkTime(1 �� walkTime �� 1000)��taxiTime(1 �� taxiTime �� 1000), �Կո�ָ�
//
////�������:
////���һ��������ʾ��С������ܸϵ��칫�ҵ�ʱ��
//
////***************************************************************
////��������:
////2
////-2 -2
////0 -2
////-4 -2
////15 3
////�������:
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
//	//������⳵ �򳵵������
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
//	// ����򳵵������
//	for (int i = 0; i < s.ntexis; i++){
//		s.texis.push_back(Point<int>(Xs[i], Ys[i]));
//	}
//
//	//����칫������
//	cin >> temp;
//	s.office.x(temp);
//	cin >> temp;
//	s.office.y(temp);
//
//	//������·�������ĵ�λʱ��
//
//	cin >> s.eachWalkTime >> s.eachTexiTime;
//
//	//������
//	cout << s.run() << endl;
//
//	return 0;
//}