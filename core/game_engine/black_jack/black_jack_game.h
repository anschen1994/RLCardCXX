#pragma once
#include "black_jack_dealer.h"
#include "black_jack_player.h"
#include "black_jack_judger.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

namespace rlcard
{
    namespace engine
    {
        struct BlackJackHistory
        {
            BlackJackDealer dealer_;
            // BlackJackJudger judger_;
            map<string, int> winner_;
            BlackJackPlayer player_;
            BlackJackPlayer banker_;
            BlackJackHistory(const BlackJackDealer & _dealer, const map<string, int> & _winner, const BlackJackPlayer & _player, const BlackJackPlayer & _banker) : \
            dealer_(_dealer), winner_(_winner), player_(_player), banker_(_banker) {}
        };

        struct BlackJackGameState
        {
            vector<string> allow_actions_;
            map<string, vector<string>> players_hands_;
            vector<string> banker_hands_;
            vector<string> current_player_hands_;
        };

        enum BlackJackAction
        {
            Hit,
            Stand,
            ActionNum
        };

        class BlackJackGame : public Game
        {
            public:
                BlackJackGame();

                ~BlackJackGame();

                bool Reset(); // intialize a game

                BlackJackGameState Step(const string & action);

                // void StepBack();

                inline int GetPlayerNumber() {return player_num_;}

                inline int GetActionNumber() {return 2;};

                inline int GetCurrentPlayerID() {return p_players_.at(game_pointer_)->GetPlayerID();};

                inline int GetCurrentPlayerScore() {return p_players_.at(game_pointer_)->GetScore();}

                inline PlayerStatus GetCurrentPlayerStatus() {return p_players_.at(game_pointer_)->GetStatus();}

                bool IsGameOver();

                BlackJackGameState GetState(int player_id, BlackJackGameState & state);

                void GetGameResult();

                void ShowGameState();

                void ShowWinner();

                inline const vector<BlackJackHistory*> & GetGameHistory() {return history_;}

                inline const vector<BlackJackPlayer*> & GetGamePlayers() {return p_players_;}

            private:
                const int player_num_ = 6;
                BlackJackDealer* p_dealer_;
                vector<BlackJackHistory*> history_;
                vector<BlackJackPlayer*> p_players_;
                BlackJackPlayer* p_banker_;               
                BlackJackJudger* p_judger_;
                const int kStartCardNum = 2;
                map<string, int> winners_;
                size_t game_pointer_;
                BlackJackGameState* p_state_;
                bool is_over_ = false;
                bool is_allow_back_ = true;
                const int min_dealer_score_ = 17;
                shared_ptr<spdlog::logger> logger_;

        };
    }
} // namespace rlcard
