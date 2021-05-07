#include "round.h"
#include "stdio.h"
#include "../../utils/helper.h"
#include <algorithm>
#include <iostream>

namespace rlcard
{
    namespace engine
    {
        LeducholdemRound::LeducholdemRound(int _raise_amount, int _allowed_raise_num, int _num_players, int _random_seed)
        {
            random_seed_ = _random_seed;
            raise_amount_ = _raise_amount;
            allowed_raise_num_ = _allowed_raise_num;
            num_players_ = _num_players;

            game_pointer_ = 0;
            num_have_raised_ = 0;
            num_not_raised_ = 0;
            // max_raised_ = 0;
            raised_vec_ = vector<int>(num_players_, 0);
        }

        LeducholdemRound::~LeducholdemRound()
        {
            printf("round 析构函数调用成功\n");
        }

        void LeducholdemRound::StartNewRound(int _game_pointer, vector<int> *_raised_vec)
        {
            // start a new round, reset game_pointer, num_have_raised, num_not_raised
            game_pointer_ = _game_pointer;
            num_have_raised_ = 0;
            num_not_raised_ = 0;
            if (_raised_vec != nullptr && raised_vec_.size() == _raised_vec->size())
            {
                for (int i = 0; i < raised_vec_.size(); i++)
                {
                    raised_vec_.at(i) = _raised_vec->at(i);
                }
            }
            else
            {
                for (auto it = raised_vec_.begin(); it != raised_vec_.end(); it++)
                {
                    *it = 0;
                }
            }
        }

        int LeducholdemRound::ProceedRound(vector<LeducholdemPlayer *> *_players, string _action)
        {
            vector<string> legal_actions = GetLegalActions();
            int action_idx = GetIndexOfVector(legal_actions, _action);
            int max_raised = GetMaxRaised();

            if (action_idx == -1)
            {
                // printf("action %s is not legal", _action);
                cout << "action is not legal: " << _action << endl;
                return 0;
            }

            if (_action == "call")
            {
                int diff = max_raised - raised_vec_.at(game_pointer_);
                raised_vec_.at(game_pointer_) = max_raised;
                float new_inchips = _players->at(game_pointer_)->GetInChips() + diff;
                _players->at(game_pointer_)->SetInChips(new_inchips);
                num_not_raised_ += 1;
            }
            else if (_action == "raise")
            {
                int diff = max_raised - raised_vec_.at(game_pointer_) + raise_amount_;
                raised_vec_.at(game_pointer_) = max_raised + raise_amount_;
                float new_inchips = _players->at(game_pointer_)->GetInChips() + diff;
                _players->at(game_pointer_)->SetInChips(new_inchips);
                num_have_raised_ += 1;
                num_not_raised_ = 1;
            }
            else if (_action == "fold")
            {
                _players->at(game_pointer_)->SetPlayerStatus("folded");
                player_folded_ = true;
            }
            else if (_action == "check")
            {
                num_not_raised_ += 1;
            }
            else
            {
            }

            game_pointer_ = (game_pointer_ + 1 + num_players_) % num_players_; // next player

            while (_players->at(game_pointer_)->GetPlayerStatus() == "folded")
            {
                game_pointer_ = (game_pointer_ + 1 + num_players_) % num_players_; // next player
            }
            return game_pointer_;
        }

        vector<string> LeducholdemRound::GetLegalActions()
        {
            vector<string> full_actions = {"call", "raise", "fold", "check"};

            //if the number of raises already reaches the maximum number, can not raise anymore
            if (num_have_raised_ >= allowed_raise_num_)
            {
                auto iter = std::remove(full_actions.begin(), full_actions.end(), "raise");
                full_actions.erase(iter, full_actions.end());
            }

            // if the current chips are less than the highest one in the round, cannot check
            int current_p_raised = raised_vec_.at(game_pointer_);
            int max_raised_ = GetMaxRaised();

            if (current_p_raised < max_raised_)
            {
                auto iter = std::remove(full_actions.begin(), full_actions.end(), "check");
                full_actions.erase(iter, full_actions.end());
            }

            // if the current player is the highest raised one, cannot call
            if (current_p_raised == max_raised_)
            {
                auto iter = std::remove(full_actions.begin(), full_actions.end(), "call");
                full_actions.erase(iter, full_actions.end());
            }

            cout << "legal actions: " << endl;
            for (int i = 0; i < full_actions.size(); i++)
            {
                std::cout << full_actions.at(i) << "\t";
            }
            cout << std::endl;
            return full_actions;
        }

        bool LeducholdemRound::IsOver()
        {
            return (num_not_raised_ >= num_players_) ? true : false;
        }

        int LeducholdemRound::GetMaxRaised()
        {
            return (raised_vec_.at(0) > raised_vec_.at(1)) ? raised_vec_.at(0) : raised_vec_.at(1);
        }

        void LeducholdemRound::ShowRoundInfo()
        {
            // printf("random seed: %d\n", random_seed_);
            // printf("raise amount: %d\n", raise_amount_);
            // printf("allowed_raise_num_: %d\n", allowed_raise_num_);
            printf("num_players: %d\t, game_pointer: %d\n", num_players_, game_pointer_);

            printf("num have raised: %d\tnum not raised: %d\n", num_have_raised_, num_not_raised_);
            printf("raised list: ");
            for (auto it = raised_vec_.begin(); it != raised_vec_.end(); it++)
            {
                printf("%d\t", *it);
            }
            printf("\n===========================\n");
        }
    } // namespace engine
} // namespace rlcard