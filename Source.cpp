#include "RBT.h"
#include "Heap.h"
#include <vector>
#include <iostream>
#include "timing.h"

int main(){
	gss::Timing timing;

	timing.start();
	int N = 255;
	std::vector<std::vector<int> > ret(N);
	ret[1].push_back(0);
	int i = 1;
	int j = 10 % N;
	for (;; ++i, j = (j * 10) % N)
	{
		int noUpdate = 0;
		bool flag = false;
		if (ret[j].size() == 0)
		{
			ret[j].clear();
			ret[j].push_back(i);
		}
		for (int k = 1; k < N; ++k)
		{
			if ((ret[k].size()>0)
				&& (i > ret[k][ret[k].size() - 1])
				&& (ret[(k + j) % N].size() == 0))
			{
				flag = true;
				ret[(k + j) % N] = ret[k];
				ret[(k + j) % N].push_back(i);
			}
		}
		if (flag == false)
		{
			noUpdate++;
		}
		if (noUpdate == N || ret[0].size() > 0)
			break;
	}
	timing.end();

	if (ret[0].size() == 0)
	{
		std::cout << "ÎÞ½â\n";
	}
	else
	{
		long temp = 0;
		for (int i = 0; i < ret[0].size(); ++i)
		{
			temp += (int)std::pow(10, ret[0][i]);
		}
		std::cout << "½â£º" << temp << "\n";
		std::cout << "M£º" << (temp/N) << "\n";
	}

	return 0;
}