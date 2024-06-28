#include <random>

template<typename T>
class RandomT
{
public: 
	static T value(T min, T max)
	{
		return min + (max - min) * value();
	}

	static T value()
	{
		static std::uniform_real_distribution<T> distribution(0.0, 1.0);
		static std::minstd_rand generator;
		return distribution(generator);
	}
};

using Random = RandomT<float>;