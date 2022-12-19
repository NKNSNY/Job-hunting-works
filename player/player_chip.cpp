#include "player_chip.h"

bool PlayerChip::Init(int stage_width , int player_y)
{
    for (int i = 0; i < stage_width; i++)
    {
        for (int j = 0; j < stage_width; j++)
        {
            // 初期位置は全て平面
            m_char_chip [i][j] = 0 - (player_y - 1);
        }
    }

    // 99はプレイヤーの現在位置
    m_char_chip [stage_width / 2][stage_width / 2] = 99;

    m_char_chip_pos.x = stage_width / 2;
    m_char_chip_pos.y = player_y;
    m_char_chip_pos.z = stage_width / 2;

    return true;
}

bool PlayerChip::Update()
{
    return false;
}

bool PlayerChip::Draw()
{
    return false;
}

bool PlayerChip::Finalize()
{
    return false;
}
