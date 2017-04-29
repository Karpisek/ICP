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

void clear(bool ending){
    cout << CLEAR; //cisteni
    if(!ending)
        cout << "                     Solitaire 2017 - ICP";
    cout << endl << endl;
    cout << endl << endl;
}

/**
*   Tiskne TUI
*/
void print_board(Board *board) {
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
    cout << "Počet karet v balíku: ";
    cout << to_string(deck->size()) << endl;
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

    Board *board_1 = new Board();
    int input;
    //board_1 -> draw();
    //cout << board_1 -> getCard(0, 1).toString();

    // telo programu
    while(true) {
        input = 0;
        print_board(board_1);
        cin >> input;
        if(input)
            board_1->draw();
        else{
            cout <<"pis";
            cin >> input;
            cout << to_string(board_1->take(board_1->getStack(input)));
            print_board(board_1);
        }


    }



    //cout << board_1 -> toString();

}
