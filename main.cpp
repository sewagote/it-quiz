#include "src/Quiz.h"
using namespace std;

int main()
{
    #ifdef _WIN32
    // Включает поддержку UTF-8 для консоли Windows
    system("chcp 65001 > nul"); 
    #endif
    Quiz myQuiz;
    Language lang = myQuiz.selectLanguage();
    if (lang == Language::Russian) {
        myQuiz.loadLanguage("data/lang_ru.json");
        myQuiz.loadQuestions("data/questions_ru.json");
    }
    else {
        myQuiz.loadLanguage("data/lang_eng.json");
        myQuiz.loadQuestions("data/questions.json");
    }
    int choice;
    do {
        choice = myQuiz.menu();
        if (choice == 1) {
            map<Category, int> selectedCategories = myQuiz.selectCategoriesWithCount();
            myQuiz.runTest(selectedCategories);
        }
        if (choice == 2) {
            myQuiz.showLeaderboard();
        }
    } while (choice != 0);
}