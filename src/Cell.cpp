#include "Cell.h"

Cell::Cell() : mine(false), adjacentMines(0), revealed(false), flagged(false) {}

Cell::~Cell() {}
// หากช่องนี้ไม่ถูกตั้งธง จะเปิดช่อง และคืนค่าผลว่าเป็นระเบิดหรือไม่
bool Cell::reveal()
{
    if (!flagged)
        revealed = true;
    return mine;
}
// ตรวจสอบว่าเป็นระเบิดหรือไม่
bool Cell::isMine() const { return mine; }
// สลับสถานะธง (วางธง/เอาธงออก) ถ้าช่องยังไม่ถูกเปิด
void Cell::toggleFlag()
{
    if (!revealed)
        flagged = !flagged;
}
bool Cell::isRevealed() const { return revealed; }  // ตรวจสอบว่าช่องถูกเปิดหรือยัง
bool Cell::isFlagged() const { return flagged; } // ตรวจสอบว่าช่องถูกตั้งธงหรือไม่
int Cell::getAdjacentMines() const { return adjacentMines; } // คืนค่าจำนวนระเบิดรอบข้าง
void Cell::setAdjacentMines(int count) { adjacentMines = count; }// ตั้งค่าจำนวนระเบิดรอบข้าง
void Cell::setMine(bool m) { mine = m; }
 // ตั้งค่าว่าช่องนี้เป็นระเบิดหรือไม่