#pragma once

#include <vector>
#include "crt.h"

namespace crt
{

template <class T> CRT<T> crtEncode(const T & a);

template <class T> std::vector<CRT<T>> crtEncode(const std::vector<T> & a);

template <class T> std::vector<CRT<T>> crtEncryptPack(const std::vector<T> & a);

template <class T> std::vector<std::vector<CRT<T>>> crtEncryptPack(const std::vector<std::vector<T>> & a);

template <class T> std::vector<std::vector<std::vector<CRT<T>>>>
crtEncryptPack(const std::vector<std::vector<std::vector<T>>> & a);

template <class T> std::vector<std::vector<std::vector<std::vector<CRT<T>>>>>
crtEncryptPack(const std::vector<std::vector<std::vector<std::vector<T>>>> & a);

} // crt

#include "encryption.hpp"
