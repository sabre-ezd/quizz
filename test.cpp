#include "struct.h"
using namespace std;

void start_test()
{
    cout<<"Otwieranie bazy... ";
    fstream baza ("baza.txt", ios::in);
    cout<<"zakonczono."<<endl;
    cout<<"Podaj liczbe pytan: ";
    int pytania; cin>>pytania;
    cout<<"Ladowanie bazy... ";
    int total=0;
    vector<zadanie>
    while (true) {
        getline(baza);
        if (baza.eof())
            break;
        total++:
    }
    cout<<"zaladowano "<<total<<" pytan."<<endl;
    baza.seekg(0);
    baza.clear();

}