#include "struct.h"

using namespace std;

void init_test(const string &nazwa = "baza.txt", bool egzamin = false) {
    vector<zadanie> test;
    if (egzamin) {
        maszyna_losujaca(test, 0, nazwa);
    } else {
        cout << "Podaj liczbe pytan: ";
        int pytania;
        cin >> pytania;
        maszyna_losujaca(test, pytania);
    }
    start_test(test);
}

void start_test(vector<zadanie> test) {
    vector<klucz_odpowiedzi> prawidlowe;
    vector<klucz_odpowiedzi> bledne;
    klucz_odpowiedzi temp = {};
    if (test.empty()) {
        cout << "Brak pytan w tescie. Musisz dodac pytania zanim rozpoczniesz." << endl;
        return;
    }
    for (auto &i:test) {
        display_zadanie(i);
        temp.zadanie = i;
        temp.input = input_zadanie(i);
        if (i.odpowiedzi[temp.input].prawidlowa)
            prawidlowe.push_back(temp);
        else
            bledne.push_back(temp);
    }
    test_summary(test, prawidlowe, bledne);
}

void test_summary(const vector<zadanie> &test, const vector<klucz_odpowiedzi> &prawidlowe,
                  const vector<klucz_odpowiedzi> &bledne) {
    char choice;
    cout << "Wynik: " << prawidlowe.size() << "/" << test.size() << "=" << setprecision(4)
         << ((float) prawidlowe.size() * 100.0 / test.size()) << "%" << endl;
    while (true) {
        cout << "1 - Poprawne odpowiedzi" << endl
             << "2 - Bledne odpowiedzi" << endl
             << "0 - Zakoncz test" << endl;
        cout << "Wybor: ";
        cin >> choice;
        switch (choice) {
            case '1':
                zadanie_summary(prawidlowe);
                break;
            case '2':
                zadanie_summary(bledne);
                break;
            case '0':
                return;
            default:
                cout << "Nieprawidlowy wybor." << endl;
                break;
        }
    }
}

void zadanie_summary(const vector<klucz_odpowiedzi> &rozwiazane) {
    int wybor = 0;
    do {
        for (unsigned int i = 0; i < rozwiazane.size(); i++) {
            cout << i + 1 << ". " << rozwiazane[i].zadanie.tresc_pytanie << endl;
        }
        cout << "Pytanie do sprawdzenia(0 by wyjsc): ";
        cin >> wybor;
        if (wybor == 0)
            continue;
        else if (wybor > rozwiazane.size())
            cout << "Nieprawidlowy wybor" << endl;
        else {
            display_zadanie(rozwiazane[wybor - 1].zadanie);
            cout << "Twoja odpowiedz: " << rozwiazane[wybor - 1].zadanie.odpowiedzi[rozwiazane[wybor - 1].input].tresc
                 << endl;
            cout << "Prawidlowa odpowiedz: ";
            for (auto &i:rozwiazane[wybor - 1].zadanie.odpowiedzi) {
                if (i.prawidlowa) {
                    cout << i.tresc << endl;
                    break;
                }
            }
        }
    } while (wybor != 0);
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-nullptr"
#pragma ide diagnostic ignored "cert-msc50-cpp"
#pragma ide diagnostic ignored "cert-msc32-c"

void maszyna_losujaca(vector<zadanie> &test, int pytania, const string &name) {
    srand(time(NULL));
    int seed = time(NULL);
    cout << "Otwieranie bazy... ";
    fstream baza(name.c_str(), ios::in);
    if (baza.fail()) {
        cout << "Wystapil blad podczas otwierania pliku. Koncze..." << endl;
        return;
    }
    cout << "zakonczono." << endl;
    vector<zadanie> tempbaza;
    load_pytania(baza, tempbaza);
    if (tempbaza.size() < pytania || pytania == 0) {
        pytania = tempbaza.size();
    }
    cout << "Losowanie..." << endl;
    for (int i = 0; i < pytania; i++) {
        int randomed = rand() % (int) tempbaza.size();
        test.push_back(tempbaza[randomed]);
        shuffle(begin(test.back().odpowiedzi), end(test.back().odpowiedzi), default_random_engine(seed));
        tempbaza.erase(tempbaza.begin() + randomed);
        cout << "\rProgress: " << i + 1 << "/" << pytania << flush;
    }
    vector<zadanie>().swap(tempbaza);
}

void display_zadanie(const zadanie &x) {
    const char odpowiedzi[4] = {'A', 'B', 'C', 'D'};
    cout << endl << x.tresc_pytanie << endl;
    for (int i = 0; i < 4; i++) {
        cout << odpowiedzi[i] << " - " << x.odpowiedzi[i].tresc << endl;
    }
}

int input_zadanie(zadanie &x) {
    char odpowiedz = 0;
    cout << "Odpowiedz: ";
    cin >> odpowiedz;
    return score_zadanie(x, odpowiedz);
}

int score_zadanie(zadanie &x, char odpowiedz) {
    int wynik = 4;
    switch (odpowiedz) {
        case 'a':
        case 'A':
            wynik = 0;
            break;
        case 'b':
        case 'B':
            wynik = 1;
            break;
        case 'c':
        case 'C':
            wynik = 2;
            break;
        case 'd':
        case 'D':
            wynik = 3;
            break;
        default:
            break;
    }
    return wynik;
}