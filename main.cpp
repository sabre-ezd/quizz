#include "test.cpp"
#include "base.cpp"
#include "struct.h"
using namespace std;

int main() {
    main_menu();
    return 0;
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
                start_test();
                break;
            case '2':
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