#include "player.h"
#include	"dx11mathutil.h"
#include	"ModelMgr.h"
#include	"CDirectInput.h"

// モンスターの親子関係及び初期位置・初期角度を定義したデータ
Player::PlayerInitData Player::ObjectInitData [] =
{
    // 親                    // モデル番号                    // 初期位置                 // 初期角度
    // 注意 : 必ず子供より親が先に並ぶこと
    {Player::NONE,         Player::HIP,                    {0.0f,20.0f,0.0f},              {0,0,0}},
    {Player::HIP,            Player::BODY,                  {0.0f,1.3f,-0.3f},           {0,0,0}},
    {Player::BODY,         Player::HEAD,                  {0.0f,4.5f,0.0f},        {0,0,0}},

    {Player::BODY,         Player::ARMR1,               {2.0f,4.0f,-0.8f},         {0,0,0}},
    {Player::BODY,         Player::ARML1,                {-2.0f,4.0f,-0.8f},          {0,0,0}},
    {Player::HIP,            Player::LEGR1,                {0.9f,-0.3f,0.0f},          {0,0,0}},
    {Player::HIP,			  Player::LEGL1,				  {-0.9f,-0.1f,0.0f},			  {0,0,0}},

    {Player::ARMR1,       Player::ARMR2,               {1.9f,-2.5f,0.0f},       {0,0,0}},
    {Player::ARML1,       Player::ARML2,                {-2.0f,-2.6f,0.0f},         {0,0,0}},

    {Player::LEGR1,        Player::LEGR2,                 {0.5f,-4.4f,0.0f},      {0,0,0}},
    {Player::LEGL1,        Player::LEGL2,                  {-0.5f,-4.7f,0.0f},        {0,0,0}},

    {Player::ARMR2,       Player::ARMR3,               {1.8f,-1.3f,1.0f},       {0,0,0}},
    {Player::ARML2,       Player::ARML3,                {-1.8f,-1.1f,1.0f},         {0,0,0}},

    {Player::LEGR2,        Player::LEGR3,                 {0.3f,-3.7f,-0.5f},      {0,0,0}},
    {Player::LEGL2,        Player::LEGL3,                  {-0.3f,-3.5f,-0.5f},        {0,0,0}},

     {Player::END,          Player::END,                       {0.0f,0.0f,0.0f,},                {0,0,0}},     // 終了
};

// モデルファイル名リスト
Player::PlayerModelData Player::XFileData [] =
{
    {Player::HIP,              "assets/model/player/player_hip.x"},
    {Player::BODY,            "assets/model/player/player_body.x"},
    {Player::HEAD,            "assets/model/player/player_head.x"},
    {Player::ARMR1,          "assets/model/player/player_l_arm01.x"},
    {Player::ARML1,          "assets/model/player/player_r_arm01.x"},
    {Player::LEGR1,           "assets/model/player/player_l_leg01.x"},
    {Player::LEGL1,           "assets/model/player/player_r_leg01.x"},
    {Player::ARMR2,          "assets/model/player/player_l_arm02.x"},
    {Player::ARML2,          "assets/model/player/player_r_arm02.x"},
    {Player::LEGR2,           "assets/model/player/player_l_leg02.x"},
    {Player::LEGL2,            "assets/model/player/player_r_leg02.x"},
    {Player::ARMR3,          "assets/model/player/player_l_arm03.x"},
    {Player::ARML3,          "assets/model/player/player_r_arm03.x"},
    {Player::LEGR3,           "assets/model/player/player_l_leg03.x"},
    {Player::LEGL3,            "assets/model/player/player_r_leg03.x"},

    {Player::END,nullptr}
};

// モデルを読み込んだかどうか
bool Player::m_modelloadflag = false;

bool Player::Init()
{
    return false;
}

bool Player::Init(int stage_width , int player_y)
{
    bool sts = true;

    // 行列初期化
    DX11MtxIdentity(m_mtx);					// モデルを読み込む

    // 読み込みが完了していなければ読み込む
    if (Player::m_modelloadflag == false)
    {
        // モデル読み込み（プレイヤー）
        for (int i = 0; i < static_cast<int>(Player::PARTSMAX) - 2; i++)
        {
            sts = ModelMgr::GetInstance().LoadModel(
                Player::XFileData [i].XfileName ,	// ファイル名 
                "shader/vs.hlsl" ,				// 頂点シェーダー
                "shader/psline.hlsl" ,				// ピクセルシェーダー
                "assets/model/player/");				// テクスチャの格納フォルダ
            if (!sts)
            {
                char str [128];
                sprintf_s<128>(str , "%s" , Player::XFileData [i].XfileName);
                MessageBox(nullptr , str , "load error" , MB_OK);
            }
        }
        Player::m_modelloadflag = true;
    }

    // モデルポインターをセット
    for (int i = 0; i < static_cast<int>(Player::PARTSMAX) - 2; i++)
    {
        SetModel(ModelMgr::GetInstance().GetModelPtr(XFileData [i].XfileName) , i);
    }

    m_player_anim.SetAnim(PlayerAnimation::STANDBY);
    //m_player_anim.SetAnim(PlayerAnimation::CLIMB);

    m_player_stage_width = stage_width;
    m_player_hight = player_y;

    m_player_chip.Init(m_player_stage_width , m_player_hight);

    ObjectInitData [0].FirstPosition = { ((float) m_player_stage_width - 1) * 10.0f ,
        (float) m_player_hight * 20 , ((float) m_player_stage_width - 1) * -10.0f };

    // プレイヤ行列初期化(初期位置)（自分のことだけを考えた行列を作成）
    for (int i = 0; i < static_cast<int>(PLAYERPARTS::PARTSMAX) - 2; i++)
    {
        DX11MakeWorldMatrix(m_mtxlocalpose [i] , ObjectInitData [i].FirstAngle , ObjectInitData [i].FirstPosition);
        m_mtxlocalpose [i] = PlayerAnimData::GetLocalData(m_player_anim.m_anim_num , m_mtxlocalpose [i] , i);
    }

    // 親子関係を考慮した行列を計算する
    CaliculateParentChildMtx();					// 親の行列を掛け算してグローバルポーズを作る

    m_walk_time = 31;

    m_player_direction = 0;
    m_standby_direction = 0;
    m_player_qube_move_flg = false;

    m_player_hp = 10000;

    m_player_crush_flg = false;

    return sts;
}

void Player::Draw()
{
    // モデル描画
    for (int i = 0; i < static_cast<int>(PLAYERPARTS::PARTSMAX) - 2; i++)
    {
        m_models [i]->Draw(m_mtxParentChild [i]);
    }
}

void Player::Update(int camera_pos)
{
    m_player_camera_pos = camera_pos;

    // ローカルポーズを更新する
    UpdateLocalpose();

    // 親子関係を考慮した行列を計算する
    CaliculateParentChildMtx();

    // 上限を設ける
    if (m_player_hp > 10000)
    {
        m_player_hp = 10000;
    }

    // プレイヤーが潰されたら体力大幅減少
    if (m_player_crush_flg)
    {
        m_player_hp -= 5000;
        m_player_chip.m_char_chip_pos.y++;
        m_player_hight++;
        m_mtxlocalpose [0]._42 += 20.0f;
        m_player_crush_flg = false;
    }

    // 時間経過で体力減少
    if (m_player_hp > 0)
    {
        m_player_hp--;
    }
}

void Player::Finalize()
{
}

void Player::SetPlayerStageTop(int y , int x , int stage_top , int stage_bottom)
{
    if (m_player_chip.m_char_chip [y][x] != 99)
    {
        m_player_chip.m_char_chip [y][x] = stage_top - (m_player_hight - 1);
    }

    m_player_stage_bottom = stage_bottom;
}

void Player::SetClimbFlg(int y , int x , bool fall_flg)
{
    m_player_climb_flg5 [y][x] = fall_flg;
}

XMFLOAT3 Player::GetPlayerPos()
{
    XMFLOAT3 pos {};
    pos.x = m_mtxlocalpose [0]._41;
    pos.y = m_mtxlocalpose [0]._42;
    pos.z = m_mtxlocalpose [0]._43;

    return pos;
}

void Player::UpdateLocalpose()
{
    // 各パーツの回転角度(前フレームからの変位量)
    XMFLOAT3			partsangle [static_cast<int>(PLAYERPARTS::PARTSMAX)];
    XMFLOAT3			partstrans [static_cast<int>(PLAYERPARTS::PARTSMAX)];

    // 角度と移動量を初期化
    for (int i = 0; i < static_cast<int>(PLAYERPARTS::PARTSMAX); i++)
    {
        partsangle [i].x = 0.0f;
        partsangle [i].y = 0.0f;
        partsangle [i].z = 0.0f;
        partstrans [i].x = 0.0f;
        partstrans [i].y = 0.0f;
        partstrans [i].z = 0.0f;
    }

    // プレイヤーの角度、位置の変更でアニメーション
    for (int i = 0; i < 15; i++)
    {
        partsangle [i] = m_player_anim.UpdateAngle(i);
        partstrans [i] = m_player_anim.UpdateTrans(i);
    }

    // 自動的に待機モーションへ
    if (m_player_anim.m_animation_time > 0)
    {
        m_player_anim.m_animation_time--;
        if (m_player_anim.m_animation_time == 0)
        {
            m_player_anim.SetAnim(PlayerAnimation::STANDBY);
            //m_player_anim.SetAnim(PlayerAnimation::CLIMB);
            for (int i = 0; i < static_cast<int>(PLAYERPARTS::PARTSMAX) - 2; i++)
            {
                m_mtxlocalpose [i] = PlayerAnimData::GetLocalData(m_player_anim.m_anim_num , m_mtxlocalpose [i] , i);
            }
        }
    }

    // 今の位置
    XMFLOAT3 now_pos {};
    now_pos.x = m_player_chip.m_char_chip_pos.x * 20;
    now_pos.y = m_player_chip.m_char_chip_pos.y * 20;
    now_pos.z = m_player_chip.m_char_chip_pos.z * -20;

    // 入力したら移動する（左）
    if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_LEFT) && m_walk_time == 31)
    {
        m_player_direction = 1;
        if ((m_standby_direction == 0) || (m_standby_direction == m_player_direction))
        {
            DX11MakeWorldMatrix(m_mtxlocalpose [0] , ObjectInitData [0].FirstAngle , now_pos);
            partsangle [0].y = 270.0f + (90.0f * (m_player_camera_pos - 1));
        }

        // カメラのポジションで移動位置を変える
        switch (m_player_camera_pos)
        {
            case 1:
                MovePlayer({ -1,0,0 });
                break;
            case 2:
                MovePlayer({ 0,0,-1 });
                break;
            case 3:
                MovePlayer({ 1,0,0 });
                break;
            case 4:
                MovePlayer({ 0,0,1 });
                break;
        }
    }

    if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_RIGHT) && m_walk_time == 31)
    {
        m_player_direction = 3;
        if ((m_standby_direction == 0) || (m_standby_direction == m_player_direction))
        {
            DX11MakeWorldMatrix(m_mtxlocalpose [0] , ObjectInitData [0].FirstAngle , now_pos);
            partsangle [0].y = 90.0f + (90.0f * (m_player_camera_pos - 1));
        }

        switch (m_player_camera_pos)
        {
            case 1:
                MovePlayer({ 1,0,0 });
                break;
            case 2:
                MovePlayer({ 0,0,1 });
                break;
            case 3:
                MovePlayer({ -1,0,0 });
                break;
            case 4:
                MovePlayer({ 0,0,-1 });
                break;
        }
    }

    if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_UP) && m_walk_time == 31)
    {
        m_player_direction = 2;
        if ((m_standby_direction == 0) || (m_standby_direction == m_player_direction))
        {
            DX11MakeWorldMatrix(m_mtxlocalpose [0] , ObjectInitData [0].FirstAngle , now_pos);
            partsangle [0].y = 0.0f + (90.0f * (m_player_camera_pos - 1));
        }

        switch (m_player_camera_pos)
        {
            case 1:
                MovePlayer({ 0,0,-1 });
                break;
            case 2:
                MovePlayer({ 1,0,0 });
                break;
            case 3:
                MovePlayer({ 0,0,1 });
                break;
            case 4:
                MovePlayer({ -1,0,0 });
                break;
        }
    }

    if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_DOWN) && m_walk_time == 31)
    {
        m_player_direction = 4;
        if ((m_standby_direction == 0) || (m_standby_direction == m_player_direction))
        {
            DX11MakeWorldMatrix(m_mtxlocalpose [0] , ObjectInitData [0].FirstAngle , now_pos);
            partsangle [0].y = 180.0f + (90.0f * (m_player_camera_pos - 1));
        }

        switch (m_player_camera_pos)
        {
            case 1:
                MovePlayer({ 0,0,1 });
                break;
            case 2:
                MovePlayer({ -1,0,0 });
                break;
            case 3:
                MovePlayer({ 0,0,-1 });
                break;
            case 4:
                MovePlayer({ 1,0,0 });
                break;
        }
    }

    // キューブを動かすモード
    if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_LSHIFT))
    {
        if (m_standby_direction == 0)
        {
            m_standby_direction = m_player_direction;
        }
    }
    else if (CDirectInput::GetInstance().CheckKeyBufferRelease(DIK_LSHIFT))
    {
        m_standby_direction = 0;
    }

    // 移動の線形補間
    if (m_walk_time < 31)
    {
        m_mtxlocalpose [0]._41 = m_walk_start_pos.x * (1.0f - (m_walk_time / 30.0f)) + m_walk_end_pos.x * (m_walk_time / 30.0f);
        m_mtxlocalpose [0]._42 = m_walk_start_pos.y * (1.0f - (m_walk_time / 30.0f)) + m_walk_end_pos.y * (m_walk_time / 30.0f);
        m_mtxlocalpose [0]._43 = m_walk_start_pos.z * (1.0f - (m_walk_time / 30.0f)) + m_walk_end_pos.z * (m_walk_time / 30.0f);

        m_walk_time++;

        if (m_walk_time == 15)
        {
            m_player_chip.m_char_chip_pos.x = m_move_direction.x;
            m_player_chip.m_char_chip_pos.y = m_move_direction.y;
            m_player_chip.m_char_chip_pos.z = m_move_direction.z;
        }

        if (m_walk_time == 31)
        {
            m_player_qube_move_flg = false;
        }
    }

    // パーツの角度ローカルポーズを表す行列を計算
    XMFLOAT4X4 partsmtx;
    for (int i = 0; i < 15; i++)
    {
        DX11MakeWorldMatrix(partsmtx , partsangle [i] , partstrans [i]);
        DX11MtxMultiply(m_mtxlocalpose [i] , partsmtx , m_mtxlocalpose [i]);
    }

}

void Player::CaliculateParentChildMtx()
{

    // ループを使わない

    // 腰
    m_mtxParentChild [Player::HIP] = m_mtxlocalpose [Player::HIP];

    // 胴体
    DX11MtxMultiply(m_mtxParentChild [Player::BODY] , m_mtxlocalpose [Player::BODY] , m_mtxlocalpose [Player::HIP]);

    // 頭
    DX11MtxMultiply(m_mtxParentChild [Player::HEAD] , m_mtxlocalpose [Player::HEAD] , m_mtxlocalpose [Player::BODY]);
    DX11MtxMultiply(m_mtxParentChild [Player::HEAD] , m_mtxParentChild [Player::HEAD] , m_mtxlocalpose [Player::HIP]);

    // 右上腕
    DX11MtxMultiply(m_mtxParentChild [Player::ARMR1] , m_mtxlocalpose [Player::ARMR1] , m_mtxlocalpose [Player::BODY]);
    DX11MtxMultiply(m_mtxParentChild [Player::ARMR1] , m_mtxParentChild [Player::ARMR1] , m_mtxlocalpose [Player::HIP]);

    // 左上腕
    DX11MtxMultiply(m_mtxParentChild [Player::ARML1] , m_mtxlocalpose [Player::ARML1] , m_mtxlocalpose [Player::BODY]);
    DX11MtxMultiply(m_mtxParentChild [Player::ARML1] , m_mtxParentChild [Player::ARML1] , m_mtxlocalpose [Player::HIP]);

    // 右ふともも
    DX11MtxMultiply(m_mtxParentChild [Player::LEGR1] , m_mtxlocalpose [Player::LEGR1] , m_mtxlocalpose [Player::HIP]);

    // 左ふともも
    DX11MtxMultiply(m_mtxParentChild [Player::LEGL1] , m_mtxlocalpose [Player::LEGL1] , m_mtxlocalpose [Player::HIP]);

    // 右下腕
    DX11MtxMultiply(m_mtxParentChild [Player::ARMR2] , m_mtxlocalpose [Player::ARMR2] , m_mtxlocalpose [Player::ARMR1]);
    DX11MtxMultiply(m_mtxParentChild [Player::ARMR2] , m_mtxParentChild [Player::ARMR2] , m_mtxlocalpose [Player::BODY]);
    DX11MtxMultiply(m_mtxParentChild [Player::ARMR2] , m_mtxParentChild [Player::ARMR2] , m_mtxlocalpose [Player::HIP]);

    // 左下腕
    DX11MtxMultiply(m_mtxParentChild [Player::ARML2] , m_mtxlocalpose [Player::ARML2] , m_mtxlocalpose [Player::ARML1]);
    DX11MtxMultiply(m_mtxParentChild [Player::ARML2] , m_mtxParentChild [Player::ARML2] , m_mtxlocalpose [Player::BODY]);
    DX11MtxMultiply(m_mtxParentChild [Player::ARML2] , m_mtxParentChild [Player::ARML2] , m_mtxlocalpose [Player::HIP]);

    // 右ふくらはぎ
    DX11MtxMultiply(m_mtxParentChild [Player::LEGR2] , m_mtxlocalpose [Player::LEGR2] , m_mtxlocalpose [Player::LEGR1]);
    DX11MtxMultiply(m_mtxParentChild [Player::LEGR2] , m_mtxParentChild [Player::LEGR2] , m_mtxlocalpose [Player::HIP]);

    // 左ふくらはぎ
    DX11MtxMultiply(m_mtxParentChild [Player::LEGL2] , m_mtxlocalpose [Player::LEGL2] , m_mtxlocalpose [Player::LEGL1]);
    DX11MtxMultiply(m_mtxParentChild [Player::LEGL2] , m_mtxParentChild [Player::LEGL2] , m_mtxlocalpose [Player::HIP]);

    // 右指
    DX11MtxMultiply(m_mtxParentChild [Player::ARMR3] , m_mtxlocalpose [Player::ARMR3] , m_mtxlocalpose [Player::ARMR2]);
    DX11MtxMultiply(m_mtxParentChild [Player::ARMR3] , m_mtxParentChild [Player::ARMR3] , m_mtxlocalpose [Player::ARMR1]);
    DX11MtxMultiply(m_mtxParentChild [Player::ARMR3] , m_mtxParentChild [Player::ARMR3] , m_mtxlocalpose [Player::BODY]);
    DX11MtxMultiply(m_mtxParentChild [Player::ARMR3] , m_mtxParentChild [Player::ARMR3] , m_mtxlocalpose [Player::HIP]);

    // 左指
    DX11MtxMultiply(m_mtxParentChild [Player::ARML3] , m_mtxlocalpose [Player::ARML3] , m_mtxlocalpose [Player::ARML2]);
    DX11MtxMultiply(m_mtxParentChild [Player::ARML3] , m_mtxParentChild [Player::ARML3] , m_mtxlocalpose [Player::ARML1]);
    DX11MtxMultiply(m_mtxParentChild [Player::ARML3] , m_mtxParentChild [Player::ARML3] , m_mtxlocalpose [Player::BODY]);
    DX11MtxMultiply(m_mtxParentChild [Player::ARML3] , m_mtxParentChild [Player::ARML3] , m_mtxlocalpose [Player::HIP]);

    // 右足つま先
    DX11MtxMultiply(m_mtxParentChild [Player::LEGR3] , m_mtxlocalpose [Player::LEGR3] , m_mtxlocalpose [Player::LEGR2]);
    DX11MtxMultiply(m_mtxParentChild [Player::LEGR3] , m_mtxParentChild [Player::LEGR3] , m_mtxlocalpose [Player::LEGR1]);
    DX11MtxMultiply(m_mtxParentChild [Player::LEGR3] , m_mtxParentChild [Player::LEGR3] , m_mtxlocalpose [Player::HIP]);

    // 左足つま先
    DX11MtxMultiply(m_mtxParentChild [Player::LEGL3] , m_mtxlocalpose [Player::LEGL3] , m_mtxlocalpose [Player::LEGL2]);
    DX11MtxMultiply(m_mtxParentChild [Player::LEGL3] , m_mtxParentChild [Player::LEGL3] , m_mtxlocalpose [Player::LEGL1]);
    DX11MtxMultiply(m_mtxParentChild [Player::LEGL3] , m_mtxParentChild [Player::LEGL3] , m_mtxlocalpose [Player::HIP]);

}

void Player::MovePlayer(CharChipInt3 move_direction)
{
    // 一歩進んだ位置
    XMFLOAT3 player_pos {};
    player_pos.x = m_player_chip.m_char_chip_pos.x + move_direction.x;
    player_pos.y = m_player_chip.m_char_chip_pos.y + move_direction.y;
    player_pos.z = m_player_chip.m_char_chip_pos.z + move_direction.z;

    // 端っこ
    if (player_pos.x <= -1)
    {
        return;
    }
    else if (player_pos.x >= m_player_stage_width)
    {
        return;
    }
    else if (player_pos.z <= -1)
    {
        return;
    }
    else if (player_pos.z >= m_player_stage_width)
    {
        return;
    }

    // シフトを押していると押す引くモードになる
    if (m_standby_direction == 0)
    {
        // 一つ降りる
        if ((m_player_chip.m_char_chip [(int) player_pos.z][(int) player_pos.x] == -1) ||
            ((m_player_chip.m_char_chip [(int) player_pos.z][(int) player_pos.x] == 0) &&
                (m_player_climb_flg5 [(int) player_pos.z][(int) player_pos.x])))
        {
            m_walk_start_pos.x = m_player_chip.m_char_chip_pos.x * 20;
            m_walk_start_pos.y = m_player_chip.m_char_chip_pos.y * 20;
            m_walk_start_pos.z = m_player_chip.m_char_chip_pos.z * -20;
            m_walk_end_pos.x = player_pos.x * 20;
            m_walk_end_pos.y = (player_pos.y - 1) * 20;
            m_walk_end_pos.z = player_pos.z * -20;

            m_walk_time = 0;

            m_player_hight--;

            m_player_chip.m_char_chip [m_player_chip.m_char_chip_pos.z][m_player_chip.m_char_chip_pos.x] = 0;
            m_player_chip.m_char_chip [(int) player_pos.z][(int) player_pos.x] = 99;

            m_move_direction.x = player_pos.x;
            m_move_direction.y = player_pos.y - 1;
            m_move_direction.z = player_pos.z;

            return;
        }

        // 通常移動
        if (m_player_chip.m_char_chip [(int) player_pos.z][(int) player_pos.x] == 0)
        {
            m_walk_start_pos.x = m_player_chip.m_char_chip_pos.x * 20;
            m_walk_start_pos.y = m_player_chip.m_char_chip_pos.y * 20;
            m_walk_start_pos.z = m_player_chip.m_char_chip_pos.z * -20;
            m_walk_end_pos.x = player_pos.x * 20;
            m_walk_end_pos.y = player_pos.y * 20;
            m_walk_end_pos.z = player_pos.z * -20;

            m_walk_time = 0;

            m_player_chip.m_char_chip [m_player_chip.m_char_chip_pos.z][m_player_chip.m_char_chip_pos.x] = 0;
            m_player_chip.m_char_chip [(int) player_pos.z][(int) player_pos.x] = 99;

            m_move_direction.x = player_pos.x;
            m_move_direction.y = player_pos.y;
            m_move_direction.z = player_pos.z;

            m_player_anim.SetAnim(PlayerAnimation::WALK);
            for (int i = 0; i < static_cast<int>(PLAYERPARTS::PARTSMAX) - 2; i++)
            {
                m_mtxlocalpose [i] = PlayerAnimData::GetLocalData(m_player_anim.m_anim_num , m_mtxlocalpose [i] , i);
            }
        }

        // 登るよ
        if (((m_player_chip.m_char_chip [(int) player_pos.z][(int) player_pos.x] == 1) &&
            (!m_player_climb_flg5 [(int) player_pos.z][(int) player_pos.x])) ||
            (m_player_chip.m_char_chip [(int) player_pos.z][(int) player_pos.x] == 2) &&
            (m_player_climb_flg5 [(int) player_pos.z][(int) player_pos.x]))
        {
            m_walk_start_pos.x = m_player_chip.m_char_chip_pos.x * 20;
            m_walk_start_pos.y = m_player_chip.m_char_chip_pos.y * 20;
            m_walk_start_pos.z = m_player_chip.m_char_chip_pos.z * -20;
            m_walk_end_pos.x = player_pos.x * 20;
            m_walk_end_pos.y = (player_pos.y + 1) * 20;
            m_walk_end_pos.z = player_pos.z * -20;

            m_walk_time = 0;

            m_player_hight++;

            m_player_chip.m_char_chip [m_player_chip.m_char_chip_pos.z][m_player_chip.m_char_chip_pos.x] = 0;
            m_player_chip.m_char_chip [(int) player_pos.z][(int) player_pos.x] = 99;

            m_move_direction.x = player_pos.x;
            m_move_direction.y = player_pos.y + 1;
            m_move_direction.z = player_pos.z;
        }
        // 下を通るよ
        else if ((m_player_chip.m_char_chip [(int) player_pos.z][(int) player_pos.x] == 1) &&
            (m_player_climb_flg5 [(int) player_pos.z][(int) player_pos.x]))
        {
            m_walk_start_pos.x = m_player_chip.m_char_chip_pos.x * 20;
            m_walk_start_pos.y = m_player_chip.m_char_chip_pos.y * 20;
            m_walk_start_pos.z = m_player_chip.m_char_chip_pos.z * -20;
            m_walk_end_pos.x = player_pos.x * 20;
            m_walk_end_pos.y = player_pos.y * 20;
            m_walk_end_pos.z = player_pos.z * -20;

            m_walk_time = 0;

            m_player_chip.m_char_chip [m_player_chip.m_char_chip_pos.z][m_player_chip.m_char_chip_pos.x] = 0;
            m_player_chip.m_char_chip [(int) player_pos.z][(int) player_pos.x] = 99;

            m_move_direction.x = player_pos.x;
            m_move_direction.y = player_pos.y;
            m_move_direction.z = player_pos.z;

            m_player_anim.SetAnim(PlayerAnimation::WALK);
            for (int i = 0; i < static_cast<int>(PLAYERPARTS::PARTSMAX) - 2; i++)
            {
                m_mtxlocalpose [i] = PlayerAnimData::GetLocalData(m_player_anim.m_anim_num , m_mtxlocalpose [i] , i);
            }
        }
    }
    else
    {
        // 進行方向と反対
        XMFLOAT3 reverse_player_pos {};
        reverse_player_pos.x = m_player_chip.m_char_chip_pos.x - move_direction.x;
        reverse_player_pos.y = m_player_chip.m_char_chip_pos.y - move_direction.y;
        reverse_player_pos.z = m_player_chip.m_char_chip_pos.z - move_direction.z;

        // 二歩先
        XMFLOAT3 next_player_pos {};
        next_player_pos.x = m_player_chip.m_char_chip_pos.x + (move_direction.x * 2);
        next_player_pos.y = m_player_chip.m_char_chip_pos.y + (move_direction.y * 2);
        next_player_pos.z = m_player_chip.m_char_chip_pos.z + (move_direction.z * 2);

        // オーバーフラグ
        bool over_flg = false;

        if (next_player_pos.x <= -1)
        {
            over_flg = true;
            next_player_pos.x = player_pos.x;
        }
        else if (next_player_pos.x >= m_player_stage_width)
        {
            over_flg = true;
            next_player_pos.x = player_pos.x;
        }
        else if (next_player_pos.z <= -1)
        {
            over_flg = true;
            next_player_pos.z = player_pos.z;
        }
        else if (next_player_pos.z >= m_player_stage_width)
        {
            over_flg = true;
            next_player_pos.z = player_pos.z;
        }

        // プレイヤーの先にキューブがあり、かつ
        // プレイヤーの二歩先に何もない、もしくは
        // プレイヤーの二歩先にまだキューブが落ちてきていない、もしくは
        // プレイヤーの先にキューブがあり、かつ
        // オーバーフラグ（二歩先がオーバーしている）がtrue
        if ((((m_player_chip.m_char_chip [(int) player_pos.z][(int) player_pos.x] == 1) &&
            (!m_player_climb_flg5 [(int) player_pos.z][(int) player_pos.x])) ||
            ((m_player_chip.m_char_chip [(int) player_pos.z][(int) player_pos.x] == 2) &&
                (m_player_climb_flg5 [(int) player_pos.z][(int) player_pos.x])) &&
            ((m_player_chip.m_char_chip [(int) next_player_pos.z][(int) next_player_pos.x] == 0) ||
                ((m_player_chip.m_char_chip [(int) next_player_pos.z][(int) next_player_pos.x] == 1) &&
                    (m_player_climb_flg5 [(int) next_player_pos.z][(int) next_player_pos.x])))) ||
            ((((m_player_chip.m_char_chip [(int) player_pos.z][(int) player_pos.x] == 1) &&
                (!m_player_climb_flg5 [(int) player_pos.z][(int) player_pos.x])) ||
                ((m_player_chip.m_char_chip [(int) player_pos.z][(int) player_pos.x] == 2) &&
                    (m_player_climb_flg5 [(int) player_pos.z][(int) player_pos.x])))) &&
            (over_flg))
        {
            if (m_standby_direction == m_player_direction)
            {
                m_walk_start_pos.x = m_player_chip.m_char_chip_pos.x * 20;
                m_walk_start_pos.y = m_player_chip.m_char_chip_pos.y * 20;
                m_walk_start_pos.z = m_player_chip.m_char_chip_pos.z * -20;
                m_walk_end_pos.x = player_pos.x * 20;
                m_walk_end_pos.y = player_pos.y * 20;
                m_walk_end_pos.z = player_pos.z * -20;

                m_walk_time = 0;

                m_player_chip.m_char_chip [m_player_chip.m_char_chip_pos.z][m_player_chip.m_char_chip_pos.x] = 0;
                m_player_chip.m_char_chip [(int) player_pos.z][(int) player_pos.x] = 99;

                m_player_qube_move_flg = true;

                m_move_direction.x = player_pos.x;
                m_move_direction.y = player_pos.y;
                m_move_direction.z = player_pos.z;

                // ここに押すアニメーションをセット
                //m_player_anim.SetAnim(PlayerAnimation::WALK);
                //for (int i = 0; i < static_cast<int>(PLAYERPARTS::PARTSMAX) - 2; i++)
                //{
                //    m_mtxlocalpose [i] = PlayerAnimData::GetLocalData(m_player_anim.m_anim_num , m_mtxlocalpose [i] , i);
                //}
            }
        }
        // プレイヤーの後ろに何もなく　かつ
        // プレイヤーの進行方向の逆　かつ
        // プレイヤーの進行方向ではなく　かつ
        // プレイヤーの目の前にキューブがある　かつ
        // キューブが落ちてきている
        else if (((m_player_chip.m_char_chip [(int) player_pos.z][(int) player_pos.x] == 0) ||
            ((m_player_chip.m_char_chip [(int) player_pos.z][(int) player_pos.x] == 1) &&
                (m_player_climb_flg5 [(int) player_pos.z][(int) player_pos.x]))) &&
            ((m_standby_direction % 2 == m_player_direction % 2) &&
                (m_standby_direction != m_player_direction)) &&
            (((m_player_chip.m_char_chip [(int) reverse_player_pos.z][(int) reverse_player_pos.x] == 1) &&
                (!m_player_climb_flg5 [(int) reverse_player_pos.z][(int) reverse_player_pos.x])) ||
                ((m_player_chip.m_char_chip [(int) reverse_player_pos.z][(int) reverse_player_pos.x] == 2) &&
                    (m_player_climb_flg5 [(int) reverse_player_pos.z][(int) reverse_player_pos.x]))))
        {
            m_walk_start_pos.x = m_player_chip.m_char_chip_pos.x * 20;
            m_walk_start_pos.y = m_player_chip.m_char_chip_pos.y * 20;
            m_walk_start_pos.z = m_player_chip.m_char_chip_pos.z * -20;
            m_walk_end_pos.x = player_pos.x * 20;
            m_walk_end_pos.y = player_pos.y * 20;
            m_walk_end_pos.z = player_pos.z * -20;

            m_walk_time = 0;

            m_player_chip.m_char_chip [m_player_chip.m_char_chip_pos.z][m_player_chip.m_char_chip_pos.x] = 0;
            m_player_chip.m_char_chip [(int) player_pos.z][(int) player_pos.x] = 99;

            m_player_qube_move_flg = true;

            m_move_direction.x = player_pos.x;
            m_move_direction.y = player_pos.y;
            m_move_direction.z = player_pos.z;

            // ここに引くアニメーションをセット
            //m_player_anim.SetAnim(PlayerAnimation::WALK);
            //for (int i = 0; i < static_cast<int>(PLAYERPARTS::PARTSMAX) - 2; i++)
            //{
            //    m_mtxlocalpose [i] = PlayerAnimData::GetLocalData(m_player_anim.m_anim_num , m_mtxlocalpose [i] , i);
            //}
        }
    }
}
