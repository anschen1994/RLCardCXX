#include <iostream>
#include <random>
#include "game.h"

using std::cout;

namespace rlcard
{
    namespace engine
    {
        // GameState 构造函数
        LeducholdemGameState::LeducholdemGameState(int _game_pointer, int _round_counter, Card *_public_card,
                                                   LeducholdemRound *_round, LeducholdemDealer *_dealer,
                                                   vector<LeducholdemPlayer *> &_players)
        {
            game_pointer_ = _game_pointer;
            round_counter_ = _round_counter;
            if (_public_card != nullptr)
                public_card_ = new Card(*_public_card); // 浅拷贝, 无指针
            round_ = new LeducholdemRound(*_round);     // 浅拷贝, 无指针
            dealer_ = new LeducholdemDealer(*_dealer);  // 深拷贝，重写拷贝构造函数, 有指针
            for (LeducholdemPlayer *temp_player : _players)
            {
                LeducholdemPlayer *new_player = new LeducholdemPlayer(*temp_player); // 深拷贝, 重写拷贝构造函数, 有指针
                players_.push_back(new_player);
            }
            cout << "test~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        }

        // GameState 析构函数
        LeducholdemGameState::~LeducholdemGameState()
        {
            cout << "Game state 析构函数调用开始----" << endl;
            delete public_card_;
            public_card_ = nullptr;
            delete round_;
            round_ = nullptr;
            delete dealer_;
            dealer_ = nullptr;
            for (LeducholdemPlayer *temp_player : players_)
            {
                // cout << "Delete Game state player: " << endl;
                // temp_player->ShowPlayerInfo();
                delete temp_player;
                temp_player = nullptr;
            }
            players_.clear();

            cout << "Game state 析构函数调用结束----" << endl;
        }

        LeducholdemGame::LeducholdemGame(bool _allow_step_back)
        {
            allow_step_back_ = _allow_step_back;
            random_seed_ = 1;
            small_blind_ = 1;
            big_blind_ = 2 * small_blind_;
            raise_amount_ = big_blind_;
            allowed_raise_num_ = 2;
            num_players_ = 2;

            public_card_ = nullptr;
            judger_ = nullptr;
            dealer_ = nullptr;
            round_ = nullptr;
        }

        LeducholdemGame::~LeducholdemGame()
        {
            delete judger_;
            judger_ = nullptr;
            delete dealer_;
            dealer_ = nullptr;
            delete public_card_;
            public_card_ = nullptr;
            delete round_;
            round_ = nullptr;
            for (auto temp_player : players_)
            {
                delete temp_player;
                temp_player = nullptr;
            }
            players_.clear();

            for (auto temp_history : game_history_)
            {
                delete temp_history;
                temp_history = nullptr;
            }
            game_history_.clear();

            cout << "destroy game..." << endl;
        }

        LeducholdemPlayerState LeducholdemGame::InitGame()
        {
            // 初始化 Dealer
            if (dealer_ != nullptr)
                delete dealer_;
            cout << "test" << endl;
            dealer_ = new LeducholdemDealer(random_seed_);
            dealer_->Shuffle();

            // 初始化 Players
            for (auto temp_player : players_)
            {
                if (temp_player != nullptr)
                    delete temp_player;
            }
            players_.clear();
            for (int i = 0; i < num_players_; i++)
            {
                LeducholdemPlayer *player = new LeducholdemPlayer(i, random_seed_);
                players_.push_back(player);
            }

            // 初始化 Judger
            if (judger_ != nullptr)
                delete judger_;
            judger_ = new LeducholdemJudger(random_seed_);

            // First Round, 发牌
            for (int i = 0; i < num_players_; i++)
            {
                Card *temp_card = dealer_->DealCard();
                players_.at(i)->InsertHandCard(temp_card);
            }

            // Random Choose small blind and big blind
            std::default_random_engine generator(random_seed_);
            std::uniform_int_distribution<int> distribution(0, 1);
            int sb = distribution(generator); // random pick small blind
            int bb = (sb + 1) % num_players_;
            players_.at(sb)->SetInChips(small_blind_);
            players_.at(bb)->SetInChips(big_blind_);

            if (public_card_ != nullptr)
                delete public_card_;
            public_card_ = nullptr;
            game_pointer_ = sb; // small blind move first

            // 初始化 Round
            if (round_ != nullptr)
                delete round_;
            round_ = new LeducholdemRound(raise_amount_, allowed_raise_num_, num_players_, random_seed_);

            vector<int> raised_vec = GetRaisedVec();
            round_->StartNewRound(game_pointer_, &raised_vec);

            // 其他初始项
            round_counter_ = 0;
            for (auto temp_history : game_history_)
            {
                if (temp_history != nullptr)
                    delete temp_history;
            }
            game_history_.clear();

            LeducholdemPlayerState p_state = GetState(game_pointer_);
            return p_state;
            // round_->ShowRoundInfo();
            // player->ShowPlayerInfo();
        }

        LeducholdemPlayerState LeducholdemGame::Step(string _action)
        {
            if (allow_step_back_)
            {
                LeducholdemGameState *r_state = new LeducholdemGameState(game_pointer_, round_counter_,
                                                                         public_card_, round_, dealer_, players_);
                game_history_.push_back(r_state);
            }

            game_pointer_ = round_->ProceedRound(&players_, _action);
            if (round_->IsOver()) // 第一回合结束后发一张public card
            {
                // dealer_->ShowDeck("before 2nd round");
                if (round_counter_ == 0)
                {
                    public_card_ = dealer_->DealCard();
                    round_->SetRaiseAmount(2 * raise_amount_);
                }
                // cout << "new pubcard: " << public_card_->GetCardRepresentation() << endl;
                // dealer_->ShowDeck("after 2nd round");
                round_counter_ += 1;
                vector<int> new_raised_vec = GetRaisedVec();
                round_->StartNewRound(game_pointer_, &new_raised_vec);
            }
            LeducholdemPlayerState p_state = GetState(game_pointer_);
            return p_state;
        }

        LeducholdemPlayerState LeducholdemGame::GetState(int _player_id)
        {
            vector<int> raised_vec = GetRaisedVec();
            vector<string> legal_actions = round_->GetLegalActions();
            LeducholdemPlayerState p_state = players_.at(_player_id)->GetState(public_card_, &raised_vec, &legal_actions);
            p_state.cur_player_ = _player_id;
            return p_state;
        }

        bool LeducholdemGame::IsOver()
        {
            if (round_counter_ >= 2)
                return true;

            for (auto player : players_)
            {
                if (player->GetPlayerStatus() != "alive")
                    return true;
            }
            return false;
        }

        vector<float> LeducholdemGame::GetPayOffs()
        {
            vector<float> chips_payoffs = judger_->LeducholdemJudgeGame(&players_, public_card_);
            return chips_payoffs;
        }

        bool LeducholdemGame::StepBack()
        {
            if (game_history_.size() > 0)
            {
                cout << "Step back 开始..." << endl;
                LeducholdemGameState *last_game_state = game_history_.back();
                game_history_.pop_back();

                game_pointer_ = last_game_state->game_pointer_;
                round_counter_ = last_game_state->round_counter_;
                delete public_card_;
                public_card_ = last_game_state->public_card_;
                delete round_;
                round_ = last_game_state->round_;
                delete dealer_;
                dealer_ = last_game_state->dealer_;

                for (LeducholdemPlayer *temp_player : players_)
                {
                    delete temp_player;
                    temp_player = nullptr;
                }
                players_.clear();
                players_ = last_game_state->players_;

                cout << "Step back 成功..." << endl;
                return true;
            }
            return false;
        }

        vector<int> LeducholdemGame::GetRaisedVec()
        {
            vector<int> raised_vec;
            for (int i = 0; i < players_.size(); i++)
            {
                int temp_raise = players_.at(i)->GetInChips();
                raised_vec.push_back(temp_raise);
            }
            return raised_vec;
        }
    } // namespace engine
} // namespace rlcard