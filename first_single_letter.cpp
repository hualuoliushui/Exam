//#include <iostream>
//#include <string>
//
////��ʵ��һ�����������ҳ��ַ����е�һ��ֻ����һ�ε��ַ������磬�����ַ�����ֻ����ǰ�����ַ�"go"ʱ����һ��ֻ����һ�ε��ַ���"g"�����Ӹ��ַ����ж���ǰ�����ַ���google"ʱ����һ��ֻ����һ�ε��ַ���"l"�� 
//
////����һ��int�������ʾ256���ַ�����������ֵ��Ϊ 0.
////ÿ����һ���ַ��������ַ���λ�ô����ַ���Ӧ�����±��С�
////��ֵΪ0�����ʾ��һ�ζ��룬���� ��� ++index
////��ֵ��Ϊ0�����ʾ��ζ��룬ֱ�����ñ��Ϊ -1
////֮�����������ҵ�>0����С��ţ��������±��Ӧ���ַ�Ϊ����
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
//		std::cout << "\n��һ��ֻ����һ�ε��ַ���" << s.FirstAppearingOnce() << "\n";
//	}
//	return 0;
//}