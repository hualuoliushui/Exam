//#include <iostream>
//using std::cout;
//using std::cin;
//using std::endl;
//
//
////��ģʽ�еĵڶ����ַ����ǡ�*��ʱ��
////1������ַ�����һ���ַ���ģʽ�еĵ�һ���ַ���ƥ�䣬��ô�ַ�����ģʽ������һ���ַ���Ȼ��ƥ��ʣ��ġ�
////2����� �ַ�����һ���ַ���ģʽ�еĵ�һ���ַ��಻ƥ�䣬ֱ�ӷ���false��
////
////����ģʽ�еĵڶ����ַ��ǡ�*��ʱ��
////����ַ�����һ���ַ���ģʽ��һ���ַ���ƥ�䣬��ģʽ����2���ַ�������ƥ�䡣����ַ�����һ���ַ���ģʽ��һ���ַ�ƥ�䣬������3��ƥ�䷽ʽ��
////1��ģʽ����2�ַ����൱��x*�����ԣ�
////2���ַ�������1�ַ���ģʽ����2�ַ���
////3���ַ�������1�ַ���ģʽ���䣬������ƥ���ַ���һλ����Ϊ*����ƥ���λ��
//
//class Solution {
//private:
//	inline bool isAsterisk(char ch){
//		return ch == '*';
//	}
//	inline bool isDot(char ch){
//		return ch == '.';
//	}
//	inline bool isEnd(char ch){
//		return ch == '\0';
//	}
//	inline bool isSame(char ch1, char ch2){
//		return ch1 == ch2;
//	}
//	
//
//	bool helper(char* str, char* pattern){
//		if (isEnd(*str) && isEnd(*pattern))
//			return true;
//		if (!isEnd(*str) && isEnd(*pattern))
//			return false;
//
//		char cur = *pattern;
//		char next = *(pattern + 1);
//		if (isAsterisk(next)){												// ģʽ�еĵڶ����ַ��� "*" 
//			if (isSame(cur, *str)											// �ַ�����һ���ַ���ģʽ��һ���ַ�ƥ��
//				|| (isDot(*pattern) && !isEnd(*str)))						
//				return 
//					helper(str + 1, pattern + 2)							// �ַ�������1�ַ���ģʽ����2�ַ�d
//					|| helper(str + 1, pattern)								// �ַ�������1�ַ���ģʽ���䣬������ƥ���ַ���һλ����Ϊ*����ƥ���λ
//					|| helper(str, pattern + 2);							// ģʽ����2�ַ����൱��x*������
//			else															// �ַ�����һ���ַ���ģʽ��һ���ַ���ƥ��
//				return helper(str, pattern + 2);							// ģʽ����2���ַ�������ƥ��
//		}
//		else{																// ģʽ�еĵڶ����ַ����ǡ�*��
//			if (isSame(cur, *str) || (isDot(*pattern) && !isEnd(*str)))		// �ַ�����һ���ַ���ģʽ�еĵ�һ���ַ���ƥ��
//				return helper(str + 1, pattern + 1);						// �ַ�����ģʽ������һ���ַ���Ȼ��ƥ��ʣ���
//			return															// �ַ�����һ���ַ���ģʽ�еĵ�һ���ַ��಻ƥ��
//				false;													    // ֱ�ӷ��� false
//		}
//	}
//
//public:
//	bool match(char* str, char* pattern)
//	{
//		if (pattern == nullptr || str == nullptr){
//			return false;
//		}
//
//		return helper(str, pattern);
//	}
//};
//
//int main(void){
//	Solution s;
//
//	char str[50] = "aaa";
//	char pattern[50] = "ab*a";
//	//cin >> str >> pattern;
//	cout <<	s.match(str, pattern);
//	return 0;
//}