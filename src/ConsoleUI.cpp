#include "ConsoleUI.h"

void ConsoleUI::printDivider() {
    std::cout << std::string(32, '-') << std::endl;
};

void ConsoleUI::printHeader(std::string title) {
    int width = std::max(30, (int)title.size() + 4);
    std::string border(width, '=');
    std::cout << "+" << border << "+" << std::endl;
    int padding = (width - (int)title.size()) / 2;
    std::cout << "|" << std::string(padding, ' ') << title << std::string(width - padding - (int)title.size(), ' ') << "|" << std::endl;
    std::cout << "+" << border << "+" << std::endl;
};

void ConsoleUI::printProgressBar(int current, int total) {
    int width = 20;
    int filled = width * (current/double(total));
    std::cout << "[";
    for (size_t i = 0; i < width; i++) {
        if ( i < filled) {
            std::cout << "=";
        }
        else if (i == filled) {
            std::cout << ">";
        }
        else {
            std::cout << ".";
        }
    }
    std::cout << "] " << current << "/" << total << std::endl;
};