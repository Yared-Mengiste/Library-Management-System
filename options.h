#ifndef OPTIONS_H
#define OPTIONS_H

#include <iostream>
/* extra libraries */
#include <cstdlib> //for system("CLS")
#include <iomanip> //for centerText()
#include <chrono>  //for std::chrono
#include <thread>  //for std::this_thread::sleep_for
#include <string>  // for printLine
#include <windows.h> // for getConsoleWidth
#include <Limits>
#include "library.h"


int getConsoleWidth() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}

void centerText(const std::string& text) {
    int consoleWidth = getConsoleWidth();
    int padding = (consoleWidth - text.length()) / 2; // Calculate padding
    std::cout << std::string(padding, ' ') << text << std::endl; // Print centered text
}

void printLine(char character) {
    int length = getConsoleWidth();
    std::cout << std::string(length, character) << std::endl;
}



void displayMenu() {
    
}
void printTitle()
{
        printLine('=');
        centerText("\033[32mAbrehot Library\033[0m");
        printLine('=');
}

#endif // OPTIONS_H