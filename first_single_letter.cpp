//#include <iostream>
//#include <string>
//
////请实现一个函数用来找出字符流中第一个只出现一次的字符。例如，当从字符流中只读出前两个字符"go"时，第一个只出现一次的字符是"g"。当从该字符流中读出前六个字符“google"时，第一个只出现一次的字符是"l"。 
//
////利用一个int型数组表示256个字符，这个数组初值置为 0.
////每读出一个字符，将该字符的位置存入字符对应数组下标中。
////若值为0，则表示第一次读入，设置 编号 ++index
////若值不为0，则表示多次读入，直接设置编号为 -1
////之后在数组中找到>0的最小编号，该数组下标对应的字符为所求。
//
//#define NUM 128
//
//class Solution
//{
//private:
//	int index;
//	int letters[NUM];
//public:
//	Solution()
//	{
//		index = 0;
//		for (int i = 0; i < NUM; ++i) 
//			letters[i] = 0;
//	}
//	//Insert one char from stringstream
//	void Insert(char ch)
//	{
//		if (letters[ch]) letters[ch] = -1;
//		else{
//			letters[ch] = ++index;
//		}
//	}
//	//return the first appearence once char in current stringstream
//	char FirstAppearingOnce()
//	{
//		char ret = '#';
//		int min_value = ~(1 << 31);
//		for (int i = 0; i < NUM; i++){
//			if (i == 49){
//				int test = 0;
//				test++;
//			}
//			if (letters[i] >0 && letters[i]<min_value){
//				min_value = letters[i];
//				ret = i;
//			}
//		}
//
//		return ret;
//	}
//
//};
//
//int main(){
//	Solution s;
//	char key;
//	while (true){
//		std::cin.get(key);
//
//		if (key == '#') break;
//		if (key == '\n')continue;
//
//		s.Insert(key);
//		std::cout << "\n第一个只出现一次的字符：" << s.FirstAppearingOnce() << "\n";
//	}
//	return 0;
//}