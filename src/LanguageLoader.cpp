#include "LanguageLoader.h"
#include "json.hpp"
#include <fstream>
#include <iostream>

using namespace std;

using json = nlohmann::json;

map<string,string> LanguageLoader::load(string filename) {
    map<string, string> lang;
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Не удалось открыть файл" << endl;
        return lang;
    }
    try {
        json data = json::parse(file);
        for (auto& [key, value] : data.items()) {
            if (key == "categories") {
                for (auto& [catKey, catValue] : value.items()) {
                    lang["category_" + catKey] = catValue;
                }
            } else {
                lang[key] = value;
            }
        }
    } catch (json::parse_error& error) {
        cerr << "Language file parse error: " << error.what() << endl;
    }
    return lang;
}