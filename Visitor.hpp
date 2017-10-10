#pragma once

template<typename... Types>
struct Visitor;

template<typename T
	,typename... Types
>
struct Visitor<T, Types...> 
	: Visitor<Types...>
{
	// ͨ��using�������ػ����Visitͬ������
	using Visitor<Types...>::visit;
	virtual void visit(const T&) = 0;
};

template<typename T>
struct Visitor<T>
{
	virtual void visit(const T&) = 0;
};