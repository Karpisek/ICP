/**
* @file stack.h
* @author Miroslav Karpíšek
* @date 24 April 2017
* @brief Soubor obsahuje třídu carddeck.
*/

#ifndef STACK_H
#define STACK_H

#include "card.h++"

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Stack;

class Stack
{
private:
    Card pop();
protected:
    vector<Card> _stack;
    unsigned int _size;
public:
     Stack(unsigned int size);
     Stack pop(Card card);
     bool contains(Card* card);
     bool put(Card card);
     bool put(Stack stack);
     unsigned int size();
     void push(Card);
     string toString();
     Card get(int i);


};


#endif
