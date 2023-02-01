#include <stdlib.h>
#include <cinttypes>
#include "dx11util.h"
#include "CModel.h"
#include "CCamera.h"
#include "DX11Settransform.h"
#include "dx11mathutil.h"
#include "Application.h"
#include "CDirectInput.h"
#include "updatespherecamera.h"
#include "BoundingSphere.h"
#include "myimgui.h"
#include "ModelMgr.h"
#include "StageHit.h"
#include "player/player.h"
#include "stage/stage.h"
#include "quad2d.h"
#include "number_billboard.h"
#include "custom_status.h"
#include "game.h"

constexpr int stage_qube_num = 5;
constexpr int player_y = 1;

Player g_player;

ReturnUI ui_num;
int score;
int score_num [6];

Quad2D UI_HP;
Quad2D UI_score;
Quad2D UI_score_num [6];
Num_Billboard billboard_score;

int g_stage_rate;

void GameLoad()
{
    Stage::StageLoad();
}

void GameInit(CustomStatus cs)
{
    // カメラの位置と注視点をセット（正方形の中心を見る）
    CCamera::GetInstance()->m_camera_eye = { ((float) stage_qube_num - 1.0f) * 10.0f , 180.0f + (player_y + 20.0f) ,
        (float) stage_qube_num * -50 };
    CCamera::GetInstance()->m_camera_lookat = { ((float) stage_qube_num - 1.0f) * 10.0f , player_y * 20.0f ,
        ((float) stage_qube_num - 1.0f) * -10.0f };

    // カメラの四方向の位置と回転の時間を設定
    CCamera::GetInstance()->m_camera_pos = 1;
    CCamera::GetInstance()->m_camera_move_time = 11;
    CCamera::GetInstance()->m_camera_y_move_time = 11;

    CCamera::GetInstance()->m_camera_move_flg = false;
    CCamera::GetInstance()->m_camera_y_move_flg = false;

    CCamera::GetInstance()->Init(
        10.0f ,							// ニアクリップ
        10000.0f ,						// ファークリップ
        XM_PI / 5.0f ,					// 視野角
        static_cast<float>(Application::CLIENT_WIDTH) ,		// スクリーン幅
        static_cast<float>(Application::CLIENT_HEIGHT) ,		// スクリーンの高さ
        CCamera::GetInstance()->m_camera_eye , CCamera::GetInstance()->m_camera_lookat , { 0.0f,1.0f,0.0f });

    // 平行光源をセット
    DX11LightInit(
        DirectX::XMFLOAT4(1 , 1 , -1 , 0));


    //Stage::Init(stage_qube_num , 5 , 1000 , 1500 , 5);
    Stage::Init(cs.stage_width , cs.stage_height , cs.fall_distance , cs.survival_time , cs.fall_speed);
    g_stage_rate = cs.qube_rate;

    g_player.Init(stage_qube_num , player_y);

    XMFLOAT2 uv [4] = { { 0.0f,0.0f},{1.0f,0.0f},{0.0f,1.0f},{1.0f,1.0f} };

    UI_HP.Init(200 , 200 , { 1.0f,1.0f,1.0f,1.0f } , uv);
    UI_HP.LoadTexture("assets/UI/life.png");
    UI_HP.SetPosition(40.0f , 100.0f , 0.0f);

    uv [0] = { 0.0f,0.3f };
    uv [1] = { 1.0f,0.3f };
    uv [2] = { 0.0f,0.65f };
    uv [3] = { 1.0f,0.65f };

    UI_score.Init(200 , 100 , { 1.0f,1.0f,1.0f,1.0f } , uv);
    UI_score.LoadTexture("assets/UI/score.png");
    UI_score.SetPosition(1150.0f , 30.0f , 0.0f);

    uv [0] = { 0.0f,0.0f };
    uv [1] = { 0.15f,0.0f };
    uv [2] = { 0.0f,0.5f };
    uv [3] = { 0.15f,0.5f };

    for (int i = 0; i < 6; i++)
    {
        UI_score_num [i].Init(30 , 60 , { 1.0f,1.0f,1.0f,1.0f } , uv);
        UI_score_num [i].LoadTexture("assets/UI/number.png");
        UI_score_num [i].SetPosition(1200.0f - (i * 30) , 120.0f , 0.0f);
    }

    billboard_score.Init();

    score = 0;

}

void GameInput(uint64_t dt)
{
    CDirectInput::GetInstance().GetKeyBuffer();
}

int GameUpdate(uint64_t dt)
{
    if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_SPACE))
    {
        CCamera::GetInstance()->m_camera_move_flg = true;
    }

    if (CCamera::GetInstance()->m_camera_move_flg)
    {
        CCamera::GetInstance()->Update(stage_qube_num);
    }

    g_player.Update(CCamera::GetInstance()->m_camera_pos);

    if (g_player.m_player_qube_move_flg)
    {
        XMFLOAT3 before_pos {};
        before_pos.x = g_player.m_move_direction.x;
        before_pos.y = g_player.m_move_direction.y;
        before_pos.z = g_player.m_move_direction.z;

        // 後ろに引いてる？
        if (g_player.m_standby_direction != g_player.m_player_direction)
        {
            before_pos.x = (g_player.m_player_chip.m_char_chip_pos.x * 2 - g_player.m_move_direction.x);
            before_pos.z = (g_player.m_player_chip.m_char_chip_pos.z * 2 - g_player.m_move_direction.z);
        }

        XMFLOAT3 after_pos {};
        after_pos.x = g_player.m_move_direction.x - g_player.m_player_chip.m_char_chip_pos.x;
        after_pos.x += before_pos.x;
        after_pos.y = g_player.m_move_direction.y - g_player.m_player_chip.m_char_chip_pos.y;
        after_pos.y += before_pos.y;
        after_pos.z = g_player.m_move_direction.z - g_player.m_player_chip.m_char_chip_pos.z;
        after_pos.z += before_pos.z;

        g_player.m_player_qube_move_flg = Stage::ChangeQubePos(before_pos , after_pos);
    }

    Stage::Update();
    Stage::StageRateUpdate(g_stage_rate);

    XMFLOAT3 pos {};
    pos.x = g_player.m_player_chip.m_char_chip_pos.x;
    pos.y = g_player.m_player_chip.m_char_chip_pos.y - 1;
    pos.z = g_player.m_player_chip.m_char_chip_pos.z;

    ui_num = Stage::ChangeColor(pos);

    ui_num.player_hp = 10000;

    g_player.m_player_hp += ui_num.player_hp;
    score += ui_num.stage_score;
    score += ui_num.color_change_score;

    pos.y++;

    for (int y = 0; y < stage_qube_num; y++)
    {
        for (int x = 0; x < stage_qube_num; x++)
        {
            g_player.SetPlayerStageTop(y , x , Stage::GetStageTop(y , x));
            g_player.SetClimbFlg(y , x , Stage::GetStageFallFlg(y , x));
        }
    }

    g_player.m_player_crush_flg = Stage::CrushPlayer(pos , g_player.m_walk_time);

    if (g_player.m_player_hp < 0)
    {
        return 4;
    }

    if ((g_player.m_player_chip.m_char_chip_pos.y * 20.0f != CCamera::GetInstance()->m_camera_lookat.y) &&
        !CCamera::GetInstance()->m_camera_y_move_flg)
    {
        CCamera::GetInstance()->PlayerChase(g_player.m_player_chip.m_char_chip_pos.y);
    }

    CCamera::GetInstance()->PlayerChase();

    UI_HP.SetScale(1 , g_player.m_player_hp / 10000.0f , 1.0f);
    UI_HP.SetPosition(40.0f , 100.0f + (100.0f - (g_player.m_player_hp / 100.0f)) , 0.0f);
    UI_HP.updateVbuffer();

    score_num [0] = score % 10;
    score_num [1] = (score % 100) / 10;
    score_num [2] = (score % 1000) / 100;
    score_num [3] = (score % 10000) / 1000;
    score_num [4] = (score % 100000) / 10000;
    score_num [5] = (score % 1000000) / 100000;

    for (int i = 0; i < 6; i++)
    {
        UI_score_num [i].ChangeNumberUV(score_num [i]);
        UI_score_num [i].updateVbuffer();
    }

    if (ui_num.color_change_score != 0)
    {
        billboard_score.Update(pos , CCamera::GetInstance()->m_camera_pos , ui_num.color_change_score);
    }
    else if (ui_num.stage_score != 0)
    {
        billboard_score.Update(pos , CCamera::GetInstance()->m_camera_pos , ui_num.stage_score);
    }

    return 10;

}

// IMGUIウインドウ
void imguidebug()
{

}

void GameRender(uint64_t dt)
{

    float col [4] = { 0.7f,0.7f,0.7f,1 };

    // 描画前処理
    DX11BeforeRender(col);

    XMFLOAT4X4 mtx;

    // プロジェクション変換行列取得
    mtx = CCamera::GetInstance()->GetProjectionMatrix();
    DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::PROJECTION , mtx);

    // ビュー変換行列を取得
    mtx = CCamera::GetInstance()->GetCameraMatrix();
    DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::VIEW , mtx);

    Stage::Draw();

    g_player.Draw();

    UI_HP.ChangeRainbowColor();
    UI_HP.Draw();

    UI_score.Draw();
    for (int i = 0; i < 6; i++)
    {
        UI_score_num [i].Draw();
    }

    billboard_score.Draw();

    // 描画後処理
    DX11AfterRender();
}

void GameDispose()
{

    ModelMgr::GetInstance().Finalize();

    //DX11Uninit();
}