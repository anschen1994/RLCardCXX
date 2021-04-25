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
                
                inline bool operator==(const Card & _card) {return _card.rank_ == rank_ && _card.suit_ == suit_;}

                int hash(const string & _suit, const string & _rank);

                inline string GetCardRepresentation() {return rank_ + suit_;}

                inline string GetSuit(){return suit_;}

                inline string GetRank(){return rank_;}

            protected:
                const string suit_;
                const string rank_;
                const int hash_value_;
        };

        class Dealer
        {
            public:
                Dealer() = default;

                ~Dealer();

                virtual void Shuffle() = 0; // shuffle the remained cards

                virtual void InitCards() = 0;

                inline int GetRemainedCardNumber(){return int(remained_cards_.size());}

                inline int GetTotalCardNumber(){return (int)deck_.size();}

            protected:
                vector<Card*> deck_;
                vector<Card*> remained_cards_;
        };

        class Player
        {
            public:
                Player(int _player_id) : player_id_(_player_id) {}

                ~Player();

                virtual vector<string> AvailableOrder() = 0;

                inline int GetPlayerID(){return player_id_;}

                vector<Card*> GetHandCard();

            protected:
                const int player_id_;
                vector<Card*> hand_cards_;
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
 
                // virtual void StepBack();

                virtual inline int GetPlayerNumber() = 0;

                virtual inline int GetActionNumber() = 0;

                virtual bool IsGameOver() = 0;

        };
    }
}