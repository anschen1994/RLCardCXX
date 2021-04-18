#include "helper.h"

using namespace std;
namespace rlcard
{
    template <typename _T>
    int GetIndexOfVector(const vector<_T> & vec, const _T & element)
    {
        auto it = find(vec.begin(), vec.end(), element);
        if (it == vec.end())
        {
            return -1;
        }
        else
        {
            int index = it - vec.begin();
            return index;
        }
    }
} // namespace rlcard
