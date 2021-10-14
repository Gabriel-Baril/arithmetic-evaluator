#pragma once
#include <type_traits>
#include "wrapper.hpp"

enum class Bound { Null };

template<typename T>// requires std::is_arithmetic_v<T>
struct Interval
{
	T val;
	wrapper<T>* min;
	wrapper<T>* max;
	Interval(T val, const wrapper<T>& min, const wrapper<T>& max)
	{
		this->min = &const_cast<wrapper<T>&>(min);
		this->max = &const_cast<wrapper<T>&>(max);
		set_val(val);
	}

	Interval(T val, Bound, const wrapper<T>& max)
	{
		this->min = nullptr;
		this->max = &const_cast<wrapper<T>&>(max);
		set_val(val);
	}

	Interval(T val, const wrapper<T>& min, Bound) : min(min), max(max)
	{
		this->min = &const_cast<wrapper<T>&>(min);
		this->max = nullptr;
		set_val(val);
	}

	void set_val(T val)
	{
		if (min != nullptr && val < min->val)		 this->val = min->val;
		else if (max != nullptr && val > max->val)	 this->val = max->val;
		else										 this->val = val;
	}

	void set_min(T min)
	{
		this->min->val = min;
	}

	void set_max(T max)
	{
		this->max->val = max;
	}

	T get_val()
	{
		return this->val;
	}

	T get_min()
	{
		return this->min->val;
	}

	T get_max()
	{
		return this->max->val;
	}
};