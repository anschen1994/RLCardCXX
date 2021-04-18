#pragma once 
#include "config.h"
#include <map>

using namespace std;

namespace rlcard
{
    namespace engine
    {
        class Card
        {
            public:
                Card(const string & _suit, const string & _rank) : suit_(_suit), rank_(_rank), hash_value_(hash(_suit, _rank)){}
                
                inline bool operator==(const Card & _card);

                int hash(const string & _suit, const string & _rank);

                inline string GetCardRepresentation();

            protected:
                const string suit_;
                const string rank_;
                const int hash_value_;
        };

        class Dealer
        {
            public:
                Dealer() = default;

                virtual ~Dealer() = 0;

                virtual void Shuffle() = 0; // shuffle the remained cards

                virtual bool DealCard(int num_params, ...) = 0;

                inline int GetRemainedCardNumber();

                inline int GetTotalCardNumber();

            protected:
                vector<Card*> deck_;
                vector<Card*> remained_cards_;
        };

        class Player
        {
            public:
                Player(int _player_id) : player_id_(_player_id) {}

                virtual ~Player() = 0;

                virtual vector<string> AvailableOrder() = 0;
                
                virtual void Play() = 0;


            protected:
                const int player_id_;
                vector<Card*> hand_cards_;
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

                virtual void Step(const string & action) = 0;

                virtual void StepBack();

                virtual int GetPlayerNumber() = 0;

                virtual int GetActionNumber() = 0;

                virtual int GetPlayerID() = 0;

                virtual bool IsGameOver() = 0;

        };
    }
}