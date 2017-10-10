#pragma once
#include<chrono>
using namespace std;
using namespace std::chrono;

class Timer
{
public:
	Timer()
		:m_begin(high_resolution_clock::now())
	{}
	void reset() {
		m_begin = high_resolution_clock::now();
	}

	// ∫¡√Î
	template<typename Duration=milliseconds>
	int64_t elapsed() const {
		return duration_cast<Duration>(high_resolution_clock::now() - m_begin).count();
	}

	// Œ¢√Î
	int64_t elapsed_micro() const {
		return elapsed<microseconds>();
	}
	
	// ƒ…√Î
	int64_t elapsed_nano() const {
		return elapsed<nanoseconds>();
	}
private:
	time_point<high_resolution_clock> m_begin;
};