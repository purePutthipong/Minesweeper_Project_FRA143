#ifndef GAME_H
#define GAME_H

#include <vector>
#include <memory>
#include <utility>
#include "GameObject.h"

class Game
{
private:
    int width, height, mines;
    int flagsUsed;
    int score;
    bool gameOver;
    bool firstClick = true;
    std::pair<int, int> explodedCell;                            // ตำแหน่งของระเบิดที่ถูกเปิด
    std::vector<std::vector<std::shared_ptr<GameObject>>> board; // กระดานของเกม (เก็บ Cell หรือ MineCell โดยใช้ smart pointer)

    void placeMines(int safeX, int safeY); // วางระเบิดบนกระดาน โดยยกเว้นตำแหน่งที่ผู้เล่นคลิกครั้งแรก (safeX, safeY)
    void calculateAdjacency();             // คำนวณจำนวนระเบิดที่อยู่รอบๆ ช่องแต่ละช่อง
    int countAdjacentMines(int x, int y);  // นับจำนวนระเบิดรอบๆ ช่องที่กำหนด
    int revealEmpty(int x, int y);         // เปิดช่องว่างที่ไม่มีระเบิดรอบๆ อย่างต่อเนื่อง (recursive)

public:
    Game(int w, int h, int m);                     // Constructor: สร้างเกมโดยกำหนดขนาดกระดาน และจำนวนระเบิด
    bool revealCell(int x, int y);                 // เปิดช่องที่ตำแหน่ง (x, y) ถ้าคลิกระเบิดจะคืนค่า true
    void toggleFlag(int x, int y);                 // สลับสถานะธงที่ตำแหน่ง (x, y)
    bool isValid(int x, int y) const;              // ตรวจสอบว่าตำแหน่ง (x, y) อยู่ในขอบเขตของกระดานหรือไม่
    bool isWin() const;                            // ตรวจสอบว่าผู้เล่นชนะหรือยัง (ไม่มีช่องที่ไม่เปิดซึ่งไม่ใช่ระเบิดเหลืออยู่)
    void printBoard(bool revealAll = false) const; // แสดงกระดานบนหน้าจอ (revealAll = true จะเปิดทุกช่อง)
    int getScore() const;                          // คืนค่าคะแนนปัจจุบัน
    bool isGameOver() const;                       // ตรวจสอบว่าสถานะเกมจบแล้วหรือไม่
};

#endif
