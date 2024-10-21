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


void handleChoice(int choice);
Library newLibrary("data\\library_data.txt","data\\members.txt");

int main() {
    int choice;

    // Display the menu in a loop
    while (true) {
        newLibrary.options();
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (std::cin.fail()) { // Check for invalid input
            std::cin.clear(); // Clear the error state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid input
            std::cout << "\033[31mInvalid input! Please enter a number (1-9).\033[0m\n";
            continue; // Restart the loop
        }

        // Handle the choice
        if (choice == 12) {
            std::cout << "Exiting the program. Goodbye!\n";
            std::cout << "Press Enter to continue...";
            std::cin.ignore();
            std::cin.get();
            break;
        } else {
            handleChoice(choice);
        }
    }

    return 0;
}
void handleChoice(int choice) {
    switch (choice) {
        case 1:
            std::cout << "Adding Book...\n";
            newLibrary.addBook();
            break;
        case 2:           
            std::cout << "Adding Member...\n";
            newLibrary.addMember();
            break;
        case 3:
            std::cout << "Borrowing Book...\n";
            newLibrary.borrowBook();
            break;
        case 4:
            std::cout << "Displaying Borrowed Books...\n";
            newLibrary.borrowedBooks();

            break;
        case 5:
            std::cout << "Deleting Book...\n";
            newLibrary.deleteBook();
            break;
        case 6:
            std::cout << "Display Books...\n";
            newLibrary.displayBooks();
            break;
        case 7:
            std::cout << "Display Members...\n";
            newLibrary.displayMembers();
            break;
        case 8:
            std::cout << "Edit Member Profile...\n";
            newLibrary.editMember();            
            break;
        case 9:
            std::cout << "Return Book...\n";
            newLibrary.returnBook();
            break;
        case 10:
	        std::cout << "Searching Book...\n";
            newLibrary.searchBook();
            break;
        case 11:
            std::cout << "Searching Member...\n";
            newLibrary.searchMember();
            break;
        default:
            std::cout << "\033[31mInvalid input! Input range should be (1-12)!\033[0m\n";
            break;
    }

}
