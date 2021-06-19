#include <iostream>
#include "player.h"

using std::cout;
using std::endl;

namespace rlcard
{
    namespace engine
    {
        LeducholdemPlayer::LeducholdemPlayer(const int _player_id, int _random_seed) : Player(_player_id)
        {
            player_status_ = "alive";
            hand_cards_ = {};
            random_seed_ = _random_seed;
            in_chips_ = 0;
        }

        LeducholdemPlayer::~LeducholdemPlayer()
        {
        }

        LeducholdemPlayerState LeducholdemPlayer::GetState(Card *_public_card, float _all_chips, vector<string> *_legal_actions)
        {
            // TODO
            LeducholdemPlayerState p_game_state;
            if (hand_cards_.size() > 0)
            {
                p_game_state.hand_card_representation_ = hand_cards_[0]->GetCardRepresentation();
            }
            if (_public_card != nullptr)
            {
                p_game_state.public_card_representation_ = _public_card->GetCardRepresentation();
            }
            p_game_state.all_chips_ = _all_chips;
            p_game_state.my_chips_ = in_chips_;
            p_game_state.legal_actions_ = _legal_actions;

            return p_game_state;
        }

        const int LeducholdemPlayer::GetPlayerID()
        {
            return player_id_;
        }

        vector<string> LeducholdemPlayer::AvailableOrder()
        {
            vector<string> order = {};
            return order;
        }

        void LeducholdemPlayer::Play()
        {
        }

        void LeducholdemPlayer::ShowPlayerInfo()
        {
            cout << "player id: " << player_id_ << "\t player state: " << player_status_ << endl;
            cout << "# of handcard: " << hand_cards_.size() << endl;
        }
    } // namespace engine
} // namespace rlcard