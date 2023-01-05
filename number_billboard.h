#pragma once

#include "CBillBoard.h"

class Num_Billboard
{
public:

    void Init();
    void Update(DirectX::XMFLOAT3 player_pos , int camera_pos , int score);
    void Draw();
    void Finalize();

private:

    CBillBoard m_number_billboard [6];

    int m_draw_time;

};
