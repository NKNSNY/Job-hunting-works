#pragma once

#include <DirectxMath.h>

class PlayerAnimation
{
public:

    // アニメーションの種類
    enum ANIMATIONNUM
    {
        STANDBY ,           // 待機
        WALK ,               // 歩く
        CLIMB ,              // 登る
        DESCEND ,          // 降りる
        JUMP ,              // 飛び降りる
        SET ,                // 引く、押す
        HEAL ,               // 回復
        DAMAGE ,           // 潰される
        BLACKHOLE        // ブラックホール
    };

    // アニメーション更新処理
    DirectX::XMFLOAT3 UpdateAngle(int parts);
    DirectX::XMFLOAT3 UpdateTrans(int parts);

    // アニメーションを指定する
    void SetAnim(ANIMATIONNUM anim_num);

    // 指定された時間のアニメーション
    // どのパーツか
    // 0 で角度を返す、1 で位置を返す
    DirectX::XMFLOAT3 GetStandby(int parts , int angle_trans);      // 待機
    DirectX::XMFLOAT3 GetWalk(int parts , int angle_trans);          // 歩く
    DirectX::XMFLOAT3 GetClimb(int parts , int angle_trans);        // 登る

    // どのアニメーションか
    ANIMATIONNUM m_anim_num;

    // 現在のアニメーションの時間
    int m_animation_time;

};
