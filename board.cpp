/**
* @file board.cpp
* @author Miroslav Karpíšek
* @date 26 April 2017
* @brief Soubor obsahuje deklaraci třídy board.
*/

#include "board.h++"
#include "memory.h++"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;

Board::Board(int count_of_games) {
    this->_grave = new Deck(0);
    this->_deck = Deck::createDeck();

    _name = "hra_";
    _name += to_string(count_of_games + 1);
    _deck->shuffle();
    _score = 0;
    _moves = 0;

    //rozdani "zásobníků"
    for(int i = 0; i < 7; i++) {
        Deck *magazine = new Deck(0);
        for(int o = i; o > 0; o--) {
            magazine->put(_deck->pop());
        }
        _magazines.push_back(magazine);
    }

    //rozdání prvních karet do stacků
    for(int i = 0; i < 7; i++) {
        Stack *stacks = new Stack(13);
        stacks->push(_deck->pop());
        _stacks.push_back(stacks);
    }

    //inicializace "finálních balíčků"
    Foundation *fond_H = new Foundation(HEARDS);
    Foundation *fond_D = new Foundation(DIAMONDS);
    Foundation *fond_C = new Foundation(CLUBS);
    Foundation *fond_S = new Foundation(SPADES);
    _fonds.push_back(fond_H);
    _fonds.push_back(fond_D);
    _fonds.push_back(fond_C);
    _fonds.push_back(fond_S);


}

bool Board::take(Stack *stack) {
    save();
    if(!_grave->empty()) {
        Card card = _grave->pop();
        if(stack->put(card)) {
            _moves++;
            _score += 5;
            return true;
        }
        _grave->put(card);
    }

    _memory.pop_back();
    return false;
}

bool Board::take(Foundation *fond) {
    save();
    Card card = _grave->pop();

    if(fond->put(card)) {
        _moves++;
        _score += 10;
        return true;
    }
    _memory.pop_back();
    return false;
}

bool Board::StackToStack(Card *c, Stack *stack_to, Stack *stack_from, Deck *magazine) {
    save();
    Stack poped = stack_from->pop(*c);
    if(stack_to->put(poped)) {
        if(stack_from->size() == 0 && !magazine->empty()) {
            stack_from->push(magazine->pop());
        }
        _moves++;
        _score += 5;
        return true;
    }
    else {
        stack_from->push(poped);
        _memory.pop_back();
        return false;
    }
}

bool Board::StackToFinal(Card *c, Foundation *final_to, Stack *stack_from, Deck *magazine) {
    save();
    Stack poped = stack_from->pop(*c);
    cout << poped.toString();
    if(poped.size() > 1 || poped.size() == 0) {
        stack_from->push(poped);
        _memory.pop_back();
        return false;
    }
    if(final_to->put(poped)) {
        if(stack_from->size() == 0 && !magazine->empty()) {
            stack_from->push(magazine->pop());
        }
        _moves++;
        _score += 50;
        return true;
    }
    else {
        stack_from->push(poped);
        _memory.pop_back();
        return false;
    }
}

bool Board::save(string name) {

}

bool Board::load(FILE *ptr) {

}

bool Board::undo() {

    if(_memory.size() > 0) {
        _score = _memory.back()->getScore();
        _moves = _memory.back()->getMoves();

        // omnovení lízacího a odhazovácího balíčku
        _deck = _memory.back()->getDeck();
        _grave = _memory.back()->getGrave();

        // obnovení stacků a magazines a finálních balíčků
        for(int i = 0; i < 7; i++) {
            _stacks.at(i) = _memory.back()->getStack(i);
            _magazines.at(i) = _memory.back()->getMagazine(i);

            if(i < 4) {
                _fonds.at(i) = _memory.back()->getFinal(i);
            }
        }

        _memory.pop_back();
        return true;
    }
    return false;

}

void Board::save() {
    Memory *mem = new Memory(this);
    _memory.push_back(mem);
}

Deck* Board::getDeck() {
    return _deck;
}

Deck* Board::getGrave() {
    return _grave;
}

Deck* Board::getMagazine(int i) {
    return _magazines.at(i);
}

Stack* Board::getStack(int i) {
    return _stacks.at(i);
}

Foundation* Board::getFinal(int i) {
    return _fonds.at(i);
}

int Board::getScore() {
    return _score;
}

int Board::getMoves() {
    return _moves;
}

string Board::getName() {
    return _name;
}

/**
*  vezme kartu z balíčku a odloží ji na odkládací. pokud je balíček prázdný
*  "obrátí" odkládací balíček a složí první kartu.
*/
bool Board::draw() {
    save();
    if(_deck->size() + _grave->size() > 0) {
        if(_deck->size() > 0)
            _grave->put(_deck->pop());
        else {
            while(_grave->size() > 0) {
                _deck->put(_grave->pop());
            }
            _grave->put(_deck->pop());
            _score -= 50;
            if(_score < 0)
                _score = 0;
        }

        _moves++;
        return true;
    }
    _memory.pop_back();
    return false;
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
    output += to_string(_deck->size());
    output += "\n";
    output += "Odkládací balíček: ";
    output += _grave->onTop().toString();
    output += "     [L]";
    output += "\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -";
    output += "\n   [A]      [B]      [C]      [D]      [E]      [F]      [G]   ";

    // převedení "zásobníků" a "stacků" do stringu
    for(int o = 0; o < 7; o++) {
        output += "\n";
        for(int i = 0; i < 7; i++) {
            output += "   ";
            if(_magazines.at(i)->size() > o) {
                output += " # ";
            }
            else if(_stacks.at(i)->size() > counter.at(i)) {
                output += _stacks.at(i)->get(counter.at(i)).toString();
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
        if(_fonds.at(i)->size() == 0) {
            switch(_fonds.at(i)->myColor()) {
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
            output += _fonds.at(i)->onTop().toString();
        }
        output += "   ";
    }
    output += "\n                  [W]    [X]    [Y]    [Z]";
    output += "\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -";
    output += "\n";

    return output;
}
