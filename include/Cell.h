#ifndef CELL_H
#define CELL_H

#include "GameObject.h" // คลาส Cell สืบทอดมาจาก GameObject ใช้แทนช่องในเกม Minesweeper

class Cell : public GameObject
{
protected:
    bool mine;         // true ถ้าในช่องนี้มีระเบิด
    int adjacentMines; // จำนวนระเบิดรอบๆ ช่องนี้
    bool revealed;     // true ถ้าช่องนี้ถูกเปิดแล้ว
    bool flagged;      // true ถ้ามีธงปักไว้

public:
    Cell();
    virtual ~Cell();

    virtual bool reveal() override;                    // เมธอดเปิดช่อง ถ้าเปิดแล้วจะคืนค่า true
    virtual bool isMine() const override;              // เช็คว่าช่องนี้มีระเบิดหรือไม่
    virtual void toggleFlag() override;                // สลับสถานะปักธง
    virtual bool isRevealed() const override;          // ตรวจสอบว่าช่องนี้ถูกเปิดแล้วหรือยัง
    virtual bool isFlagged() const override;           // ตรวจสอบว่าช่องนี้ถูกปักธงไว้หรือไม่
    virtual int getAdjacentMines() const override;     // ตรวจสอบว่าช่องนี้ถูกปักธงไว้หรือไม่
    virtual void setAdjacentMines(int count) override; // กำหนดจำนวนระเบิดรอบๆ ช่องนี้
    void setMine(bool m);
};

#endif
