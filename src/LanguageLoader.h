#pragma once

#include <map>
#include <string>


using namespace std;

class LanguageLoader {
    public:
    map<string, string> load(string filename);
};