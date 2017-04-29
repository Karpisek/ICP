/**
* @file stack.h
* @author Miroslav Karpíšek
* @date 24 April 2017
* @brief Soubor obsahuje třídu carddeck.
*/

#ifndef FOUNDATION_H
#define FOUNDATION_H

#include "card.h++"
#include "stack.h++"
#include "enums.h++"

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Foundation;

class Foundation
{
protected:
    vector<Card> _fond;
    color _color;
    unsigned int _size;
public:
     Foundation(color color);
     bool put(Stack stack);
     unsigned int size();
     string toString();
     Card onTop();
     color myColor();

     /**
      * @return if final pack is empty
      */
     bool empty();
};


#endif
