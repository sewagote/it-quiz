#pragma once
#ifndef CONSOLEUI_H
#define CONSOLEUI_H
#include <iostream>
#include <string>

class ConsoleUI {
    public:
    void printHeader(std::string title);
    void printDivider();
    void printProgressBar(int current, int total);
};
#endif