/**
 * @file cardDeck.cpp
 * @author Miroslav Karpíšek
 * @date 24 April 2017
 * @brief Soubor obsahuje třídu carddeck.
 */

 #include "deck.h++"

 #include <stdbool.h>
 #include <iostream>
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <algorithm>
 #include <ctime>

 using namespace std;

 long seed() {
     srand (time(NULL));
     return rand()%10000;
 }

 Deck::Deck(unsigned int size) {
     _size = size;
 }

 Deck Deck::createDeck() {
    Deck standart(52);
    for(int i = 1; i < 14; i++) {
        Card *card_d = new Card(i, DIAMONDS);
        Card *card_h = new Card(i, HEARDS);
        Card *card_s = new Card(i, SPADES);
        Card *card_c = new Card(i, CLUBS);
        standart.put(*card_d);
        standart.put(*card_h);
        standart.put(*card_s);
        standart.put(*card_c);
    }

    return standart;
}

 void Deck::put(Card card) {
     _deck.push_back(card);
 }

 Card Deck::pop() {
     Card card = _deck.back();
     _deck.pop_back();
     return card;

 }

 Card Deck::onTop() {
     if(_deck.empty()) {
         Card *card = new Card(0,DIAMONDS);
         return *card;
     }
     return _deck.back();
 }

 void Deck::shuffle() {
     for(int i = 0; i < seed(); i++){
         std::random_shuffle ( _deck.begin(), _deck.end());
     }
 }

 unsigned int Deck::size() {
     return _deck.size();
 }

 string Deck::toString() {
     string output;
     for(int i = 0; i < _deck.size(); i++) {
         output += _deck.at(i).toString();
         output += "\n";
     }
     return output;
 }
