#pragma once

#include "CBillBoard.h"
#include "quad2d.h"
#include "custom_status.h"

class Custom
{
public:

    void CustomLoad();

    void CustomInit();
    CustomPlus CustomUpdate();
    void CustomDraw();
    void CustomFinalize();

private:

    CBillBoard m_custom;

    Quad2D m_choose_box [6];

    Quad2D m_go_play;
    Quad2D m_go_title;
    Quad2D m_arrow;

    int m_choose_pos;
    bool m_choose_flg;
    bool m_choose_alpha_flg;         // trueはプラス , falseはマイナス
    float m_choose_alpha_time;      // alpha値を増減
    int m_choose_height;               // どこを選んでいるのか（縦）
    int m_choose_wight [6];           // どこを選んでいるのか（横）

    CustomPlus m_csp;

};