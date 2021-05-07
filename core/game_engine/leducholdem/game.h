#pragma once
#include "player.h"
#include "dealer.h"
#include "judger.h"
#include "round.h"

namespace rlcard
{
    namespace engine
    {
        struct LeducholdemGameState
        {
            LeducholdemRound *round_;
            LeducholdemDealer *dealer_;
            vector<LeducholdemPlayer *> players_;
            Card *public_card_;
            int game_pointer_;
            int round_counter_;

            // 构造函数
            LeducholdemGameState(int _game_pointer, int _round_counter, Card *_public_card,
                                 LeducholdemRound *_round, LeducholdemDealer *_dealer,
                                 vector<LeducholdemPlayer *> &_players);
            // 析构函数
            ~LeducholdemGameState();
        };

        class LeducholdemGame
        {
        private:
            bool allow_step_back_;
            int random_seed_;
            int small_blind_;
            int big_blind_;
            int raise_amount_;
            int allowed_raise_num_;
            int num_players_;

            int game_pointer_;
            int round_counter_;
            Card *public_card_;
            LeducholdemJudger *judger_;
            vector<LeducholdemPlayer *> players_;
            LeducholdemDealer *dealer_;
            LeducholdemRound *round_;
            vector<LeducholdemGameState *> game_history_;

        public:
            LeducholdemGame(bool _allow_step_back);
            ~LeducholdemGame();
            LeducholdemPlayerState InitGame();
            LeducholdemPlayerState Step(string _action);
            LeducholdemPlayerState GetState(int _player_id);
            bool IsOver();
            vector<float> GetPayOffs();
            bool StepBack();
            vector<int> GetRaisedVec();

            // inline LeducholdemJudger *GetJudger() { return judger_; }
            // inline vector<LeducholdemPlayer *> GetPlayers() { return players_; }
            // inline LeducholdemDealer *GetDealer() { return dealer_; }
        };
    } // namespace engine
} // namespace rlcard