/**
* @file board.h++
* @author Miroslav Karpíšek
* @date 26 April 2017
* @brief Hlavičkový soubor pro board.cpp
*/

#ifndef BOARD_H
#define BOARD_H

#define SPADE_F   "\033[6;11m\u2660\033[0m"
#define CLUB_F    "\033[6;11m\u2663\033[0m"
#define HEART_F   "\033[6;31m\u2665\033[0m"
#define DIAMOND_F "\033[6;31m\u2666\033[0m"
#define CLEAR     "\033[2J"

#include "card.h++"
#include "deck.h++"
#include "stack.h++"
#include "foundation.h++"

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Board;

class Board
{
 protected:
    Deck _deck; // simuluje lízací balíček
    Deck _grave; // simuluje odkládací balíček

    vector<Stack> _stacks; // simluace stacků na boardu (7)
    vector<Deck> _magazines; // simluace "zásobníků" jednotlivých stacků (6)
    vector<Foundation> _fonds; // simluace finálních blaíčků jednotlivých barev (4)

 public:
    Board();
    void draw(); // vezme kartu z lizaciho balicku a vlozi ji na odkladaci
    bool take(string to); // vezme kartu z odkladaciho balicku a pokusi se vlozit na zvoleny balicek
    bool put(int from, int to); // vezme "stack" a vloziho na zvoleny stack/nebo found
    Card topGrave();
    bool emptyGrave();
    string toString(); // pro debug a konsolový výpis
};


#endif
