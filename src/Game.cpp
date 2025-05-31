#include "Game.h"
#include "Cell.h"
#include "MineCell.h"
#include <iostream>
#include <iomanip>
#include <random>
#include <ctime>
#include <algorithm>
#include <limits>

#define RED "\033[31m"
#define YELLOW "\033[33m"
#define RESET "\033[0m"
// Constructor: สร้างกระดานเปล่า ขนาด width x height และกำหนดจำนวนระเบิด
Game::Game(int w, int h, int m)
    : width(w), height(h), mines(m), flagsUsed(0), score(0), gameOver(false), explodedCell{-1, -1}
{
    board.resize(height, std::vector<std::shared_ptr<GameObject>>(width));
    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j)
            board[i][j] = std::make_shared<Cell>();
}
// วางระเบิดแบบสุ่ม ยกเว้นบริเวณรอบๆ จุดที่ผู้เล่นคลิกครั้งแรก
void Game::placeMines(int safeX, int safeY)
{
    std::vector<std::pair<int, int>> positions;

    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j)
        {
            if (std::abs(i - safeX) <= 1 && std::abs(j - safeY) <= 1)
                continue;
            positions.emplace_back(i, j);
        }
// สุ่มตำแหน่ง
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(positions.begin(), positions.end(), g);
// วางระเบิดตามจำนวนที่กำหนด
    for (int i = 0; i < mines; ++i)
    {
        auto [x, y] = positions[i];
        board[x][y] = std::make_shared<MineCell>();
    }
}
// นับจำนวนระเบิดรอบๆ ช่องที่ระบุ
int Game::countAdjacentMines(int x, int y)
{
    int count = 0;
    for (int i = -1; i <= 1; i++)
        for (int j = -1; j <= 1; j++)
        {
            int nx = x + i, ny = y + j;
            if (nx >= 0 && nx < height && ny >= 0 && ny < width &&
                board[nx][ny] && board[nx][ny]->isMine())
                count++;
        }
    return count;
}
// คำนวณและกำหนดจำนวนระเบิดรอบๆ สำหรับ Cell ทุกช่อง
void Game::calculateAdjacency()
{
    for (int x = 0; x < height; x++)
        for (int y = 0; y < width; y++)
            if (!board[x][y]->isMine())
                board[x][y]->setAdjacentMines(countAdjacentMines(x, y));
}
// เปิดช่องว่างต่อๆ กันแบบอัตโนมัติ เมื่อคลิกช่องที่ไม่มีระเบิดและรอบข้างก็ไม่มี
int Game::revealEmpty(int x, int y)
{
    int revealedCount = 0;
    // แก้โดยกำหนด 4 ทิศทาง บน ล่าง ซ้าย ขวา
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    for (int i = 0; i < 4; ++i)
    {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (nx >= 0 && ny >= 0 && nx < height && ny < width)
        {
            auto &cell = board[nx][ny];
            if (cell && !cell->isRevealed() && !cell->isMine())
            {
                cell->reveal();
                revealedCount++;
                if (cell->getAdjacentMines() == 0)
                    revealedCount += revealEmpty(nx, ny);
            }
        }
    }
    return revealedCount;
}
// ผู้เล่นคลิกเพื่อเปิดช่อง
bool Game::revealCell(int x, int y)
{
    if (!isValid(x, y) || board[x][y]->isRevealed() || board[x][y]->isFlagged())
        return false;

    if (firstClick)
    {
        placeMines(x, y);
        calculateAdjacency();
        firstClick = false;
    }

    bool hitMine = board[x][y]->reveal();

    if (hitMine)
    {
        explodedCell = {x, y};
        gameOver = true;
    }
    else
    {
        int revealedCount = 1; // Count the initially revealed cell
        if (board[x][y]->getAdjacentMines() == 0)
            revealedCount += revealEmpty(x, y);
        score += revealedCount * 10; // Add 10 points for each revealed cell
    }

    return hitMine;
}
// สำหรับปักหรือเอาธงออก
void Game::toggleFlag(int x, int y)
{
    if (!isValid(x, y))
        return;

    bool wasFlagged = board[x][y]->isFlagged();
    board[x][y]->toggleFlag();

    if (!wasFlagged && board[x][y]->isFlagged())
    {
        flagsUsed++;
        if (board[x][y]->isMine())
            score += 5;
        else
            score = std::max(0, score - 2);
    }
    else if (wasFlagged && !board[x][y]->isFlagged())
    {
        flagsUsed--;
    }
}

bool Game::isValid(int x, int y) const
{
    return x >= 0 && y >= 0 && x < height && y < width;
}

bool Game::isWin() const
{
    for (int x = 0; x < height; x++)
        for (int y = 0; y < width; y++)
            if (board[x][y] && !board[x][y]->isRevealed() && !board[x][y]->isMine())
                return false;
    return true;
}

void Game::printBoard(bool revealAll) const
{
    std::cout << "\nFlags: " << flagsUsed << "/" << mines << "\n\n   ";
    for (int y = 0; y < width; y++)
        std::cout << std::setw(2) << y;
    std::cout << "\n";

    for (int x = 0; x < height; x++)
    {
        std::cout << std::setw(2) << x << " ";
        for (int y = 0; y < width; y++)
        {
            const auto &cell = board[x][y];
            if (cell->isRevealed())
            {
                if (cell->isMine())
                {
                    if (x == explodedCell.first && y == explodedCell.second)
                        std::cout << RED << " B" << RESET; // Changed from X to B
                    else
                        std::cout << RED << " M" << RESET; // Changed from * to M
                }
                else
                {
                    std::cout << " " << cell->getAdjacentMines();
                }
            }
            else if (revealAll && cell->isMine())
            {
                if (x == explodedCell.first && y == explodedCell.second)
                    std::cout << RED << " B" << RESET; // Changed from X to B
                else
                    std::cout << RED << " M" << RESET; // Changed from * to M
            }
            else if (cell->isFlagged())
            {
                std::cout << YELLOW << " F" << RESET;
            }
            else
            {
                std::cout << " .";
            }
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}
// แสดงคะแนนที่ได้ในปัจจุบัน
int Game::getScore() const { return score; }
// ตรวจสอบว่าเกมจบหรือยัง
bool Game::isGameOver() const { return gameOver; }
