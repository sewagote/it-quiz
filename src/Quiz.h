#pragma once
#include "utils.h"
#include "ConsoleUI.h"
#include "ScoreBoard.h"
#include "QuestionLoader.h"
#include "LanguageLoader.h"
#include <algorithm>
#include <random>
#include <fstream>
#include <stdexcept>
#include <sstream>

class Quiz {
    private:
    int score = 0;
    int streak = 0;
    ConsoleUI ui;
    ScoreBoard scoreboard;
    map <string, string> lang;
    int countByCategory(Category cat);
    vector<QuestionItem> questions;
    QuestionLoader loader;
    LanguageLoader langLoader;
    void saveResult(int total);
    void printCategories();
    vector<int> readCategoriesIds();



    public:
    Language selectLanguage();
    void loadLanguage(string filename);
    void loadQuestions(string filename);
    void showLeaderboard();
    map<Category, int> selectCategoriesWithCount();
    void runTest(map<Category, int> categoryValue);
    int menu();
};
