#include <iostream>
#include <fstream>
#include "nlohmann/json.hpp"
using namespace std;

<<<<<<< HEAD
#define DATA_DIR "Enter your your the path to the file"
=======
#define DATA_DIR "Enter your the path to the file"
>>>>>>> c3cff02e1b6318dcd31d2a05f3743ad2473f78d2

int main() {
    nlohmann::json dir;
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

    ofstream file(DATA_DIR "fsonr.txt");
    file << dir;
    file.close();
}