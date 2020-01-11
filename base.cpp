#include "struct.h"
using namespace std;

void add_question(fstream &baza)
{
    zadanie temp;
    cout<<"Dodawanie pytania do bazy."<<endl
        <<"Tresc pytania: ";
    cin.ignore(1000, '\n');
    getline(cin, temp.pytanie);
    input_odpowiedz(temp);
    input_prawidlowa(temp);
    cout<<"Dodawanie pytania do bazy...";
    baza.seekp(0, ios::end);
    baza<<endl<<temp.pytanie<<";";
    for (const auto& i : temp.odpowiedzi) {
        if (i.prawidlowa)
            baza<<"~";
        baza<<i.tresc<<";";
    }

    cout<<"Pytanie dodane."<<endl;
}

void input_odpowiedz(zadanie &x)
{
    for (int i=0; i<4; i++) {
        cout<<"Odpowiedz "<<i+1<<": ";
        getline(cin, x.odpowiedzi[i].tresc);
    }
}

void input_odpowiedz(zadanie &x, int i)
{
        cout<<"Odpowiedz "<<i+1<<": ";
        getline(cin, x.odpowiedzi[i].tresc);
}

bool input_prawidlowa(zadanie &x)
{
    int prawidlowa;
    cout << "Prawidlowa odpowiedz (1,2,3,4)";
    while(cin >> prawidlowa) {
        if (prawidlowa > 0 && prawidlowa < 5) {
            x.odpowiedzi[prawidlowa-1].prawidlowa = true;
            return true;
        }
        else cout << "Nieprawidlowy znak - dozwolone tylko 1, 2, 3, 4: ";
    }
    return false;
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
            <<"2 - Edytuj pytanie"<<endl
            <<"0 - Powrot"<<endl
            <<"Wybor: "){
        int wybor; cin>>wybor;
        switch (wybor){
            case 1:
                add_question(baza);
                break;
            case 2:
                // TODO: Edit questions
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