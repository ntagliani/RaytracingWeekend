#pragma once

#include <random>

template<typename T>
inline T unaryRand() {
    static std::uniform_real_distribution<T> distribution(T(0), T(1));
    static std::minstd_rand generator;
    return distribution(generator);
}
template<typename T>
inline T scaledUnaryRand(T min, T max) {
    return min + (max - min) * unaryRand<T>();

}


