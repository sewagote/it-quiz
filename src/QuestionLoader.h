#pragma once
#include <vector>
#include <string>
#include "utils.h"

class QuestionLoader {
    public:
    vector<QuestionItem> load(string filename);
};