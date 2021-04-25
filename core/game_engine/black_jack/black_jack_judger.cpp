#include "black_jack_judger.h"



namespace rlcard
{
    namespace engine
    {
        int BlackJackJudger::JudgeScore(const vector<Card*> cards)
        {
            int score = 0;
            int num_A = 0;
            for (auto pcard : cards)
            {
                string rank = pcard->GetRank();
                score += kRank2Score.at(rank);
                if (rank == "A")
                {
                    num_A ++;
                }
            }
            if (score > kFullScore && num_A > 0)
            {
                for (int i = 0; i < num_A; i++)
                {
                    score = score - kDiffScoreAce;
                    if (score <= kFullScore)
                    {
                        break;
                    }
                }
            }
            return score;
        }

        void BlackJackJudger::JudgeRound(BlackJackPlayer & player)
        {
            int player_score = JudgeScore(player.GetHandCard());
            if (player_score <= kFullScore)
            {
                player.SetStatus("alive");
            }
            else
            {
                player.SetStatus("bust");
            }
            player.SetScore(player_score);
        }
    }
}