#pragma once
// #include "../base_engine.h"
#include "player.h"

namespace rlcard
{
    namespace engine
    {
        class LeducholdemRound
        {
        private:
            int random_seed_;
            int raise_amount_;      // the raise amount for each raise, fix num for each round
            int allowed_raise_num_; // allowed maximum raised number (times)
            int num_players_;

            int game_pointer_; // the person_id need to act now in the round
            bool player_folded_;

            int num_have_raised_;    // number of raise
            int num_not_raised_;     // number without raise, If everyone not raise, round over
            vector<int> raised_vec_; // raised amount for each player

        public:
            LeducholdemRound(int _raise_amount, int _allowed_raise_num, int _num_players, int _random_seed);
            ~LeducholdemRound();
            void StartNewRound(int _game_pointer, vector<int> *_raised_vec);
            // bool ProcessRound(int num_params, ...) { return false; } //ignore
            int ProceedRound(vector<LeducholdemPlayer *> *_players, string _action);
            vector<string> GetLegalActions();
            bool IsOver();

            inline void SetRaiseAmount(int x) { raise_amount_ = x; }
            int GetMaxRaised();
            void ShowRoundInfo();
        };
    } // namespace engine
} // namespace rlcard