#pragma once
#include <iostream>

template<typename T>
struct wrapper
{
	T val;
	wrapper(T val) : val(val) {}

	operator T()
	{
		return val;
	}

	wrapper<T>& operator=(T val)
	{
		this->val = val;
		return this;
	}
};