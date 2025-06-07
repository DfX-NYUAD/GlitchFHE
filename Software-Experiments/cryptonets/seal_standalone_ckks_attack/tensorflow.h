#pragma once

#include <string>
#include <vector>

namespace tensorflow
{

template <class T, class U> std::vector<std::vector<std::vector<T>>>
pad(const std::vector<std::vector<std::vector<T>>> & input, const std::vector<std::vector<std::vector<std::vector<U>>>> & filters, const std::vector<size_t> & strides);

template <class T, class U> std::vector<std::vector<std::vector<T>>>
conv2d(
    const std::vector<std::vector<std::vector<T>>> & input,
    const std::vector<std::vector<std::vector<std::vector<U>>>> & filters,
    const std::vector<size_t> & strides
);

template <class T, class U> std::vector<std::vector<std::vector<std::vector<T>>>>
conv2d_pad_same_nhwc(
    const std::vector<std::vector<std::vector<std::vector<T>>>> & inputs,
    const std::vector<std::vector<std::vector<std::vector<U>>>> & filters,
    const std::vector<size_t> & strides
);

template <class T, class U> std::vector<std::vector<std::vector<std::vector<T>>>>
conv2d(
    const std::vector<std::vector<std::vector<std::vector<T>>>> & inputs,
    const std::vector<std::vector<std::vector<std::vector<U>>>> & filters,
    const std::vector<size_t> & strides,
    const std::string & padding,
    const std::string & data_format
);

} // tensorflow

#include "tensorflow.hpp"
