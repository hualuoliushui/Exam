#pragma once
#include<iostream>
#include<string>
#include<functional>
#include<map>
using namespace std;

#include"NonCopyable.hpp"

template<typename Func>
class Events
	:NonCopyable
{
public:
	Events()
	{}
	~Events()
	{}

	int connect(Func& f) {
		return connect(std::move(f));
	}

	int connect(Func&& f) {
		return assign(std::forward<Func>(f));
	}

	void disconnect(int key) {
		connections_.erase(key);
	}

	template<typename... Args>
	void notify(Args&&... args) {
		for (auto& it : connections_) {
			it.second(std::forward<Args>(args)...);
		}
	}

private:
	template<typename F>
	int assign(F&& f) {
		int k = observerId_++;
		connections_.emplace(k, std::forward<F>(f));
		return k;
	}

	int observerId_ = 0;
	std::map<int, Func> connections_;
};