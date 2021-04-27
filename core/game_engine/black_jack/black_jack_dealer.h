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
                
                void InitCards();
                
                void Shuffle();

                bool DealCard(BlackJackPlayer & player);

            private:
                static default_random_engine rand_gen_;
                vector<Card*> deck_;
                vector<Card*> remained_cards_;
        };
    }
}
