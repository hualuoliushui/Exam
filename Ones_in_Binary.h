#ifndef ONES_IN_BINARY_H
#define ONES_IN_BINARY_H

namespace gss
{
	/*
		T葎 char、short、 int、long、long long
	*/
	template<typename T>
	class Ones_in_Binary
	{
	protected:
		
	public:
		static T solve(T v)
		{
			T num = 0;
			while (v)
			{
				v &= (v - 1);
				++num;
			}
			return num;
		}
	};
}

#endif