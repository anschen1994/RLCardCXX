#include "helper.h"
#include <set>

// using namespace std;
namespace rlcard
{
    // template <typename _T>
    // int GetIndexOfVector(const vector<_T> & vec, const _T & element)
    // {
    //     auto it = find(vec.begin(), vec.end(), element);
    //     if (it == vec.end())
    //     {
    //         return -1;
    //     }
    //     else
    //     {
    //         int index = it - vec.begin();
    //         return index;
    //     }
    // }

    int Rank2Int(string rank)
    {
        // 将牌的rank转化为int方便比较
        std::set<string> int_set = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};
        if (int_set.find(rank) != int_set.end())
        {
            return std::stoi(rank);
        }

        if (rank == "T")
            return 10;
        if (rank == "J")
            return 11;
        if (rank == "Q")
            return 12;
        if (rank == "K")
            return 13;
        if (rank == "A")
            return 14;
        return 0;
    }
} // namespace rlcard
