#include "struct.h"
#include "test.cpp"
#include "base.cpp"
using namespace std;

int main(int argc, char* argv[]) {
    if (argc == 0) {
        if (!filesystem::exists("baza.txt")) {
            cout << "Nie znaleziono bazy. Tworzenie...";
            fstream plik;
            plik.open("baza.txt", ios::out);
            plik.close();
            cout << "zakonczono." << endl;
        }
        main_menu();
        return 0;
    }
    else if (argc == 1){
        cout<<"TRYB EGZAMINU"<<endl;
        init_test(argv[0], true);
        return 0;
    }
}

void main_menu() {
    char choice;
    while(true) {
        cout<<"Menu glowne:"<<endl
            <<"1 - Rozpocznij test"<<endl
            <<"2 - Zarzadzanie baza pytan"<<endl
            <<"Q - Wyjscie"<<endl
            <<"Wybor: ";
        cin>>choice;
        switch(choice) {
            case '1':
                init_test();
                break;
            case '2':
                base_menu();
                break;
            case 'q':
            case 'Q':
                return;
            default:
                cout<<"Nieprawidlowy wybor.";
                break;
        }
    }
}