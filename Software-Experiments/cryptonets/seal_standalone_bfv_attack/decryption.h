#pragma once

#include <vector>
#include "crt.h"

namespace crt
{

template <class T> std::vector<T>
decrypt(const CRT<T> & a);

template <class T> std::vector<std::vector<T>>
decrypt(const std::vector<CRT<T>> & a);

template <class T> std::vector<std::vector<std::vector<T>>>
decrypt(const std::vector<std::vector<CRT<T>>> & a);

} // crt

#include "decryption.hpp"
