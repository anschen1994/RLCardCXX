#include "black_jack_dealer.h"
#include <ctime>
#include <algorithm>

namespace rlcard
{
    namespace engine
    {
        default_random_engine BlackJackDealer::rand_gen_(time(0));

        BlackJackDealer::BlackJackDealer()
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
            for (auto card : _dealer.remained_cards_)
            {
                Card* p_card = new Card(card->GetSuit(), card->GetRank());
                remained_cards_.push_back(p_card);
            }
        }

        BlackJackDealer::~BlackJackDealer()
        {
            ;
        }        

        void BlackJackDealer::InitCards()
        {
            for (auto & suit : kSuit)
            {
                for (auto & rank : kRank)
                {
                    Card* pCard = new Card(suit, rank);
                    remained_cards_.emplace_back(pCard);
                }
            }
        }

        void BlackJackDealer::Shuffle()
        {
            std::shuffle(remained_cards_.begin(), remained_cards_.end(), rand_gen_);
        }

        bool BlackJackDealer::DealCard(BlackJackPlayer & player)
        {
            if (remained_cards_.empty())
            {
                return false;
            }
            Card* pCard = remained_cards_.back();
            remained_cards_.pop_back();
            player.AddHandCard(pCard);
            Card* pCard_copy = new Card(*pCard);
            deck_.emplace_back(pCard_copy);
            return true;
        }

    }
}