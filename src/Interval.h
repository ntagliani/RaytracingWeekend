#pragma once

#include <limits>

template<typename T>
class IntervalT
{
public:

	IntervalT() = default;

	IntervalT(T _min, T _max)
		:min(_min)
		,max(_max) {

	}

	T min{ std::numeric_limits<T>::infinity() };
	T max{ -std::numeric_limits<T>::infinity()};

	bool contains(const T& value) const
	{
		return min <= value && value <= max;
	}

	bool excludes(const T& value) const
	{
		return value < min || value > max;
	}

	bool surrounds(const T& value) const
	{
		return min < value && value < max;
	}

	static const IntervalT empty;
	static const IntervalT universe;

};

template<typename T>
const IntervalT<T> IntervalT<T>::empty = IntervalT{};

template<typename T>
const IntervalT<T> IntervalT<T>::universe = IntervalT{ -std::numeric_limits<T>::infinity(),  std::numeric_limits<T>::infinity()};

using Interval = IntervalT<float>;
