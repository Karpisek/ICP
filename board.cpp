/**
* @file board.cpp
* @author Miroslav Karpíšek
* @date 26 April 2017
* @brief Soubor obsahuje deklaraci třídy board.
*/

#include "board.h++"
#include "memory.h++"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;

Board::Board(string name) {
    _ok = false;
    this->_grave = new Deck(0);
    this->_deck = Deck::createDeck();

    _name = name;
    _deck->shuffle();
    _score = 0;
    _moves = 0;

    //rozdani "zásobníků"
    for(int i = 0; i < 7; i++) {
        Deck *magazine = new Deck(0);
        for(int o = i; o > 0; o--) {
            magazine->put(_deck->pop());
        }
        _magazines.push_back(magazine);
    }

    //rozdání prvních karet do stacků
    for(int i = 0; i < 7; i++) {
        Stack *stacks = new Stack(13);
        stacks->push(_deck->pop());
        _stacks.push_back(stacks);
    }

    //inicializace "finálních balíčků"
    Foundation *fond_H = new Foundation(HEARDS);
    Foundation *fond_D = new Foundation(DIAMONDS);
    Foundation *fond_C = new Foundation(CLUBS);
    Foundation *fond_S = new Foundation(SPADES);
    _fonds.push_back(fond_H);
    _fonds.push_back(fond_D);
    _fonds.push_back(fond_C);
    _fonds.push_back(fond_S);

    _ok = true;
}

bool Board::isOk() {
    return _ok;
}

Board::Board(string name, bool) {

    _ok = false;
    string file_name = "saves/" + name + ".save";
    string str;
    char helper = '\0';

    FILE *fp = fopen(file_name.c_str(), "r");
    if(fp == NULL) {
        return;
    }

    int number;
    color color;

    for(helper = fgetc(fp); helper != '$'; helper = fgetc(fp)) {
        str.clear();
        _score = 0;
        _moves = 0;
        this->_deck = new Deck(0);
        this->_grave = new Deck(0);
        this->_stacks.clear();
        this->_magazines.clear();
        this->_fonds.clear();

        // nacitani score
        for(; helper != '\n'; helper = fgetc(fp)) {
            str.push_back(helper);
        }
        _score = stoi(str);
        str.clear();

        // nacitani tahu
        for(helper = fgetc(fp); helper != '\n'; helper = fgetc(fp)) {
            str.push_back(helper);
        }
        _moves = stoi(str);

        // nacitani lízacího balíčku
        for(helper = fgetc(fp); helper != '\n'; helper = fgetc(fp)) {
            if(helper == ',') {
                Card *c = new Card(number, color);
                _deck->put(*c);
            }
            else {
                // prvni misto
                if(helper == 'D') {
                    color = DIAMONDS;
                }
                else if(helper == 'H') {
                    color = HEARDS;
                }
                else if(helper == 'S') {
                    color = SPADES;
                }
                else if(helper == 'C') {
                    color = CLUBS;
                }
                else if(helper == '\n') {
                    break;
                }
                else {
                    return;
                }

                //druhe misto
                helper = fgetc(fp);
                if(helper == '1') {
                    if(fgetc(fp) == '0') {
                        number = 10;
                        continue;
                    }
                    return;
                }
                else if(helper != '-') {
                    return;
                }

                //treti misto
                helper = fgetc(fp);
                switch (helper) {
                    case 'A':
                        number = 1;
                        break;

                    case 'K':
                        number = 13;
                        break;

                    case 'Q':
                        number = 12;
                        break;

                    case 'J':
                        number = 11;
                        break;

                    case '9':
                        number = 9;
                        break;

                    case '8':
                        number = 8;
                        break;

                    case '7':
                        number = 7;
                        break;

                    case '6':
                        number = 6;
                        break;

                    case '5':
                        number = 5;
                        break;

                    case '4':
                        number = 4;
                        break;

                    case '3':
                        number = 3;
                        break;

                    case '2':
                        number = 2;
                        break;
                }
            }
        }

        // naciteni odhazovaciho balicku
         for(helper = fgetc(fp); helper != '\n'; helper = fgetc(fp)) {
             if(helper == ',') {
                 Card *c = new Card(number, color);
                 _grave->put(*c);
             }
             else {
                 // prvni misto
                 if(helper == 'D') {
                     color = DIAMONDS;
                 }
                 else if(helper == 'H') {
                     color = HEARDS;
                 }
                 else if(helper == 'S') {
                     color = SPADES;
                 }
                 else if(helper == 'C') {
                     color = CLUBS;
                 }
                 else if(helper == '\n') {
                     break;
                 }
                 else {
                     return;
                 }

                 //druhe misto
                 helper = fgetc(fp);
                 if(helper == '1') {
                     if(fgetc(fp) == '0') {
                         number = 10;
                         continue;
                     }
                     return;
                 }
                 else if(helper != '-') {
                     return;
                 }

                 //treti misto
                 helper = fgetc(fp);
                 switch (helper) {
                     case 'A':
                         number = 1;
                         break;

                     case 'K':
                         number = 13;
                         break;

                     case 'Q':
                         number = 12;
                         break;

                     case 'J':
                         number = 11;
                         break;

                     case '9':
                         number = 9;
                         break;

                     case '8':
                         number = 8;
                         break;

                     case '7':
                         number = 7;
                         break;

                     case '6':
                         number = 6;
                         break;

                     case '5':
                         number = 5;
                         break;

                     case '4':
                         number = 4;
                         break;

                     case '3':
                         number = 3;
                         break;

                     case '2':
                         number = 2;
                         break;
                 }
             }
         }


         // inicializace stacku
         for(int i = 0; i < 7; i++) {
             Stack *stacks = new Stack(13);
             _stacks.push_back(stacks);
         }

         // inicializace magu
         for(int i = 0; i < 7; i++) {
             Deck *stacks = new Deck(0);
             _magazines.push_back(stacks);
         }

         // inicializace fonds
         Foundation *fond_H = new Foundation(HEARDS);
         Foundation *fond_D = new Foundation(DIAMONDS);
         Foundation *fond_C = new Foundation(CLUBS);
         Foundation *fond_S = new Foundation(SPADES);
         _fonds.push_back(fond_H);
         _fonds.push_back(fond_D);
         _fonds.push_back(fond_C);
         _fonds.push_back(fond_S);

         // nacitani stacku
         for(int i = 0; i < 7; i++) {
             for(helper = fgetc(fp); helper != '\n'; helper = fgetc(fp)) {
                 cout << helper << endl;
                 if(helper == ',') {
                     Card *c = new Card(number, color);
                     _stacks.at(i)->push(*c);
                 }
                 else {
                     // prvni misto
                     if(helper == 'D') {
                         color = DIAMONDS;
                     }
                     else if(helper == 'H') {
                         color = HEARDS;
                     }
                     else if(helper == 'S') {
                         color = SPADES;
                     }
                     else if(helper == 'C') {
                         color = CLUBS;
                     }
                     else if(helper == '\n') {
                         break;
                     }
                     else {
                         return;
                     }

                     //druhe misto
                     helper = fgetc(fp);
                     if(helper == '1') {
                         if(fgetc(fp) == '0') {
                             number = 10;
                             continue;
                         }
                         return;
                     }
                     else if(helper != '-') {
                         return;
                     }

                     //treti misto
                     helper = fgetc(fp);
                     switch (helper) {
                         case 'A':
                             number = 1;
                             break;

                         case 'K':
                             number = 13;
                             break;

                         case 'Q':
                             number = 12;
                             break;

                         case 'J':
                             number = 11;
                             break;

                         case '9':
                             number = 9;
                             break;

                         case '8':
                             number = 8;
                             break;

                         case '7':
                             number = 7;
                             break;

                         case '6':
                             number = 6;
                             break;

                         case '5':
                             number = 5;
                             break;

                         case '4':
                             number = 4;
                             break;

                         case '3':
                             number = 3;
                             break;

                         case '2':
                             number = 2;
                             break;
                     }
                 }
             }



         }

         // nacitani magazinu
         for(int i = 0; i < 7; i++) {
             for(helper = fgetc(fp); helper != '\n'; helper = fgetc(fp)) {
                 cout << helper << endl;
                 if(helper == ',') {
                     Card *c = new Card(number, color);
                     _magazines.at(i)->put(*c);
                 }
                 else {
                     // prvni misto
                     if(helper == 'D') {
                         color = DIAMONDS;
                     }
                     else if(helper == 'H') {
                         color = HEARDS;
                     }
                     else if(helper == 'S') {
                         color = SPADES;
                     }
                     else if(helper == 'C') {
                         color = CLUBS;
                     }
                     else if(helper == '\n') {
                         break;
                     }
                     else {
                         return;
                     }

                     //druhe misto
                     helper = fgetc(fp);
                     if(helper == '1') {
                         if(fgetc(fp) == '0') {
                             number = 10;
                             continue;
                         }
                         return;
                     }
                     else if(helper != '-') {
                         return;
                     }

                     //treti misto
                     helper = fgetc(fp);
                     switch (helper) {
                         case 'A':
                             number = 1;
                             break;

                         case 'K':
                             number = 13;
                             break;

                         case 'Q':
                             number = 12;
                             break;

                         case 'J':
                             number = 11;
                             break;

                         case '9':
                             number = 9;
                             break;

                         case '8':
                             number = 8;
                             break;

                         case '7':
                             number = 7;
                             break;

                         case '6':
                             number = 6;
                             break;

                         case '5':
                             number = 5;
                             break;

                         case '4':
                             number = 4;
                             break;

                         case '3':
                             number = 3;
                             break;

                         case '2':
                             number = 2;
                             break;
                     }
                 }
             }



         }

         // nacitani finalnich baliku
         for(int i = 0; i < 4; i++) {
             for(helper = fgetc(fp); helper != '\n'; helper = fgetc(fp)) {
                 cout << helper << endl;
                 if(helper == ',') {
                     Card *c = new Card(number, color);
                     _fonds.at(i)->put(*c);
                 }
                 else {
                     // prvni misto
                     if(helper == 'D') {
                         color = DIAMONDS;
                     }
                     else if(helper == 'H') {
                         color = HEARDS;
                     }
                     else if(helper == 'S') {
                         color = SPADES;
                     }
                     else if(helper == 'C') {
                         color = CLUBS;
                     }
                     else if(helper == '\n') {
                         break;
                     }
                     else {
                         return;
                     }

                     //druhe misto
                     helper = fgetc(fp);
                     if(helper == '1') {
                         if(fgetc(fp) == '0') {
                             number = 10;
                             continue;
                         }
                         return;
                     }
                     else if(helper != '-') {
                         return;
                     }

                     //treti misto
                     helper = fgetc(fp);
                     switch (helper) {
                         case 'A':
                             number = 1;
                             break;

                         case 'K':
                             number = 13;
                             break;

                         case 'Q':
                             number = 12;
                             break;

                         case 'J':
                             number = 11;
                             break;

                         case '9':
                             number = 9;
                             break;

                         case '8':
                             number = 8;
                             break;

                         case '7':
                             number = 7;
                             break;

                         case '6':
                             number = 6;
                             break;

                         case '5':
                             number = 5;
                             break;

                         case '4':
                             number = 4;
                             break;

                         case '3':
                             number = 3;
                             break;

                         case '2':
                             number = 2;
                             break;
                     }
                 }
             }



         }

         save();
    }

    _memory.pop_back();


     // nacitani jmena
     for(helper = fgetc(fp); helper != '\n'; helper = fgetc(fp)) {
         _name.push_back(helper);
     }

    fclose(fp);
    _ok = true;
}

bool Board::take(Stack *stack) {
    save();
    if(!_grave->empty()) {
        Card card = _grave->pop();
        if(stack->put(card)) {
            _moves++;
            _score += 5;
            return true;
        }
        _grave->put(card);
    }

    _memory.pop_back();
    return false;
}

bool Board::take(Foundation *fond) {
    save();
    Card card = _grave->pop();

    if(fond->put(card)) {
        _moves++;
        _score += 10;
        return true;
    }
    _memory.pop_back();
    return false;
}

bool Board::StackToStack(Card *c, Stack *stack_to, Stack *stack_from, Deck *magazine) {
    save();
    Stack poped = stack_from->pop(*c);
    if(stack_to->put(poped)) {
        if(stack_from->size() == 0 && !magazine->empty()) {
            stack_from->push(magazine->pop());
        }
        _moves++;
        _score += 5;
        return true;
    }
    else {
        stack_from->push(poped);
        _memory.pop_back();
        return false;
    }
}

bool Board::StackToFinal(Card *c, Foundation *final_to, Stack *stack_from, Deck *magazine) {
    save();
    Stack poped = stack_from->pop(*c);
    cout << poped.toString();
    if(poped.size() > 1 || poped.size() == 0) {
        stack_from->push(poped);
        _memory.pop_back();
        return false;
    }
    if(final_to->put(poped)) {
        if(stack_from->size() == 0 && !magazine->empty()) {
            stack_from->push(magazine->pop());
        }
        _moves++;
        _score += 50;
        return true;
    }
    else {
        stack_from->push(poped);
        _memory.pop_back();
        return false;
    }
}

bool Board::undo() {

    if(_memory.size() > 0) {
        _score = _memory.back()->getScore();
        _moves = _memory.back()->getMoves();

        // omnovení lízacího a odhazovácího balíčku
        _deck = _memory.back()->getDeck();
        _grave = _memory.back()->getGrave();

        // obnovení stacků a magazines a finálních balíčků
        for(int i = 0; i < 7; i++) {
            _stacks.at(i) = _memory.back()->getStack(i);
            _magazines.at(i) = _memory.back()->getMagazine(i);

            if(i < 4) {
                _fonds.at(i) = _memory.back()->getFinal(i);
            }
        }

        _memory.pop_back();
        return true;
    }
    return false;

}

bool Board::saveGame() {
    string save_name = "saves/" + _name;
    save_name += ".save";
    FILE *fp = fopen(save_name.c_str(), "w");
    if (fp == NULL) {
        return false;
    }
    /**
     * formát výstupu při ukládání
     *
     * <jmeno>
     * <score>
     * <tahy>
     * <deck>
     * <grave>
     * <stack1>
     * ...
     * <mag1>
     * ...
     * <final>
     * ...
     * <mem>
     * &
     * <mem>
     * &
     * ...
     *
     */
     // paměť pro undo
     for(int i = 0; i < (int)_memory.size(); i++) {

         //vypis skore
         fprintf(fp, "%s", to_string(_memory.at(i)->getScore()).c_str());
         fprintf(fp, "\n");

         //vypis tahu
         fprintf(fp, "%s", to_string(_memory.at(i)->getMoves()).c_str());
         fprintf(fp, "\n");

         //vypis decku
         fprintf(fp, "%s", _memory.at(i)->getDeck()->toString().c_str());
         fprintf(fp, "\n");

         //vypis gravu
         fprintf(fp, "%s", _memory.at(i)->getGrave()->toString().c_str());
         fprintf(fp, "\n");

         for(int o = 0; o < 7; o++) {
             // stacky
             fprintf(fp, "%s", _memory.at(i)->getStack(o)->toString().c_str());
             fprintf(fp, "\n");
         }

         for(int o = 0; o < 7; o++) {
             // mag.
             fprintf(fp, "%s", _memory.at(i)->getMagazine(o)->toString().c_str());
             fprintf(fp, "\n");
         }

         for(int o = 0; o < 4; o++) {
             // final.
             fprintf(fp, "%s", _memory.at(i)->getFinal(o)->toString().c_str());
             fprintf(fp, "\n");
         }

     }

     // výpis skóre
     fprintf(fp, "%s", to_string(_score).c_str());
     fprintf(fp, "\n");

     // výpis tahů
     fprintf(fp, "%s", to_string(_moves).c_str());
     fprintf(fp, "\n");

     // výpis decku
     fprintf(fp, "%s", _deck->toString().c_str());
     fprintf(fp, "\n");

     // výpis gravu
     fprintf(fp, "%s", _grave->toString().c_str());
     fprintf(fp, "\n");

    // výpis stacků, magazinu, finalnich
    for(int i = 0; i < 7; i++) {
         // stacky
         fprintf(fp, "%s", _stacks.at(i)->toString().c_str());
         fprintf(fp, "\n");
    }

    for(int i = 0; i < 7; i++) {
         // mag.
         fprintf(fp, "%s", _magazines.at(i)->toString().c_str());
         fprintf(fp, "\n");
    }
    for(int i = 0; i < 4; i++) {
         // final.
         fprintf(fp, "%s", _fonds.at(i)->toString().c_str());
         fprintf(fp, "\n");

    }

    fprintf(fp, "$");

    // výpis jména
    fprintf(fp, "%s", _name.c_str());
    fprintf(fp, "\n");


    fclose(fp);
    return true;
}

void Board::save() {
    Memory *mem = new Memory(this);
    _memory.push_back(mem);
}

Deck* Board::getDeck() {
    return _deck;
}

Deck* Board::getGrave() {
    return _grave;
}

Deck* Board::getMagazine(int i) {
    return _magazines.at(i);
}

Stack* Board::getStack(int i) {
    return _stacks.at(i);
}

Foundation* Board::getFinal(int i) {
    return _fonds.at(i);
}

int Board::getScore() {
    return _score;
}

int Board::getMoves() {
    return _moves;
}

string Board::getName() {
    return _name;
}

/**
*  vezme kartu z balíčku a odloží ji na odkládací. pokud je balíček prázdný
*  "obrátí" odkládací balíček a složí první kartu.
*/
bool Board::draw() {
    save();
    if(_deck->size() + _grave->size() > 0) {
        if(_deck->size() > 0)
            _grave->put(_deck->pop());
        else {
            while(_grave->size() > 0) {
                _deck->put(_grave->pop());
            }
            _grave->put(_deck->pop());
            _score -= 50;
            if(_score < 0)
                _score = 0;
        }

        _moves++;
        return true;
    }
    _memory.pop_back();
    return false;
}

vector<string> Board::hint() {
    // 1.)kontorla vlozeni karty z baliku
    //      - do hry
    //      - do finálního
    // 2.)kontrola pretazeni karet z plánu
    //      - na plán
    //      - do finálního
    // 3.)kontrola zda předchozí ano..
    //      -pokud prazdny balik tak říct že není jak poradit :D
    //


    vector<string> output;

    // kontrola vlozeni karty
    for(int i = 0; i < 7; i++) {
        if(getGrave()->size() > 0) {
            if(getStack(i)->onTop().compareVal(getGrave()->onTop()) == 1 && getGrave()->onTop().value() != 1) {
                if(!getStack(i)->onTop().sameColor(getGrave()->onTop())){
                    string hint;
                    hint += "Vložte kartu z odhazovacího balíčku: " + getGrave()->onTop().toString();
                    hint += "\nna kartu: " + getStack(i)->onTop().toString() + "\n";
                    hint += "nacházající se na " + to_string(i + 1) + ". balíku z leva";
                    hint += "\n";
                    output.push_back(hint);
                }
            }
        }
    }

    // kontrola vlozeni karty na finální
    for(int i = 0; i < 4; i++) {
        if(getFinal(i)->empty()) {
            if(getGrave()->onTop().value() == 1) {
                if(getGrave()->onTop().myColor() == getFinal(i)->myColor()) {
                    string hint;
                    hint += "Vložte Eso z odhazovacího balíčku: " + getGrave()->onTop().toString();
                    hint += " na finální balík.";
                    hint += "\n";
                    output.push_back(hint);
                }
            }
        }
        else if(getFinal(i)->onTop().hashCode() % 10 == getGrave()->onTop().hashCode() % 10) {
            if(getFinal(i)->onTop().compareVal(getGrave()->onTop()) == -1) {
                string hint;
                hint += "Vložte kartu z odhazovacího balíčku: " + getGrave()->onTop().toString();
                hint += "\nna kartu: " + getFinal(i)->onTop().toString() + "\n";
                hint += "nacházající se na finálním balíku";
                hint += "\n";
                output.push_back(hint);
            }
        }
    }

    // kontrola pretazeni karet z planu
    for(int i = 0; i < 7; i++) {
        for(int o = 0; o < (int)getStack(i)->size(); o++) {
            for(int x = 0; x < 7; x++) {
                if(getStack(x)->onTop().compareVal(getStack(i)->get(o)) == 1 && getStack(i)->get(o).value() != 1) {
                    if(!getStack(i)->get(o).sameColor(getStack(x)->onTop())){
                        string hint;
                        hint += "Vložte stacku začínající kartou: " + getStack(i)->get(o).toString();
                        hint += "\nna kartu: " + getStack(x)->onTop().toString() + "\n";
                        hint += "nacházající se na " + to_string(i + 1) + ". balíku z leva";
                        hint += "\n";
                        output.push_back(hint);
                    }
                }
            }
        }
    }

    // kontrola pretazeni na finalni balik z planu
    for(int i = 0; i < 7; i++) {
        if(getStack(i)->size() > 0) {
            for(int x = 0; x < 4; x++) {
                if(getFinal(x)->empty()) {
                    if(getStack(i)->onTop().value() == 1) {
                        if(getGrave()->onTop().myColor() == getFinal(x)->myColor()) {
                            string hint;
                            hint += "Vložte Eso z plátna: " + getStack(i)->onTop().toString();
                            hint += " na finální balík.";
                            hint += "\n";
                            output.push_back(hint);
                        }
                    }
                }
                else if(getFinal(x)->onTop().hashCode() % 10 == getStack(i)->onTop().hashCode() % 10) {
                    if(getFinal(x)->onTop().compareVal(getStack(i)->onTop()) == -1) {
                        string hint;
                        hint += "Vložte kartu z hrací desky" + getStack(i)->onTop().toString();
                        hint += "\nna kartu: " + getFinal(x)->onTop().toString() + "\n";
                        hint += "nacházající se na finálním balíku";
                        hint += "\n";
                        output.push_back(hint);
                    }
                }
            }
        }
    }

    // kontrola jestli jež nějaká rada byla poskytnuta, jinak navrhnuto jine reseni
    if(output.size() == 0 && getDeck()->size() > 0) {
        string hint;
        hint += "S kartami co jsou na hracím plátně, ani s aktuální na odhazovacím balíčku\n";
        hint += "se nedá nic zahrát, doporučujeme si líznout novou kartu pomocí [T]";
        hint += "\n";
        output.push_back(hint);
    }

    if(output.size() == 0) {
        string hint;
        hint += "V aktuální pozici hry, nemáme jak vám poradit, zkuste například UNDO";
        hint += "\nnebo novou hru";
        hint += "\n";
        output.push_back(hint);
    }

    return output;
}

string Board::toString() {
    vector<int> counter;
    string output;

    // inicializace counteru
    for(int i = 0; i < 7; i++)
        counter.push_back(0);

    // příprava rozhraní
    //output += "***************************************************************\n\n";
    output += "Počet karet v balíku: ";
    output += to_string(_deck->size());
    output += "\n";
    output += "Odkládací balíček: ";
    output += _grave->onTop().toString();
    output += "     [L]";
    output += "\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -";
    output += "\n   [A]      [B]      [C]      [D]      [E]      [F]      [G]   ";

    // převedení "zásobníků" a "stacků" do stringu
    for(int o = 0; o < 7; o++) {
        output += "\n";
        for(int i = 0; i < 7; i++) {
            output += "   ";
            if((int)_magazines.at(i)->size() > o) {
                output += " # ";
            }
            else if((int)_stacks.at(i)->size() > counter.at(i)) {
                output += _stacks.at(i)->get(counter.at(i)).toString();
                counter.at(i) += 1;
            }
            else {
                output += "   ";
            }
            output += "   ";
        }
    }

    // převedení finálních balíků
    output += "\n\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -";
    output += "\nFinální balíky: ";
    for(int i = 0; i < 4; i++) {
        output += "   ";
        if(_fonds.at(i)->size() == 0) {
            switch(_fonds.at(i)->myColor()) {
                case DIAMONDS:
                    output += DIAMOND_F;
                    break;
                case HEARDS:
                    output += HEART_F;
                    break;
                case CLUBS:
                    output += CLUB_F;
                    break;
                case SPADES:
                    output += SPADE_F;
                    break;
            }
        }
        else {
            output += _fonds.at(i)->onTop().toString();
        }
        output += "   ";
    }
    output += "\n                  [W]    [X]    [Y]    [Z]";
    output += "\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -";
    output += "\n";

    return output;
}
