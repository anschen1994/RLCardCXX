#include <iostream>
#include "judger.h"
#include "../../utils/helper.h"

using rlcard::Rank2Int;
using std::cout;
using std::endl;

namespace rlcard
{
    namespace engine
    {
        vector<float> LeducholdemJudger::LeducholdemJudgeGame(vector<LeducholdemPlayer *> *_players, Card *_public_card)
        {
            // Judge who are the winners
            vector<float> winners = {0, 0};
            vector<float> payoffs = {0, 0};

            bool found_winner_flag = false;
            auto it = _players->begin();
            for (int i = 0; i < _players->size(); i++) // case1:一方弃牌情况
            {
                if ((*it)->GetPlayerStatus() == "folded")
                {
                    winners[(i + 1) % 2] = 1;
                    // winners.at((i + 1) % 2) = 1;  //防止越界报错
                    found_winner_flag = true;
                    break;
                }
                // cout << i << "\tplayer id: " << (*it)->GetPlayerID() << "\tplayer state: " << (*it)->player_status_ << endl;
                it++;
            }

            auto player1 = _players->begin();
            auto player2 = player1 + 1;
            Card *player1_handcard = (*player1)->GetHandCards().at(0);
            Card *player2_handcard = (*player2)->GetHandCards().at(0);

            string p1_handcard_rank = player1_handcard->GetRank();
            string p2_handcard_rank = player2_handcard->GetRank();
            string public_card_rank = _public_card->GetRank();

            if (!found_winner_flag) // case2:平局情况，手牌相等
            {
                if (p1_handcard_rank == p2_handcard_rank)
                {
                    winners[0] = 1;
                    winners[1] = 1;
                    found_winner_flag = true;
                }
            }

            if (!found_winner_flag) // case3: 一方手牌和public card相等情况
            {
                if (p1_handcard_rank == public_card_rank)
                {
                    winners[0] = 1;
                    found_winner_flag = true;
                }
                else if (p2_handcard_rank == public_card_rank)
                {
                    winners[1] = 1;
                    found_winner_flag = true;
                }
                else
                {
                }
            }

            if (!found_winner_flag) //case4: 双方手牌比较
            {
                if (Rank2Int(p1_handcard_rank) > Rank2Int(p2_handcard_rank))
                {
                    winners[0] = 1;
                }
                else
                {
                    winners[1] = 1;
                }
                found_winner_flag = true;
            }

            // cout << Rank2Int("J") << "\t" << Rank2Int("8") << "\t" << Rank2Int("A") << "\t" << Rank2Int("1") << "\t" << Rank2Int("S") << endl;
            cout << "winners: " << winners[0] << "\t" << winners[1] << endl;

            // Compute the total chips
            float total_chips = 0;
            total_chips += (*player1)->GetInChips();
            total_chips += (*player2)->GetInChips();
            int total_winners = 0;
            for (int i = 0; i < 2; i++)
            {
                total_winners += winners[i];
            }
            float each_win = total_chips / total_winners;
            cout << "total chips: " << total_chips << "\ttotal winners: " << total_winners << "\teach win: " << each_win << endl;

            vector<float> payed_chips = {(*player1)->GetInChips(), (*player2)->GetInChips()};
            for (int i = 0; i < 2; i++)
            {
                if (winners[i] == 1)
                {
                    payoffs[i] = each_win - payed_chips[i];
                }
                else
                {
                    payoffs[i] = -payed_chips[i];
                }
            }

            cout << "payoffs: " << payoffs[0] << "\t" << payoffs[1] << endl;
            return payoffs;
        }
    } // namespace engine
} // namespace rlcard