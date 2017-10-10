#include<iostream>
#include"AOP.hpp"
#include"Timer.hpp"
struct TimeElapseAspect {
	void Before(int i) {
		m_lastTime = m_t.elapsed();
	}

	void After(int i) {
		std::cout << "time elapsed: " << m_t.elapsed() - m_lastTime << std::endl;
	}

private:
	double m_lastTime;
	Timer m_t;
};

struct LoggingAspect {
	void Before(int i) {
		std::cout << "entering" << std::endl;
	}

	void After(int i) {
		std::cout << "leaving" << std::endl;
	}
};

void foo(int a) {
	std::cout << "real HT function: " << a << std::endl;
}

//int main(void) {
//	Invoke<LoggingAspect, TimeElapseAspect>(&foo, 1);
//	std::cout << "-----------------------------" << std::endl;
//	Invoke<TimeElapseAspect, LoggingAspect>(&foo, 1);
//	return 0;
//
//}