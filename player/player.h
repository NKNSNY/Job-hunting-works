#pragma once
#include "gameobject.h"
#include "CModel.h"
#include"player_anim.h"
#include "player_anim_data.h"
#include "player_chip.h"

class Player :public GameObject
{
public:

    // オブジェクト名
    enum PLAYERPARTS
    {
        HIP ,			// 腰
        BODY ,			// 胴体
        HEAD ,		// 頭
        ARMR1 ,		// 右上腕
        ARML1 ,		// 左上腕
        LEGR1 ,		// 右太もも
        LEGL1 ,		// 左太もも
        ARMR2 ,
        ARML2 ,
        LEGR2 ,
        LEGL2 ,
        ARMR3 ,
        ARML3 ,
        LEGR3 ,
        LEGL3 ,
        NONE ,			// なし
        END ,			// データなし
        PARTSMAX
    };

    // 構造体型タグ
    struct	PlayerInitData
    {
        Player::PLAYERPARTS		ParentObjectNo;		// 親オブジェクトＮｏ
        Player::PLAYERPARTS		ModelNo;					// モデル番号
        DirectX::XMFLOAT3	FirstPosition;		// 最初の位置
        DirectX::XMFLOAT3	FirstAngle;			// 最初の角度
    };

    // プレイヤーのモデル名リスト
    struct	PlayerModelData
    {
        Player::PLAYERPARTS		ModelNo;					// モデル番号
        const char * XfileName;										// Ｘファイル名
    };

    // 初期配置データ
    static PlayerInitData	ObjectInitData [];

    // モデルファイル名リスト
    static PlayerModelData			XFileData [];

    // モデルセット
    void SetModel(CModel * p , int idx)
    {
        m_models [idx] = p;
    }

    // オーバーロード
    bool Init();

    bool Init(int stage_width , int player_y);
    void Draw();
    void Update(int camera_pos);
    void Finalize();

    // ステージの高さの情報をセット
    void SetPlayerStageTop(int y , int x , int stage_top);
    // ステージが登れるかどうかセット
    void SetClimbFlg(int y , int x , bool fall_flg);

    PlayerAnimation m_player_anim;          // プレイヤーのアニメーション関連

    PlayerChip m_player_chip;                  // プレイヤーがどこにいるか

    int m_player_camera_pos;                   // カメラからのプレイヤーの情報
    int m_player_stage_width;                  // ステージの幅
    int m_player_hight;                           // プレイヤーの現在の高さ

    bool m_player_climb_flg5 [7][7];          // プレイヤーが登れるか

    int m_walk_time;                               // 歩く時間
    DirectX::XMFLOAT3 m_walk_start_pos;   // 歩き始める場所
    DirectX::XMFLOAT3 m_walk_end_pos;     // 歩き終わる場所
    DirectX::XMFLOAT3 m_move_direction;   // 移動量

    int m_player_direction;                       // プレイヤーの向き
    int m_standby_direction;                     // シフトを押した時のプレイヤーの向き

    bool m_player_qube_move_flg;              // プレイヤーがキューブを動かしたか

    int m_player_hp;                               // プレイヤーのHP

    bool m_player_crush_flg;                     // プレイヤーが潰されたかどうか

private:
    void UpdateLocalpose();				// ローカルポーズを更新する
    void CaliculateParentChildMtx();	// 親子関係を考慮した行列を作成
    static bool m_modelloadflag;		// モデルを読み込んだかどうか
    CModel * m_models [PLAYERPARTS::PARTSMAX];
    DirectX::XMFLOAT4X4			m_mtxlocalpose [PARTSMAX];	// 自分のことだけを考えた行列
    DirectX::XMFLOAT4X4			m_mtxParentChild [PARTSMAX];	// 親子関係を考慮した行列

    float						m_speed = 0.0f;				// スピード
    DirectX::XMFLOAT3			m_angle;					// 回転角

    // プレイヤーの動く処理
    void MovePlayer(CharChipInt3 move_direction);

    //int m_idx = 0;

};