#include "QuestionLoader.h"
#include "json.hpp"
#include <fstream>
using json = nlohmann::json;
using namespace std;

vector<QuestionItem> QuestionLoader::load(string filename) {
    vector<QuestionItem> questions;
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Не удалось открыть файл" << endl;
        return questions;
    }
    try {
        json data = json::parse(file);
        for (auto& item : data["questions"]) {
            string text = item["text"];
            vector<string> options = item["options"].get<vector<string>>();
            int correct = item["correct"];
            string category = item["category"];
            string explanation = item["explanation"];
            Difficulty difficulty = stringToDifficulty(item["difficulty"]);
            questions.push_back({text, options, correct, stringToCategory(category), explanation, difficulty});
        }
    } catch (json::parse_error& error) {
        cerr << "JSON parse error: " << error.what() << endl;
    }
    return questions;
}