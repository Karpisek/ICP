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

int menu(bool err) {

    string input;

    cout << "NOVÁ HRA            [N]" << endl;
    cout << "NAHRÁT ULOŽENOU HRU [U]" << endl;
    cout << "UKONČIT PROGRAM     [X]" << endl;
    cout << endl << endl;
    if(err) {
        cout << "                  \033[5;31mZadejte prosím platný znak\033[0m\n";
        cout << endl;
    }
    else {
        cout << endl << endl;
    }
    cout << "Vaše volba: ";

    cin >> input;
    if (input == "N" || input == "n")
        return 0;
    if (input == "U" || input == "u")
        return 1;
    if (input == "X" || input == "x")
        return 2;
    return -1;
}

int in_game(bool err) {
    string input;
    cout << "Jakou akci si přejete provést: \n";
    cout << endl;
    cout << "LÍZNOUT KARTU          [L]" << endl;
    cout << "PŘESUNOUT KARTU/STACK  [P]" << endl;
    cout << "VRÁTIT SE DO MENU      [X]" << endl;
    cout << endl;
    if(err) {
        cout << "                  \033[5;31mZadejte prosím platný znak\033[0m\n";
        cout << endl;
    }
    else {
        cout << endl << endl;
    }
    cout << "Vaše volba: ";
    cin >> input;

    if (input == "L" || input == "l")
        return 0;
    if (input == "P" || input == "p")
        return 1;
    if (input == "X" || input == "x")
        return 2;
    return -1;
}

int card_move(Board *board, bool err) {
    clear(false);
    cout << board->toString();

    string input;

    cout << "Zvolte výchozí pozici (písmeno v hranatých závorkách): \n";
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl << endl;
    if(err) {
        cout << "                  \033[5;31mZadejte prosím platný znak\033[0m\n";
        cout << endl;
    }
    else {
        cout << endl << endl;
    }
    cout << "Vaše volba: ";

    cin >> input;

    //karta z odkládacího balíčku
    if (input == "L" || input == "l") {

        //kontrola zda-li není odhazovací balíček prázdný
        if(board->emptyGrave()) {
            clear(false);
            cout << board->toString();

            cout << endl;
            cout << endl;
            cout << "\033[5;31mOdhazovací balíček je prázný, proveďte prosím jinou akci\033[0m\n";
            cout << endl;
            cout << endl << endl;
            if(err) {
                cout << "                  \033[5;31mZadejte prosím platný znak\033[0m\n";
                cout << endl;
            }
            else {
                cout << endl << endl;
            }
            cout << endl;

            usleep(SLEEP_TIME);
            return -1;
        }
        else {
            clear(false);
            cout << board->toString();

            cout << "Zvolte cílovou pozici (písmeno v hranatých závorkách): \n";
            cout << endl;
            cout << "Zvolená karta: " << board->topGrave().toString();
            cout << endl;
            cout << endl << endl;
            if(err) {
                cout << "                  \033[5;31mZadejte prosím platný znak\033[0m\n";
                cout << endl;
            }
            else {
                cout << endl << endl;
            }
            cout << "Vaše volba: ";
            cin >> input;


            // zvolení stacku jako cílovou destinaci
            if (input == "A" || input == "a" ||
                input == "B" || input == "b" ||
                input == "C" || input == "c" ||
                input == "D" || input == "d" ||
                input == "E" || input == "e" ||
                input == "F" || input == "f" ||
                input == "G" || input == "g" ) {



            }
        }



    }

    // vybrání stacku
    if (input == "A" || input == "a" ||
        input == "B" || input == "b" ||
        input == "C" || input == "c" ||
        input == "D" || input == "d" ||
        input == "E" || input == "e" ||
        input == "F" || input == "f" ||
        input == "G" || input == "g" ) {




    }
    return -1;




}

void start_game() {

    Board *board_1 = new Board();
    bool err = false;
    while(true) {
        clear(false);
        cout << board_1->toString();
        switch (in_game(err)) {
            // chybna volba
            case -1:
                err = true;
                continue;

            // líznout kartu
            case 0:
                err = false;
                board_1->draw();
                continue;

            // přesunout kartu
            case 1:
                card_move(board_1, false);




                break;

            case 2:
                clear(false);
                return;
        };

    }
}

// telo hry
int main(int argc, char const *argv[]) {
    bool err;

    while(true) {
        clear(false);

        //nejsme ve hre -> zobrazit menu
        switch (menu(err)) {
            // chybna volba
            case -1:
                err = true;
                continue;

            //nova hra
            case 0:
                //zanoreni se do hry
                start_game();
                err = false;
                break;

            //nacist ulozenou
            case 1:
                // TODO
                break;
            //ukoncit program
            case 2:
                clear(true);
                return 0;
        }

        // jsme ve hře -> zanořit


    }
}
