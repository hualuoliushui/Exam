#pragma once

template<typename... Types>
struct Visitor;

template<typename T
	,typename... Types
>
struct Visitor<T, Types...> 
	: Visitor<Types...>
{
	// 通过using避免隐藏基类的Visit同名方法
	using Visitor<Types...>::visit;
	virtual void visit(const T&) = 0;
};

template<typename T>
struct Visitor<T>
{
	virtual void visit(const T&) = 0;
};