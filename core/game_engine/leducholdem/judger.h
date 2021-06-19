#pragma once
#include "../base_engine.h"
#include "player.h"

namespace rlcard
{
    namespace engine
    {
        class LeducholdemJudger : public Judger
        {
        private:
            int random_seed_;

        public:
            LeducholdemJudger(int _random_seed) : random_seed_(_random_seed) {}
            ~LeducholdemJudger() {}
            bool JudgeRound(int num_params, ...) { return false; } //not used, ignore
            bool JudgeGame(int num_params, ...) { return false; }  //not used, ignore

            vector<float> LeducholdemJudgeGame(vector<LeducholdemPlayer *> *_players, Card *_public_card);
        };
    } // namespace engine
} // namespace rlcard