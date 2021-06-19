#include <iostream>
#include <algorithm>
#include "dealer.h"

using std::cout;
using std::endl;
using std::random_shuffle;

namespace rlcard
{
    namespace engine
    {
        // 初始化
        LeducholdemDealer::LeducholdemDealer(int _random_seed)
        {
            random_seed_ = _random_seed;

            Card *card1 = new Card("Spades", "J");
            Card *card2 = new Card("Spades", "Q");
            Card *card3 = new Card("Spades", "K");
            Card *card4 = new Card("Hearts", "J");
            Card *card5 = new Card("Hearts", "Q");
            Card *card6 = new Card("Hearts", "K");
            deck_ = {card1, card2, card3, card4, card5, card6};
            pot_ = 0;
            cout << "constructed leducholdem Dealer success~" << endl;
        }

        // 析构，释放内存
        LeducholdemDealer::~LeducholdemDealer()
        {
            cout << "=========================\n"
                 << "destruct deck_ item" << endl;
            for (int i = 0; i < deck_.size(); i++)
            {
                // string cardname = deck_[i]->GetCardRepresentation();
                // cout << "delete card:" << i << "\t card id: " << cardname << endl;
                delete deck_[i];
            }
        }

        // 洗牌
        void LeducholdemDealer::Shuffle()
        {
            //TODO:need implement
            std::srand(random_seed_);
            random_shuffle(deck_.begin(), deck_.end());
        }

        // 发牌
        Card *LeducholdemDealer::DealCard(int num_params, ...)
        {
            //TODO:need implement
            Card *backCard = deck_.back();
            deck_.pop_back();
            return backCard;
        }

        // 打印牌序
        void LeducholdemDealer::ShowDeck(string msg)
        {
            cout << msg << endl;
            for (int i = 0; i < deck_.size(); i++)
            {
                cout << deck_[i]->GetCardRepresentation() << "\t" << endl;
            }
        }

    } // namespace engine
} // namespace rlcard