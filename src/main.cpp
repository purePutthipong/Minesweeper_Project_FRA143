#include "Game.h"
#include <iostream>
#include <limits>
#include <sstream>

#define RED "\033[31m"
#define RESET "\033[0m"

#ifdef _WIN32
#include <windows.h>
#endif

void enableVirtualTerminalProcessing() {
#ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) {
        return;
    }
    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode)) {
        return;
    }
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if (!SetConsoleMode(hOut, dwMode)) {
        return;
    }
#endif
}

int main()
{
    enableVirtualTerminalProcessing(); // Enable ANSI escape codes for Windows
    char playAgainChoice;
    do
    {
        int width, height, mines;
// แสดงเมนูเลือกความยาก
        std::cout << "==== MINESWEEPER ====\n";
        std::cout << "Select difficulty:\n";
        std::cout << "1. Easy (8x8, 10 mines)\n";
        std::cout << "2. Medium (12x12, 20 mines)\n";
        std::cout << "3. Hard (16x16, 40 mines)\n";
        
        int choice;
        while (true)
        {
            std::cout << "Choice: ";
            std::cin >> choice;

            if (std::cin.fail()) {
                std::cin.clear(); // clear error flags
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard invalid input
                std::cout << RED << "Invalid input. Please enter a number." << RESET << "\n";
                continue;
            }
// ตั้งค่าขนาดกระดานและจำนวนกับดักตามระดับความยาก
            if (choice == 1)
            {
                width = height = 8, mines = 10;
                break;
            }
            else if (choice == 2)
            {
                width = height = 12, mines = 20;
                break;
            }
            else if (choice == 3)
            {
                width = height = 16, mines = 40;
                break;
            }
            else
                std::cout << RED << "Invalid input. Please enter a number between 1-3." << RESET << "\n";
        }
// สร้างออบเจกต์เกมด้วยพารามิเตอร์ที่เลือกไว้
        Game game(width, height, mines);
 // วนลูปจนกว่าจะชนกับระเบิดหรือชนะ
        while (!game.isGameOver() && !game.isWin())
        {
            game.printBoard();
            std::cout << "Enter command (r x y = reveal, f x y = flag): ";

            std::string line;
            // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Replaced by std::ws
            std::getline(std::cin >> std::ws, line);

            std::istringstream iss(line);
            char cmd;
            int y, x; // Note: User inputs y then x, but typical array access is x (row) then y (col)

            if (!(iss >> cmd >> y >> x))
            {
            // หากป้อนคำสั่งไม่ตรงตามเงื่อนไขcommand,column,rowจะปริ้น
                std::cout << RED << "Invalid command format. Please try again, e.g. r 1 2 or f 0 3" << RESET << "\n";
                continue;
            }

            if (!game.isValid(x, y)) // Assuming Game class uses x for row, y for col internally
            {
                std::cout << RED << "Invalid position. Coordinates out of bounds." << RESET << "\n";
                continue;
            }

        if (cmd == 'r') // เปิดช่อง
            if (cmd == 'r') 
                game.revealCell(x, y);
            else if (cmd == 'f') // วางหรือเอาธงออก
                game.toggleFlag(x, y);
            else
                std::cout << RED << "Unknown command. Please use 'r' to reveal or 'f' to flag." << RESET << "\n";
        }

        game.printBoard(true); // แสดงกระดานทั้งหมดเมื่อจบเกม
        if (game.isGameOver())
            std::cout << "\033[31mYou hit a mine! Game Over!\n\033[0m"; // Added RED color
        else
            std::cout << "\033[32mCongratulations! You win!\n\033[0m"; // Added GREEN color

        std::cout << "Your Score: " << game.getScore() << " points\n";

        std::cout << "\nPlay again? (y/n): ";
        std::cin >> playAgainChoice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear buffer

    } while (playAgainChoice == 'y' || playAgainChoice == 'Y'); // เพิ่มคำสั่งเมื่อหลังจากโดนระเบิดหรือชนะเกม ให้โชว์กระดานทั้งหมด จำนวนแต้ม และคำสั่งให้เล่นใหม่หรือไม่

    std::cout << "Thanks for playing!\n";
    return 0;
}
