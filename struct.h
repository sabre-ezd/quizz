//
// Created by djsou on 30.12.2019.
//

#ifndef QUIZZ_STRUCT_H
#define QUIZZ_STRUCT_H

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <filesystem>
#include <random>
using namespace std;

struct odpowiedz
{
    string tresc;
    bool prawidlowa;
};


struct zadanie
{
    string pytanie;
    array<odpowiedz, 4> odpowiedzi;
};

struct klucz_odpowiedzi
{
    zadanie pytanie;
    int input{};
};

// Declarations
void main_menu();
void base_menu();
void start_test();
void maszyna_losujaca(vector<zadanie> &test);
void input_odpowiedz(zadanie &x);
bool input_prawidlowa(zadanie &x);
void add_question(fstream &baza);
void display_zadanie(const zadanie& x);
int input_zadanie(zadanie& x);
int score_zadanie(zadanie& x, char odpowiedz);
void test_summary(vector<zadanie> test, vector<klucz_odpowiedzi> prawidlowe, vector<klucz_odpowiedzi> bledne);


#endif //QUIZZ_STRUCT_H
