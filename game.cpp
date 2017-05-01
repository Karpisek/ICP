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

    else if(state == NAME)
        cout << "               Zadejte jmeno nove hry                        ";

    else if(state == LOAD)
        cout << "                Zvolte uloženou hru                          ";

    else
        cout << "UNDO [U] | ZMENIT HRU [Z] | ULOZIT [S] |           | MENU [X]";

    cout << endl;
    cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
    cout << endl;

    if (state == MENU || state == MENU_WITH_GAME || state == NAME) {
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
    cout << endl;
    cout << "Zadejte vámi vybranou kartu (vybere se celý stack pod ní)." << endl;
    cout << "Ve tvaru:          [2-10,J,Q,K,A][H,D,S,C]" << endl;
    cout << "                                  "<<HEART_F<<" "<<DIAMOND_F<<" "<<SPADE_F<<" "<<CLUB_F<< endl;
}

void print_choosen(Card *c) {
    cout << endl;
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
    for(int o = 0; o < 13; o++) {
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

        cout << "  ";
        if(ptr_final->empty()) {
            cout << " ";
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
            cout << " ";
        }
        else {
            cout << ptr_final->onTop().toString();
        }
        cout << "  ";
    }
    cout << endl <<"                  [W]    [R]    [Y]    [Q]" << endl;
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

                state = NAME;
                err = false;

            }

            // nacist uloženu [S, s]
            else if(input == "S" || input == "s") {

                state = LOAD;
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
                state = NAME;
                err = false;

            }

            // nacist uloženu [S, s]
            else if(input == "S" || input == "s") {
                state = LOAD;
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

                boards.at(focus - 1)->undo();
                err = false;

            }

            // zmenit hru [Z, z]
            else if(input == "Z" || input == "z") {

                state = CHANGE;
                err = false;

            }

            // Ulozit [S, s]
            else if(input == "S" || input == "s") {

                err = !boards.at(focus - 1)->saveGame();

            }

            // Vrátit se do menu [X, x]
            else if(input == "X" || input == "x") {

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
            string abc = "ABCDEFGH"; //pomocna abeceda
            string helper;
            color card_color;


            print_board(boards, state, focus);
            print_look_for(err);
            print_ending(err);
            cin >> input;
            cout << endl;



            // Zpracování vstupu (2 nebo 3 místný (jinek error))
            if(input == "U" || input == "u") {
                state = INGAME;

                boards.at(focus - 1)->undo();
                err = false;
                continue;

            }

            // zmenit hru [Z, z]
            else if(input == "Z" || input == "z") {

                state = CHANGE;
                err = false;
                continue;

            }

            // Ulozit [S, s]
            else if(input == "S" || input == "s") {

                err = !boards.at(focus - 1)->saveGame();
                continue;
            }

            // Vrátit se do menu [X, x]
            else if(input == "X" || input == "x") {

                state = INGAME;
                err = false;
                continue;
            }

            else if(input.size() == 3) {
                helper = input.substr(0,2);

                if(has_only_digits(helper)) {
                    number = stoi(input.substr(0,2));
                    helper = input.substr(2,1);

                    err = false;
                    if(helper == "H" || helper == "h")
                        card_color = HEARDS;
                    else if(helper == "D" || helper == "d")
                        card_color = DIAMONDS;
                    else if(helper == "S" || helper == "s")
                        card_color = SPADES;
                    else if(helper == "C" || helper == "c")
                        card_color = CLUBS;
                    else {
                        err = true;
                    }

                }
            }
            else if(input.size() == 2) {
                helper = input.substr(0,1);

                // Zadano ciselne
                if(has_only_digits(helper)) {
                    number = stoi(input.substr(0,1));
                    helper = input.substr(1,1);

                    err = false;
                    if(helper == "H" || helper == "h")
                        card_color = HEARDS;
                    else if(helper == "D" || helper == "d")
                        card_color = DIAMONDS;
                    else if(helper == "S" || helper == "s")
                        card_color = SPADES;
                    else if(helper == "C" || helper == "c")
                        card_color = CLUBS;
                    else {
                        err = true;
                    }
                }
                else if(helper == "J" || helper == "j")
                    number = 11;
                else if(helper == "Q" || helper == "q")
                    number = 12;
                else if(helper == "K" || helper == "k")
                    number = 13;
                else if(helper == "A" || helper == "a")
                    number = 1;
                else {
                    err = true;
                }

                if(helper == "J" || helper == "j" ||
                   helper == "Q" || helper == "q" ||
                   helper == "K" || helper == "k" ||
                   helper == "A" || helper == "a" ) {

                       helper = input.substr(1,1);

                       err = false;
                       if(helper == "H" || helper == "h")
                           card_color = HEARDS;
                       else if(helper == "D" || helper == "d")
                           card_color = DIAMONDS;
                       else if(helper == "S" || helper == "s")
                           card_color = SPADES;
                       else if(helper == "C" || helper == "c")
                           card_color = CLUBS;
                       else {
                           err = true;
                       }

                   }


            }
            else {
                err = true;
                continue;
            }

            //TODO vymazat !err
            if(!err) {
                bool found = false;
                Card *c = new Card(number, card_color);

                // zadaná karta je neplatná
                if(c->value() == 0) {
                    err = true;
                    continue;
                }

                // zadana karta se nachazi na odhazovacim balicku
                if(c->equals(boards.at(focus - 1)->getGrave()->onTop())) {
                    found = true;

                    // předání informace o vybrání karty
                    print_board(boards, state, focus);
                    cout << endl;
                    cout << "Zvolená karta z lízacího balíčku: ";
                    cout << c->toString() << endl;
                    cout << "Zvolte stack či finální balík kam si přejete kartu vložit (Písmeno v [ ])";
                    cout << endl;
                    print_ending(err);

                    cin >> input;

                    //Vyhodnocení vstupu
                    // undo [U, u]
                    if(input == "U" || input == "u") {
                        state = INGAME;

                        boards.at(focus - 1)->undo();
                        err = false;
                        continue;

                    }

                    // zmenit hru [Z, z]
                    else if(input == "Z" || input == "z") {

                        state = CHANGE;
                        err = false;
                        continue;

                    }

                    // Ulozit [S, s]
                    else if(input == "S" || input == "s") {

                        err = !boards.at(focus - 1)->saveGame();
                    }

                    // Vrátit se do menu [X, x]
                    else if(input == "X" || input == "x") {

                        state = INGAME;
                        err = false;
                        continue;
                    }

                    // Vložit na stack [A, a]
                    else if(input == "A" || input == "a") {

                        // Vytvoření ukazatele na zvolený balíček a předaní
                        // jej jako parametru pro metodu board.take()
                        // která vezme kartu z hrobu a zahraje na zvolený balíček
                        Stack *choosen = boards.at(focus - 1)->getStack(0);
                        if(boards.at(focus - 1)->take(choosen)) {
                            state = INGAME;
                            err = false;
                            continue;
                        }
                        else {
                            err = true;
                            continue;
                        }
                    }

                    // Vložit na stack [B, b]
                    else if(input == "B" || input == "b") {

                        // Vytvoření ukazatele na zvolený balíček a předaní
                        // jej jako parametru pro metodu board.take()
                        // která vezme kartu z hrobu a zahraje na zvolený balíček
                        Stack *choosen = boards.at(focus - 1)->getStack(1);
                        if(boards.at(focus - 1)->take(choosen)) {
                            state = INGAME;
                            err = false;
                            continue;
                        }
                        else {
                            err = true;
                            continue;
                        }
                    }

                    // Vložit na stack [C, c]
                    else if(input == "C" || input == "c") {

                        // Vytvoření ukazatele na zvolený balíček a předaní
                        // jej jako parametru pro metodu board.take()
                        // která vezme kartu z hrobu a zahraje na zvolený balíček
                        Stack *choosen = boards.at(focus - 1)->getStack(2);
                        if(boards.at(focus - 1)->take(choosen)) {
                            state = INGAME;
                            err = false;
                            continue;
                        }
                        else {
                            err = true;
                            continue;
                        }
                    }

                    // Vložit na stack [D, d]
                    else if(input == "D" || input == "d") {

                        // Vytvoření ukazatele na zvolený balíček a předaní
                        // jej jako parametru pro metodu board.take()
                        // která vezme kartu z hrobu a zahraje na zvolený balíček
                        Stack *choosen = boards.at(focus - 1)->getStack(3);
                        if(boards.at(focus - 1)->take(choosen)) {
                            state = INGAME;
                            err = false;
                            continue;
                        }
                        else {
                            err = true;
                            continue;
                        }
                    }

                    // Vložit na stack [E, e]
                    else if(input == "E" || input == "e") {

                        // Vytvoření ukazatele na zvolený balíček a předaní
                        // jej jako parametru pro metodu board.take()
                        // která vezme kartu z hrobu a zahraje na zvolený balíček
                        Stack *choosen = boards.at(focus - 1)->getStack(4);
                        if(boards.at(focus - 1)->take(choosen)) {
                            state = INGAME;
                            err = false;
                            continue;
                        }
                        else {
                            err = true;
                            continue;
                        }
                    }

                    // Vložit na stack [F, f]
                    else if(input == "F" || input == "f") {

                        // Vytvoření ukazatele na zvolený balíček a předaní
                        // jej jako parametru pro metodu board.take()
                        // která vezme kartu z hrobu a zahraje na zvolený balíček
                        Stack *choosen = boards.at(focus - 1)->getStack(5);
                        if(boards.at(focus - 1)->take(choosen)) {
                            state = INGAME;
                            err = false;
                            continue;
                        }
                        else {
                            err = true;
                            continue;
                        }
                    }

                    // Vložit na stack [G, g]
                    else if(input == "G" || input == "g") {

                        // Vytvoření ukazatele na zvolený balíček a předaní
                        // jej jako parametru pro metodu board.take()
                        // která vezme kartu z hrobu a zahraje na zvolený balíček
                        Stack *choosen = boards.at(focus - 1)->getStack(6);
                        if(boards.at(focus - 1)->take(choosen)) {
                            state = INGAME;
                            err = false;
                            continue;
                        }
                        else {
                            err = true;
                            continue;
                        }
                    }

                    // Vložit na final [W, w]
                    else if(input == "W" || input == "W") {

                        // Vytvoření ukazatele na zvolený balíček a předaní
                        // jej jako parametru pro metodu board.take()
                        // která vezme kartu z hrobu a zahraje na zvolený balíček
                        Foundation *choosen_final = boards.at(focus - 1)->getFinal(0);
                        if(boards.at(focus - 1)->take(choosen_final)) {
                            state = INGAME;
                            err = false;
                            continue;
                        }
                        else {
                            err = true;
                            continue;
                        }
                    }

                    // Vložit na final [X, X]
                    else if(input == "R" || input == "r") {

                        // Vytvoření ukazatele na zvolený balíček a předaní
                        // jej jako parametru pro metodu board.take()
                        // která vezme kartu z hrobu a zahraje na zvolený balíček
                        Foundation *choosen_final = boards.at(focus - 1)->getFinal(1);
                        if(boards.at(focus - 1)->take(choosen_final)) {
                            state = INGAME;
                            err = false;
                            continue;
                        }
                        else {
                            err = true;
                            continue;
                        }
                    }

                    // Vložit na final [Y, Y]
                    else if(input == "Y" || input == "y") {

                        // Vytvoření ukazatele na zvolený balíček a předaní
                        // jej jako parametru pro metodu board.take()
                        // která vezme kartu z hrobu a zahraje na zvolený balíček
                        Foundation *choosen_final = boards.at(focus - 1)->getFinal(2);
                        if(boards.at(focus - 1)->take(choosen_final)) {
                            state = INGAME;
                            err = false;
                            continue;
                        }
                        else {
                            err = true;
                            continue;
                        }
                    }

                    // Vložit na final [Q, a]
                    else if(input == "Q" || input == "q") {

                        // Vytvoření ukazatele na zvolený balíček a předaní
                        // jej jako parametru pro metodu board.take()
                        // která vezme kartu z hrobu a zahraje na zvolený balíček
                        Foundation *choosen_final = boards.at(focus - 1)->getFinal(3);
                        if(boards.at(focus - 1)->take(choosen_final)) {
                            state = INGAME;
                            err = false;
                            continue;
                        }
                        else {
                            err = true;
                            continue;
                        }
                    }

                    // Vližení jiného znaku
                    else {
                        state = GAME_CARD;
                        err = true;
                        continue;
                    }

                }

                // hledani karty ve stacích
                if(!found) {
                    for(int i = 0; i < 7; i++) {
                        // nalezení karty ve stacích
                        if(boards.at(focus - 1)->getStack(i)->contains(c)) {
                            found = true;

                            //ověření jestli je karta na vrcholu stacku
                            if(true) {

                                // předání informace o vybrání karty
                                print_board(boards, state, focus);
                                cout << endl;
                                cout << "Zvolená karta: ";
                                cout << c->toString() << endl;
                                cout << "Ze stacku: ";
                                cout << abc[i] << endl;
                                cout << "Zvolte stack či finální balík kam si přejete stack vložit (Písmeno v [ ])";
                                cout << endl;
                                print_ending(err);

                                cin >> input;

                                //Vyhodnocení vstupu
                                // undo [U, u]
                                if(input == "U" || input == "u") {
                                    state = INGAME;

                                    boards.at(focus - 1)->undo();
                                    err = false;
                                }

                                // zmenit hru [Z, z]
                                else if(input == "Z" || input == "z") {

                                    state = CHANGE;
                                    err = false;
                                }

                                // Ulozit [S, s]
                                else if(input == "S" || input == "s") {

                                    err = !boards.at(focus - 1)->saveGame();
                                }

                                // Vrátit se do menu [X, x]
                                else if(input == "X" || input == "x") {

                                    state = INGAME;
                                    err = false;
                                }

                                // Vložit na stack [A, a]
                                else if(input == "A" || input == "a") {

                                    // Vytvoření ukazatele na zvolený balíček a předaní
                                    // vyjmutí zvoleného stacku a pokus vložit jej na takový balíček
                                    Deck *ptr_magazine =  boards.at(focus - 1)->getMagazine(i);
                                    Stack *ptr_stack_from = boards.at(focus - 1)->getStack(i);
                                    Stack *ptr_stack_to = boards.at(focus -1)->getStack(0);

                                    if(boards.at(focus - 1)->StackToStack(c, ptr_stack_to, ptr_stack_from, ptr_magazine)) {
                                        state = INGAME;
                                        err = false;
                                    }
                                    else {
                                        err = true;
                                        state = GAME_CARD;
                                    }
                                }

                                // Vložit na stack [B, b]
                                else if(input == "B" || input == "b") {

                                    // Vytvoření ukazatele na zvolený balíček a předaní
                                    // vyjmutí zvoleného stacku a pokus vložit jej na takový balíček
                                    Deck *ptr_magazine =  boards.at(focus - 1)->getMagazine(i);
                                    Stack *ptr_stack_from = boards.at(focus - 1)->getStack(i);
                                    Stack *ptr_stack_to = boards.at(focus -1)->getStack(1);

                                    if(boards.at(focus - 1)->StackToStack(c, ptr_stack_to, ptr_stack_from, ptr_magazine)) {
                                        state = INGAME;
                                        err = false;
                                    }
                                    else {
                                        err = true;
                                        state = GAME_CARD;
                                    }
                                }

                                // Vložit na stack [C, c]
                                else if(input == "C" || input == "c") {

                                    // Vytvoření ukazatele na zvolený balíček a předaní
                                    // vyjmutí zvoleného stacku a pokus vložit jej na takový balíček
                                    Deck *ptr_magazine =  boards.at(focus - 1)->getMagazine(i);
                                    Stack *ptr_stack_from = boards.at(focus - 1)->getStack(i);
                                    Stack *ptr_stack_to = boards.at(focus -1)->getStack(2);

                                    if(boards.at(focus - 1)->StackToStack(c, ptr_stack_to, ptr_stack_from, ptr_magazine)) {
                                        state = INGAME;
                                        err = false;
                                    }
                                    else {
                                        err = true;
                                        state = GAME_CARD;
                                    }
                                }

                                // Vložit na stack [D, d]
                                else if(input == "D" || input == "d") {

                                    // Vytvoření ukazatele na zvolený balíček a předaní
                                    // vyjmutí zvoleného stacku a pokus vložit jej na takový balíček
                                    Deck *ptr_magazine =  boards.at(focus - 1)->getMagazine(i);
                                    Stack *ptr_stack_from = boards.at(focus - 1)->getStack(i);
                                    Stack *ptr_stack_to = boards.at(focus -1)->getStack(3);

                                    if(boards.at(focus - 1)->StackToStack(c, ptr_stack_to, ptr_stack_from, ptr_magazine)) {
                                        state = INGAME;
                                        err = false;
                                    }
                                    else {
                                        err = true;
                                        state = GAME_CARD;
                                    }
                                }

                                // Vložit na stack [E, e]
                                else if(input == "E" || input == "e") {

                                    // Vytvoření ukazatele na zvolený balíček a předaní
                                    // vyjmutí zvoleného stacku a pokus vložit jej na takový balíček
                                    Deck *ptr_magazine =  boards.at(focus - 1)->getMagazine(i);
                                    Stack *ptr_stack_from = boards.at(focus - 1)->getStack(i);
                                    Stack *ptr_stack_to = boards.at(focus -1)->getStack(4);

                                    if(boards.at(focus - 1)->StackToStack(c, ptr_stack_to, ptr_stack_from, ptr_magazine)) {
                                        state = INGAME;
                                        err = false;
                                    }
                                    else {
                                        err = true;
                                        state = GAME_CARD;
                                    }
                                }

                                // Vložit na stack [F, f]
                                else if(input == "F" || input == "f") {

                                    // Vytvoření ukazatele na zvolený balíček a předaní
                                    // vyjmutí zvoleného stacku a pokus vložit jej na takový balíček
                                    Deck *ptr_magazine =  boards.at(focus - 1)->getMagazine(i);
                                    Stack *ptr_stack_from = boards.at(focus - 1)->getStack(i);
                                    Stack *ptr_stack_to = boards.at(focus - 1)->getStack(5);

                                    if(boards.at(focus - 1)->StackToStack(c, ptr_stack_to, ptr_stack_from, ptr_magazine)) {
                                        state = INGAME;
                                        err = false;
                                    }
                                    else {
                                        err = true;
                                        state = GAME_CARD;
                                    }
                                }

                                // Vložit na stack [G, g]
                                else if(input == "G" || input == "g") {

                                    // Vytvoření ukazatele na zvolený balíček a předaní
                                    // vyjmutí zvoleného stacku a pokus vložit jej na takový balíček
                                    Deck *ptr_magazine =  boards.at(focus - 1)->getMagazine(i);
                                    Stack *ptr_stack_from = boards.at(focus - 1)->getStack(i);
                                    Stack *ptr_stack_to = boards.at(focus -1)->getStack(6);

                                    if(boards.at(focus - 1)->StackToStack(c, ptr_stack_to, ptr_stack_from, ptr_magazine)) {
                                        state = INGAME;
                                        err = false;
                                    }
                                    else {
                                        err = true;
                                        state = GAME_CARD;
                                    }
                                }

                                // Vložit na stack [W, w]
                                else if(input == "W" || input == "w") {

                                    // Vytvoření ukazatele na zvolený balíček a předaní
                                    // vyjmutí zvoleného stacku a pokus vložit jej na takový balíček
                                    Deck *ptr_magazine =  boards.at(focus - 1)->getMagazine(i);
                                    Stack *ptr_stack_from = boards.at(focus - 1)->getStack(i);
                                    Foundation *ptr_final = boards.at(focus -1)->getFinal(0);

                                    if(boards.at(focus - 1)->StackToFinal(c, ptr_final, ptr_stack_from, ptr_magazine)) {
                                        state = INGAME;
                                        err = false;
                                    }
                                    else {
                                        err = true;
                                        state = GAME_CARD;
                                    }
                                }

                                // Vložit na final [X, x]
                                else if(input == "R" || input == "r") {

                                    // Vytvoření ukazatele na zvolený balíček a předaní
                                    // vyjmutí zvoleného stacku a pokus vložit jej na takový balíček
                                    Deck *ptr_magazine =  boards.at(focus - 1)->getMagazine(i);
                                    Stack *ptr_stack_from = boards.at(focus - 1)->getStack(i);
                                    Foundation *ptr_final = boards.at(focus -1)->getFinal(1);

                                    if(boards.at(focus - 1)->StackToFinal(c, ptr_final, ptr_stack_from, ptr_magazine)) {
                                        state = INGAME;
                                        err = false;
                                    }
                                    else {
                                        err = true;
                                        state = GAME_CARD;
                                    }
                                }

                                // Vložit na final [Y, y]
                                else if(input == "Y" || input == "y") {

                                    // Vytvoření ukazatele na zvolený balíček a předaní
                                    // vyjmutí zvoleného stacku a pokus vložit jej na takový balíček
                                    Deck *ptr_magazine =  boards.at(focus - 1)->getMagazine(i);
                                    Stack *ptr_stack_from = boards.at(focus - 1)->getStack(i);
                                    Foundation *ptr_final = boards.at(focus - 1)->getFinal(2);

                                    if(boards.at(focus - 1)->StackToFinal(c, ptr_final, ptr_stack_from, ptr_magazine)) {
                                        state = INGAME;
                                        err = false;
                                    }
                                    else {
                                        err = true;
                                        state = GAME_CARD;
                                    }
                                }

                                // Vložit na stack [Q, q]
                                else if(input == "Q" || input == "q") {

                                    // Vytvoření ukazatele na zvolený balíček a předaní
                                    // vyjmutí zvoleného stacku a pokus vložit jej na takový balíček
                                    Deck *ptr_magazine =  boards.at(focus - 1)->getMagazine(i);
                                    Stack *ptr_stack_from = boards.at(focus - 1)->getStack(i);
                                    Foundation *ptr_final = boards.at(focus - 1)->getFinal(3);

                                    if(boards.at(focus - 1)->StackToFinal(c, ptr_final, ptr_stack_from, ptr_magazine)) {
                                        state = INGAME;
                                        err = false;
                                    }
                                    else {
                                        err = true;
                                        state = GAME_CARD;
                                    }
                                }

                                // Vližení jiného znaku
                                else {
                                    state = GAME_CARD;
                                    err = true;
                                    continue;
                                }



                            }

                            break;
                        }
                    }

                }

                if(!found) {

                    err = true;
                    continue;
                }

                state = INGAME;
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

        // nacházime se při výběru jména hry
        else if(state == NAME) {
            print_menu(state);
            print_ending(err);
            cin >> input;
            cout << endl;

            state = INGAME;
            boards.push_back(new Board(input));
            focus = boards.size(); // změna focusu hry na nově vytvořenou hru
            err = false;
        }

        // nacházime se při výběru hry k nahrání
        else if(state == LOAD) {
            print_menu(state);
            print_ending(err);
            cin >> input;
            cout << endl;

            state = INGAME;
            boards.push_back(new Board(input, true));
            focus = boards.size(); // změna focusu hry na nově vytvořenou hru
            err = false;
        }

    }



    //cout << board_1 -> toString();

}
