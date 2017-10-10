#include"Events.hpp"
#include<iostream>
using namespace std;

struct stA {
	int a, b;
	void print(int a, int b) { cout << a << ", " << b << endl; }
};

void print(int a, int b) { cout << a << ", " << b << endl; }

//int main(void) {
//	Events<std::function<void(int, int)>> myevent;
//
//	auto key = myevent.connect(print);
//	stA t;
//	auto labdakey = myevent.connect([&t](int a, int b) {t.a = a; t.b = b; t.print(a, b); });
//	std::function<void(int, int)> f = std::bind(&stA::print, &t, std::placeholders::_1, std::placeholders::_2);
//	myevent.connect(f);
//
//	int a = 1, b = 2;
//	myevent.notify(a, b);
//	myevent.disconnect(key);
//	getchar();
//	return 0;
//}