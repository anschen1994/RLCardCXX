#include "black_jack_player.h"



namespace rlcard
{
    namespace engine
    {
        void BlackJackPlayer::AddHandCard(Card* pCard)
        {
            hand_cards_.emplace_back(pCard);
        }

        void BlackJackPlayer::SetStatus(string & status)
        {
            status_ = status;
        }

        void BlackJackPlayer::SetStatus(string && status)
        {
            status_ = status;
        }

        void BlackJackPlayer::SetScore(int score)
        {
            score_ = score;
        }

        vector<string> BlackJackPlayer::AvailableOrder()
        {
            return {"stand", "hit"};
        }
    }
}