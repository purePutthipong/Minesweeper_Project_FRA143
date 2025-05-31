#ifndef MINE_CELL_H
#define MINE_CELL_H

#include "Cell.h"
// คลาส MineCell คือ Cell ที่มีระเบิดแน่นอน
class MineCell : public Cell
{
public:
    MineCell();
    virtual bool reveal() override;
    // เมธอด override reveal สำหรับ MineCell จะมีพฤติกรรมเฉพาะเมื่อเปิด
};

#endif
