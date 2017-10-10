#include"IoCContainer.hpp"
#include <iostream>
struct Bus {
	void Test() const { std::cout << "Bus::test()\n"; }
};

struct Car {
	void Test() const { std::cout << "Car::test()\n"; }
};

struct Base {
	virtual void Func() {}
	virtual ~Base(){}
};

struct DerivedB :Base
{
	void Func() override {
		std::cout << "call func in DerivedB\n";
	}
};

struct DerivedC : Base {
	void Func() override {
		std::cout << "call func in DerivedC\n";
	}
};

struct DerivedD : Base {
	void Func() override {
		std::cout << "call func in DerivedD\n";
	}
};

struct A {
	A(Base* ptr) :m_ptr(ptr) {}
	void Func() { m_ptr->Func(); }
	~A() {
		if (m_ptr != nullptr) {
			delete m_ptr;
			m_ptr = nullptr;
		}
	}
private:
	Base* m_ptr;
};

void TestIoC() {
	IoCContainer ioc;
	ioc.RegisterType<A, DerivedB>("B");
	ioc.RegisterType<A, DerivedC>("C");
	ioc.RegisterType<A, DerivedD>("D");

	auto pa = ioc.ResolveShared<A>("B");
	pa->Func();
	auto pa1 = ioc.ResolveShared<A>("C");
	pa1->Func();

	ioc.RegisterSimple<Bus>("bus");
	ioc.RegisterSimple<Car>("car");
	auto bus = ioc.ResolveShared<Bus>("bus");
	bus->Test();
	auto car = ioc.ResolveShared<Car>("car");
	car->Test();
}

//int main(void) {
//	TestIoC();
//	getchar();
//	return 0;
//}