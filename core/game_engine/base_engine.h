#pragma once
#include "../config/config.h"
#include <map>

using namespace std;

namespace rlcard
{
    namespace engine
    {
        class Card
        {
        public:
            Card(const string &_suit, const string &_rank) : suit_(_suit), rank_(_rank), hash_value_(hash(_suit, _rank)) {}

            int hash(const string &_suit, const string &_rank);

            inline string GetCardRepresentation() { return rank_ + suit_; } // change: 内联函数定义放在头文件?

            inline bool operator==(const Card &_card) { return _card.rank_ == rank_ && _card.suit_ == suit_; }
            const string suit_;
            const string rank_;

        protected:
            const int hash_value_;
        };

        class Dealer
        {
        public:
            Dealer() = default;

            virtual ~Dealer(); // change: 析构函数没必要写成纯虚函数？

            virtual void Shuffle() = 0; // shuffle the remained cards

            virtual Card *DealCard(int num_params, ...) = 0;

            inline int GetRemainedCardNumber();

            inline int GetTotalCardNumber();

        protected:
            vector<Card *> deck_;
            vector<Card *> remained_cards_;
        };

        class Player
        {
        public:
            Player(int _player_id) : player_id_(_player_id) {}

            virtual ~Player(){};

            virtual vector<string> AvailableOrder() = 0;

            virtual void Play() = 0;
            vector<Card *> hand_cards_;

        protected:
            int player_id_;
        };

        class Judger
        {
        public:
            Judger() = default;

            virtual bool JudgeRound(int num_params, ...) = 0; // vars that need to be modified can be passed in the form of pointers

            virtual bool JudgeGame(int num_params, ...) = 0; // vars that need to be modified can be passed in the form of pointers
        };

        class Round
        {
        public:
            Round() = default;

            virtual bool ProcessRound(int num_params, ...) = 0;

        protected:
            int round_id_;
        };

        class Game
        {
        public:
            Game() = default;

            virtual bool Reset() = 0; // intialize a game

            virtual void Step(const string &action) = 0;

            virtual void StepBack();

            virtual int GetPlayerNumber() = 0;

            virtual int GetActionNumber() = 0;

            virtual int GetPlayerID() = 0;

            virtual bool IsGameOver() = 0;
        };
    } // namespace engine
} // namespace rlcard