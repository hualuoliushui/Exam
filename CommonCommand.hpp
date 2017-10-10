#pragma once
#include<functional>
#include<type_traits>

template<typename R=void>
struct CommonCommand {
private:
	std::function<R()> f_;

public:
	// ֧�� �ɵ��ö���
	template<typename F
		, typename... Args
		, typename = typename std::enable_if<!std::is_member_function_pointer<F>::value::type
		>
		void wrap(F&& f, Args&&... args) {
		f_ = [&] {return f(args...); };
	}

	// ֧�� ������Ա����
	template<typename R
		,typename C
		,typename... DArgs
		,typename P
		,typename... Args
	>
		void wrap(R(C::*f)(DArgs...) const, P&& p, Args&&... args) {
		f_ = [&, f] {return (*p.*f)(args...); };
	}

	// ֧�� �ǳ�����Ա����
	template<typename R
		,typename C
		,typename... DArgs
		,typename P
		,typename... Args
	>
		void wrap(R(C::*f)(DArgs...), P&& p, Args&&... args) {
		f_ = [&, f] {return (*p.*f)(args...); };
	}

	R Excecute() {
		return f_();
	}
};