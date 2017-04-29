/**
* @file stack.cpp
* @author Miroslav Karpíšek
* @date 24 April 2017
* @brief Soubor obsahuje třídu cardstack.
*/

#include "stack.h++"

#include <stdbool.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

Stack::Stack(unsigned int size) {
    _size = size;
}

Stack Stack::pop(Card card) {
    int index = -1;
    for(int i = 0; i < _stack.size(); i++) {

        if(_stack.at(i).equals(card)) {
            index = i;
            break;
        }
    }
    if(index >= 0) {
        Stack cut(13);
        for(int i = index; i < _stack.size(); i++) {
            //cout << _stack.at(i).toString() << endl;
            cut.push(_stack.at(i));

        }

        for(int i = _stack.size() - 1; i >= index; i--) {
            _stack.pop_back();
        }

        return cut;
    }

    return 0;

}

// obchazi povinost zacinat kralem
void Stack::push(Card card) {
    _stack.push_back(card);
}

Card Stack::pop() {
    Card card = _stack.back();
    _stack.pop_back();
    return card;
}

bool Stack::contains(Card* card) {
    for (int i = 0; i < _stack.size(); i++) {
        if(get(i).equals(*card)) {
            return true;
        }
    }
    return false;
}

bool Stack::put(Card card) {

    cout << card.toString()<<endl;
    // test jeslti neni pocet karet vyssi nez max
    if(_stack.size() < _size) {
        cout << "pocet ok" <<endl;
        // kontrola jestli neni balicek prazdny -> v tom případě lze vložit jen krále
        if(_stack.empty()) {
            cout << "prazdny balicek ok" <<endl;
            if(card.value() == 13) {
                _stack.push_back(card);
                return true;
            }
            else {
                cout << "prazdny balicek fail" <<endl;
                return false;
            }
        }

        // jinak kontrola jestli vkladana karta je o 1 nizsi nez vrchni + je opacne barvy
        Card top_card = _stack.back();

        if(top_card.compareVal(card) == 1){
            cout << "kontrola hodnot" <<endl;
            if(!card.sameColor(top_card)) {
                _stack.push_back(card);
                return true;
            }
            else {
                return false;
            }
        }
        else {
            return false;
        }
    }
    else {
        cout << "spatny pocet: " << to_string(_size) <<endl;
        return false;
    }

}

bool Stack::put(Stack stack) {
    bool one = false;

    for(int i = 0; i < stack.size(); i++) {
        one = put(stack.get(i));
        if(!one) {
            return false;
        }

    }
    return one;
}

unsigned int Stack::size() {
    return _stack.size();
}

Card Stack::get(int i) {
    if(i < _stack.size())
        return _stack.at(i);

    Card *ret = new Card(0, DIAMONDS);
    return *ret;
}

string Stack::toString() {
    string output;
    for(int i = 0; i < _stack.size(); i++) {
        output += _stack.at(i).toString();
        output += "\n";
    }
    return output;
}
