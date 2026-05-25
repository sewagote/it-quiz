#include "ScoreBoard.h"
#include "json.hpp"
#include <fstream>
using json = nlohmann::json;


void ScoreBoard::load(string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Не удалось открыть файл" << endl;
        return;
    }
    try {
        json data = json::parse(file);
        for (auto& item : data["scores"]) {
            ScoreEntry entry;
            string userName = item["userName"];
            string date = item["date"];
            int score = item["score"];
            int questionCounter = item["questionCounter"];
            entry.userName = userName;
            entry.date = date;
            entry.score = score;
            entry.questionCounter = questionCounter;
            scores.push_back(entry);
        }
    }
    catch(json::parse_error& error) {
        cerr << "JSON parse error:" << error.what() << endl;
    }
}

void ScoreBoard::save(string filename) {
    json data;
    data["scores"] = json::array();

    for (auto& entry : scores) {
        json object;
        object["userName"] = entry.userName;
        object["date"] = entry.date;
        object["score"] = entry.score;
        object["questionCounter"] = entry.questionCounter;
        data["scores"].push_back(object);
    }
    ofstream file(filename);
    file << data.dump(4);
    file.close();
}

void ScoreBoard::addEntry(ScoreEntry entry) {
    scores.push_back(entry);
    sort(scores.begin(), scores.end(), [](const ScoreEntry& a, const ScoreEntry& b) {
        return a.score > b.score;
    });
    if (scores.size() > 5) {
        scores.resize(5);
    }
}

void ScoreBoard::display(ConsoleUI& ui) {
    ui.printHeader("LEADERBOARD");
    ui.printDivider();
    for (size_t i = 0; i < scores.size(); i++) {
        cout << i+1 << "." << scores[i].userName << " " << scores[i].score << "pts " << scores[i].questionCounter << "q " << scores[i].date << endl;
    }
    ui.printDivider();
}