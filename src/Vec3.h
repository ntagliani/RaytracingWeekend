#pragma once

#include "Random.h"

#include <cmath>
#include <cstring>
#include <ostream>
#include <type_traits>

#include <array>

#define DECLARE_MEMBER_ACCESSOR(name, pos, fieldname)                          \
    template <typename U = T>                                                  \
    typename std::enable_if_t<(N > pos), U> name() const                       \
    {                                                                          \
        return fieldname[pos];                                                 \
    }                                                                          \
    template <typename U = T> typename std::enable_if_t<(N > pos), U> &name()  \
    {                                                                          \
        return fieldname[pos];                                                 \
    }

template <typename T, size_t N> class vec
{
  public:
    using value_type = T;
    using size_type = size_t;
    static constexpr size_type size = N;
    using reference = value_type &;
    using const_reference = const value_type &;
    using pointer = value_type *;
    using const_pointer = const value_type *;

    using iterator = pointer;
    using const_iterator = const_pointer;

    vec() { memset(m_data, 0, bytes()); }

    vec(const std::initializer_list<T> values)
    {
        if (values.size() == N)
        {
            size_t i = 0;
            for (auto v : values)
            {
                m_data[i++] = v;
            }
        }
    }

    template <typename Arg, typename... Args> vec(Arg value, Args... args)
    {
        assign<0>(value, args...);
    }

    vec(const vec &v) = default;
    vec &operator=(const vec &v) = default;
    vec(vec &&) = default;
    vec &operator=(vec &&) = default;

    DECLARE_MEMBER_ACCESSOR(x, 0, m_data);
    DECLARE_MEMBER_ACCESSOR(y, 1, m_data);
    DECLARE_MEMBER_ACCESSOR(z, 2, m_data);
    DECLARE_MEMBER_ACCESSOR(w, 3, m_data);

    DECLARE_MEMBER_ACCESSOR(a, 0, m_data);
    DECLARE_MEMBER_ACCESSOR(b, 1, m_data);
    DECLARE_MEMBER_ACCESSOR(c, 2, m_data);
    DECLARE_MEMBER_ACCESSOR(d, 3, m_data);

    size_t bytes() const { return N * sizeof(T); }

    const T *data() const { return &m_data[0]; }

    /// Iterators

    iterator begin() { return &*m_data.begin(); }

    const_iterator begin() const { return cbegin(); }

    const_iterator cbegin() const { return &*m_data.begin(); }

    iterator end() { return &*m_data.begin() + N; }

    const_iterator end() const { return cend(); }

    const_iterator cend() const { return &*m_data.cbegin() + N; }

  private:
    template <size_t idx = 0, typename Arg = T, typename... Args>
    inline void assign(Arg value, Args... args)
    {
        m_data[idx] = value;
        assign<idx + 1>(args...);
    }

    template <size_t idx, typename = std::enable_if_t<(idx <= N)>>
    inline void assign()
    {
    }

    std::array<T, N> m_data;
};

template <typename T> class vec3
{
  public:
    vec3() : e{0, 0, 0} {}
    vec3(T x, T y, T z) : e{x, y, z} {}

    T x() const { return e[0]; }
    T y() const { return e[1]; }
    T z() const { return e[2]; }

    T &x() { return e[0]; }
    T &y() { return e[1]; }
    T &z() { return e[2]; }

    vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
    T operator[](int i) const { return e[i]; }
    T &operator[](int i) { return e[i]; }

    vec3 &operator+=(const vec3 &v)
    {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }

    vec3 &operator+=(const T t)
    {
        e[0] += t;
        e[1] += t;
        e[2] += t;
        return *this;
    }

    vec3 &operator*=(const T t)
    {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }

    vec3 &operator/=(const T t) { return *this *= 1 / t; }

    T length() const { return std::sqrt(length_squared()); }

    T length_squared() const { return e[0] * e[0] + e[1] * e[1] + e[2] * e[2]; }

    bool near_zero() const
    {
        constexpr static T epsilon = T(1e-6);
        return std::fabs(e[0]) < epsilon && std::fabs(e[1]) < epsilon &&
               std::fabs(e[2]) < epsilon;
    }

    vec3 &normalize()
    {
        *this /= length();
        return *this;
    }

    static vec3 random()
    {
        return vec3(RandomT<T>::value(), RandomT<T>::value(),
                    RandomT<T>::value());
    }

    static vec3 random(T min, T max)
    {
        return vec3(RandomT<T>::value(min, max), RandomT<T>::value(min, max),
                    RandomT<T>::value(min, max));
    }

    T e[3];
};

// vec3 Utility Functions
template <typename T>
inline std::ostream &operator<<(std::ostream &out, const vec3<T> &v)
{
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

template <typename T>
inline vec3<T> operator+(const vec3<T> &u, const vec3<T> &v)
{
    return vec3<T>(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

template <typename T> inline vec3<T> operator+(const vec3<T> &u, const T v)
{
    return vec3<T>(u.e[0] + v, u.e[1] + v, u.e[2] + v);
}

template <typename T>
inline vec3<T> operator-(const vec3<T> &u, const vec3<T> &v)
{
    return vec3<T>(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

template <typename T>
inline vec3<T> operator*(const vec3<T> &u, const vec3<T> &v)
{
    return vec3<T>(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

template <typename T> inline vec3<T> operator*(T t, const vec3<T> &v)
{
    return vec3<T>(t * v.e[0], t * v.e[1], t * v.e[2]);
}

template <typename T> inline vec3<T> operator*(const vec3<T> &v, T t)
{
    return t * v;
}

template <typename T> inline vec3<T> operator/(vec3<T> v, T t)
{
    return (1 / t) * v;
}

template <typename T> inline T dot(const vec3<T> &u, const vec3<T> &v)
{
    return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}

template <typename T> inline vec3<T> cross(const vec3<T> &u, const vec3<T> &v)
{
    return vec3<T>(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                   u.e[2] * v.e[0] - u.e[0] * v.e[2],
                   u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

template <typename T> inline vec3<T> unit_vector(vec3<T> v)
{
    return v / v.length();
}

template <typename T> inline vec3<T> random_unit_vector()
{
    return unit_vector(vec3<T>::random(T(-1), T(1)));
}

using vec3f = vec3<float>;
using vec3d = vec3<double>;

using Pixel = vec3f;
using Color = vec3f;
using Point = vec3f;
