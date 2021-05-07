#include <iostream>
#include "player.h"

using std::cout;
using std::endl;

namespace rlcard
{
    namespace engine
    {
        // LeducholdemPlayer::LeducholdemPlayer(const int _player_id, int _random_seed) : Player(_player_id)
        LeducholdemPlayer::LeducholdemPlayer(const int _player_id, int _random_seed)
        {
            player_id_ = _player_id;
            player_status_ = "alive";
            hand_cards_ = {};
            random_seed_ = _random_seed;
            in_chips_ = 0;
        }

        // 拷贝构造函数
        LeducholdemPlayer::LeducholdemPlayer(const LeducholdemPlayer &_player)
        {
            random_seed_ = _player.random_seed_;
            in_chips_ = _player.in_chips_;
            player_status_ = _player.player_status_;
            player_id_ = _player.player_id_;

            for (Card *temp_card : _player.hand_cards_)
            {
                Card *new_card = new Card(*temp_card);
                hand_cards_.push_back(new_card);
            }
            cout << "player 拷贝构造函数调用成功" << endl;
        }

        LeducholdemPlayer::~LeducholdemPlayer()
        {
            for (auto temp_card : hand_cards_)
            {
                delete temp_card;
            }
            cout << "player 析构函数调用成功" << endl;
        }

        LeducholdemPlayerState LeducholdemPlayer::GetState(Card *_public_card, vector<int> *_all_chips, vector<string> *_legal_actions)
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
            // p_game_state.all_chips_ = _all_chips;
            for (auto iter = _all_chips->begin(); iter != _all_chips->end(); iter++)
            {
                p_game_state.all_chips_.push_back(*iter);
            }
            p_game_state.my_chips_ = in_chips_;
            // p_game_state.legal_actions_ = _legal_actions;
            for (auto iter = _legal_actions->begin(); iter != _legal_actions->end(); iter++)
            {
                p_game_state.legal_actions_.push_back(*iter);
            }

            return p_game_state;
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
            cout << "inchips: " << in_chips_ << "\t# of handcard: " << hand_cards_.size() << endl;
            cout << "Cards in hand: ";
            for (auto temp_card : hand_cards_)
            {
                cout << temp_card->GetCardRepresentation() << "\t";
            }
            cout << endl;
        }
    } // namespace engine
} // namespace rlcard