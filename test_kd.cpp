#ifdef TEST_KD_CPP
#include"KDTree.h"
#include<iostream>
int main() {
	KDT::KDTree<int> kd;
	int i, j;
	while (cin >> kd.n >> kd.k) {
		for (i = 0; i < kd.n; i++) for (j = 0; j < kd.k; j++) cin >> KDT::po[i].coord_[j];
		kd.build(0, kd.n - 1);
		int t, m;
		for (cin >> t; t--;) {
			KDT::Point<int> q;
			for (j = 0; j < kd.k; j++) cin >> q.coord_[j];
			cin >> m;
			kd.query(q, m);
			kd.print(m);
		}
	}
	return 0;
}
#endif