/**
* @file board.h++
* @author Miroslav Karpíšek
* @date 26 April 2017
* @brief Hlavičkový soubor pro board.cpp
*/

#ifndef GAME_H
#define GAME_H

#include "card.h++"
#include "deck.h++"
#include "stack.h++"
#include "enums.h++"
#include "foundation.h++"
#include "board.h++"

#define SLEEP_TIME 2000000 // prodleva pri spatnych posunech

#define ERR_VOLBA "\033[5;31mZadána neplatná volba\033[0m"
#define CLEAR     "\033[2J"
#define ACTUAL "\033[5;31m\u25A0\033[0m"
#define TABS "              "

#define MENU 0
#define MENU_WITH_GAME 10
#define INGAME 1
#define CHANGE 2
#define GAME_CARD 3
#define LOAD 4
#define NAME 5

//#define HINTS 5

#define NOVA_HRA "N"
#define NACIST "S"
#define UKONCIT "X"





#endif
