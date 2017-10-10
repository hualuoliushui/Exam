#include <vector>
#include<iostream>
#include<memory>
using namespace std;
class DoubleBinary
{

public:
	int run(int n)
	{
		int count = 0; if (n < 0)n = -n;
		while (n)
		{
			shared_ptr<DoubleBinary> x;
			n >>= 1;
			++count;
		}
		return count;
	}
};

#include<iostream>
#include<vector>
#include<list>
using namespace std;
class Solution {
public:
	struct Point{
		int x_;
		int y_;
		Point(int x = 0, int y = 0)
			:x_(x), y_(y) {}
	};
	class IsContinous {
	public:
		Point* ori_;
		bool isContinuous(const Point& point) {
			int ax = abs(ori_->x_ - point.x_);
			int bx = abs(ori_->y_ - point.y_);
			if ((ax == 0 && bx == 1)
				|| (ax == 1 && bx == 0)
				|| (ax == 0 && bx == 0))
				return true;
			return false;
		}
	};
	vector<list<Point*>> points_;
	int ret_;
	int m_;
	int n_;
	IsContinous check_;
	Solution(int m = 0, int n = 0)
		:m_(m), n_(n), ret_(0) {}
	~Solution() {
		for (auto l : points_) {
			for (list<Point*>::iterator it = l.begin(); it != l.end(); ++it) {
				delete (*it);
				l.erase(it++);
			}
		}
	}
	int addLand(int x, int y) {
		if (x<0 || x >m_
			|| y<0 || y>n_)
			return ret_;
		Point* p = new Point(x, y);
		if (points_.empty()) {
			list<Point*> temp;
			temp.push_back(p);
			points_.push_back(temp);
			return ++ret_;
		}
		check_.ori_ = p;
		int c_times=0;
		vector<int> c_indexes;
		int i, j;
		for (i = 0; i < points_.size(); ++i) {
			for (auto p : points_[i]) {
				if (check_.isContinuous(*p)) {
					++c_times;
					c_indexes.push_back(i);
					break;
				}
			}
		}
		if (c_times) {
			int index = c_indexes[0];
			points_[index].push_back(p);
			if (c_times > 1) {
				for (i = 1; i < c_times; ++i) {
					for (auto p : points_[c_indexes[i]]) {
						points_[index].push_back(p);
					}
				}
				for (i = 1; i < c_times; ++i) {
					points_[c_indexes[i]].reverse();
					points_[c_indexes[i]].clear();
				}
				ret_ -= (c_times - 1);
			}
			return ret_;
		}
		else {
			list<Point*> t_;
			t_.push_back(p);
			points_.push_back(t_);
			return ++ret_;
		}
	}
};
//int main(void) {
//	int m, n, k, x, y;
//	cin >> m >> n >> k;
//	Solution s(m, n);
//	int i;
//	for (i = 0; i < k; ++i) {
//		cin >> x >> y;
//		printf("%d ", s.addLand(x, y));
//	}
//	return 0;
//}

#include <iostream>
using namespace std;
double solve(double R, int n) {
	double cur = R;
	double ret = 1.0;
	while (n) {
		if ((n & 1) == 1)
			ret *= cur;
		cur *= cur;
		n >>= 1;
	}
	return ret;
}
//int main() {
//	double R;
//	int n;
//	while (cin >> R >> n)//注意while处理多个case
//	{
//		double ret = solve(R, n);
//		int iret = ret;
//		if (ret - iret <= 0.000001)
//			printf("%d", iret);
//		else
//			printf("%e", solve(R, n));
//	}
//	return 0;
//}