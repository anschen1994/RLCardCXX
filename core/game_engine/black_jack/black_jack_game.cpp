#include "black_jack_game.h"
#include <iostream>


namespace rlcard
{
    namespace engine
    {
        bool BlackJackGame::Reset()
        {
            p_dealer_ = new BlackJackDealer("alive", 0);
            p_dealer_->Shuffle();
            for (int i = 0; i < player_num_; i++)
            {
                BlackJackPlayer* pPlayer = new BlackJackPlayer(i);
                p_players_.push_back(pPlayer);
            }
            p_judger_ = new BlackJackJudger();
            for (int i = 0; i < kStartCardNum; i++)
            {
                for (auto player : p_players_)
                {
                    p_dealer_->DealCard(*player);
                }
                p_dealer_->DealCard(*p_dealer_);
            }
            for (int i = 0; i < player_num_; i++)
            {
                p_judger_->JudgeRound(*p_players_.at(i));
            }
            p_judger_->JudgeRound(*p_dealer_);

            // winners_.at("dealer") = 0;
            winners_.insert({"dealer", 0});
            for (int i = 0; i < player_num_; i++)
            {
                // winners_.at("player" + to_string(i)) = 0;
                winners_.insert({"player" + to_string(i), 0});
            }
            game_pointer_ = 0;
            p_state_ = new BlackJackGameState();
            GetState(game_pointer_, *p_state_);
            return true;
        }

        BlackJackGameState BlackJackGame::Step(const string & action)
        {
            if (is_allow_back_)
            {
                BlackJackPlayer player = *p_players_.at(game_pointer_);
                BlackJackDealer dealer = *p_dealer_;
                map<string, int> winner = winners_;
                BlackJackHistory* p_his = new BlackJackHistory(dealer, winner, player);
                history_.push_back(p_his);
            }

            if (action == "stand")
            {
                while (p_dealer_->GetScore() < min_dealer_score_)
                {
                    p_dealer_->DealCard(*p_dealer_);
                    p_judger_->JudgeRound(*p_dealer_);
                }
                p_judger_->JudgeRound(*p_players_.at(game_pointer_));
                GetGameResult();
            }
            else
            {
                p_dealer_->DealCard(*p_players_.at(game_pointer_));
                p_judger_->JudgeRound(*p_players_.at(game_pointer_));
                if (p_players_.at(game_pointer_)->GetStatus() == "bust")
                {
                    GetGameResult();
                }
            }
            IsGameOver();
            // construct state
            BlackJackGameState next_state = GetState(game_pointer_, *p_state_);

            game_pointer_ = (game_pointer_ + 1) % player_num_;
            return next_state;
        }

        BlackJackGame::~BlackJackGame()
        {
            p_players_.clear();
            delete p_judger_;
            delete p_dealer_;
            winners_.clear();
            history_.clear();
            delete p_state_;
        }

        void BlackJackGame::GetGameResult()
        {
            string player_name = "player" + to_string(game_pointer_);
            if (p_players_.at(game_pointer_)->GetStatus() == "bust")
            {
                winners_.at(player_name) = -1;
            }
            else if (p_dealer_->GetStatus() == "bust")
            {
                winners_.at(player_name) = 2; 
            }
            else
            {
                int player_score = p_players_.at(game_pointer_)->GetScore();
                int dealer_score = p_dealer_->GetScore();
                if (player_score < dealer_score)
                {
                    winners_.at(player_name) = -1;
                }
                else if (player_score > dealer_score)
                {
                    winners_.at(player_name) = 2;
                }
                else
                {
                    winners_.at(player_name) = 1;
                }
            }
        }

        bool BlackJackGame::IsGameOver()
        {
            for (int i = 0; i < player_num_; i++)
            {
                if (winners_.at("player" + to_string(i)) == 0)
                {
                    is_over_ = false;
                    return false;
                }
            }
            is_over_ = true;
            return true;
        }

        BlackJackGameState BlackJackGame::GetState(int player_id, BlackJackGameState & state)
        {
            state.allow_actions_ = {"hit", "stand"};
            state.current_player_hands_.clear();
            state.dealer_hands_.clear();
            for (size_t i = 0; i < p_players_.size(); i++)
            {
                string player_name = "player" + to_string(i) + "hand";
                if (state.players_hands_.find(player_name) == state.players_hands_.end())
                {
                    state.players_hands_.insert({player_name, {}});
                }
                else
                {
                    state.players_hands_.at(player_name).clear();
                }
                for (auto card : p_players_.at(i)->GetHandCard())
                {
                    state.players_hands_.at(player_name).push_back(card->GetRank());
                    if (i == player_id)
                    {
                        state.current_player_hands_.push_back(card->GetRank());
                    }
                }
            }
            if (is_over_)
            {
                for (auto card : p_dealer_->GetHandCard())
                {
                    state.dealer_hands_.push_back(card->GetRank());
                }
            }
            else
            {
                for (size_t i = 0; i < p_dealer_->GetHandCard().size(); i++)
                {
                    if (i == 0)
                    {
                        continue;
                    }
                    state.dealer_hands_.push_back(p_dealer_->GetHandCard().at(i)->GetRank());
                }
            }
            return state;
        }
        
        void BlackJackGame::ShowGameState()
        {
            cout << "allowable actions" << endl;
            for (auto action : p_state_->allow_actions_)
            {
                cout << action << "\t";
            }
            cout << endl;
            cout << "dealer's hands" << endl;
            for (auto card : p_state_->dealer_hands_)
            {
                cout << card << "\t";
            }
            cout << endl;
            cout << "players' hands" << endl;
            for (auto it = p_state_->players_hands_.begin(); it != p_state_->players_hands_.end(); it++)
            {
                cout << it->first << endl;
                for (auto card : it->second)
                {
                    cout << card << "\t";
                } 
                cout << endl;
            }
            cout << "current player hands" << endl;
            for (auto card : p_state_->current_player_hands_)
            {
                cout << card << "\t";
            }
            cout << endl;
        }

        void BlackJackGame::ShowWinner()
        {
            cout << "current game winners:" << endl;
            for (auto it = winners_.begin(); it != winners_.end(); it ++)
            {
                cout << it->first << ":" << it->second << endl;
            }
        }
    }
}