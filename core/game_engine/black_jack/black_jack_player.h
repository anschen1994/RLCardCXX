#pragma once
#include "base_engine.h"

namespace rlcard
{
    namespace engine
    {
        class BlackJackPlayer : public Player
        {
            public:
                BlackJackPlayer(int _player_id=0) : Player(_player_id) {}

                BlackJackPlayer(const string & _status, const int & _score, const int & _player_id) \
                : Player(_player_id), status_(_status), score_(_score) {}

                virtual ~BlackJackPlayer() {;}

                void AddHandCard(Card* pCard);

                vector<string> AvailableOrder();

                void SetStatus(string & status);

                void SetStatus(string && status);

                void SetScore(int score);

                inline int GetScore(){return score_;}
                
                inline string GetStatus(){return status_;}

            protected:
                string status_;
                int score_;
        };
    }
}