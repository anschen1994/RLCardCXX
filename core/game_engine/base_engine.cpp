#include "base_engine.h"
#include "../utils/helper.h"

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

        // inline bool Card::operator==(const Card &_card)
        // {
        //     return _card.rank_ == rank_ && _card.suit_ == suit_;
        // }

        // inline string Card::GetCardRepresentation()
        // {
        //     return rank_ + suit_;
        // }

        Dealer::~Dealer()
        {
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