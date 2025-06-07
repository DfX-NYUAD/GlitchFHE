#pragma once

#include <vector>
#include <cstddef>

namespace numpy
{

size_t sizeCeilPowerOfTwo(size_t n);

template <class T, class U> std::vector<std::vector<T>>
add(const std::vector<std::vector<T>> & a, const std::vector<U> & b);

template <class T, class U> std::vector<std::vector<std::vector<std::vector<T>>>>
add(const std::vector<std::vector<std::vector<std::vector<T>>>> & a, const std::vector<U> & b);

template <class T> T add_vector(std::vector<T> & v);

template <class T> std::vector<size_t> argmax(const std::vector<std::vector<T>> & m);

template <class T> std::vector<std::vector<T>>
combine(const std::vector<std::vector<std::vector<T>>> & a);

template <class T> size_t countEqual(const std::vector<T> & a, const std::vector<T> & b);

template <class T, class U> std::vector<std::vector<T>>
dot(const std::vector<std::vector<T>> & a, const std::vector<std::vector<U>> & b);

template <class T> T mean(const std::vector<T> & a);

template <class T> T // affects precision
mean(const std::vector<std::vector<T>> & a);

template <class T> T // affects precision
mean(const std::vector<std::vector<std::vector<T>>> & a);

template <class T> T mean(const std::vector<std::vector<std::vector<std::vector<T>>>> & a);

template <class T> std::vector<std::vector<T>>
reshape2d(const std::vector<std::vector<std::vector<std::vector<T>>>> & a, const std::vector<size_t> & dimensions);

template <class T> std::vector<std::vector<std::vector<std::vector<T>>>>
reshape4d(const std::vector<std::vector<T>> & m, const std::vector<size_t> & dimensions);

template <class T> std::vector<std::vector<T>>
reshapeOrder(const std::vector<std::vector<T>> & a, const std::vector<size_t> order);

template <class T> std::vector<std::vector<std::vector<T>>>
reshapeOrder(const std::vector<std::vector<std::vector<T>>> & a, const std::vector<size_t> order);

template <class T> std::vector<std::vector<std::vector<std::vector<T>>>>
reshapeOrder(const std::vector<std::vector<std::vector<std::vector<T>>>> & a, const std::vector<int> order);

template <class T, class U> T scale(const U & n, const T & scaler);

template <class T, class U> std::vector<T>
scale(const std::vector<U> & n, const T & scaler);

template <class T, class U> std::vector<std::vector<T>>
scale(const std::vector<std::vector<U>> & n, const T & scaler);

template <class T, class U> std::vector<std::vector<std::vector<T>>>
scale(const std::vector<std::vector<std::vector<U>>> & n, const T & scaler);

template <class T, class U> std::vector<std::vector<std::vector<std::vector<T>>>>
scale(const std::vector<std::vector<std::vector<std::vector<U>>>> & n, const T & scaler);

template <class T> std::vector<size_t> shape(const T & v);

template <class T> std::vector<size_t> shape(const std::vector<T> & v);

template <class T> T shift(const T & n, size_t s);

template <class T> std::vector<T> shift(const std::vector<T> & n, size_t s);

template <class T> std::vector<std::vector<T>> shift(const std::vector<std::vector<T>> & n, size_t s);

template <class T> std::vector<std::vector<std::vector<T>>> shift(const std::vector<std::vector<std::vector<T>>> & n, size_t s);

template <class T> std::vector<std::vector<std::vector<std::vector<T>>>> shift(const std::vector<std::vector<std::vector<std::vector<T>>>> & n, size_t s);

template <class T> T square(const T & a);

template <class T> std::vector<T> square(const std::vector<T> & a);

template <class T> std::vector<std::vector<T>> square(const std::vector<std::vector<T>> & a);

template <class T> std::vector<std::vector<std::vector<T>>> square(const std::vector<std::vector<std::vector<T>>> & a);

template <class T> std::vector<std::vector<std::vector<std::vector<T>>>> square(const std::vector<std::vector<std::vector<std::vector<T>>>> & a);

template <class T> std::vector<T> subset(const std::vector<T> & v, size_t begin, size_t end);

template <class T> std::vector<std::vector<std::vector<std::vector<T>>>> subvector(const std::vector<std::vector<std::vector<std::vector<T>>>> & x, const std::vector<size_t> & indices);

} // numpy

#include "numpy.hpp"
