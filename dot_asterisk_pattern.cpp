//#include <iostream>
//using std::cout;
//using std::cin;
//using std::endl;
//
//
////当模式中的第二个字符不是“*”时：
////1、如果字符串第一个字符和模式中的第一个字符相匹配，那么字符串和模式都后移一个字符，然后匹配剩余的。
////2、如果 字符串第一个字符和模式中的第一个字符相不匹配，直接返回false。
////
////而当模式中的第二个字符是“*”时：
////如果字符串第一个字符跟模式第一个字符不匹配，则模式后移2个字符，继续匹配。如果字符串第一个字符跟模式第一个字符匹配，可以有3种匹配方式：
////1、模式后移2字符，相当于x*被忽略；
////2、字符串后移1字符，模式后移2字符；
////3、字符串后移1字符，模式不变，即继续匹配字符下一位，因为*可以匹配多位；
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
//		if (isAsterisk(next)){												// 模式中的第二个字符是 "*" 
//			if (isSame(cur, *str)											// 字符串第一个字符跟模式第一个字符匹配
//				|| (isDot(*pattern) && !isEnd(*str)))						
//				return 
//					helper(str + 1, pattern + 2)							// 字符串后移1字符，模式后移2字符d
//					|| helper(str + 1, pattern)								// 字符串后移1字符，模式不变，即继续匹配字符下一位，因为*可以匹配多位
//					|| helper(str, pattern + 2);							// 模式后移2字符，相当于x*被忽略
//			else															// 字符串第一个字符跟模式第一个字符不匹配
//				return helper(str, pattern + 2);							// 模式后移2个字符，继续匹配
//		}
//		else{																// 模式中的第二个字符不是“*”
//			if (isSame(cur, *str) || (isDot(*pattern) && !isEnd(*str)))		// 字符串第一个字符和模式中的第一个字符相匹配
//				return helper(str + 1, pattern + 1);						// 字符串和模式都后移一个字符，然后匹配剩余的
//			return															// 字符串第一个字符和模式中的第一个字符相不匹配
//				false;													    // 直接返回 false
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