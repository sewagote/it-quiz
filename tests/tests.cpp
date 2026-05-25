#include "utils.h"
#include "QuestionLoader.h"
#include "ScoreBoard.h"
#include "ConsoleUI.h"
#include <iostream>
using namespace std;

int passed = 0;
int failed = 0;

void check(bool condition, string testName) {
    if (condition) {
        cout << "✓ " << testName << endl;
        passed++;
    } else {
        cout << "✗ " << testName << endl;
        failed++;
    }
}

void testStringToCategory() {
    check(stringToCategory("Networking") == Category::Networking, "stringToCategory: Networking");
    check(stringToCategory("Programming") == Category::Programming, "stringToCategory: Programming");
    check(stringToCategory("Hardware") == Category::Hardware, "stringToCategory: Hardware");
    check(stringToCategory("OC") == Category::OC, "stringToCategory: OC");
    check(stringToCategory("Нетворкинг") == Category::Networking, "stringToCategory: Нетворкинг (RU)");
    check(stringToCategory("Программирование") == Category::Programming, "stringToCategory: Программирование (RU)");
    check(stringToCategory("Аппаратное обеспечение") == Category::Hardware, "stringToCategory: Аппаратное обеспечение (RU)");
}

void testStringToDifficulty() {
    check(stringToDifficulty("Easy") == Difficulty::Easy, "stringToDifficulty: Easy");
    check(stringToDifficulty("Medium") == Difficulty::Medium, "stringToDifficulty: Medium");
    check(stringToDifficulty("Hard") == Difficulty::Hard, "stringToDifficulty: Hard");
    check(stringToDifficulty("Unknown") == Difficulty::Hard, "stringToDifficulty: Unknown defaults to Hard");
}

void testGetCurrentDate() {
    string date = getCurrentDate();
    check(date.size() == 10, "getCurrentDate: length is 10");
    check(date[4] == '-', "getCurrentDate: first dash at index 4");
    check(date[7] == '-', "getCurrentDate: second dash at index 7");
    check(date.substr(0, 4) == "2026", "getCurrentDate: year is 2026");
}

void testQuestionLoader() {
    QuestionLoader loader;
    vector<QuestionItem> questions = loader.load("data/questions.json");
    check(questions.size() > 0, "QuestionLoader: loads questions");
    check(questions.size() >= 20, "QuestionLoader: loads at least 20 questions");
    check(!questions[0].questionText.empty(), "QuestionLoader: first question has text");
    check(questions[0].options.size() == 4, "QuestionLoader: first question has 4 options");
    check(questions[0].correctOption >= 1 && questions[0].correctOption <= 4, "QuestionLoader: correct option in range 1-4");
    vector<QuestionItem> empty = loader.load("nonexistent.json");
    check(empty.size() == 0, "QuestionLoader: returns empty vector for missing file");
}

void testScoreBoardAddEntry() {
    ScoreBoard board;
    ScoreEntry e1;
    e1.userName = "Alice";
    e1.score = 10;
    e1.questionCounter = 5;
    e1.date = "2026-05-10";
    board.addEntry(e1);
    ScoreEntry e2;
    e2.userName = "Bob";
    e2.score = 20;
    e2.questionCounter = 5;
    e2.date = "2026-05-10";
    board.addEntry(e2);
    ScoreEntry e3;
    e3.userName = "Charlie";
    e3.score = 15;
    e3.questionCounter = 5;
    e3.date = "2026-05-10";
    board.addEntry(e3);
    board.save("test_scores.json");
    ScoreBoard board2;
    board2.load("test_scores.json");
    ConsoleUI ui;
    board2.display(ui);
    check(true, "ScoreBoard: save and load without crash");
}

void testScoreBoardTopFive() {
    ScoreBoard board;
    for (int i = 1; i <= 7; i++) {
        ScoreEntry e;
        e.userName = "Player" + to_string(i);
        e.score = i * 10;
        e.questionCounter = 5;
        e.date = "2026-05-10";
        board.addEntry(e);
    }
    board.save("test_scores_top5.json");
    ScoreBoard board2;
    board2.load("test_scores_top5.json");
    check(true, "ScoreBoard: top-5 save without crash");
}

int main() {
    cout << "=== Running tests ===" << endl << endl;

    cout << "--- stringToCategory ---" << endl;
    testStringToCategory();

    cout << "\n--- stringToDifficulty ---" << endl;
    testStringToDifficulty();

    cout << "\n--- getCurrentDate ---" << endl;
    testGetCurrentDate();

    cout << "\n--- QuestionLoader ---" << endl;
    testQuestionLoader();

    cout << "\n--- ScoreBoard ---" << endl;
    testScoreBoardAddEntry();
    testScoreBoardTopFive();

    cout << "\n===================" << endl;
    cout << passed << " passed, " << failed << " failed" << endl;

    return failed > 0 ? 1 : 0;
}