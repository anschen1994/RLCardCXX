#pragma once
#include "base_engine.h"
#include "black_jack_player.h"

using namespace std;
namespace rlcard
{
    namespace engine
    {
        class BlackJackJudger
        {
            public:
                BlackJackJudger() = default;

                int JudgeScore(const vector<Card*>& cards);

                void JudgeRound(BlackJackPlayer & player);


            private:
                const map<string, int> kRank2Score = {{"A", 11}, {"2", 2}, {"3", 3}, {"4", 4}, {"5", 5}, {"6", 6}, {"7", 7}, \
                                          {"8", 8}, {"9", 9}, {"T", 10}, {"J", 10}, {"Q", 10}, {"K", 10}};
                const int kFullScore = 21;
                const int kDiffScoreAce = 10;
        };
    }
}