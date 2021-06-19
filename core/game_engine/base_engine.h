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
                Card(const string & _suit, const string & _rank) : suit_(_suit), rank_(_rank){}
                
                inline bool operator==(const Card & _card) {return _card.rank_ == rank_ && _card.suit_ == suit_;}

                int hash(const string &_suit, const string &_rank);

                inline string GetCardRepresentation() {return rank_ + suit_;}

                inline string GetSuit()const {return suit_;}

                inline string GetRank() const {return rank_;}

            protected:
                int hash_value_;
                const string suit_;
                const string rank_;
        };

        class Dealer
        {
            public:
                Dealer() = default;

                virtual ~Dealer();

                virtual void Shuffle() = 0; // shuffle the remained cards

                virtual void InitCards() = 0;

                inline int GetRemainedCardNumber(){return int(remained_cards_.size());}

                inline int GetTotalCardNumber(){return (int)deck_.size();}

            protected:
                vector<Card *> deck_;
                vector<Card *> remained_cards_;
        };

        class Player
        {
            public:
                Player(int _player_id) : player_id_(_player_id) {}

                Player(const Player & _player);

                virtual ~Player();

                virtual vector<string> AvailableOrder() = 0;

                inline int GetPlayerID() const {return player_id_;}

                const vector<Card*> & GetHandCard();

            protected:
                int player_id_;
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

                virtual inline int GetPlayerID() = 0;

                virtual bool IsGameOver() = 0;
        };
    } // namespace engine
} // namespace rlcard
