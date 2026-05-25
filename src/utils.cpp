#include "utils.h"
using namespace std;

string categoryToString(Category cat) {
    switch (cat) {
        case Category::Networking: return "Networking";
        case Category::Programming: return "Programming";
        case Category::Hardware: return "Hardware";
        case Category::OC: return "OC";
        default: return "Unknown category";
    }
}

string difficultyToString(Difficulty diff) {
    switch (diff) {
        case Difficulty::Easy: return "Easy";
        case Difficulty::Medium: return "Medium";
        case Difficulty::Hard: return "Hard";
        default: return "Easy";
    }
}

Difficulty stringToDifficulty(string str) {
    if (str == "Easy") return Difficulty::Easy;
    else if (str == "Medium") return Difficulty::Medium;
    else return Difficulty::Hard;
}

Category stringToCategory(string str) {
    if (str == "Networking" || str == "Нетворкинг") return Category::Networking;
    else if (str == "Programming" || str == "Программирование") return Category::Programming;
    else if (str == "Hardware" || str == "Аппаратное обеспечение") return Category::Hardware;
    else return Category::OC;
}

Category intToCategory(int ID) {
    switch (ID) {
        case 1: return Category::Networking;
        case 2: return Category::Programming;
        case 3: return Category::Hardware;
        case 4: return Category::OC;
        default: return Category::Networking;
    }
}

int readValidInt(int min, int max) {
    int userInput;
    while (!(cin >> userInput) || userInput < min || userInput > max) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Ошибка ввода, попробуйте снова\n";
    }
    return userInput;
}

string getCurrentDate() {
    time_t now = time(0);
    tm* ltm = localtime(&now);  

    int year = ltm->tm_year + 1900;

    int month = ltm->tm_mon + 1;
    string str_month = to_string(month);
    if (month < 10) str_month = "0" + str_month;

    int day = ltm->tm_mday;
    string str_day = to_string(day);
    if (day < 10) str_day = "0" + str_day;
    
    return to_string(year) + "-" + str_month + "-" + str_day;
}