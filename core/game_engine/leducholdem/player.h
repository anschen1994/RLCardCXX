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
            float all_chips_;
            float my_chips_;
            vector<string> *legal_actions_;
        };

        class LeducholdemPlayer : public Player
        {
        private:
            int random_seed_;

        public:
            float in_chips_;
            string player_status_;
            LeducholdemPlayer(const int _player_id, int _random_seed);
            ~LeducholdemPlayer();
            LeducholdemPlayerState GetState(Card *_public_card, float _all_chips, vector<string> *_legal_actions);
            const int GetPlayerID();
            vector<string> AvailableOrder();
            void Play();

            void ShowPlayerInfo();
        };
    } // namespace engine
} // namespace rlcard