/**
 * @file tests.cpp
 * @author Miroslav Karpíšek
 * @date 24 April 2017
 * @brief Soubor obsahuje asserttesty pro jednotlive třídy.
 */

#include <assert.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <unistd.h>

#include "game.h++"

using std::cout;
using namespace std;

void clear(bool ending){
    cout << CLEAR; //cisteni
    if(!ending)
        cout << "                     Solitaire 2017 - ICP";
    cout << endl << endl;
    cout << endl << endl;
}

bool has_only_digits(const string s){
  return s.find_first_not_of( "0123456789" ) == string::npos;
}

void print_ending(bool err) {
    if(err) {
        cout << ERR_VOLBA;
        cout << endl;
    }
    else {
        cout << endl;
    }

    cout << endl;
    cout << "Vaše volba: ";
}

void print_menu(int state) {
    cout << CLEAR;
    cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -";
    cout << endl;

    if(state == MENU)
        cout << "NOVA HRA [N] | NACIST [S] |                     | UKONCIT [X]";

    else if(state == CHANGE)
        cout << "                                                   | MENU [X]";

    else if(state == MENU_WITH_GAME)
        cout << "NOVA HRA [N] | NACIST [S] | VRATIT DO HRY [Z]   | UKONCIT [X]";

    else
        cout << "UNDO [U] | ZMENIT HRU [Z] | ULOZIT [S] |           | MENU [X]";

    cout << endl;
    cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
    cout << endl;

    if (state == MENU || state == MENU_WITH_GAME) {
        for(int i = 0; i < 15; i++)
            cout << endl;
    }
}

void print_change(vector<Board*> boards, int focus) {

    // Pomocna abeceda
    string abc = "ABCDEFGH";

    // uprava focusu pro pristup do pole
    focus = focus - 1;

    // pouze jedna hra a to hra ze ktere jsme se sem dostali
    for(int i = 0; i < 3; i++)
        cout << endl;

    for(int i = 0; i < 15; i++) {
        cout << TABS;

        if(i < boards.size()) {
            cout << "[";

            // výběr poslední hry

            cout << abc[i];

            cout << "] ";

            cout << boards.at(i)->getName();

            cout << " ";

            if(i == focus)
                cout << ACTUAL;


        }

        cout << endl;
    }
}

void print_game_control(bool err) {
    cout << endl;
    cout << "LÍZNOUT KARTU              [T]" << endl;
    cout << "PŘEJÍT K VÝBĚRU KARTY      [L]" << endl;
    cout << endl;
}

void print_look_for(bool err) {
    cout << endl;
    cout << "Zadejte vámi vybranou kartu (vybere se celý stack pod ní)." << endl;
    cout << "Ve tvaru:          [2-10,J,Q,K,A][H,D,S,C]" << endl;
    cout << endl;
}

void print_choosen(Card *c) {
    cout << endl;
    cout << "Zadejte vámi vybranou kartu (vybere se celý stack pod ní)." << endl;
    cout << "Ve tvaru:          [2-10,J,Q,K,A][H,D,S,C]" << endl;
    cout << endl;
    cout << "Zvolená karta: " << c->toString() << endl;
}


/**
*   Tiskne TUI
*/
void print_board(vector<Board*> boards, int state, int focus) {

    focus = focus - 1; // úprava pro přístup do pole
    Board *board = boards.at(focus);
    int score = board->getScore();
    int moves = board->getMoves();

    Deck *deck = board->getDeck();
    Deck *grave = board->getGrave();

    vector<Stack*> stacks;
    vector<Deck*> mags;
    vector<Foundation*> finals;
    vector<int> counter;

    for(int i = 0; i < 7; i++){
        stacks.push_back(board->getStack(i));
    }

    for(int i = 0; i < 7; i++){
        mags.push_back(board->getMagazine(i));
    }

    for(int i = 0; i < 4; i++){
        finals.push_back(board->getFinal(i));
    }

    // inicializace counteru
    for(int i = 0; i < 7; i++)
        counter.push_back(0);

    //  "vyčištění" okna terminálu
    cout << CLEAR; //cisteni

    //  příprava rozhraní
    print_menu(state);
    cout << "Počet karet v balíku: ";
    cout << to_string(deck->size());
    if(deck->size() < 10)
        cout << " ";
    cout << "                  score: ";
    cout << to_string(score);

    if(score > 9)
        cout << "   ";

    else if(score > 99)
        cout << "  ";

    else if(score > 999)
        cout << " ";

    else
        cout << "    " ;

    cout << "tahy: ";
    cout << to_string(moves);
    cout << endl;
    cout << "Odkládací balíček: ";
    cout << grave->onTop().toString();
    cout << "     [L]" << endl;
    cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
    cout << "   [A]      [B]      [C]      [D]      [E]      [F]      [G]   ";

    //  převedení "zásobníků" a "stacků" do stringu
    for(int o = 0; o < 7; o++) {
        cout << endl;
        for(int i = 0; i < 7; i++) {
            cout << "   ";

            //  tisknuti "rubu karet"
            if(mags.at(i)->size() > o) {
                cout << " # ";
            }

            //  tisknuti karet ve stacích "lícem"
            else if(stacks.at(i)->size() > counter.at(i)) {

                // tiskne kartu ze stacku i na pozici uloženou v counter(i)
                Stack *ptr_stack = stacks.at(i);
                int position = counter.at(i);

                cout << ptr_stack->get(position).toString();
                //cout << board->stackGet(counter.at(i), i).toString();
                counter.at(i) += 1;
            }
            else {
                cout << "   ";
            }
            cout << "   ";
        }
    }

    // převedení finálních balíků

    cout << endl << endl;
    cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
    cout << "Finální balíky: ";

    Foundation *ptr_final;
    for(int i = 0; i < 4; i++) {

        ptr_final = finals.at(i);

        cout << "   ";
        if(ptr_final->empty()) {
            switch(ptr_final->myColor()) {
                case DIAMONDS:
                    cout << DIAMOND_F;
                    break;
                case HEARDS:
                    cout << HEART_F;
                    break;
                case CLUBS:
                    cout << CLUB_F;
                    break;
                case SPADES:
                    cout << SPADE_F;
                    break;
            }
        }
        else {
            cout << ptr_final->onTop().toString();
        }
        cout << "   ";
    }
    cout << endl <<"                  [W]    [X]    [Y]    [Z]" << endl;
    cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;



}

// telo hry
int main(int argc, char const *argv[]) {
    vector <Board*> boards;
    string input;
    int focus = 0; // jakou hru si přejeme hrát
    int state = MENU;
    bool err = false; //kontorluje zda-li v minulém cyklu nezadal uživatel špatný vstup

    // telo programu
    while(true) {

        // Nachazíme se v menu bez rozehrané hry
        if(state == MENU) {
            print_menu(state);
            print_ending(err);
            cin >> input;
            cout << endl;

            // vyhodnocení vstupu
            // nová hra [N, n]
            if(input == "N" || input == "n") {
                state = INGAME;
                boards.push_back(new Board(boards.size()));
                focus = boards.size(); // změna focusu hry na nově vytvořenou hru
                err = false;

            }

            // nacist uloženu [S, s]
            else if(input == "S" || input == "s") {
                err = false;
            }

            // ukončit program [X, x]
            else if(input == "X" || input == "x") {
                cout << CLEAR;
                return 0;
            }

            // zadání neplatného znaku
            else {
                state = MENU;
                err = true;
            }
        }

        // Nacházíme se v menu s rozehranou hrou
        else if(state == MENU_WITH_GAME) {
            print_menu(state);
            print_ending(err);
            cin >> input;
            cout << endl;

            // vyhodnocení vstupu
            // nová hra [N, n]
            if(input == "N" || input == "n") {
                state = INGAME;
                boards.push_back(new Board(boards.size()));
                focus = boards.size(); // změna focusu hry na nově vytvořenou hru
                err = false;

            }

            // nacist uloženu [S, s]
            else if(input == "S" || input == "s") {
                err = false;
            }

            // vrátit se do hry [Z, z]
            else if(input == "Z" || input == "z") {
                state = INGAME;
                err = false;
            }

            // ukončit program [X, x]
            else if(input == "X" || input == "x") {
                cout << CLEAR;
                return 0;
            }

            // zadání neplatného znaku
            else {
                state = MENU;
                err = true;
            }

        }

        // Nacházíme se ve hře
        else if(state == INGAME) {
            print_board(boards, state, focus);
            print_game_control(err);
            print_ending(err);
            cin >> input;
            cout << endl;

            // vyhodnocení vstupu
            // undo [U, u]
            if(input == "U" || input == "u") {
                state = INGAME;

                //TODO undo
                err = false;

            }

            // zmenit hru [Z, z]
            else if(input == "Z" || input == "z") {

                state = CHANGE;
                err = false;

            }

            // Ulozit [S, s]
            else if(input == "S" || input == "s") {

                //TODO uložit hru
                err = false;
            }

            // Vrátit se do menu [X, x]
            else if(input == "X" || input == "x") {

                //TODO uložit hru
                state = MENU_WITH_GAME;
                err = false;
            }

            // Líznout kartu [T, t]
            else if(input == "T" || input == "t") {

                boards.at(focus - 1)->draw();
                err = false;
            }

            // přesun do fáze výběru karty [L, l]
            else if(input == "L" || input == "l") {

                state = GAME_CARD;
                err = false;
            }

            // zadání neplatného znaku
            else {
                state = INGAME;
                err = true;
            }

        }

        // TODO upravit vstupy
        // Nacházíme se ve hře -> ve výběru karty
        else if(state == GAME_CARD) {
            int number;
            string helper;
            color card_color;


            print_board(boards, state, focus);
            print_look_for(err);
            print_ending(err);
            cin >> input;
            cout << endl;



            // Zpracování vstupu (2 nebo 3 místný (jinek error))
            if(input.size() == 3) {
                helper = input.substr(0,2);

                if(has_only_digits(helper)) {
                    number = stoi(input.substr(0,2));
                    helper = input.substr(2,1);

                    err = false;
                    if(helper == "H")
                        card_color = HEARDS;
                    else if(helper == "D")
                        card_color = DIAMONDS;
                    else if(helper == "S")
                        card_color = SPADES;
                    else if(helper == "C")
                        card_color = CLUBS;
                    else {
                        err = true;
                    }

                }
            }
            else if(input.size() == 2) {
                helper = input.substr(0,1);

                if(has_only_digits(helper)) {
                    number = stoi(input.substr(0,1));
                    helper = input.substr(1,1);

                    err = false;
                    if(helper == "H")
                        card_color = HEARDS;
                    else if(helper == "D")
                        card_color = DIAMONDS;
                    else if(helper == "S")
                        card_color = SPADES;
                    else if(helper == "C")
                        card_color = CLUBS;
                    else {
                        err = true;
                    }
                }
                else if(helper == "J")
                    number = 11;
                else if(helper == "Q")
                    number = 12;
                else if(helper == "K")
                    number = 13;
                else if(helper == "A")
                    number = 1;
                else {
                    err = true;
                }

                if(helper == "J" ||
                   helper == "Q" ||
                   helper == "K" ||
                   helper == "A" ) {

                       helper = input.substr(1,1);

                       err = false;
                       if(helper == "H")
                           card_color = HEARDS;
                       else if(helper == "D")
                           card_color = DIAMONDS;
                       else if(helper == "S")
                           card_color = SPADES;
                       else if(helper == "C")
                           card_color = CLUBS;
                       else {
                           err = true;
                       }

                   }


            }
            else {
                err = true;
            }

            //TODO vymazat !err
            if(!err) {
                bool found = false;
                Card *c = new Card(number, card_color);
                if(c->value() == 0) {
                    err = true;
                    continue;
                }

                // zadana karta se nachazi na odhazovacim balicku
                if(c->equals(boards.at(focus - 1)->getGrave()->onTop())) {
                    found = true;
                    //TODO vyjmuti karty

                    continue;
                }

                // hledani karty ve stacích
                if(!found) {
                    for(int i = 0; i < 7; i++) {
                        if(boards.at(focus - 1)->getStack(i)->contains(c)) {
                            found = true;
                            // TODO vyjmuti stacku
                        }
                    }
                }

                if(!found) {
                    //TODO error
                    err = true;
                    continue;
                }








                print_board(boards, state, focus);
                print_choosen(c);
                print_ending(err);

            }



        }

        // Nacházíme se v menu pro změnu rozehraných her
        else if(state == CHANGE) {

            string abc = "ABCDEFGH"; //pomocná abeceda
            string low_abc = "abcdefgh"; //pomocná abeceda
            string helper, helper_low;

            print_menu(state);
            print_change(boards, focus);
            print_ending(err);

            cin >> input;
            cout << endl;

            // vyhodnocení vstupu
            // Zpět do menu [X, x]
            if(input == "X" || input == "x") {
                state = MENU_WITH_GAME;
                err = false;
            }
            else {
                for(int i = 0; i < boards.size(); i++) {
                    helper = abc[i];
                    helper_low = low_abc[i];

                    if(input == helper || input == helper_low) {

                        state = INGAME;
                        focus = i + 1;
                        err = false;
                        break;

                    }

                    state = CHANGE;
                    err = true;
                }
            }



        }




    }



    //cout << board_1 -> toString();

}
