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

class Memory;
class Board;

class Board
{
 protected:
    string _name; // pojmenování hry
    int _score;
    int _moves;
    Deck* _deck; // simuluje lízací balíček
    Deck* _grave; // simuluje odkládací balíček

    vector<Stack*> _stacks; // simluace stacků na boardu (7)
    vector<Deck*> _magazines; // simluace "zásobníků" jednotlivých stacků (6)
    vector<Foundation*> _fonds; // simluace finálních blaíčků jednotlivých barev (4)

    vector<Memory*> _memory;
    // paměť tahů

 public:

    Board(string name);
    Board(string name, bool history);

    bool draw(); // vezme kartu z lizaciho balicku a vlozi ji na odkladaci
    bool take(Stack *stack); // vezme kartu z odkladaciho balicku a pokusi se vlozit na zvoleny balicek
    bool take(Foundation *fond); //vezme kartu z odkladaciho blaicku a pokusi se ji vlozit na finalní balík
    bool StackToStack(Card *c, Stack *stack_to, Stack *stack_from, Deck *magazine);
    bool StackToFinal(Card *c, Foundation *final_to, Stack *stack_from, Deck *magazine);
    bool put(int from, int to); // vezme "stack" a vloziho na zvoleny final

    bool undo(); // vrátí tah (načteno z paměti)

    bool saveGame(); // uloží hru s názvem name
    bool load(string name); // načte hru uloženou ve zvolenem

    void save(); // uloží do paměti

    Board parse();
    Deck* getDeck();
    Deck* getGrave();
    Deck* getMagazine(int i);
    Stack* getStack(int i);
    Foundation* getFinal(int i);

    int getScore();
    int getMoves();

    string getName();


    string toString(); // pro debug a konsolový výpis
};


#endif
