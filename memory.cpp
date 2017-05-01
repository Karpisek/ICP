/**
* @file memory.cpp
* @author Miroslav Karpíšek
* @date 1 May 2017
* @brief Soubor obsahuje asserttesty pro jednotlive třídy.
*/

#include "memory.h++"

using namespace std;

Memory::Memory(Board *board) {

    // kopírování jména
    _name = board->getName();

    // kopírování skóre
    _score = board->getScore();

    // kopírování tahů
    _moves = board->getMoves();

    this->_grave = new Deck(0);
    this->_deck = new Deck(0);

    // kopírování aktualního balíčů
    for(int i = 0; i < board->getDeck()->size(); i++) {
        _deck->put(board->getDeck()->get(i));
    }

    // kopírování odhazovacího balíčku
    for(int i = 0; i < board->getGrave()->size(); i++) {
        _grave->put(board->getGrave()->get(i));
    }
    cout << "pointer adrr: " << _grave << endl;

    // kopírování stacků
    for(int i = 0; i < 7; i++) {
        Stack *ptr_to_clone = new Stack(*(board->getStack(i)));
        _stacks.push_back(*ptr_to_clone);
    }

    // kopírování zásobníků
    for(int i = 0; i < 7; i++) {
        Deck *ptr_to_clone = new Deck(*(board->getMagazine(i)));
        _magazines.push_back(*ptr_to_clone);
    }

    // kopírování finálních balíků
    for(int i = 0; i < 4; i++) {
        Foundation *ptr_to_clone = new Foundation(*(board->getFinal(i)));
        _fonds.push_back(*ptr_to_clone);
    }

}

Deck* Memory::getDeck() {
    return _deck;
}

Deck* Memory::getGrave() {
    return _grave;
}

Deck* Memory::getMagazine(int i) {
    return &_magazines.at(i);
}

Stack* Memory::getStack(int i) {
    return &_stacks.at(i);
}

Foundation* Memory::getFinal(int i) {
    return &_fonds.at(i);
}

int Memory::getScore() {
    return _score;
}

int Memory::getMoves() {
    return _moves;
}

string Memory::getName() {
    return _name;
}
