#include<queue>
#include<algorithm>
using namespace std;

namespace KDT {
	const int N = 55555, K = 10;
#define sqr(x) (x)*(x);
	template<typename T>
	struct Point {
		static int idx_;
		T coord_[K];
		bool operator<(const Point<T>& r) const {
			return coord_[idx_] < r.coord_[idx_];
		}
	};
	template<typename T>
	int Point<T>::idx_ = -1;

	Point<int> po[N];

	template<typename T>
	class KDTree {
	public:
		int k, n;
		typedef pair<double, Point<T> > TP;
		priority_queue<TP> kq;
		Point<T> points_[(N << 2)];
		int son[(N << 2)];

		void build(int l, int r, int rt = 1, int dep = 0) {
			if (l > r)return;
			son[rt] = r - 1;
			son[rt * 2] = son[rt * 2 + 1] = -1;
			Point<T>::idx_ = dep%k;
			int mid = (l + r) / 2;
			nth_element(po + l, po + mid, po + r + 1);
			points_[rt] = po[mid];
			build(l, mid - 1, rt * 2, dep + 1);
			build(mid + 1, r, rt * 2 + 1, dep + 1);
		}

		void query(Point<T> p, int m, int rt = 1, int dep = 0) {
			if (son[rt] == -1) return;
			TP kd(0, points_[rt]);
			int i;
			for (i = 0; i < k; ++i) kd.first += sqr(kd.second.coord_[i] - p.coord_[i]);
			int dim = dep%k, x = rt * 2, y = rt * 2 + 1, fg = 0;
			if (p.coord_[dim] >= points_[rt].coord_[dim]) swap(x, y);
			if (~son[x]) query(p, m, x, dep + 1);
			if (kq.size() < m) kq.push(kd), fg = 1;
			else {
				if (kd.first < kq.top().first) kq.pop(), kq.push(kd);
				double tmp = sqr(p.coord_[dim] - points_[rt].coord_[dim]);
				if (tmp < kq.top().first)
					fg = 1;
			}
			if (~son[y] && fg) query(p, m, y, dep + 1);
		}

		void print(const Point<T>& p) {
			for (int j = 0; j < k; j++) printf("%d%c", p.coord_[j], j == k - 1 ? '\n' : ' ');
		}

		void print(int m) {
			printf("the closest %d points arg:\n", m);
			vector<Point<T>> ps;
			while (!kq.empty()) {
				ps.push_back(kq.top().second);
				kq.pop();
			}
			int i;
			for (i = ps.size() - 1; i >= 0; --i)
				printf(ps[i]);
		}
	};
}

