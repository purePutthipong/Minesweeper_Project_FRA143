#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H
// คลาส abstract สำหรับวัตถุในเกมทุกชนิด เช่น Cell หรือ MineCell
class GameObject
{
public:
    virtual ~GameObject() {}
    virtual bool reveal() = 0;                    // เมธอดสำหรับเปิดวัตถุ
    virtual bool isMine() const = 0;              // ตรวจสอบว่ามีระเบิดหรือไม่
    virtual void toggleFlag() = 0;                // สลับสถานะธง
    virtual bool isRevealed() const = 0;          // ตรวจสอบว่าวัตถุถูกเปิดหรือยัง
    virtual bool isFlagged() const = 0;           // ตรวจสอบว่ามีธงหรือไม่
    virtual int getAdjacentMines() const = 0;     // จำนวนระเบิดรอบข้าง
    virtual void setAdjacentMines(int count) = 0; // ตั้งค่าจำนวนระเบิดรอบข้าง
};

#endif
