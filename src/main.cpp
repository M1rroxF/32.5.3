#include <iostream>
#include <fstream>
#include "nlohmann/json.hpp"
using namespace std;

#define DATA_DIR "Enter your"

int main() {
    nlohmann::json dir;
    cout << "1 - input\n"
            "2 - search\n";
    int i; cin >> i;
    if (i == 1) {
        for (int j = 0; j < 5; j++) {
            cout << "Enter film name:\n";
            cin.ignore();
            string filmName;
            getline(cin, filmName);

            string text;
            cout << "studio: ";
            cin >> text;
            dir[filmName]["studio"] = text;

            cout << "date: ";
            cin >> text;
            dir[filmName]["date"] = text;

            cout << "author: ";
            cin >> text;
            dir[filmName]["author"] = text;

            cout << "director: ";
            cin >> text;
            dir[filmName]["director"] = text;

            cout << "producer: ";
            cin >> text;
            dir[filmName]["producer"] = text;


            do {
                // main character and actor or ext:(text) (text_2)
                cout << "main character and actor or ext: ";
                cin >> text;
                if (text != "ext") {
                    string text_1, text_2;
                    cin >> text_1 >> text_2;
                    dir[filmName]["main characters"][text][text_1] = text_2;
                }
            } while (text != "ext");
        }
        ofstream file(DATA_DIR "fsonr.txt");
        file << dir;
        file.close();
    }
    else {
        ifstream file(DATA_DIR "fsonr.txt");
        file >> dir;
        file.close();

        string searchName;
        cout << "Enter search name: ";
        cin >> searchName;

        for (auto it_1 = dir.begin(); it_1 != dir.end(); it_1++) {
            for (auto it_2 = dir[it_1.key()]["main characters"].begin(); it_2 != dir[it_1.key()]["main characters"].end(); it_2++) {
                if (    it_2.key() == searchName ||
                        it_2.value().begin().key() == searchName ||
                        it_2.value().begin().value() == searchName)
                    cout << it_2.key() << " " << it_2.value().begin().key() << " " << it_2.value().begin().value() << endl;
            }
        }
    }
}