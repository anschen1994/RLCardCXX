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

        BlackJackDealer::BlackJackDealer(const BlackJackDealer & _dealer)
        {
            for (auto card : _dealer.deck_)
            {
                Card* p_card = new Card(card->GetSuit(), card->GetRank());
                deck_.push_back(p_card);
            }
            // for (auto card : _dealer.remained_cards_)
            // {
            //     Card* p_card = new Card(card->GetSuit(), card->GetRank());
            //     remained_cards_.push_back(p_card);
            // }
        }

        BlackJackDealer::~BlackJackDealer()
        {
            for (auto card : deck_)
            {
                delete card;
            }
            // for (auto card : remained_cards_)
            // {
            //     delete card;
            // }
            deck_.clear();
            // remained_cards_.clear();
        }        

        void BlackJackDealer::InitCards()
        {
            for (auto & suit : kSuit)
            {
                for (auto & rank : kRank)
                {
                    Card* pCard = new Card(suit, rank);
                    deck_.emplace_back(pCard);
                    // remained_cards_.emplace_back(pCard);
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
            return true;
        }

    }
}