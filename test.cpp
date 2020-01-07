#include "struct.h"
using namespace std;

void start_test()
{
    vector<zadanie> test;
    maszyna_losujaca(test);
    vector<zadanie> prawidlowe;
    vector<zadanie> bledne;

}

void maszyna_losujaca(vector<zadanie> &test)
{
    cout<<"Otwieranie bazy... ";
    fstream baza ("baza.txt", ios::in);
    if (baza.fail())  {
        cout<<"Wystapil blad podczas otwierania pliku. Koncze..."<<endl;
        return;
    }
    cout<<"zakonczono."<<endl;
    cout<<"Podaj liczbe pytan: ";
    int pytania; cin>>pytania;
    cout<<"Ladowanie bazy... ";
    int total=0;
    vector<zadanie> tempbaza;
    string temp;
    while (getline(baza, temp)) {
        if (baza.eof())
            break;
        total++;
    }
    cout<<"znaleziono "<<total<<" pytan."<<endl;
    baza.seekg(0);
    baza.clear();
    zadanie zad_temp;
    cout<<"Ladowanie pytan do pamieci...";
    while (getline(baza, temp)) {
        istringstream iss(temp);
        getline(iss,zad_temp.pytanie,';');
        for (auto & i : zad_temp.odpowiedzi) {
            getline(iss, i.tresc, ';');
            if (i.tresc[0] == '~'){
                i.tresc.erase(0,1);
                i.prawidlowa = true;
            }
        }
        cout<<"Wczytano pytanie z pliku...";
        tempbaza.push_back(zad_temp);
        cout<<"wczytano do pamieci."<<endl;
    }
}

void display_zadanie(const zadanie& x)
{
    const char odpowiedzi[4] = {'A', 'B', 'C', 'D'};
    cout<<x.pytanie<<endl;
    for (int i=0; i<4; i++){
        cout<<odpowiedzi[i]<<" - "<<x.odpowiedzi->tresc[i];
    }
}

void input_zadanie(zadanie& x)
{
    char odpowiedz;
    cout<<"Odpowiedz: "; cin>>odpowiedz;
    score_zadanie(x,odpowiedz);
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