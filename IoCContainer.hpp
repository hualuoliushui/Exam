#pragma once
#include<string>
#include<unordered_map>
#include<memory>
#include<functional>
using namespace std;
#include"Any.hpp"
#include"NonCopyable.hpp"

class IoCContainer {
public:
	IoCContainer(void) {}
	~IoCContainer(void) {}

	// 支持 依赖对象
	template<typename T
		,typename Depend
		,typename... Args
	>
	typename std::enable_if<!std::is_base_of<T,Depend>::value>::type
		RegisterType(const string& strKey) {
		std::function<T*(Args...)> function = [](Args... args) {return new T(new Depend(args...)); };
		RegisterType(strKey, function);
	}

	// 支持 继承
	template<typename T
		, typename Depend
		, typename... Args
	>
		typename std::enable_if<std::is_base_of<T, Depend>::value>::type
		RegisterType(const string& strKey) {
		std::function<T*(Args...)> function = [](Args... args) {return new Depend(args...); };
		RegisterType(strKey, function);
	}

	// 支持 普通对象
	template<class T
		,typename... Args>
		void RegisterSimple(const string& strKey) {
		std::function<T*(Args...)> function = [](Args... args) {return new T(args...); };
		RegisterType(strKey, function);
	}

	template<typename T
		, typename... Args
	>
		T* Resolve(const string& strKey, Args... args) {
		if (m_creatorMap.find(strKey) == m_creatorMap.end())
			return nullptr;
		Any resolver = m_creatorMap[strKey];
		std::function<T*(Args...)> function = resolver.AnyCast<std::function<T*(Args...)>>();

		return function(args...);
	}

	template<typename T
		, typename... Args
	>
		std::shared_ptr<T> ResolveShared(const string& strKey, Args... args) {
		T* t = Resolve<T>(strKey, args...);
		return std::shared_ptr<T>(t);
	}

private:
	void RegisterType(const string& strKey, Any constructor) {
		if (m_creatorMap.find(strKey) != m_creatorMap.end())
			throw std::invalid_argument("this key has already exist!");

		m_creatorMap.emplace(strKey, constructor);
	}
private:
	unordered_map<string, Any> m_creatorMap;
};
