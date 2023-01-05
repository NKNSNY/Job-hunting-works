#pragma once

#include <vector>

#include "qube.h"

struct ReturnUI
{
    int player_hp;
    int stage_score;
    int color_change_score;
};

class Stage
{
public:

    // ステージの幅、高さ、落下距離、生存時間、落下速度を入力（上限　幅 7　高さ 20）
    static bool Init(int stage_width , int stage_hight , int fall_time , int survival_time , int fall_speed);
    static bool Update();
    static bool Draw();
    static void Finalize();

    // 設定した割合分キューブが落下
    static bool StageRateUpdate(int stage_qube_rate);
    // プレイヤーの位置の色を変える
    static ReturnUI ChangeColor(DirectX::XMFLOAT3 stage_player_pos);
    // プレイヤーが動かしたキューブを入れ替える
    static bool ChangeQubePos(DirectX::XMFLOAT3 before_pos , DirectX::XMFLOAT3 after_pos);
    // プレイヤーが潰されているか
    static bool CrushPlayer(DirectX::XMFLOAT3 stage_player_pos , int move_time);

    // ステージのトップを取得
    static int GetStageTop(int y , int x);
    // キューブが落下し終えてるか取得
    static bool GetStageFallFlg(int y , int x);

private:

    // キューブの番号を取得(横幅 , 高さ , 縦幅)
    static int GetQubeNumber(DirectX::XMFLOAT3 number)
    {
        return (number.z * m_stage_width) + number.x + (number.y * pow(m_stage_width , 2));
    }
    // キューブの番号を取得(横幅 , 高さ , 縦幅)
    static int GetQubeNumber(float number_x , float number_y , float number_z)
    {
        return (number_z * m_stage_width) + number_x + (number_y * pow(m_stage_width , 2));
    }

    // ステージの大きさ　[高さ][縦幅][横幅]
    static int m_stage [20][7][7];

    static int m_stage_width;           // ステージの横幅
    static int m_stage_hight;           // ステージの縦幅

    static int m_stage_bottom;         // ステージの現在の一番下
    static int m_stage_top [7][7];    // ステージの現在の高さの情報

    static int m_random_width;        // 横の落下位置
    static int m_random_hight;        // 縦の落下位置
    static int m_random_top;          // ランダムで選ばれた位置の高さ

    static int m_create_bottom;      // 落下高さの上限を上げていく

    static int m_stage_color;          // 現在のステージの色
    static bool m_stage_color_flg_x [20][7];        // 横一列の色を変えるフラグ
    static bool m_stage_color_flg_y [20][7];        // 縦一列の色を変えるフラグ
    static bool m_stage_color_reset_flg;             // 色をリセットするフラグ

    static int m_next_add_score;                      // 色が変わった時に増える数値
    static int m_now_add_score;                       // 現在の増えるスコア

};