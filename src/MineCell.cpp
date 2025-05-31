#include "MineCell.h"
// สร้าง MineCell และตั้งให้ช่องนี้เป็นระเบิดทันที
MineCell::MineCell()
{
    setMine(true);
}
// เมื่อถูกเปิด จะตั้งค่าช่องว่าเปิดแล้ว และคืนค่า true เพื่อบอกว่าเป็นระเบิด
bool MineCell::reveal()
{
    revealed = true; // ช่องถูกเปิดแล้ว
    return true;     // คืน true เพราะช่องนี้เป็นระเบิด
}
