#pragma once

#include <chrono>
#include <iostream>
#include <string>
#include <vector>
#include "decryption.h"
#include "io.h"
#include "numpy.h"
#include "tensorflow.h"

using namespace std::chrono;
using namespace numpy;

using crt::decrypt;
using io::print;
using std::string;
using std::vector;
using tensorflow::conv2d;

// #include <typeinfo> // debug
// #include "decryption.hpp"

namespace ml
{

template <class Type, class Tensor> void
showInfo(const string & title, const high_resolution_clock::time_point & t, const Tensor & tensor, const string & varname)
{
    const double mstos = 1000;
    milliseconds elapsed = duration_cast<milliseconds>(high_resolution_clock::now() - t);
    std::cout << title << " ( " << (elapsed.count()/mstos) << " s ) ";
    std::cout << varname << " ";
    print(shape(tensor));
}

template <class T> vector<vector<vector<vector<T>>>>
scaledMeanPool2d(const vector<vector<vector<vector<T>>>> & x, size_t kernel_size)
{
    auto no_of_samples = shape(x)[0];
    auto no_of_channels = shape(x)[3];
    auto sample_size = shape(x)[1];
    auto pool_size = kernel_size;
    auto strides = sample_size / pool_size;
    vector<vector<vector<vector<T>>>> out;
    for (size_t n=0; n<no_of_samples; n++)
    {
        vector<vector<vector<T>>> temp_per_channel(
            strides, vector<vector<T>>(
                strides, vector<T>(no_of_channels)
        ));
        for (size_t c=0; c<no_of_channels; c++)
        {
            for (size_t stride_row=0; stride_row<strides; stride_row++)
            {
                for (size_t stride_col=0; stride_col<strides; stride_col++)
                {
                    auto row_start = stride_row * pool_size;
                    auto col_start = stride_col * pool_size;
                    temp_per_channel[stride_row][stride_col][c] = mean( subvector(x, vector<size_t>{n,n+1, row_start,row_start+pool_size, col_start,col_start+pool_size, c,c+1}) );
                }
            }
        }
        out.push_back(temp_per_channel);
    }
    return out;
}

template <class T, class U, class V> vector<size_t>
predict(const vector<vector<vector<vector<T>>>> & x, const vector<size_t> & y,
    const vector<vector<vector<vector<U>>>> & w1, const vector<V> & b1,
    const vector<vector<vector<vector<U>>>> & w4, const vector<V> & b4,
    const vector<vector<U>> & w8, const vector<V> & b8,
    double & acc)
{
    cout << "xo "; io::print(numpy::shape(x));

    high_resolution_clock::time_point t = high_resolution_clock::now();
    auto h1 = add( conv2d(x, w1, vector<size_t>{1,2,2,1}, "SAME", "NHWC"), b1 );
    showInfo<T>("convadd ", t, h1, "h1");

    t = high_resolution_clock::now();
    auto h2 = square(h1);
    showInfo<T>("square  ", t, h2, "h2");

    t = high_resolution_clock::now();
    auto h3 = scaledMeanPool2d(h2, 2);
    showInfo<T>("meanpool", t, h3, "h3");

    t = high_resolution_clock::now();
    auto h4 = add( conv2d(h3, w4,  vector<size_t>{1,2,2,1}, "SAME", "NHWC"), b4);
    showInfo<T>("convadd ", t, h4, "h4");

    t = high_resolution_clock::now();
    auto h5 = scaledMeanPool2d(h4, 2);
    showInfo<T>("meanpool", t, h5, "h5");

    t = high_resolution_clock::now();
    auto h6 = reshape2d( h5, vector<size_t>{h5.size(), h5[0].size() * h5[0][0].size() * h5[0][0][0].size()} );
    showInfo<T>("reshape ", t, h6, "h6");

    t = high_resolution_clock::now();
    auto h7 = square1(h6);
    showInfo<T>("square  ", t, h7, "h7");

    t = high_resolution_clock::now();
    //auto h8 = add( dot(h7,w8), b8 );
    auto h8inter = dot(h7,w8);
    auto h8 = add(h8inter, b8);
    showInfo<T>("dotadd  ", t, h8, "h8");

    t = high_resolution_clock::now();
    auto h8p = decrypt(h8);
    showInfo<T>("decrypt ", t, h8, "h8");

    t = high_resolution_clock::now();
    auto h8_reshaped = reshapeOrder( h8p, vector<size_t>{1,0,2} );
    cout << "h8_reshaped "; print(shape(h8_reshaped));
    auto h8_combined = combine(h8_reshaped);
    cout << "h8_combined "; print(shape(h8_combined));
    auto h8_reshaped2 = reshapeOrder( h8_combined, vector<size_t>{1,0} );
    showInfo<T>("plainops", t, h8_reshaped2, "h8_reshaped2");

    auto o = argmax(h8_reshaped2);
    showInfo<T>("o", t, o, "o");
    showInfo<T>("y", t, y, "y");
    std::cout << o.size() <<std::endl;
    std::cout << y.size() <<std::endl;
    acc = double( countEqual(o, y) ) / o.size();
    return o;
}

} // ml
