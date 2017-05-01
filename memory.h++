/**
* @file card.cpp
* @author Miroslav Karpíšek
* @date 1 May 2017
* @brief Soubor obsahuje asserttesty pro jednotlive třídy.
*/

#ifndef MEM_H
#define MEM_H

#include "board.h++"

#include <string>
#include <vector>

using namespace std;

class Board;
class Memory;

class Memory {
    protected:
        string _name; // pojmenování hry
        int _score;
        int _moves;
        Deck* _deck; // simuluje lízací balíček
        Deck* _grave; // simuluje odkládací balíček

        vector<Stack> _stacks; // simluace stacků na boardu (7)
        vector<Deck> _magazines; // simluace "zásobníků" jednotlivých stacků (6)
        vector<Foundation> _fonds;
    public:
        Memory(Board *board); // uklada aktualni stav hry

        Deck* getDeck();
        Deck* getGrave();
        Deck* getMagazine(int i);
        Stack* getStack(int i);
        Foundation* getFinal(int i);

        int getScore();
        int getMoves();

        string getName();

};

#endif
