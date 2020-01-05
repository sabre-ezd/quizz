#include "struct.h"
using namespace std;

void add_question(fstream &baza)
{
    zadanie temp;
    cout<<"Dodawanie pytania do bazy."<<endl
        <<"Tresc pytania: ";
    cin>>temp.pytanie;
    cin.ignore(1000, '\n');
    for (int i=0; i<4; i++) {
        cout<<"Odpowiedz "<<i+1<<": ";
        getline(cin, temp.odpowiedzi[i].tresc);
    }
    while(input_odpowiedz(temp)) {

    }
    cout<<"Dodawanie pytania do bazy...";
    baza.seekp(0, ios::end);
    baza<<temp.pytanie<<";";
    for (const auto& i : temp.odpowiedzi) {
        if (i.prawidlowa)
            baza<<"!"<<i.tresc;
        else baza<<i.tresc;
    }
    cout<<"Pytanie dodane."<<endl;
}

bool input_odpowiedz(zadanie &x)
{
    int prawidlowa;
    cout << "Prawidlowa odpowiedz (1,2,3,4)";
    while(cin >> prawidlowa) {
        if (x.odpowiedzi[prawidlowa].prawidlowa)
            return true;
        else cout << "Nieprawidlowy znak - dozwolone tylko 1, 2, 3, 4: ";
    }
}

void base_menu()
{
    cout<<"Otwieranie bazy...";
    fstream baza("baza.txt", ios::in | ios::out);
    if (baza.fail())  {
        cout<<"Wystapil blad podczas otwierania pliku. Koncze..."<<endl;
        return;
    }
    cout<<"zakonczono."<<endl;
    while(cout<<"1 - Dodaj pytanie"<<endl
              <<"0 - Powrot"<<endl
              <<"Wybor: "){
        int wybor; cin>>wybor;
        switch (wybor){
            case 1:
                add_question(baza);
                break;
            case 0:
                cout<<"Zamykanie bazy...";
                baza.close();
                cout<<"zamknieto. Powrot..."<<endl;
                return;
            default:
                cout<<"Nieprawidlowy wybor."<<endl;
                break;
        }
    }
}