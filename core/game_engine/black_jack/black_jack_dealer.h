#pragma once
#include "base_engine.h"
#include <random>
#include "black_jack_player.h"

namespace rlcard
{
    namespace engine
    {
        class BlackJackDealer : public Dealer
        {
            public:
                BlackJackDealer();

                BlackJackDealer(const BlackJackDealer & _dealer);

                ~BlackJackDealer();

                void InitCards();
                
                void Shuffle();

                bool DealCard(BlackJackPlayer & player);
                
                inline size_t GetDeckCardNumber() {return deck_.size();}

            private:
                static default_random_engine rand_gen_;
        };
    }
}
