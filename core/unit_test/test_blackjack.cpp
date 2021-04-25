#include"black_jack/black_jack_game.h"
#include<iostream>

using namespace std;
using namespace rlcard;
int main()
{
    engine::BlackJackGame game;
    game.Reset();
    cout << "PlayerNumber: " << game.GetPlayerNumber() << endl;
    cout << "ActionNumber: " << game.GetActionNumber() << endl;
    game.ShowGameState();
    for (int i = 0; i < game.GetPlayerNumber(); i++)
    {
        cout << "============" << endl;
        game.Step("hit");
        game.ShowGameState();
        game.ShowWinner();
    }
    for (int i = 0; i < game.GetPlayerNumber(); i++)
    {
        if (game.GetCurrentPlayerScore() < 11)
        {
            game.Step("hit");
        }
        else
        {
            game.Step("stand");
        }
        cout << "============" << endl;
        game.ShowGameState();
        game.ShowWinner();
    }
    return 0;
}