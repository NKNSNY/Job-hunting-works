#pragma once

#include "CBillBoard.h"
#include "quad2d.h"

class Result
{
public:

    void ResultLoad();

    // ゲームオーバー時
    void ResultInit();
    int ResultUpdate();
    void ResultDraw();
    void ResultFinalize();

    // ゲームクリア時

private:

    CBillBoard m_result;

    Quad2D m_go_title;
    Quad2D m_retry;
    Quad2D m_choose_arrow;

    int m_choose_pos;
    bool m_choose_alpha_flg;         // trueはプラス , falseはマイナス
    float m_choose_alpha_time;      // alpha値を増減

};
