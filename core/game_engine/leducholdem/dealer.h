#pragma once
#include <algorithm>
#include "../base_engine.h"

using std::shuffle;

namespace rlcard
{
    namespace engine
    {
        class LeducholdemDealer : public Dealer
        {
        private:
            int random_seed_;
            float pot_;

        public:
            LeducholdemDealer(int _random_seed);
            ~LeducholdemDealer();
            void Shuffle();
            Card *DealCard(int num_params, ...);
            void ShowDeck(string msg);
        };
    } // namespace engine
} // namespace rlcard