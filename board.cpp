/**
* @file board.cpp
* @author Miroslav Karpíšek
* @date 26 April 2017
* @brief Soubor obsahuje deklaraci třídy board.
*/

#include "board.h++"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;

Board::Board() : _deck(52), _grave(0){
    _deck = Deck::createDeck();
    _deck.shuffle();

    //rozdani "zásobníků"
    for(int i = 0; i < 7; i++) {
        Deck magazine(0);
        for(int o = i; o > 0; o--) {
            magazine.put(_deck.pop());
        }
        _magazines.push_back(magazine);
    }

    //rozdání prvních karet do stacků
    for(int i = 0; i < 7; i++) {
        Stack stacks(13);
        stacks.push(_deck.pop());
        _stacks.push_back(stacks);
    }

    //inicializace "finálních balíčků"
    Foundation fond_H(HEARDS);
    Foundation fond_D(DIAMONDS);
    Foundation fond_C(CLUBS);
    Foundation fond_S(SPADES);
    _fonds.push_back(fond_H);
    _fonds.push_back(fond_D);
    _fonds.push_back(fond_C);
    _fonds.push_back(fond_S);


}

bool Board::take(Stack *stack) {
    if(!_grave.empty()) {
        Card card = _grave.pop();
        if(stack->put(card))
            return true;

        _grave.put(card);
    }
    return false;
}


Deck* Board::getDeck() {
    return &_deck;
}

Deck* Board::getGrave() {
    return &_grave;
}

Deck* Board::getMagazine(int i) {
    return &_magazines.at(i);
}

Stack* Board::getStack(int i) {
    return &_stacks.at(i);
}

Foundation* Board::getFinal(int i) {
    return &_fonds.at(i);
}

/**
*  vezme kartu z balíčku a odloží ji na odkládací. pokud je balíček prázdný
*  "obrátí" odkládací balíček a složí první kartu.
*/
void Board::draw() {
    if(_deck.size() > 0)
        _grave.put(_deck.pop());
    else {
        while(_grave.size() > 0) {
            _deck.put(_grave.pop());
        }
        _grave.put(_deck.pop());
    }
}




string Board::toString() {
    vector<int> counter;
    string output;

    // inicializace counteru
    for(int i = 0; i < 7; i++)
        counter.push_back(0);

    // příprava rozhraní
    //output += "***************************************************************\n\n";
    output += "Počet karet v balíku: ";
    output += to_string(_deck.size());
    output += "\n";
    output += "Odkládací balíček: ";
    output += _grave.onTop().toString();
    output += "     [L]";
    output += "\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -";
    output += "\n   [A]      [B]      [C]      [D]      [E]      [F]      [G]   ";

    // převedení "zásobníků" a "stacků" do stringu
    for(int o = 0; o < 7; o++) {
        output += "\n";
        for(int i = 0; i < 7; i++) {
            output += "   ";
            if(_magazines.at(i).size() > o) {
                output += " # ";
            }
            else if(_stacks.at(i).size() > counter.at(i)) {
                output += _stacks.at(i).get(counter.at(i)).toString();
                counter.at(i) += 1;
            }
            else {
                output += "   ";
            }
            output += "   ";
        }
    }

    // převedení finálních balíků
    output += "\n\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -";
    output += "\nFinální balíky: ";
    for(int i = 0; i < 4; i++) {
        output += "   ";
        if(_fonds.at(i).size() == 0) {
            switch(_fonds.at(i).myColor()) {
                case DIAMONDS:
                    output += DIAMOND_F;
                    break;
                case HEARDS:
                    output += HEART_F;
                    break;
                case CLUBS:
                    output += CLUB_F;
                    break;
                case SPADES:
                    output += SPADE_F;
                    break;
            }
        }
        else {
            output += _fonds.at(i).onTop().toString();
        }
        output += "   ";
    }
    output += "\n                  [W]    [X]    [Y]    [Z]";
    output += "\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -";
    output += "\n";

    return output;
}
