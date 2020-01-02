//
// Created by djsou on 30.12.2019.
//

#ifndef QUIZZ_STRUCT_H
#define QUIZZ_STRUCT_H

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
struct zadanie
{
    string pytanie;
    string odpowiedzi[4];
    char prawidlowa;
};

// Declarations
void main_menu();

bool input_odpowiedz(zadanie &x);

#endif //QUIZZ_STRUCT_H
