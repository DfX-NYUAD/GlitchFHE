#pragma once

#include <iostream>
#include <fstream>

using std::cout;
using std::ifstream;
using std::string;
using std::vector;

namespace io
{

template <class T> vector<T>
load(const string & filename)
{
    vector<T> v;
    ifstream fin(filename);
    string line;
    while ( std::getline(fin, line) ) v.push_back( T( std::stod(line) ) );
    return v;
}

template <class T> vector<vector<T>>
load(const string & filename, char delimiter)
{
    vector<vector<T>> m;
    ifstream fin(filename);
    string line;
    while ( std::getline(fin, line) )
    {
        auto items = split(line, delimiter);
        vector<T> v;
        for ( auto & item : items ) v.push_back( std::stod(trim(item)) );
        m.push_back(v);
    }
    return m;
}

template <class T> void
print(const vector<T> & v)
{
    for ( auto & e : v ) cout << e << ' ';
    cout << '\n';
}

template <class T> void
print(const vector<vector<T>> & m)
{
    for ( auto & v : m )
    {
        for ( auto & e : v ) cout << e << ' ';
        cout << '\n';
    }
}

template <class T> void
print(const vector<vector<vector<T>>> & n)
{
    for ( auto & m : n )
    {
        for ( auto & v : m )
        {
            cout << "[ ";
            for ( auto & e : v ) cout << e << ' ';
            cout << "]\n";
        }
        cout << '\n';
    }
}

template <class T> void
print(const vector<vector<vector<vector<T>>>> & a)
{
    for ( auto & n : a )
    {
        for ( auto & m : n )
        {
            cout << "{ ";
            for ( auto & v : m )
            {
                cout << "[ ";
                for ( auto & e : v ) cout << e << ' ' ;
                cout << "] ";
            }
            cout << "} ";
        }
        cout << '\n';
    }
}

} // io
