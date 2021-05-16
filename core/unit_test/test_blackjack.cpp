#include"black_jack/black_jack_game.h"
#include<iostream>
#include"spdlog/spdlog.h"
#include"spdlog/sinks/basic_file_sink.h"

using namespace std;
using namespace rlcard;
int main()
{
    // spdlog::register_logger(spdlog::basic_logger_mt("game_logger", "./logs/game.log"));
    engine::BlackJackGame game;
    game.Reset();
    // cout << "PlayerNumber: " << game.GetPlayerNumber() << endl;
    spdlog::info("PlayerNumber: {}", game.GetPlayerNumber());
    cout << "ActionNumber: " << game.GetActionNumber() << endl;
    game.ShowGameState();
    for (int i = 0; i < game.GetPlayerNumber(); i++)
    {
        cout << "============" << endl;
        game.Step("hit");
        game.ShowGameState();
        game.ShowWinner();
        if (i == 1)
        {
            game.GetGameHistory().at(1)->player_.SetScore(10);
            cout << "========" << endl;
            cout << game.GetGamePlayers().at(1)->GetScore() << "!= 10" << endl;
            cout << "========" << endl;
        }
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