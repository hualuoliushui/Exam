#include "Any.hpp"
#include<iostream>
#include<string>
using namespace std;
void TestAny() {
	Any n;
	auto r = n.IsNull();
	string s1 = "hello";
	n = s1;
	n.AnyCast<string>();
	Any n1 = 1;
	n1.Is<int>();
}

//int main(void) {
//	TestAny();
//	getchar();
//	return 0;
//}



class Test {
public:
	template<typename A>
	void print_(A a) {
		std::cout << a << "\n";
	}
	template<typename... T>
	void print(T... args) {
		std::initializer_list<int>{ (print_(args), 0)... };
	}
};
//
//int main(void) {
//	Test t;
//	t.print(1, 1.1, "gss");
//	getchar();
//	return 0;
//}