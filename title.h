#pragma once
#include "stage/qube.h"
#include "CBillBoard.h"
#include "quad2d.h"

class Title
{
public:

    void TitleInit();
    int TitleUpdate();
    void TitleDraw();
    void TitleFinalize();

    // タイトル画面のデータ
    void TitlePreparationData();
    // タイトル画面の準備
    void TitlePreparation();

    bool m_ready_flg;                   // タイトル画面の準備が完了しているか

private:

    Qube m_title_qube;

    CBillBoard m_background;

    Quad2D m_title;
    Quad2D m_normal_play;
    Quad2D m_custom_play;
    Quad2D m_challenge_play;
    Quad2D m_choose_arrow;

    int m_choose_pos;
    bool m_choose_move_flg;         // trueはプラス , falseはマイナス
    bool m_choose_alpha_flg;         // trueはプラス , falseはマイナス
    float m_choose_alpha_time;      // alpha値を増減

    int m_preparation_num;          // タイトル画面の種類
    int m_qube_move_time;           // キューブが動ける時間
    int m_title_move_time;           // タイトルが動ける時間
    DirectX::XMFLOAT3 m_qube_pos;       // 変化していくキューブの位置
    DirectX::XMFLOAT3 m_title_pos;      // 変化していくタイトルの位置

};
