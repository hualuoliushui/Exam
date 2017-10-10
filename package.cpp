#include<iostream>
#include<vector>
using namespace std;

class Package
{
private:
	vector<int> packs_;
	int capacity_;

	int max(int a, int b)
	{
		return a >= b ? a : b;
	}
	void zero_one_package(int cost, int weight)
	{
		for (int v = capacity_; v >= cost; --v)
			packs_[v] = max(packs_[v], packs_[v - cost] + weight);
	}
	void complete_package(int cost, int weight)
	{
		for (int v = cost; v <= capacity_; ++v)
			packs_[v] = max(packs_[v], packs_[v - cost] + weight);
	}
	void multiple_package(int cost, int weight, int num)
	{
		if (cost*num >= capacity_)
			return complete_package(cost, weight);
		int k, left_n = num;
		for (k = 1; k < num; k *= 2)
		{
			zero_one_package(k*cost, k*weight);
			left_n -= k;
		}
		return zero_one_package(left_n*cost, left_n*weight);
	}
public:
	int run(int capacity, vector<int>& costs, vector<int>& weights, bool is_exactly = true, bool is_inf = false, vector<int>* nums = nullptr)
	{
		int item_n = costs.size();
		if (costs.size() != weights.size())
			return 0;
		this->capacity_ = capacity;
		if (!is_exactly)
			this->packs_.resize(capacity + 1, 0);
		else
		{
			this->packs_.resize(capacity_ + 1, INT_MIN);
			this->packs_[0] = 0;
		}
		int i;
		if (nums == nullptr)
		{
			if (is_inf)
				for (i = 0; i < item_n; ++i)
					this->zero_one_package(costs[i], weights[i]);
			else
				for (i = 0; i < item_n; ++i)
					this->complete_package(costs[i], weights[i]);
			
		}
		else
		{
			if (costs.size() != (*nums).size())
				return 0;
			for (i = 0; i < item_n; ++i)
			{
				multiple_package(costs[i], weights[i], (*nums)[i]);
			}
		}
		return this->packs_[this->capacity_];
	}
};

