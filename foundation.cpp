/**
 * @file Foundation.cpp
 * @author Miroslav Karpíšek
 * @date 24 April 2017
 * @brief Soubor obsahuje asserttesty pro jednotlive třídy.
 */

#include "foundation.h++"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;

Foundation::Foundation(color color) {
    _color = color;
}

bool Foundation::put(Stack stack) {
    if(stack.size() != 1) {
        return false;
    }
    else {
        Card card = stack.get(0);
        int rest = card.hashCode() % 10;
        cout << to_string(rest);
        int color_num;
        switch (_color) {
            case DIAMONDS:
                color_num = 2;
                break;
            case HEARDS:
                color_num = 4;
                break;
            case SPADES:
                color_num = 1;
                break;
            case CLUBS:
                color_num = 3;
                break;
        }
        cout << to_string(color_num) << " "<< to_string(rest);
        if(color_num == rest) {
            //cout << endl;
            //cout << "carta: " << to_string(card.value()) << "blaicek: " << _fond.size();
            //cout << endl << card.toString();
            if(card.value() == _fond.size() + 1) {
                _fond.push_back(card);
                return true;
            }
        }
        else {
            return false;
        }
        return false;
    }

}


bool Foundation::put(Card card) {
    int rest = card.hashCode() % 10;
    int color_num;
    switch (_color) {
        case DIAMONDS:
            color_num = 2;
            break;
        case HEARDS:
            color_num = 4;
            break;
        case SPADES:
            color_num = 1;
            break;
        case CLUBS:
            color_num = 3;
            break;
    }
    if(color_num == rest) {
        if(card.value() == _fond.size() + 1) {
            _fond.push_back(card);
            return true;
        }
    }
    else {
        return false;
    }
    return false;


}

unsigned int Foundation::size() {
    return _fond.size();
}

string Foundation::toString() {
    string output;
    for(int i = 0; i < _fond.size(); i++) {
        output += _fond.at(i).toString();
        output += "\n";
    }
    return output;
}

Card Foundation::onTop() {
    if(_fond.empty()) {
        Card *card = new Card(0,DIAMONDS);
        return *card;
    }
    return _fond.back();
}

color Foundation::myColor() {
    return _color;
}

bool Foundation::empty() {
    return _fond.empty();
}
