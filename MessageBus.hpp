#pragma once
#include<string>
#include<functional>
#include<map>
#include "Any.hpp"
#include "function_traits.hpp"
#include "NonCopyable.hpp"

using namespace std;

class MessageBus
	:NonCopyable
{
public:
	// 注册消息
	template<typename F>
	void attach(F&& f, const string& strTopic = "") {
		auto func = to_function(std::forward<F>(f));
		add(strTopic, std::move(func));
	}

	// 发送消息
	template<typename R>
	void sendReq(const string& strTopic = "") {
		using function_type = std::function<R()>;
		string strMsgType = strTopic + typeid(function_type).name();
		auto range = map_.equal_range(strMsgType);
		for (Iterator it = range.first; it != range.second; ++it) {
			auto f = it->second.AnyCast<function_type>();
			f();
		}
	}
	template<typename R
		,typename... Args
	>
		void sendReq(Args&&... args, const string& strTopic = "") {
		using function_type = std::function<R(Args...)>;
		string strMsgType = strTopic + typeid(function_type).name();
		auto range = map_.equal_range(strMsgType);
		for (Iterator it = range.first; it != range.second; ++it) {
			auto f = it->second.AnyCast<function_type>();
			f(std::forward<Args>(args)...);
		}
	}

	// 移除某个主题，需要主题和消息类型
	template<typename R
		,typename... Args
	>
		void remove(const string& strTopic = "") {
		using function_type = std::function<R(Args...)>;// typename function_traits<void(CArgs)>::stl_function_type;

		string strMsgType = strTopic + typeid(function_type).name();
		int count = map_.count(strMsgType);
		auto range = map_.equal_range(strMsgType);
		map_.erase(range.first, range.second);
	}

private:
	template<typename F>
	void add(const string& strTopic, F&& f) {
		string strMsgType = strTopic + typeid(F).name();
		map_.emplace(std::move(strMsgType), std::forward<F>(F));
	}

private:
	std::multimap<string, Any> map_;
	typedef std::multimap<string, Any>::iterator Iterator;

};