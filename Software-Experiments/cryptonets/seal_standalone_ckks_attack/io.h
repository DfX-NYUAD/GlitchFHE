#pragma once

#include <string>
#include <vector>

namespace io
{

template <class T> std::vector<T> load(const std::string & filename);

template <class T> std::vector<std::vector<T>> load(const std::string & filename, char delimiter);

template <class T> void print(const std::vector<T> & v);

template <class T> void print(const std::vector<std::vector<T>> & m);

template <class T> void print(const std::vector<std::vector<std::vector<T>>> & n);

template <class T> void print(const std::vector<std::vector<std::vector<std::vector<T>>>> & a);

std::vector<std::string> split(const std::string & s, char delimiter);

std::string trim(const std::string & sin);

std::vector<std::string> trim(const std::vector<std::string> & v);

} // io

#include "io.hpp"
