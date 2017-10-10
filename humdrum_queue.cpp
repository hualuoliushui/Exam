#include<iostream>
#include<vector>
using namespace std;

// ��������n��Ԫ�ص���������a[]����һ������k��
// Ҫ�����a[]��ÿ����k��Ԫ����ɵ������е���Сֵ�������ֵ��,
// ������ֵ������1����n-k+1����
class HumdrumQueue1
{
private:
	class Node {
	public:
		int index_;
		int value_;
		Node(int index = 0, int value = 0)
			:index_(index),
			value_(value)
		{};
	};

	int head_;
	int end_;
public:
	HumdrumQueue1()
		:head_(0),
		end_(0)
	{}
	// for max
	vector<int> find_limit_from_k(vector<int>& a, int k)
	{
		vector<int> ret;
		int n = a.size();
		if (n == 0)
			return ret;
		head_ = 0; end_ = 0;
		vector<Node> nodes(n);

		int i = 0,value;
		do {
			value = a[i];
			while (end_ && nodes[end_ - 1].value_ < value)
				--end_;
			nodes[end_].index_ = i; nodes[end_].value_ = value;
			end_++;

			while (nodes[head_].index_ < i - k + 1)
				++head_;

			if (i + 1 >= k)
				ret.push_back(nodes[head_].value_);
			++i;
		} while (i < n);
		if (i + 1 < k)
			ret.push_back(nodes[head_].value_);
		return ret;
	}

	static void run()
	{
		HumdrumQueue1 test;
		vector<int> test_data = { 1,5,9,4,7,8,6 };
		vector<int> ret = test.find_limit_from_k(test_data, 3);
		for (auto value : ret)
		{
			printf("%3d\n", value);
		}
	}
};
	
//int main(void)
//{
//	HumdrumQueue1::run();
//	getchar();
//	return 0;
//}