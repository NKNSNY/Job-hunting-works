#pragma once

#include "CBillBoard.h"
#include "quad2d.h"
#include "result_score.h"

class Result
{
public:

    void ResultLoad();

    void ResultInit(ResultScore rs);
    int ResultUpdate();
    void ResultDraw();
    void ResultFinalize();

private:

    CBillBoard m_result;
    CBillBoard m_result_clear;

    Quad2D m_go_title;
    Quad2D m_retry;
    Quad2D m_choose_arrow;
    
    Quad2D m_score_num [6];
    Quad2D m_small_color [8];
    Quad2D m_big_color [8];
    Quad2D m_go_title_clear;

    int m_choose_pos;
    bool m_choose_alpha_flg;         // trueはプラス , falseはマイナス
    float m_choose_alpha_time;      // alpha値を増減

    ResultScore m_result_score;

    int m_small_num;
    int m_big_num;

};
