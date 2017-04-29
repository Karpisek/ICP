/**
* @file deck.h
* @author Miroslav Karpíšek
* @date 24 April 2017
* @brief hlavičkový soubor pro třídu carddeck.
*/

#ifndef DECK_H
#define DECK_H

#include "enums.h++"
#include "card.h++"

#include <string>
#include <vector>

using namespace std;

class Deck;

class Deck
{
 protected:
    vector<Card> _deck;
    unsigned int _size;

 public:
     Deck(unsigned int size);
     static Deck createDeck();
     Card pop();
     Card onTop();

     /**
     * vrací Card na žádané pozici, (0, DIAMONDS) v případě sáhnutí mimo rozsah
     */
     Card get(int i);

     void put(Card card);
     void shuffle();

     unsigned int size();
     bool empty();

     string toString();


};

#endif
