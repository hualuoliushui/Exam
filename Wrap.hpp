#pragma once

// 不支持 const volatile版本

#include<functional>
template<typename F
	,typename... Args
	,typename = typename std::enable_if<!std::is_member_function_pointer<F>::value>::type
>
void wrap(F&& f, Args&& ... args) {
	return f(std::forward<Args>(args)...);
}

// 支持成员函数
template<typename R
	,typename C
	,typename... DArgs
	,typename P
	,typename... Args
>
void wrap(R(C::*f)(DArgs...), P&& p, Args&& ...args) {
	return (*p.*f)(std::forward<Args>(args)...);
}