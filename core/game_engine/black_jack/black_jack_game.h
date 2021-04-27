#pragma once
#include "black_jack_dealer.h"
#include "black_jack_player.h"
#include "black_jack_judger.h"

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
            BlackJackHistory(BlackJackDealer & _dealer, map<string, int> & _winner, BlackJackPlayer & _player) : \
            dealer_(_dealer), winner_(_winner), player_(_player) {}
        };

        struct BlackJackGameState
        {
            vector<string> allow_actions_;
            map<string, vector<string>> players_hands_;
            vector<string> dealer_hands_;
            vector<string> current_player_hands_;
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

                inline int GetCurrentPlayerID() {return game_pointer_;};

                inline int GetCurrentPlayerScore() {return p_players_.at(game_pointer_)->GetScore();}

                inline string GetCurrentPlayerStatus() {return p_players_.at(game_pointer_)->GetStatus();}

                bool IsGameOver();

                BlackJackGameState GetState(int player_id, BlackJackGameState & state);

                void GetGameResult();

                void ShowGameState();

                void ShowWinner();


            private:
                const int player_num_ = 6;
                BlackJackDealer* p_dealer_;
                vector<BlackJackPlayer*> p_players_;
                BlackJackJudger* p_judger_;
                const int kStartCardNum = 2;
                map<string, int> winners_;
                size_t game_pointer_;
                vector<BlackJackHistory*> history_;
                BlackJackGameState* p_state_;
                bool is_over_ = false;
                bool is_allow_back_ = false;
                const int min_dealer_score_ = 17;

        };
    }
} // namespace rlcard
