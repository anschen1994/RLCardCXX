#include "base_engine.h"
#include "../utils/helper.h"
#include <iostream>

using std::cout;
namespace rlcard
{
    namespace engine
    {
        int Card::hash(const string &_suit, const string &_rank)
        {
            int suit_index = GetIndexOfVector(kSuit, _suit);
            int rank_index = GetIndexOfVector(kRank, _rank);
            return rank_index + 100 * suit_index;
        }

        Card::Card(const Card &_card)
        {

            suit_ = _card.suit_;
            rank_ = _card.rank_;
            hash_value_ = _card.hash_value_;
            // cout << "Card 拷贝构造函数调用成功" << endl;
        }

        inline int Dealer::GetRemainedCardNumber()
        {
            return int(remained_cards_.size());
        }

        inline int Dealer::GetTotalCardNumber()
        {
            return int(deck_.size());
        }
    } // namespace engine
} // namespace rlcard