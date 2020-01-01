#include "struct.h"
using namespace std;

void add_question(fstream &baza)
{
    zadanie temp;
    cout<<"Dodawanie pytania do bazy."<<endl
        <<"Tresc pytania: ";
    cin>>temp.pytanie;
    while(true) {
        cout << "Prawidlowa odpowiedz (A,B,C,D)";
        cin >> temp.prawidlowa;
        if (temp.prawidlowa == 'A' || temp.prawidlowa == 'B' || temp.prawidlowa == 'C' || temp.prawidlowa == 'D')
            break;
        else if (temp.prawidlowa == 'a' || temp.prawidlowa == 'b' || temp.prawidlowa == 'c' || temp.prawidlowa == 'd') {
            (int) temp.prawidlowa-=32;
            break;
        }

    }

}