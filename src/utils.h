#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <map>
#include <ctime>
using namespace std;

enum class Language {
    Russian,
    English
};

enum class Category {
    Networking,
    Programming,
    Hardware,
    OC
};

enum class Difficulty {
    Easy = 1,
    Medium = 2,
    Hard = 3
};

struct QuestionItem {
    string questionText;
    vector<string> options;
    int correctOption;
    Category category;
    string explanation;
    Difficulty difficulty;
};

struct ScoreEntry {
    string userName;
    string date;
    int score;
    int questionCounter;
};

string getCurrentDate();
string categoryToString(Category cat);
string difficultyToString(Difficulty diff);
Difficulty stringToDifficulty(string str);
Category stringToCategory(string str);
Category intToCategory(int ID);
int readValidInt(int min, int max);