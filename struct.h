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
#include <iomanip>
#include <filesystem>
#include <random>

using namespace std;

struct odpowiedz {
    string tresc;
    bool prawidlowa=false;
};


struct zadanie {
    string tresc_pytanie;
    array<odpowiedz, 4> odpowiedzi;
};

struct klucz_odpowiedzi {
    zadanie zadanie;
    int input{};
};

// Declarations
void main_menu();

void base_menu();

void edit_exam();

void start_test(vector<zadanie> test);

void maszyna_losujaca(vector<zadanie> &test, int pytania = 0, const string &name = "baza.txt");

void input_tresc(zadanie &x);
void input_odpowiedz(zadanie &x);
bool input_prawidlowa(zadanie &x);
zadanie add_question(fstream &baza);
void display_zadanie(const zadanie &x);
void input_odpowiedz(zadanie &x, int i);
int input_zadanie(zadanie &x);
int score_zadanie(zadanie &x, char odpowiedz);
void test_summary(const vector<zadanie> &test, const vector<klucz_odpowiedzi> &prawidlowe,
                  const vector<klucz_odpowiedzi> &bledne);
void zadanie_summary(const vector<klucz_odpowiedzi> &rozwiazane);
void load_pytania(fstream &baza, vector<zadanie> &tempbaza);
void edit_baza(vector<zadanie> temp);
void write_question(fstream &baza, const zadanie &temp);
void edit_menu(vector<zadanie> &temp, int pytanie);


#endif //QUIZZ_STRUCT_H
