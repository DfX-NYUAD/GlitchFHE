#include "io.h"

#include <algorithm>

using namespace std;

namespace io
{

vector<string> split(const string & s, char delimiter)
{
    vector<string> v;
    string item = "";
    for ( auto & c : s )
    {
        if ( c == delimiter )
        {
            v.push_back(item);
            item = "";
        }
        else item += c;
    }
    v.push_back(item);
    return v;
}

string trim(const string & sin)
{
    string s = sin;
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
    }));
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), s.end());
    return s;
}

vector<string> trim(const vector<string> & v)
{
    vector<string> vout;
    for ( auto e : v ) vout.push_back(trim(e));
    return vout;
}

} // io
