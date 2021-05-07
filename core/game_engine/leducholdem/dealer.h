#pragma once
#include <algorithm>
#include "../base_engine.h"

using std::shuffle;

namespace rlcard
{
    namespace engine
    {
        // class LeducholdemDealer : public Dealer
        class LeducholdemDealer
        {
        private:
            int random_seed_;
            float pot_;
            vector<Card *> deck_;
            // vector<Card *> remained_cards_;

        public:
            LeducholdemDealer(int _random_seed);
            LeducholdemDealer(const LeducholdemDealer &_dealer);
            ~LeducholdemDealer();
            void Shuffle();
            Card *DealCard();
            void ShowDeck(string msg);
        };
    } // namespace engine
} // namespace rlcard