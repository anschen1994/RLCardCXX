#pragma once
#include "base_engine.h"
#include <random>
#include "black_jack_player.h"

namespace rlcard
{
    namespace engine
    {
        class BlackJackDealer : public BlackJackPlayer
        {
            public:
                BlackJackDealer(const string & _status, int _score);

                BlackJackDealer(const BlackJackDealer & _dealer);

                ~BlackJackDealer();

                void InitCards();
                
                void Shuffle();

                bool DealCard(BlackJackPlayer & player);
                
                inline size_t GetDeckCardNumber() {return deck_.size();}

            private:
                static default_random_engine rand_gen_;
                vector<Card*> deck_;
                // vector<Card*> remained_cards_;
        };
    }
}
