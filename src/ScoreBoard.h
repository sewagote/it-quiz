#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include "utils.h"
#include "ConsoleUI.h"

using namespace std;

class ScoreBoard {
    private:
        vector<ScoreEntry> scores;

    public:
        void clear() { scores.clear(); }
        void load(string filename);
        void save(string filename);
        void addEntry(ScoreEntry entry);
        void display(ConsoleUI& ui);
};