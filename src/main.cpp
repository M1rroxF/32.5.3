#include <iostream>
#include <fstream>
#include "nlohmann/json.hpp"
using namespace std;

#define DATA_DIR "Enter your the path to the file"

int main() {
    nlohmann::json dir;
    cout << "1 - input\n"
            "2 - search\n";
    int i; cin >> i;
    if (i == 1) {
        cout << "Enter film name:\n"; cin.ignore();
        string filmName;
        getline(cin, filmName);

        string text;
        cout << "studio: "; cin >> text;
        dir[filmName]["studio"] = text;

        cout << "date: "; cin >> text;
        dir[filmName]["date"] = text;

        cout << "author: "; cin >> text;
        dir[filmName]["author"] = text;

        cout << "director: "; cin >> text;
        dir[filmName]["director"] = text;

        cout << "producer: "; cin >> text;
        dir[filmName]["producer"] = text;


        do {
            // main character and actor or ext:(text) (text_2)
            cout << "main character and actor or ext: "; cin >> text;
            if (text != "ext") {
                string text_2;
                cin >> text_2;
                dir[filmName]["main characters"][text] = text_2;
            }
        } while (text != "ext");

        ofstream file(DATA_DIR "fsonr.txt");
        file << dir;
        file.close();
    }
    else {
        ifstream file(DATA_DIR "fsonr.txt");
        file >> dir;
        file.close();

        auto it = dir.begin();
        const string& filmName = it.key();

        cout << "1 - actor\n"
                "2 - character\n";
        cin >> i;

        string searchName;
        cout << "Enter " << (i == 1 ? "actor: " : "character: ");
        cin >> searchName;

        for (it = dir[filmName]["main characters"].begin(); it != dir[filmName]["main characters"].end(); it++) {
            if (i == 1 && it.value() == searchName) {
                cout << it.key() << " - " << it.value() << endl;
            } else if (i == 2 && it.key() == searchName){
                cout << it.key() << " - " << it.value() << endl;
            }
        }
    }
}
