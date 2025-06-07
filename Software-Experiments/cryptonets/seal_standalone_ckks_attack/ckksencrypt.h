#pragma once

#include <vector>




//vector<seal::Ciphertext> ckksEncode(const T & a);

//template <class T> std::vector<Ciphertext> ckksEncode(const std::vector<T> & a);

//std::vector<Ciphertext> ckksEncryptPack(const std::vector<T> & a);

//template <class T> std::vector<std::vector<Ciphertext>> ckksEncryptPack(const std::vector<std::vector<T>> & a);

template <class T> std::vector<std::vector<std::vector<Ciphertext>>>
ckksEncryptPack(const std::vector<std::vector<std::vector<T>>> & a);

template <class T> std::vector<std::vector<std::vector<std::vector<Ciphertext>>>>
ckksEncryptPack(const std::vector<std::vector<std::vector<std::vector<T>>>> & a);

// ckks

#include "ckksencrypt.hpp"
