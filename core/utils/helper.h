#pragma once
#include <algorithm>
#include <vector>
#include <string>

using namespace std;
namespace rlcard
{
    template <typename _T>
    int GetIndexOfVector(const vector<_T> & vec, const _T & element);
}


#include "helper.tpp"
