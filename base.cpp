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
        getline(cin, temp.odpowiedzi[i]);
    }
    while(input_odpowiedz(temp)) {
        if (temp.prawidlowa == 'A' || temp.prawidlowa == 'B' || temp.prawidlowa == 'C' || temp.prawidlowa == 'D')
            break;
        else if (temp.prawidlowa == 'a' || temp.prawidlowa == 'b' || temp.prawidlowa == 'c' || temp.prawidlowa == 'd') {
            temp.prawidlowa-=32;
            break;
        }
        else cout<<"Nieprawidlowy znak - dozwolone tylko A, B, C, D"<<endl;
    }
    cout<<"Dodawanie pytania do bazy...";
    baza.seekp(0, ios::end);
    baza<<temp.pytanie<<";";
    for (const auto& i : temp.odpowiedzi) {
        baza<<i<<";";
    }

}

bool input_odpowiedz(zadanie &x)
{
    cout << "Prawidlowa odpowiedz (A,B,C,D)";
    cin >> x.prawidlowa;
    return true;
}