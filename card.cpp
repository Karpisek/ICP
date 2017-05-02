/**
 * @file Card.cpp
 * @author Miroslav Karpíšek
 * @date 24 April 2017
 * @brief Soubor obsahuje asserttesty pro jednotlive třídy.
 */

 // TODO - osetrit spatný karty když number < 1 || > 13

#include "card.h++"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;

/**
* Card constructor
*
* @param    number
* @param    color
*/
Card::Card(int number, color color) {
    _color = color;
    _number = number;
    _up = true;
}

string Card::toString() {
    std::string output;

    switch (_color) {
        case DIAMONDS:
            output += DIAMOND;  //cervena
            break;

        case HEARDS:
            output += HEART;  //cervena
            break;

        case SPADES:
            output += SPADE;  //cerna
            break;

        case CLUBS:
            output += CLUB;  //cerna
            break;
    }

    switch (_number) {
        case 1:
            output += " A";
            break;
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            output += " ";
            output += to_string(_number);
            break;
        case 10:
            output += to_string(_number);
            break;
        case 11:
            output += " J";
            break;
        case 12:
            output += " Q";
            break;
        case 13:
            output += " K";
            break;
        default:
            return "   ";

    }

    return output;
}

string Card::toSave() {
    std::string output;

    switch (_color) {
        case DIAMONDS:
            output += "D";  //cervena
            break;

        case HEARDS:
            output += "H";  //cervena
            break;

        case SPADES:
            output += "S";  //cerna
            break;

        case CLUBS:
            output += "C";  //cerna
            break;
    }

    switch (_number) {
        case 1:
            output += "-A";
            break;
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            output += "-";
            output += to_string(_number);
            break;
        case 10:
            output += to_string(_number);
            break;
        case 11:
            output += "-J";
            break;
        case 12:
            output += "-Q";
            break;
        case 13:
            output += "-K";
            break;
        default:
            return "   ";

    }

    return output;
}

int Card::hashCode() {
    int hash;
    switch (_color) {
        case DIAMONDS:
            hash = 2;
            break;
        case HEARDS:
            hash = 4;
            break;
        case SPADES:
            hash = 1;
            break;
        case CLUBS:
            hash = 3;
            break;
    }

    return _number * 10 + hash;

}

bool Card::equals(Card card) {
    return hashCode() == card.hashCode();
}

color Card::myColor() {
    return _color;
}

int Card::value() {
    if (_number < 14 && _number > 0)
        return _number;
    else
        return 0;
}

void Card::turn() {
    _up = !_up;
}

int Card::compareVal(Card card) {
    return value() - card.value();
}

bool Card::sameColor(Card card) {
    switch (_color) {
        case DIAMONDS:
            if (card.hashCode() % 2 == 0) {
                return true;
            }
            else
                return false;

        case HEARDS:
            if (card.hashCode() % 2 == 0) {
                return true;
            }
            else
                return false;

        case CLUBS:
            if (card.hashCode() % 2 == 1) {
                return true;
            }
            else
                return false;

        case SPADES:
            if (card.hashCode() % 2 == 1) {
                return true;
            }
            else
                return false;

    }
}
