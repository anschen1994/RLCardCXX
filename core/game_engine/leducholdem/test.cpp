#include <iostream>
#include "dealer.h"
#include "player.h"
#include "judger.h"
#include "round.h"
#include "game.h"

using namespace std;
using rlcard::engine::Card;
using rlcard::engine::LeducholdemDealer;
using rlcard::engine::LeducholdemGame;
using rlcard::engine::LeducholdemJudger;
using rlcard::engine::LeducholdemPlayer;
using rlcard::engine::LeducholdemPlayerState;
using rlcard::engine::LeducholdemRound;

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

        rlcard::engine::Card *mycard = dealer.DealCard();
        cout << mycard->GetCardRepresentation() << endl;
        dealer.ShowDeck("After Deal card:");
    }

    if (false) // 测试 player
    {
        LeducholdemPlayer player = LeducholdemPlayer(1, 1);
        player.ShowPlayerInfo();
        cout << player.GetPlayerId() << endl;
        cout << "Player instance size: " << sizeof(player) << endl;

        Card pub_card1 = Card("Spades", "J");
        vector<string> actions = {"call", "raise", "fold"};
        vector<int> all_chips = {10, 5};
        LeducholdemPlayerState player_game_state = player.GetState(&pub_card1, &all_chips, &actions);
        // LeducholdemPlayerState GetState(Card * _public_card, float _all_chips, vector<string> *_legal_actions)

        cout << "public card: " << player_game_state.public_card_representation_ << endl;
        cout << "hand card: " << player_game_state.hand_card_representation_ << endl;
        cout << "my chips: " << player_game_state.my_chips_ << endl;

        cout << "legal actions: ";
        for (auto it = player_game_state.legal_actions_.begin(); it != player_game_state.legal_actions_.end(); it++)
        {
            cout << *it << "\t";
        }
        cout << endl;
        for (auto temp_chips : player_game_state.all_chips_)
        {
            cout << temp_chips << endl;
        }
    }

    if (false) // 测试 judger
    {
        LeducholdemPlayer player1 = LeducholdemPlayer(1, 1);
        LeducholdemPlayer player2 = LeducholdemPlayer(2, 1);

        Card pub_card = Card("Spades", "J");
        Card p1_handcard = Card("Spades", "Q");
        Card p2_handcard = Card("Hearts", "Q");

        player1.InsertHandCard(&p1_handcard);
        player2.InsertHandCard(&p2_handcard);
        player1.SetInChips(10);
        player2.SetInChips(21.4);

        vector<LeducholdemPlayer *> players = {&player1, &player2};

        LeducholdemJudger judger = LeducholdemJudger(1);
        judger.LeducholdemJudgeGame(&players, &pub_card);
    }

    if (false) // 测试 round
    {
        LeducholdemRound round = LeducholdemRound(2, 1, 2, 1);
        round.ShowRoundInfo();

        vector<int> new_raised = {3, 8};

        round.StartNewRound(0, nullptr);
        round.ShowRoundInfo();
        round.GetLegalActions();

        round.StartNewRound(0, &new_raised);
        round.ShowRoundInfo();
        round.GetLegalActions();

        LeducholdemPlayer player1 = LeducholdemPlayer(1, 1);
        LeducholdemPlayer player2 = LeducholdemPlayer(2, 1);
        player1.ShowPlayerInfo();
        player2.ShowPlayerInfo();
        vector<LeducholdemPlayer *> players_lst = {&player1, &player2};

        cout << "round proceed~~~~~~~~~~~~~~~~~~~~" << endl;
        int new_player = round.ProceedRound(&players_lst, "raise");
        cout << "next player id: " << new_player << endl;
        // round.ProceedRound(&players_lst, "fold");
        // round.ProceedRound(&players_lst, "call");
        // round.ProceedRound(&players_lst, "check");
        // round.ProceedRound(&players_lst, "not legal action");
        round.ShowRoundInfo();
        player1.ShowPlayerInfo();
        player2.ShowPlayerInfo();

        cout << "round proceed~~~~~~~~~~~~~~~~~~~~" << endl;
        new_player = round.ProceedRound(&players_lst, "call");
        cout << "next player id: " << new_player << endl;
        round.ShowRoundInfo();
        player1.ShowPlayerInfo();
        player2.ShowPlayerInfo();
    }

    if (true) // 测试 game
    {
        LeducholdemGame game = LeducholdemGame(true);
        LeducholdemPlayerState p_state = game.InitGame();
        // LeducholdemPlayerState p_state = game.GetState(0);
        cout << p_state.cur_player_ << endl;
        cout << p_state.hand_card_representation_ << endl;
        cout << p_state.public_card_representation_ << endl;

        cout << "Start Step..." << endl
             << endl;


        game.Step("call");
        game.StepBack();
    }

    return 0;
}