#include "base_engine.h"
#include "helper.h"

namespace rlcard
{
    namespace engine
    {
        int Card::hash(const string & _suit, const string & _rank)
        {
            int suit_index = rlcard::GetIndexOfVector(kSuit, _suit);
            int rank_index = rlcard::GetIndexOfVector(kRank, _rank);
            return rank_index + 100 * suit_index;
        }

        Dealer::~Dealer()
        {
            deck_.clear();
            remained_cards_.clear();
        }

        vector<Card*> Player::GetHandCard()
        {
            return hand_cards_;
        }

        Player::~Player()
        {
            hand_cards_.clear();
        }
    }
}