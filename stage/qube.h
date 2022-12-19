#pragma once

#include "gameobject.h"
#include "CModel.h"
#include "CBillBoard.h"

// キューブの種類
enum QubeType
{
    NORMAL_QUBE ,
    HEAL_QUBE ,
};

class Qube :public GameObject
{
public:

    // オーバーロード
    bool Init();

    bool Init(int qube_type_num);
    bool Update();
    bool Draw();
    void Finalize();

    // プレイヤーに踏まれたところの色を変える
    bool ColorUpdate(int color_num);
    // 上にキューブがあるなら影が変化
    bool ShadowUpdate(int fall_distance , int first_fall_distance);
    // 移動によるテクスチャの変更
    bool ChangeTexture(QubeType qube_type);

    // 縦幅、横幅、高さの順で入れる
    bool SetPos(DirectX::XMFLOAT3 pos);
    // 落下距離、生存時間、落下速度の変化幅
    bool SetFall(int fall_distance , int survival_time , int fall_speed);

    int m_fall_distance;               // 落下距離
    int m_survival_time;              // 残っている時間
    int m_fall_speed;                  // 落下速度
    bool m_fall_flg;                    // 落下するか否か
    int m_first_survival_time;      // 元の残ってる時間
    int m_first_fall_distance;      // 元の落下距離

    bool m_shadow_create_flg;     // 影を出すかどうか

    DirectX::XMFLOAT3 m_before_qube_pos;        // キューブの動く前の位置
    DirectX::XMFLOAT3 m_after_qube_pos;         // キューブの動いた後の位置
    int m_move_qube_time;                              // キューブの線形補間

    bool m_move_qube_flg;                              // 動かすキューブの位置にキューブは落ちて来ているか

    QubeType m_qube_type;                            // キューブの種類

private:

    const char * XfileName;

    static bool m_modelloadflg;

    CModel * m_model;

    CBillBoard m_qube_texture [6];          // キューブのテクスチャ
    CBillBoard m_qube_alpha [5];             // 時間経過で黒ずむ
    CBillBoard m_qube_shadow;               // 落下の影

};