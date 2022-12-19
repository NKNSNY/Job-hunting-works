#pragma once

struct CharChipInt3
{
    int x;
    int y;
    int z;
};

class PlayerChip
{
public:

    bool Init(int stage_width , int player_y);
    bool Update();
    bool Draw();
    bool Finalize();

    // プレイヤーの位置と高さの差 100は使用しない
    int m_char_chip [7][7] = {};

    CharChipInt3 m_char_chip_pos;

};
