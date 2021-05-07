#pragma once
#include "../base_engine.h"

namespace rlcard
{
    namespace engine
    {
        struct LeducholdemPlayerState // define of struct LeducholdemPlayerState
        {
            string hand_card_representation_;
            string public_card_representation_;
            vector<int> all_chips_;
            float my_chips_;
            vector<string> legal_actions_;
            int cur_player_;
        };

        // class LeducholdemPlayer : public Player
        class LeducholdemPlayer
        {
        private:
            int random_seed_;
            float in_chips_;
            string player_status_;
            vector<Card *> hand_cards_;
            int player_id_;

        public:
            LeducholdemPlayer(const int _player_id, int _random_seed);
            LeducholdemPlayer(const LeducholdemPlayer &_player);

            ~LeducholdemPlayer();
            LeducholdemPlayerState GetState(Card *_public_card, vector<int> *_all_chips, vector<string> *_legal_actions);
            vector<string> AvailableOrder();
            void Play();

            inline int GetPlayerId() { return player_id_; }
            inline vector<Card *> GetHandCards() { return hand_cards_; }
            inline float GetInChips() { return in_chips_; }
            inline string GetPlayerStatus() { return player_status_; }
            inline void SetInChips(float _in_chips) { in_chips_ = _in_chips; }
            inline void SetPlayerStatus(string _player_status) { player_status_ = _player_status; }

            inline void InsertHandCard(Card *_card1) { hand_cards_.push_back(_card1); }
            void ShowPlayerInfo();
        };
    } // namespace engine
} // namespace rlcard