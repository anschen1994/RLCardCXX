#include "black_jack_dealer.h"
#include <ctime>
#include <algorithm>

namespace rlcard
{
    namespace engine
    {
        default_random_engine BlackJackDealer::rand_gen_(time(0));

        BlackJackDealer::BlackJackDealer(const string & _status, int _score) : \
        BlackJackPlayer(_status, _score, -1)
        {
            InitCards();
        }

        void BlackJackDealer::InitCards()
        {
            for (auto & suit : kSuit)
            {
                for (auto & rank : kRank)
                {
                    Card* pCard = new Card(suit, rank);
                    deck_.emplace_back(pCard);
                    remained_cards_.emplace_back(pCard);
                }
            }
        }

        void BlackJackDealer::Shuffle()
        {
            std::shuffle(deck_.begin(), deck_.end(), rand_gen_);
        }

        bool BlackJackDealer::DealCard(BlackJackPlayer & player)
        {
            if (deck_.empty())
            {
                return false;
            }
            Card* pCard = deck_.back();
            deck_.pop_back();
            player.AddHandCard(pCard);
        }

    }
}