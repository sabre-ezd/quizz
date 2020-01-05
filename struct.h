//
// Created by djsou on 30.12.2019.
//

#ifndef QUIZZ_STRUCT_H
#define QUIZZ_STRUCT_H

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

struct odpowiedz
{
    string tresc;
    bool prawidlowa;
};

using namespace std;
struct zadanie
{
    string pytanie;
    odpowiedz odpowiedzi[4];
};

// Declarations
void main_menu();
void base_menu();
bool input_odpowiedz(zadanie &x);
void add_question(fstream &baza);
void display_zadanie(zadanie x);


#endif //QUIZZ_STRUCT_H
