#include "Quiz.h"
#include "json.hpp"
using namespace std;
using json = nlohmann::json;

Language Quiz::selectLanguage() {
    ui.printHeader("IT QUIZ");
    cout << endl;
    cout << "Выберите язык / Choose language:" << endl;
    ui.printDivider();
    cout << "1) Русский" << endl;
    cout << "2) English" << endl;
    ui.printDivider();
    int choiceLanguage = readValidInt(1, 2);
    return choiceLanguage == 1 ? Language::Russian : Language::English;
}

int Quiz::countByCategory(Category cat) {
    int count = 0;
    for (int i = 0; i < (int)questions.size(); i++) {
        if (questions[i].category == cat) count++;
    }
    return count;
}

void Quiz::loadQuestions(string filename) {
    questions = loader.load(filename);
}

void Quiz::loadLanguage(string filename) {
    lang = langLoader.load(filename);
}

int Quiz::menu() {
    ui.printHeader("IT QUIZ");
    cout << endl;
    ui.printDivider();
    cout << "0) " << lang["menuExit"] << endl;
    cout << "1) " << lang["menuStart"] << endl;
    cout << "2) " << lang["menuLeaderboard"] << endl;
    ui.printDivider();
    return readValidInt(0, 2);
}


void Quiz::printCategories() {
    ui.printDivider();
    cout << "1) " << lang["category_Networking"] << endl;
    cout << "2) " << lang["category_Programming"] << endl;
    cout << "3) " << lang["category_Hardware"] << endl;
    cout << "4) " << lang["category_OC"] << endl;
    ui.printDivider();
}   


vector<int> Quiz::readCategoriesIds() {
    cout << lang["selectCategories"] << " ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string userInput;
    getline(cin, userInput);
    stringstream parser(userInput);
    int categoryId;
    vector<int> selectedCategories;
    while (parser >> categoryId) {
        if (categoryId >= 1 && categoryId <= 4) {
            selectedCategories.push_back(categoryId);
        }
    }
    return selectedCategories;
}

map<Category, int> Quiz::selectCategoriesWithCount() {
    map<Category, int> categoryValue;
    for (const auto& cat : {Category::Networking, Category::Programming, Category::Hardware, Category::OC}) {
        categoryValue[cat] = 0;
    }
    printCategories();
    vector<int> selectedCategories = readCategoriesIds();
    for (const auto& catID : selectedCategories) {
        int maxN = countByCategory(intToCategory(catID));
        cout << lang["enterN"] << " " << lang["category_" + categoryToString(intToCategory(catID))] << " (1-" << maxN << "): ";
        int N = readValidInt(1, maxN);
        categoryValue[intToCategory(catID)] = N;
    }
    return categoryValue;
}

void Quiz::showLeaderboard() {
    scoreboard.clear();
    scoreboard.load("data/scores.json");
    scoreboard.display(ui);
}

void Quiz::saveResult(int total) {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << lang["enterName"];
    string userName;
    cin >> userName;

    ScoreEntry entry;
    entry.userName = userName;
    entry.score = score;
    entry.questionCounter = total;
    entry.date = getCurrentDate();

    scoreboard.addEntry(entry);
    scoreboard.save("data/scores.json");
}

void Quiz::runTest(map<Category, int> categoryValue) {
    score = 0;
    streak = 0;
    random_device rd;
    mt19937 g(rd());
    shuffle(questions.begin(), questions.end(), g);
    map<Category, int> showCount;
    int total = 0;
    for (const auto& pair : categoryValue) {
        total += pair.second;
    }
    int current = 0;
    for (const auto& q : questions) {
        if (categoryValue.count(q.category) == 0) continue;
        if (showCount[q.category] >= categoryValue[q.category]) continue;

        showCount[q.category]++;
        current++;
        ui.printHeader(lang["category_" + categoryToString(q.category)]);
        cout << lang["question"] << q.questionText << endl;
        ui.printDivider();
        ui.printProgressBar(current-1, total);
        for (unsigned int i = 0; i < q.options.size(); i++) {
            cout << i + 1 << ") " << q.options[i] << endl;
        }
        ui.printDivider();
        int userChoice = readValidInt(1, q.options.size());
        if (userChoice == q.correctOption) {
            cout << "✓ " << lang["correctAnswer"] << " (+" << (int)q.difficulty << ")" << endl;
            streak++;
            if (streak >= 3) {
                cout << lang["streakBonus"] << streak << "! (+ " << (int)q.difficulty + 1 << ")" << endl;
                score += (int)q.difficulty + 1; 
            }
            else {
                score += (int)q.difficulty;
            }
        } else {
            cout << "✗ " << lang["incorrectAnswer"] << endl;
            cout << lang["explanation"] << q.explanation << endl;
            cout << lang["correctAnswer"] << ": " << q.options[q.correctOption - 1] << endl;
            streak = 0;
        }
        ui.printDivider();
    }
    cout << endl;
    ui.printHeader(lang["result"] + to_string(score));
    saveResult(total);
}