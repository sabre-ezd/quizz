#include "struct.h"
using namespace std;

void start_test()
{
    vector<zadanie> test;
    maszyna_losujaca(test);
    vector<klucz_odpowiedzi> prawidlowe;
    vector<klucz_odpowiedzi> bledne;
    klucz_odpowiedzi temp = {};
    for (auto& i:test){
        display_zadanie(i);
        temp.pytanie = i;
        temp.input = input_zadanie(i);
        if (i.odpowiedzi[temp.input].prawidlowa) {
            cout<<"dobrze"<<endl;
            prawidlowe.push_back(temp);
        }
        else {
            cout<<"zle"<<endl;
            bledne.push_back(temp);
        }
    }
//1
// test_summary(test, prawidlowe, bledne);
}

//void test_summary(vector<zadanie> test, vector<klucz_odpowiedzi> prawidlowe, vector<klucz_odpowiedzi> bledne)
//{
//
//}

void maszyna_losujaca(vector<zadanie> &test)
{
    srand(time(NULL));
    int seed = time(NULL);
    cout<<"Otwieranie bazy... ";
    fstream baza ("baza.txt", ios::in);
    if (baza.fail())  {
        cout<<"Wystapil blad podczas otwierania pliku. Koncze..."<<endl;
        return;
    }
    cout<<"zakonczono."<<endl;
    cout<<"Podaj liczbe pytan: ";
    int pytania; cin>>pytania;
    vector<zadanie> tempbaza;
    load_pytania(baza, tempbaza);
    if (tempbaza.size()<pytania){
        cout<<"Zadana ilosc zadan jest wieksza niz zawartosc bazy - wczytuje wszystkie pytania..."<<endl;
        pytania = tempbaza.size();
    }
    cout<<"Losowanie..."<<endl;
    for (int i=0; i<pytania; i++){
        int randomed = rand()%pytania;
        test.push_back(tempbaza[randomed]);
        shuffle(begin(test.back().odpowiedzi), end(test.back().odpowiedzi), default_random_engine(seed));
        tempbaza.erase(tempbaza.begin()+randomed);
        cout<<"\rProgress: "<<i+1<<"/"<<pytania<<flush;
    }
    vector<zadanie>().swap(tempbaza);
}


void display_zadanie(const zadanie& x)
{
    const char odpowiedzi[4] = {'A', 'B', 'C', 'D'};
    cout<<endl<<x.pytanie<<endl;
    for (int i=0; i<4; i++){
        cout<<odpowiedzi[i]<<" - "<<x.odpowiedzi[i].tresc<<endl;
    }
}

int input_zadanie(zadanie& x)
{
    char odpowiedz = 0;
    cout<<"Odpowiedz: "; cin>>odpowiedz;
    return score_zadanie(x,odpowiedz);
}

int score_zadanie(zadanie& x, char odpowiedz)
{
    int wynik=4;
    switch(odpowiedz){
        case 'a':
        case 'A':
            wynik=0;
            break;
        case 'b':
        case 'B':
            wynik=1;
            break;
        case 'c':
        case 'C':
            wynik=2;
            break;
        case 'd':
        case 'D':
            wynik=3;
            break;
        default:
            break;
    }
    return wynik;
}