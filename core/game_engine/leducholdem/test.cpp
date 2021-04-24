#include <iostream>
#include "dealer.h"
#include "player.h"
#include "judger.h"

using namespace std;
using rlcard::engine::Card;
using rlcard::engine::LeducholdemDealer;
using rlcard::engine::LeducholdemJudger;
using rlcard::engine::LeducholdemPlayer;
using rlcard::engine::LeducholdemPlayerState;

int main()
{
    if (false) // 测试 card
    {
        Card card1 = Card("Hearts", "J");
        cout << "card representation: " << card1.GetCardRepresentation() << endl;
        cout << "card hash: " << card1.hash("Hearts", "J") << endl;
    }

    if (false) // 测试 dealer
    {
        LeducholdemDealer dealer = LeducholdemDealer(1);
        dealer.ShowDeck("Before shuffle:");
        dealer.Shuffle();
        dealer.ShowDeck("After shuffle:");
        cout << "============================" << endl;

        rlcard::engine::Card *mycard = dealer.DealCard(1);
        cout << mycard->GetCardRepresentation() << endl;
    }

    if (false) // 测试 player
    {
        LeducholdemPlayer player = LeducholdemPlayer(1, 1);
        player.ShowPlayerInfo();
        cout << player.GetPlayerID() << endl;
        cout << "Player instance size: " << sizeof(player) << endl;

        Card pub_card1 = Card("Spades", "J");
        vector<string> actions = {"call", "raise", "fold"};
        LeducholdemPlayerState player_game_state = player.GetState(&pub_card1, 10, &actions);
        // LeducholdemPlayerState GetState(Card * _public_card, float _all_chips, vector<string> *_legal_actions)

        cout << "public card: " << player_game_state.public_card_representation_ << endl;
        cout << "hand card: " << player_game_state.hand_card_representation_ << endl;
        cout << "all chips: " << player_game_state.all_chips_ << endl;
        cout << "my chips: " << player_game_state.my_chips_ << endl;

        cout << "legal actions: ";
        for (auto it = player_game_state.legal_actions_->begin(); it != player_game_state.legal_actions_->end(); it++)
        {
            cout << *it << "\t";
        }
        cout << endl;
    }

    if (true) // 测试 judger
    {
        LeducholdemPlayer player1 = LeducholdemPlayer(1, 1);
        LeducholdemPlayer player2 = LeducholdemPlayer(2, 1);

        Card pub_card = Card("Spades", "J");
        Card p1_handcard = Card("Spades", "Q");
        Card p2_handcard = Card("Hearts", "Q");

        player1.hand_cards_.push_back(&p1_handcard);
        player2.hand_cards_.push_back(&p2_handcard);
        player1.in_chips_ = 10;
        player2.in_chips_ = 21.4;

        vector<LeducholdemPlayer *> players = {&player1, &player2};

        LeducholdemJudger judger = LeducholdemJudger(1);
        judger.LeducholdemJudgeGame(&players, &pub_card);
    }

    return 0;
}