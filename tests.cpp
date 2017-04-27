/**
 * @file tests.cpp
 * @author Miroslav Karpíšek
 * @date 24 April 2017
 * @brief Soubor obsahuje asserttesty pro jednotlive třídy.
 */

#include <assert.h>
#include <stdio.h>
#include <iostream>

#include "card.h++"
#include "deck.h++"
#include "stack.h++"
#include "foundation.h++"

using std::cout;

void clear(){
    for(int i = 0; i < 10; i++){
        cout << "\n\n\n\n\n\n\n\n\n\n\n";
    }
}

int main(int argc, char const *argv[]) {
    clear();

    cout << "\n***********************************************************\n"
    << "                       Testovani Solitairu                       \n\n";

    Card c0(10, HEARDS);
    Card c1(13, DIAMONDS);
    Card c2(12, DIAMONDS);
    Card c3(1, DIAMONDS);
    Card c4(2, DIAMONDS);
    Card c5(2, CLUBS);


    cout << "Testuji jednotlive karty: ";
    assert(c1.toString() == DIAMOND"K"); // test vytvoreni karty
    assert(c0.toString() == HEART"10"); // test vytvoreni karty
    assert(c2.toString() == DIAMOND"Q"); // test vytvoreni karty
    assert(c3.toString() == DIAMOND"A"); // test vytvoreni karty
    assert(c4.toString() == DIAMOND"2"); // test vytvoreni karty

    assert(c4.sameColor(c3) == true); //testovani sameColor
    assert(c4.sameColor(c4) == true); //testovani sameColor
    assert(c4.sameColor(c5) == false); //testovani sameColor (neplatny)
    cout << "\033[6;32mOK\033[0m\n";


    Deck d1(52);
    d1.put(c1);
    d1.put(c2);
    Card cx = d1.pop();

    cout << "Testuji balíčky: ";

    assert(cx.toString() == DIAMOND"Q"); // tests put a pop
    cx = d1.pop();
    assert(cx.toString() == DIAMOND"K"); // test popu
    cx = d1.pop();
    assert(cx.toString() == "Error"); // liznuti z prazdneho balicku


    Deck test_standart = Deck::createDeck();
    for(int i = 13; i > 0; i--) {
        cx = test_standart.pop();
        Card t(i, CLUBS);
        assert(cx.equals(t) == true);

        cx = test_standart.pop();
        t = Card::Card(i, SPADES);
        assert(cx.equals(t) == true);

        cx = test_standart.pop();
        t = Card::Card(i, HEARDS);
        assert(cx.equals(t) == true);

        cx = test_standart.pop();
        t = Card::Card(i, DIAMONDS);
        assert(cx.equals(t) == true);
    }

    test_standart = Deck::createDeck();
    test_standart.shuffle();
    assert(test_standart.size() == 52);

    //for(int i = 1; i < 53; i++){
    //    cout << test_standart.pop().toString() << endl;
    //}


    cout << "\033[6;32mOK\033[0m\n";


    cout << "Testuji vkládání karty do stacku: ";
    Stack stack_test(13);
    Card cerna_dama(12, CLUBS);
    Card cerveny_janek(11, HEARDS);
    assert(stack_test.put(c0) == false);
    assert(stack_test.put(c1) == true); // K
    assert(stack_test.put(c2) == false);
    assert(stack_test.put(cerna_dama) == true); // K Q
    assert(stack_test.put(c1) == false);  //////// CYHBA TODO
    assert(stack_test.put(cerveny_janek) == true); // K Q J
    Card cervena_K(13, HEARDS);
    Card cerna_Q(12, CLUBS);
    Card cervena_J(11, DIAMONDS);
    Card cerna_10(10, SPADES);
    Card cervena_9(9, HEARDS);
    Card cerna_9(9, CLUBS);
    Stack stack_test2(13);
    Stack prazdny(13);
    assert(stack_test2.put(cervena_K) == true);
    assert(stack_test2.put(cervena_K) == false);
    assert(stack_test2.put(cerna_Q) == true);
    assert(stack_test2.put(cervena_K) == false);
    assert(stack_test2.put(cervena_J) == true);
    assert(stack_test2.put(cervena_K) == false);
    assert(stack_test2.put(cerna_10) == true);
    assert(stack_test2.put(cervena_K) == false);
    assert(stack_test2.put(cerna_9) == false);
    assert(stack_test2.put(cervena_9) == true);
    assert(stack_test2.put(cerna_10) == false); // K Q J 10 9
    assert(stack_test2.put(stack_test) == false);
    assert(stack_test.put(stack_test2) == false);
    Stack stack_test3 = stack_test2.pop(cerna_10); // 10 9
    assert(stack_test3.size() == 2);
    assert(stack_test.put(stack_test2) == false);
    assert(stack_test.put(stack_test3) == true); // K Q J 10 9
    stack_test2 = stack_test.pop(Card::Card(12, CLUBS));
    Card cerna_8(8, CLUBS);
    Stack pomocny = stack_test.pop(Card::Card(13, DIAMONDS));
    assert(prazdny.put(pomocny) == true);
    assert(prazdny.put(stack_test2) == true);
    Stack kontrola = prazdny.pop(Card::Card(9, HEARDS));
    assert(kontrola.put(Card::Card(8, SPADES)) == true);

    //cout << test_standart.toString() << endl; //testovani mychani balicku




    cout << "\033[6;32mOK\033[0m\n";

    cout << "Testuji vyjmuti karty/stacku ze stacku: ";
    cout << "\033[6;31mOK\033[0m\n";

    cout << "Testuji stacky: ";
    cout << "\033[6;31mOK\033[0m\n";

    cout << "Testuji finalní balíčky: ";

    Foundation kary(DIAMONDS);
    assert(kary.put(Card::Card(13,SPADES)) == false);
    cout << kary.toString() << endl << endl;
    assert(kary.put(Card::Card(1,DIAMONDS)) == true);
    cout << kary.toString() << endl << endl;
    assert(kary.put(Card::Card(5,DIAMONDS)) == false);
    cout << kary.toString() << endl << endl;
    assert(kary.put(Card::Card(12,CLUBS)) == false);
    cout << kary.toString() << endl << endl;
    assert(kary.put(Card::Card(12,HEARDS)) == false);
    cout << kary.toString() << endl << endl;
    assert(kary.put(Card::Card(2,HEARDS)) == false);
    cout << kary.toString() << endl << endl;
    assert(kary.put(Card::Card(1,DIAMONDS)) == false);
    cout << kary.toString() << endl << endl;
    assert(kary.put(Card::Card(2,DIAMONDS)) == true);
    cout << kary.toString() << endl << endl;


    cout << "\033[7;33mNOPE\033[0m\n";




    cout << "\n***********************************************************\n\n";


    return 0;
}
