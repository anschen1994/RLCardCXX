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
            for (auto card : remained_cards_)
            {
                delete card;
            }
            remained_cards_.clear();
        }

        const vector<Card*> & Player::GetHandCard()
        {
            return hand_cards_;
        }

        Player::Player(const Player & _player)
        {
            for (auto card : _player.hand_cards_)
            {
                Card * p_card = new Card(card->GetSuit(), card->GetRank());
                hand_cards_.push_back(p_card);
            }
            player_id_ = _player.player_id_;
        }

        Player::~Player()
        {
            for (auto card : hand_cards_)
            {
                delete card;
            }
            hand_cards_.clear();
        }
    }
}