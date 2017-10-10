//#include "timing.h"
//using namespace gss;
//
//#include <iostream>
//#include <vector>
//#include <stack>
//#include <string>
//using namespace std;
//
//class Solution {
//public:
//	int candy(vector<int> &ratings) {
//		int n = ratings.size();
//		if (n == 0){
//			return 0;
//		}
//		else if (n == 1){
//			return 1;
//		}
//
//		vector<int> temp(n, 1);
//		for (int i = 1; i<n; ++i){
//			if (ratings[i - 1]<ratings[i]){
//				temp[i] = temp[i - 1] + 1;
//			}
//			else if (ratings[i - 1]>ratings[i]){
//				if (temp[i - 1] == 1){
//					for (int j = i; j>0; --j){
//						if (ratings[j-1]>ratings[j] && temp[j-1]<=temp[j])
//							temp[j - 1] += 1;
//						else
//							break;
//					}
//				}
//			}
//		}
//
//		int ret = 0;
//		for (int i = 0; i<n; ++i){
//			ret += temp[i];
//		}
//		return ret;
//	}
//};
////
////int main(){
////	vector<int> test = { 1, 2, 3, 4, 5, 6, 7, 8, 9,8,2,3,4,5,6,6,6,7,7,8,6,5,4,3,2,2,1,0 };
////	Solution s;
////	Timing t;
////	t.start();
////	std::cout << "ret	" << s.candy(test) << std::endl;
////	/*for (auto val : ret){
////		std::cout << val << std::endl;
////	}*/
////	t.end();
////
////	//vector<int> nums = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
////	//
////	//for (auto it = nums.begin(); it != nums.end();){
////	//	if (*it % 2 == 0){
////	//		it = nums.erase(it);
////	//	}
////	//	else{
////	//		++it;
////	//	}
////	//}
////	//for (auto it = nums.begin(); it != nums.end(); ++it){
////	//	std::cout << *it << " ";
////	//}
////	//std::cout << std::endl;
////	//for (int i = 0; i < 9; ++i){
////	//	std::cout << nums[i] << " ";
////	//}
////	//std::cout << std::endl;
////	//std::cout << "nums size : " << nums.size() << std::endl;
////	//std::cout << std::endl;
////	getchar();
////	return 0;
////}
//
//#include<iostream>  
//#include<map>
//#include<list>
//using   namespace   std;
//
///*
//	模拟：
//	岛上，一对婴儿兔，
//	2年后开始生育（每年生育一对雌雄婴儿兔），生命的最后1年停止生育
//	兔子的寿命为x年
//	当对于10对兔子时，杀掉年纪最大的2对
//	y年后，岛上的兔子的总岁数。
//*/
//class RabbitTest{
//public:
//	typedef std::vector<long long> TestMap;
//	typedef long long TestNode;
//
//	TestNode now_;
//	TestNode s_;
//	TestNode e_;
//	TestNode max_size_;
//	TestNode del_num_;
//	TestNode x_;
//	TestNode y_;
//	RabbitTest(TestNode x, TestNode y, TestNode e = -1, TestNode max_size = 10, TestNode del_num = 2, TestNode s = 2)
//		:now_(0), s_(s), e_(e), max_size_(max_size), del_num_(del_num), x_(x), y_(y)
//	{
//		if (e_ == -1)
//		{
//			e_ = x - 1;
//		}
//	};
//
//	
//
//	void run_fornew(TestMap& m)
//	{
//		for (TestNode i = 0; i < now_; ++i)
//		{
//			if (i + s_ <= now_ && i + e_ >= now_)
//			{
//				m[now_] += m[i];
//			}
//		}
//	}
//
//	void run_fordie(TestMap& m)
//	{
//		for (TestNode i = 0; i < now_; ++i)
//		{
//			if (i + x_ == now_)
//			{
//				m[i] = 0;
//			}
//		}
//	}
//
//	void run_fordelete(TestMap& m)
//	{
//		TestNode size = 0;
//		for (TestNode i = 0; i < now_; ++i)
//		{
//			size += m[i];
//		}
//		if (2 * size > max_size_)
//		{
//			for (TestNode i = 0; i < now_ && del_num_>0; ++i)
//			{
//				if (m[i] < del_num_)
//				{
//					m[i] = 0;
//					del_num_ -= m[i];
//				}
//				else if (m[i] >= del_num_)
//				{
//					m[i] -= del_num_;
//					del_num_ = 0;
//				}
//			}
//		}
//	}
//
//	TestNode  run_fortotalage(TestMap& m)
//	{
//		TestNode ret = 0;
//		for (int i = 0; i < now_; ++i)
//		{
//			ret += 2*m[i] * (now_ - i);
//		}
//		return ret;
//	}
//
//	void run_forprint(TestMap& m)
//	{
//		for (TestNode i = 0; i <= now_; ++i)
//		{
//			if (m[i] == 0)
//				continue;
//			//std::cout << m[i] << "*" << i << " ";
//		}
//		//std::cout << "\n\n";
//	}
//
//	void run()
//	{
//		TestMap m(y_+1);
//		m[0] = 1;
//		TestNode ret;
//		for (TestNode i = 0; i <= y_; ++i)
//		{
//			now_ = i;
//			run_fornew(m);
//			run_fordie(m);
//			run_fordelete(m);
//			ret = run_fortotalage(m);
//			std::cout << "year[" << now_ << "] ret[" << ret << "]\n";
//			run_forprint(m);
//		}
//	}
//	
//};
//
///*
//	给定一个字符串S和有效单词的字典D，请确定可以插入到S中的最小空格数，使得最终的字符串完全由D中的有效单词组成，并输出解。
//	如果没有解则应该输出n/a
//	例如
//	输入
//	S = "ilikealibaba"
//	D = ["i", "like", "ali", "liba", "baba", "alibaba"]
//	Example Output:
//	输出
//	"i like alibaba"
//	解释：
//	字符串S可能被字典D这样拆分
//	"i like ali baba"
//	"i like alibaba"
//	很显然，第二个查分结果是空格数最少的解。
//*/
//#include<algorithm>
//#include<iostream>
//#include<string>
//#include<set>
//#include<vector>
//
//using namespace std;
//class StringTest1
//{
//	string str_;
//	set<string> dict_;
//	vector<int> indexes_;
//public:
//	void helper()
//	{
//		int start = 0;
//		int end = str_.size();
//
//		for (int i = start; i<end;)
//		{
//			if (dict_.find(str_.substr(i, end - i)) != dict_.end())
//			{
//				indexes_.push_back(i);
//				end = i;
//				i = start;
//			}
//			else
//			{
//				++i;
//			}
//		}
//	}
//	void insert_space()
//	{
//		int size_ = str_.size();
//		int end = size_;
//		int index = 0;
//		if (indexes_.size() == 0)
//		{
//			if (dict_.find(str_) == dict_.end())
//			{
//				str_ = "n/a";
//			}
//			return;
//		}
//		for (int i = 0; i < indexes_.size();++i)
//		{
//			if (indexes_[i] <= 0 || indexes_[i] >= size_)
//				continue;
//			index = indexes_[i];
//			if (dict_.find(str_.substr(index, end-index)) == dict_.end())
//			{
//				str_ = "n/a";
//				return;
//			}
//			str_ = str_.substr(0, index) + " " + str_.substr(index, size_);
//			end = index;
//		}
//	}
//	void mincut()
//	{
//		indexes_.clear();
//		helper();
//		insert_space();
//		std::cout << str_;
//		indexes_.clear();
//	}
//
//
//	int run()
//	{
//		/*string dictStr;
//		int nDict;
//
//		cin >> str_;
//		cin >> nDict;
//		for (int i = 0; i < nDict; i++)
//		{
//			cin >> dictStr;
//			dict_.insert(dictStr);
//		}*/
//		str_ = "abcde";
//		dict_.insert({"abc","de","cde","liba","baba","alibaba"});
//		mincut();
//
//		return 0;
//	}
//};
//
//
//// 满二叉排序树，高度为K，值为[1,2^K-1],
//// 给定3个数，确定包含者三个值的最小树的根节点的值
//class FullBinaryOrderTree_Exam{
//public:
//	int run(int K, int a, int b, int c)
//	{
//		std::pair<int,int> mm = minmax({ a, b, c });
//		int min_v = mm.first;
//		int max_v = mm.second;
//
//		int mid_v = 1 << (K - 1);
//		int level = K;
//		while (mid_v < min_v && level > 1)
//		{
//			mid_v += 1 << (level - 2);
//			level--;
//		}
//		while (mid_v > max_v && level > 1)
//		{
//			mid_v -= 1 << (level - 2);
//			level--;
//		}
//			
//		return mid_v;
//	}
//
//	int run(vector<int> nums)
//	{
//		return run(nums[0], nums[1], nums[2], nums[3]);
//	}
//};
//
//class Sampling_Test
//{
//public:
//	void run(void)
//	{
//		int select = 5;
//		int remaining = 10;
//		for (int i = 0; i < remaining; ++i)
//		{
//			if (rand() % remaining < select)
//			{
//				printf("%d", i);
//				select--;
//			}
//			remaining--;
//		}
//	}
//};
//
//struct S {
//	S()
//		:s(__func__) {}
//	const char *s;
//};
//
//int ival = 10;
//const int const_ival = 10;
//constexpr int const & cival_g = ival;
//constexpr int const & cival_g_c = const_ival;
//class Test
//{
//	static constexpr int const & _ival = cival_g;
//	static constexpr int const & _ival_c = const_ival;
//};
//
//#include <time.h>
//#include <stdio.h>
//
//const char* convert(char buf[], int value)
//{
//	static char digits[19] =
//	{
//		'9','8','7','6','5','4','3','2','1',
//		'0',
//		'1','2','3','4','5','6','7','8','9'
//	};
//	static const char* zero = digits + 9;
//	int i = value;
//	char*p = buf;
//	do
//	{
//		int lsd = i % 10;
//		i /= 10;
//		*p++ = zero[lsd];
//	} while (i != 0);
//	if (value < 0)
//		*p++ = '-';
//	*p = '\0';
//	std::reverse(buf, p);
//	return p;
//}
//
//template<class T>
//void print_size(void)
//{
//	std::cout << sizeof(T) << std::endl;
//}
//
//
//#include<algorithm>
//#include<iostream>
//#include<iterator>
//#include<vector>
//
//void print_permutation(vector<int>& input)
//{
//	sort(input.begin(), input.end());
//	int count = 0;
//	do
//	{
//		++count;
//		std::cout << count << ": ";
//		std::copy(input.begin(), input.end(),
//			std::ostream_iterator<int>(std::cout, ", "));
//		std::cout << std::endl;
//	} while (next_permutation(input.begin(), input.end()));
//	std::cout << "size : " << count << std::endl;
//}
//
//struct AreBothSpaces
//{
//	bool operator()(char x, char y)const
//	{
//		return x == ' ' && y == ' ';
//	}
//};
//
//void removeContinuousSpaces(string& str)
//{
//	std::cout << str << "| end \n";
//	std::string::iterator last
//		= unique(str.begin(), str.end(), AreBothSpaces());
//	std::cout << str << "| end \n";
//	str.erase(last, str.end());
//	std::cout << str << "| end \n";
//}
//
//
//#include <thread>
//#include <atomic>
//class Foo
//{
//private:
//	int count_;
//public:
//	const static int a = 1;
//public:
//	Foo()
//		:count_(0) {}
//	void runInThread()
//	{
//		while (true)
//		{
//			printf("[%d] : run in thread\n", count_++);
//		}
//
//	}
//	const static void runInAnotherThread(int)
//	{
//		while (true)
//		{
//			printf("[%d] : run in another thread\n", 1);
//		}
//
//	}
//};
//
//// a->A b->B
//// 操作a、b ： 1、乘以 2 ；2、加上1
//// 求最小的操作步骤数
//// 解决方案（逆向求解，目标数为 a，b）：偶数除以2，奇数减1；如果 偶数除以2，小于目标数，则减1； 如果奇数减1，小于目标数，则无解
////			当 等于目标数时，结束
//int abAB(int a, int b, int A, int B,int& ret)
//{
//	if (a == A && b == B)
//		return ret;
//	if (A % 2 == 0 && B % 2 == 0 && (A / 2 > a && B / 2 > b))
//	{
//		ret += 1;
//		return abAB(a, b, A/2, B/2, ret);
//	}
//	else
//	{
//		if (A - 1 < a || B - 1 < b)
//		{
//			ret = -1;
//			return ret;
//		}
//		ret += 1;
//		return abAB(a, b, A - 1, B - 1, ret);
//	}
//}
//
//// 有2^k种数，每个数的数量为2，k为[0,inf],即 1 1 2 2 4 4 8 8 16 16 .......
//// 求这些数 组成 给定 n的方案数，存在同一种数但不同数量算 一种方案。
//int kind_of_binary_2(long long n)
//{
//	int dp[100][2];
//
//	memset(dp, 0, sizeof(dp));
//	dp[0][0] = 1;
//	dp[0][1] = 1;
//	if (n & 1) dp[0][1] = 1;
//	for (int i = 1; i <= 31; ++i)
//	{
//		if (n&(1LL << i))
//		{
//			dp[i][0] += dp[i - 1][0];
//			dp[i][0] += dp[i - 1][1];
//
//			dp[i][1] += dp[i - 1][1];
//		}
//		else {
//			dp[i][0] += dp[i - 1][0];
//
//			dp[i][1] += dp[i - 1][0];
//			dp[i][1] += dp[i - 1][1];
//		}
//	}
//
//	return dp[31][0];
//}
//
//bool str_cmp(const char* lstr, const char* rstr)
//{
//	int lsize = strlen(lstr);
//	int rsize = strlen(rstr);
//
//	const char * ltp = lstr;
//	const char * rtp = rstr;
//	for (int i = 0; i < lsize && i < rsize; ++i)
//	{
//		if (ltp[i] != rtp[i])
//		{
//			return ltp[i] < rtp[i];
//		}
//	}
//	return lsize < rsize;
//}
//
//// 基数排序
//template<class E>
//void radix(vector<E>& A,int k, int r)
//{
//	int n = A.size();
//	vector<int> cnt(r);
//	vector<E> B(n);
//	int j;
//	for (int i = 0, rtoi = 1; i < k; ++i, rtoi *= r)
//	{
//		for (j = 0; j < r; ++j) cnt[j]=0;
//		for (j = 0; j < n; ++j) cnt[(A[j] / rtoi)%r]++;
//		for (j = 1; j < r; ++j) cnt[j] = cnt[j - 1] + cnt[j];
//		for (j = n - 1; j >= 0; --j) B[--cnt[(A[j] / rtoi)%r]] = A[j];
//		for (j = 0; j < n; ++j) A[j] = B[j];
//	}
//}
//
//const int maxn = 128;
//int wa_[maxn], wb_[maxn], wv_[maxn], ws_[maxn];
//int cmp(int *r, int a, int b, int l) {
//	return r[a] == r[b] && r[a + l] == r[b + l];
//}
//void da0(vector<int>& r, vector<int>& sa) {
//	int m = 0;
//	for (auto i : r)
//	{
//		if (i > m)
//			m = i;
//	}
//	++m;
//
//	r.push_back(0);
//	int n = r.size();
//	sa.resize(n);
//
// 	int i, j, p, *x = wa_, *y = wb_, *t;
//	for (i = 0; i<m; i++) 
//		ws_[i] = 0;
//	for (i = 0; i<n; i++) 
//		ws_[x[i] = r[i]]++;
//	for (i = 1; i<m; i++) 
//		ws_[i] += ws_[i - 1];
//	for (i = n - 1; i >= 0; i--) 
//		sa[--ws_[x[i]]] = i;
//	for (j = 1, p = 1; p<n; j *= 2, m = p)
//	{
//		for (p = 0, i = n - j; i<n; i++) 
//			y[p++] = i;
//		for (i = 0; i<n; i++) 
//			if (sa[i] >= j)
//				y[p++] = sa[i] - j;
//		for (i = 0; i<n; i++) 
//			wv_[i] = x[y[i]];
//		for (i = 0; i<m; i++)
//			ws_[i] = 0;
//		for (i = 0; i<n; i++) 
//			ws_[wv_[i]]++;
//		for (i = 1; i<m; i++) 
//			ws_[i] += ws_[i - 1];
//		for (i = n - 1; i >= 0; i--) 
//			sa[--ws_[wv_[i]]] = y[i];
//		for (t = x, x = y, y = t, p = 1, x[sa[0]] = 0, i = 1; i<n; i++)
//			x[sa[i]] = cmp(y, sa[i - 1], sa[i], j) ? p - 1 : p++;
//	}
//	r.pop_back();
//	sa.erase(sa.begin());
//	return;
//}
//
//// 后缀数组
//vector<int> post_substr(string str, int strage = 0)
//{
//	const char* s = str.c_str();
//	int n = str.size();
//	vector<int> sps(n);
//	for (int i = 0; i < n; ++i)
//	{
//		sps[i] = (s[i]);
//	}
//	vector<int> post;
//
//	// 倍增算法
//	switch (strage)
//	{
//	case 0:
//		da0(sps, post);
//		break;
//	case 1:
//	default:
//		da0(sps, post);
//		break;
//	}
//	
//
//	for (int i = 0; i < n; ++i)
//	{
//		printf("[%3d] : %s\n",i, &(s[post[i]]));
//	}
//	return post;
//}
////
////void main()
////{
////	gss::Timing t;
////
////	string test;
////	char buf[2];
////	for (int i = 0; i < 26; ++i)
////	{
////		snprintf(buf,sizeof(buf), "%c", (i % 26) + 'a');
////		test.append(buf);
////	}
////	t.start();
////	test = "aabaaaab";
////	post_substr(test);
////	
////	t.end();
////	getchar();
////}


//#include<iostream>
//using namespace std;
//
//int getIntFromStr(char* str, int len=2)
//{
//	int ret = 0;
//	for (int i = 0; i < len; ++i)
//	{
//		ret = 10 * ret + (str[i] - '0');
//	}
//	return ret;
//}
//
//int main(void)
//{
//	int n;
//	char buf[9] /*= "19:90:23"*/;
//	for (cin >> n/*n=1*/; n > 0; --n)
//	{
//		cin >> buf;
//		int hour = getIntFromStr(buf);
//		int minu = getIntFromStr(buf + 3);
//		int seco = getIntFromStr(buf + 6);
//
//		if (hour > 23)
//		{
//			hour %= 10;
//		}
//
//		if (minu > 59)
//		{
//			minu %= 10;
//		}
//
//		if (seco > 59)
//		{
//			seco %= 10;
//		}
//
//		printf("%02d:%02d:%02d\n", hour, minu, seco);
//	}
//	//getchar();
//	return 0;
//}



//#include<iostream>
//#include<vector>
//using namespace std;
//
//const int max_mn = 100;
//char strs[max_mn*max_mn];
//
//int main(void)
//{
//	int T, m, n, i, t_len, j, ret, k, index;
//	cin >> T;
//	//T = 1;
//
//	
//	char target[100];
//
//	while (T--)
//	{
//		ret = 0;
//		cin >> m >> n;
//		//m = n = 3;
//		for (i = 0; i < m; ++i)
//		{
//			cin >> &(strs[i*max_mn]);
//			strs[i*max_mn + n] = '\0';
//		}
//		cin >> target;
//		t_len = 0;
//		while(target[t_len]!='\0') ++t_len;
//		for (i = 0; i < m; ++i)
//		{
//			for (j = 0; j < n; ++j)
//			{
//				index = i*max_mn + j;
//				if (target[0] != strs[index])
//					continue;
//				if (j <= n - t_len)
//				{
//					for (k = 0; k < t_len; ++k)
//					{// 右
//						index = (i*max_mn + j + k);
//						if (target[k] != strs[index])
//							break;
//					}
//					index = (i*max_mn + j + t_len - 1);
//					if (k == t_len && target[t_len - 1] == strs[index])
//						++ret;
//				}
//				if (i <= m - t_len)
//				{
//					for (k = 0; k < t_len; ++k)
//					{// 下
//						index = (i + k)*max_mn + j;
//						if (target[k] != strs[index])
//							break;
//					}
//					index = ((i + t_len - 1)*max_mn + j);
//					if (k == t_len && target[t_len - 1] == strs[index])
//						++ret;
//				}
//				if (i <= m - t_len && j <= n - t_len)
//				{
//					for (k = 0; k < t_len; ++k)
//					{// 右下
//						index = ((i + k)*max_mn + j + k);
//						if (target[k] != strs[index])
//							break;
//					}
//					index = ((i + t_len - 1)*max_mn + j + t_len - 1);
//					if (k == t_len && target[t_len - 1] == strs[index])
//						++ret;
//				}
//			}
//		}
//		printf("%d\n", ret);
//	};
//	//getchar();
//	return 0;
//}

#include<iostream>
#include<vector>
using namespace std;

const int MINUTE = 60;
const int HOUR = 60 * MINUTE;
const int DAY = 24 * HOUR;
const int MONTH = 30 * DAY;
const int YEAR = 12 * MONTH;

int get_int(char* str)
{
	int ret = 0;
	while (*str != '\0' && *str != '/' && *str != ':')
	{
		ret = 10 * ret + ((*str) - '0');
		str++;
	}
		
	return ret;
}
int get_time(char* time_str1, char* time_str2)
{
	int ret = 0, month, day, year, hour, minute, second;
	month = get_int(time_str1);
	day = get_int(time_str1 + 3);
	year = get_int(time_str1 + 6);

	hour = get_int(time_str2);
	minute = get_int(time_str2 + 3);
	second = get_int(time_str2 + 6);
	
	return (year - 1970)*YEAR
		+ (month - 1)*MONTH
		+ (day - 1)*DAY
		+ (hour - 1)*HOUR
		+ (minute - 1)*MINUTE
		+ second;
}

void cal_flows_0(void)
{
	int N, M, ret, i, j;
	char time_str1[11];
	char time_str2[9];

	int start, end;

	int flow;

	vector<int> time_points;
	vector<int> flows;

	cin >> N;
	time_points.resize(N);
	flows.resize(N);
	ret = 0;
	for (i = 0; i < N; ++i)
	{
		cin >> time_str1 >> time_str2 >> flow;
		time_points[i] = get_time(time_str1, time_str2);
		flows[i] = flow;
	}

	cin >> M;
	for (i = 0; i < M; ++i)
	{
		cin >> time_str1 >> time_str2;
		start = get_time(time_str1, time_str2);
		cin >> time_str1 >> time_str2;
		end = get_time(time_str1, time_str2);
		ret = 0;
		for (j = 0; j < N; ++j)
		{
			if (time_points[j] > end)
				break;
			if (time_points[j] >= start)
				ret += flows[j];
		}
		cout << ret << endl;
	}
}

#include<deque>
#include<queue>
#include<sstream>
#include<algorithm>
#include<map>
class Solution {
private:
	struct Node {
		int index_;
		int value_;
		Node(int index, int value)
			:index_(index)
			, value_(value)
		{}
	};
public:
	vector<int> maxInWindows(const vector<int>& nums, unsigned int size)
	{
		vector<int> ret;
		int n = nums.size();
		if (n < size || n <= 0)
			return ret;

		deque<Node> kq;
		deque<Node>::iterator it;
		int i, index = 0;
		for (i = 0; i<n; ++i) {
			if (kq.empty() || nums[i]>kq.front().value_) {
				kq.clear();
				kq.push_back(Node(i, nums[i]));
			}
			else {
				it = kq.begin();
				while (it != kq.end() && (*it).value_>nums[i]) ++it;
				kq.erase(it, kq.end());
				kq.push_back(Node(i, nums[i]));
			}
			while (!kq.empty() && (i - kq.front().index_) >= size) {
				kq.pop_front();
			}
			if (!kq.empty() && i >= size - 1)
				ret.push_back(kq.front().value_);
		}

		return ret;
	}

	struct TreeNode {
		int val;
		struct TreeNode *left;
		struct TreeNode *right;
		TreeNode(int x) :
			val(x), left(NULL), right(NULL) {
		}
	};

	char* Serialize(TreeNode *root) {
		stringstream str("");
		queue<TreeNode*> nodeQueues[2];
		TreeNode* temp = nullptr;
		if (!root)
			return nullptr;
		int level = 0, other;
		nodeQueues[level].push(root);
		while (!nodeQueues[0].empty()
			|| !nodeQueues[1].empty()) {
			other = (level + 1 + 2) % 2;
			while (!nodeQueues[level].empty()) {
				temp = nodeQueues[level].front();
				nodeQueues[level].pop();
				if (!temp) {
					str << INT_MIN << "\n";
				}
				else {
					str << temp->val << "\n";
					nodeQueues[other].push(temp->left);
					nodeQueues[other].push(temp->right);
				}
			}
			level = other;
		}
		string st = str.str();
		char* ret = new char[st.size() + 1];
		for (int i = 0; i < st.size(); ++i) {
			ret[i] = st[i];
		}
		ret[st.size()] = '\0';
		return ret;
	}
	TreeNode* Deserialize(char *s) {
		if (s == nullptr)
			return nullptr;
		stringstream str(s);
		int val;
		string discard;
		char ch;
		str >> val;
		TreeNode* root = new TreeNode(val);
		queue<TreeNode*> nodeQueues[2];
		TreeNode* temp = nullptr;
		int level = 0, other;
		nodeQueues[level].push(root);
		while (!nodeQueues[0].empty()
			|| !nodeQueues[1].empty()) {
			other = (level + 1 + 2) % 2;
			while (!nodeQueues[level].empty()) {
				temp = nodeQueues[level].front();
				nodeQueues[level].pop();
				str >> val;
				if (val!=INT_MIN) {
					temp->left = new TreeNode(val);
					nodeQueues[other].push(temp->left);
				}
				str >> val;
				if (val != INT_MIN) {
					temp->right = new TreeNode(val);
					nodeQueues[other].push(temp->right);
				}
			}
			level = other;
		}
		return root;
	}

	/////////////////////////////////////////
	int minCut(string s) {
		int n = s.size();
		int i, j;
		vector<int> cuts(n + 1, 0);
		cuts[n] = -1;
		vector<vector<int>> isPalindrome(n);
		for (i = 0; i < n; i++)isPalindrome[i].resize(n, 0);
		for (i = n - 1; i >= 0; --i) {
			cuts[i] = 2147483647;
			for (j = i; j < n; j++) {
				if (s[i] == s[j] && (j - i < 2 || isPalindrome[i + 1][j - 1])) {
					isPalindrome[i][j] = 1;
					cuts[i] = min(cuts[i], cuts[j + 1] + 1);
				}
			}
		}
		return cuts[0];
	}

	private:
		int str2i(string& s, int start, int end) {
			int i, ret = 0, temp;
			for (i = start; i<end; i++) {
				temp = (s[i] - '0') + 0;
				ret = ((ret * 10) + temp);
			}
			return ret;
		}
		bool isdecode(int num) {
			return (num >= 1 && num <= 26);
		}
public:
	int numDecodings(string s) {
		int i, j, n = s.size();
		if (n == 0) return 0;
		vector<int> decodeRet(n + 1, 0);
		decodeRet[n] = 1;
		for (i = n - 1; i >= 0; i--) {
			for (j = i; j<n; j++) {
				if (!isdecode(str2i(s, i, j + 1)))
					break;
				decodeRet[i] += decodeRet[j + 1];
			}
		}
		return decodeRet[0];
	}

public:
	void insert_sort(vector<int>& nums, int start=-1, int end=-1) {
		if (start == -1 && start == end) start = 0, end = nums.size()-1;
		if (start >= end) return;
		int i, j, t;
		for (i = start; i <= end; i++) {
			t = nums[i];
			for (j = i - 1; j >= start; j--) {
				if (t < nums[j]) {
					nums[j + 1] = nums[j];
				}
				else {
					nums[j + 1] = t;
					break;
				}
			}
		}
	}

	void swap(vector<int>& nums, int i, int j) {
		int temp = nums[i];
		nums[i] = nums[j];
		nums[j] = temp;
	}

	void quick_sort_helper(vector<int>& nums, int start, int end) {
		if (end >= nums.size()) return;
		if (end <= start) return;
		/*if (end - start < 16)
			return insert_sort(nums, start, end);*/
		int i, j, prio;
		prio = start;
		i = start;
		j = end;
		while (i < j) {
			while (i < end && nums[i] <= nums[prio])i++;
			while (j > start && nums[j] >= nums[prio])j--;
			swap(nums, i, j);
		}
		swap(nums, i, j);
		swap(nums, start, j);
		quick_sort_helper(nums, start, j - 1);
		quick_sort_helper(nums, j + 1, end);
	}

	void quick_sort(vector<int>& nums) {
		quick_sort_helper(nums, 0, nums.size()-1);
	}

	vector<int> ret_pos_;

	template<int n=8,typename T=int>
	void queen_print(T pos, T mask = ((INT_MAX) >> (sizeof(T) * 8 - n - 1))) {
		int i;
		for (i = 0; !(pos & (1 << i)); i++) {
			std::cout << "  |";
		}
		std::cout << "& |";
		i++;
		for (; (mask &(1 << i)); i++) {
			std::cout << "  |";
		}
		std::cout << std::endl;
	}

	template<int n=8,typename T=int>
	T queen_helper(T row, T l, T r, int index = 0, T mask = (~(((T)1)<<(sizeof(T)*8-1))) >> (sizeof(T) * 8 - n - 1)) {
		long long test = ~(((T)1) << (sizeof(T) * 8 - 1));
		if (row == mask)
		{
			/*for (int i = 0; i < n; i++) {
				queen_print<n,T>(ret_pos_[i]);
			}
			std::cout << "\n------------------------------\n";*/
			return 1;
		}
		T pos = (~(row | l | r)) & mask;
		T t, ret = 0;
		while (pos) {
			t = pos & (~pos + 1);
			ret_pos_[index] = t;
			ret += queen_helper<n,T>(row | t, ((l | t) << 1), ((r | t) >> 1), index + 1);
			pos -= t;
		}
		return ret;
	}

	template<int n = 8,typename T=int>
	T queen() {
		ret_pos_.resize(n, 0);
		return queen_helper<n,T>(0, 0, 0);
	}
};

template<class _Ty,
	size_t _Size>
	constexpr _Ty *end_test(_Ty(&_Array)[_Size]) _NOEXCEPT
{	// get end of array
	std::cout << _Size;
	return (_Array + _Size);
}

int main(void) {
	Solution solution;
	/*solution.numDecodings("26");*/
	vector<int> test_data{ 8,7,6,5,4,3,2,1,8,1,1 };
	char t[50];
	std::cout << ((-4) >> 5);
	//solution.quick_sort(test_data);
	//std::cout << solution.queen<25,long long>() << std::endl;
	return 0;
}

//int main(void) {
//	Solution solu;
//	using TreeNode = Solution::TreeNode;
//	int s = 1;
//	TreeNode* root = new TreeNode(s++);
//	root->left = new TreeNode(s++);
//	root->right = new TreeNode(s++);
//	root->right->left = new TreeNode(s++);
//	root->right->right = new TreeNode(s++);
//
//	char* ret = solu.Serialize(root);
//	std::cout << ret << endl;
//	solu.Deserialize(ret);
//	getchar();
//	return 0;
//}


#include<iostream>
#include<vector>
using namespace std;

template<typename T>
T max(T& a, T&b) {
	return a > b ? a : b;
}

template<typename T>
T min(T& a, T& b) {
	return a > b ? b : a;
}

//int main(void) {
//	vector<int> nums;
//	long long max_nums[50][11] = { 0 }, min_nums[50][11] = { 0 };
//	int n, k, d, tmp, i, j, l;
//
//	cin >> n;
//	nums.resize(n);
//	for (i = 0; i<n; ++i) {
//		cin >> tmp; 
//		nums[i] = tmp;
//		max_nums[i][0] = tmp;
//		min_nums[i][0] = tmp;
//	}
//	cin >> k >> d;
//	long long ret = 0;
//	for (i = 0; i < n; ++i) {
//		for (j = 1; j < k; ++j) {
//			for (l = i - 1; l >= max(i - d, 0); --l) {
//				max_nums[i][j] = max(max_nums[i][j], max(max_nums[l][j - 1] * nums[i], min_nums[l][j - 1] * nums[i]));
//				min_nums[i][j] = min(min_nums[i][j], min(max_nums[l][j - 1] * nums[i], min_nums[l][j - 1] * nums[i]));
//			}
//		}
//		ret = max(ret, max(max_nums[i][k - 1], min_nums[i][k - 1]));
//	}
//	cout << ret;
//	return 0;
//}