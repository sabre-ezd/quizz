#include "struct.h"

using namespace std;

void base_menu() {
    cout << "Otwieranie bazy...";
    fstream baza("baza.txt", ios::in | ios::out);
    if (baza.fail()) {
        cout << "Wystapil blad podczas otwierania pliku. Koncze..." << endl;
        return;
    }
    cout << "zakonczono." << endl;
    vector<zadanie> temp;
    load_pytania(baza, temp);
    while (cout << "1 - Dodaj pytanie" << endl
                << "2 - Edytuj pytanie" << endl
                << "9 - Wyswietl wszystkie " << endl
                << "0 - Powrot" << endl
                << "Wybor: ") {
        baza.clear();
        baza.seekg(0);
        int wybor;
        cin >> wybor;
        switch (wybor) {
            case 1:
                temp.push_back(add_question(baza));
                break;
            case 2:
                edit_baza(temp);
                break;
            case 9:
                for (int i = 0; i < temp.size(); i++) {
                    cout << i + 1 << ". " << temp[i].tresc_pytanie << endl;
                }
                cout << endl;
                break;
            case 0: {
                cout << "Zamykanie bazy...";
                baza.close();
                fstream bufor;
                bufor.open("temp.txt", ios::out);
                for (auto &i:temp)
                    write_question(bufor, i);
                bufor.close();
                remove("baza.txt");
                rename("temp.txt", "baza.txt");
                cout << "zamknieto. Powrot..." << endl;
                return;
            }
            default:
                cout << "Nieprawidlowy wybor." << endl;
                break;
        }
    }
}

void edit_menu(vector<zadanie> &temp, int pytanie) {
    display_zadanie(temp[pytanie]);
    do {
        cout << "1 - edytuj tresc pytania" << endl
             << "2 - edytuj tresc odpowiedzi" << endl
             << "3 - edytuj prawidlowa odpowiedz" << endl
             << "4 - usun pytanie" << endl
             << "0 - powrot" << endl;
        cout << "Wybor: ";
        cin >> pytanie;
        switch (pytanie) {
            case 1:
                input_tresc(temp[pytanie]);
                break;
            case 2:
                int odpowiedz;
                cout << "Ktora odpowiedz chcesz edytowac? (1-4)";
                cin >> odpowiedz;
                if (odpowiedz <= 4 && odpowiedz >= 1)
                    input_odpowiedz(temp[pytanie], (odpowiedz - 1));
                else cout << "Nieprawidlowy wybor. Powrot..." << endl;
                break;
            case 3:
                input_prawidlowa(temp[pytanie]);
                break;
            case 4:
                temp.erase(temp.begin() + pytanie);
                return;
            case 0: {
                zadanie x = temp[pytanie];
                temp.erase(temp.begin() + pytanie);
                temp.insert(temp.begin() + pytanie, x);
                return;
            }
            default:
                cout << "Nieprawidlowy wybor." << endl;
                break;
        }
    } while (pytanie != 0);
}

zadanie add_question(fstream &baza) {
    zadanie temp;
    input_tresc(temp);
    input_odpowiedz(temp);
    input_prawidlowa(temp);
    cout << "Pytanie dodane." << endl;
    write_question(baza, temp);
    return temp;
}

void write_question(fstream &baza, const zadanie &temp) {
    baza.seekp(0, ios::end);
    baza << temp.tresc_pytanie << ";";
    for (const auto &i : temp.odpowiedzi) {
        if (i.prawidlowa)
            baza << "~";
        baza << i.tresc << ";";
    }
    baza << endl;
}

void input_tresc(zadanie &x) {
    cout << "Tresc pytania: ";
    cin.ignore(1000, '\n');
    getline(cin, x.tresc_pytanie);
}

void input_odpowiedz(zadanie &x) {
    for (int i = 0; i < 4; i++) {
        cout << "Odpowiedz " << i + 1 << ": ";
        getline(cin, x.odpowiedzi[i].tresc);
    }
}

void input_odpowiedz(zadanie &x, int i = 0) {
    cout << "Odpowiedz " << i + 1 << ": ";
    getline(cin, x.odpowiedzi[i].tresc);
}

bool input_prawidlowa(zadanie &x) {
    int prawidlowa;
    cout << "Prawidlowa odpowiedz (1,2,3,4): 1`";
    while (cin >> prawidlowa) {
        if (prawidlowa > 0 && prawidlowa < 5) {
            x.odpowiedzi[prawidlowa - 1].prawidlowa = true;
            return true;
        } else cout << "Nieprawidlowy znak - dozwolone tylko 1, 2, 3, 4: ";
    }
    return false;
}

void load_pytania(fstream &baza, vector<zadanie> &tempbaza) {
    cout << "Ladowanie bazy... ";
    unsigned int total = 0;
    string temp;
    while (getline(baza, temp)) {
        if (baza.eof())
            break;
        total++;
    }
    cout << "znaleziono " << total << " pytan." << endl;
    baza.clear();
    baza.seekg(0);
    zadanie zad_temp;
    cout << "Ladowanie pytan do pamieci...";
    while (getline(baza, temp)) {
        istringstream iss(temp);
        getline(iss, zad_temp.tresc_pytanie, ';');
        for (auto &i : zad_temp.odpowiedzi) {
            getline(iss, i.tresc, ';');
            if (i.tresc[0] == '~') {
                i.tresc.erase(0, 1);
                i.prawidlowa = true;
            } else i.prawidlowa = false;
        }
        tempbaza.push_back(zad_temp);
    }
    if (total == tempbaza.size())
        cout << "Wszystkie pytania zaladowano" << endl;
}

void edit_baza(vector<zadanie> temp) {
    int pytanie = 0;
    do {
        cout << "Wybierz pytanie(0 by wyjsc): ";
        cin >> pytanie;
        if (pytanie == 0) {
            return;
        }
        pytanie -= 1;
        if (pytanie >= temp.size())
            cout << "Nieprawidlowy wybor." << endl;
    } while (pytanie >= temp.size());
    edit_menu(temp, pytanie);
}

void edit_exam() {
    fstream baza;
    baza.open("baza.txt", ios::in);
    vector<zadanie> temp;
    load_pytania(baza, temp);
    baza.close();
    int pytanie = 0;
    for (int i = 0; i < temp.size(); i++) {
        cout << i + 1 << ". " << temp[i].tresc_pytanie << endl;
    }
    cout << "Podaj nazwe pliku: ";
    string nazwa;
    cin.ignore(1000, '\n');
    getline(cin, nazwa);
    fstream plik;
    plik.open((nazwa+".txt").c_str(), ios::out);
    cout << endl;
    do {
        cout << "Wpisz nr pytania ktore chcesz dodac do egzaminu (0 aby wyjsc)";
        cin >> pytanie;
        if (pytanie == 0)
            continue;
        else if (pytanie > temp.size())
            cout << "Nie ma takiego pytania w bazie." << endl;
        else
            write_question(plik, temp[pytanie - 1]);
    } while (pytanie != 0);
    cout << "Zapisywanie..." << endl;
    plik.close();
}