#include<iostream>
#include"Visitor.hpp"
using namespace std;

struct stA;
struct stB;

struct Base {
	typedef Visitor<stA, stB> MytVisitor;
	virtual void accept(MytVisitor&) = 0;
};

struct stA :Base {
	double val;
	void accept(Base::MytVisitor& v) {
		v.visit(*this);
	}
};

struct stB :Base {
	double val;
	void accept(Base::MytVisitor& v) {
		v.visit(*this);
	}
};

struct PrintVisitor
	:Base::MytVisitor
{
	void visit(const stA& a) {
		cout << "from stA: " << a.val << endl;
	}

	void visit(const stB& b) {
		cout << "from stB: " << b.val << endl;
	}
};

void TestVisitor() {
	PrintVisitor vis;
	stA a;
	a.val = 8.90;
	stB b;
	b.val = 9;
	Base* base = &a;
	base->accept(vis);
	base = &b;
	base->accept(vis);
}

//int main(void) {
//	TestVisitor();
//	getchar();
//	return 0;
//}