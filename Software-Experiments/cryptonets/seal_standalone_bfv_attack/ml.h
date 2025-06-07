#pragma once

#include <chrono>
#include <string>
#include <vector>

namespace ml
{

template <class Type, class Tensor> void
showInfo(const std::string & title, const std::chrono::high_resolution_clock::time_point & t, const Tensor & tensor, const std::string & varname);

template <class T> std::vector<std::vector<std::vector<std::vector<T>>>>
scaledMeanPool2d(const std::vector<std::vector<std::vector<std::vector<T>>>> & x, size_t kernel_size);

template <class T, class U, class V> std::vector<size_t>
predict(const std::vector<std::vector<std::vector<std::vector<T>>>> & x, const std::vector<size_t> & y,
    const std::vector<std::vector<std::vector<std::vector<U>>>> & w1, const std::vector<V> & b1,
    const std::vector<std::vector<std::vector<std::vector<U>>>> & w4, const std::vector<V> & b4,
    const std::vector<std::vector<U>> & w8, const std::vector<V> & b8,
    double & acc);

} // ml

#include "ml.hpp"
