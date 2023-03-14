#include "result.h"
#include "Application.h"
#include "CCamera.h"
#include "CDirectInput.h"
#include "TextureMgr.h"

ID3D11ShaderResourceView * TextureMgr::result_game_over;
ID3D11ShaderResourceView * TextureMgr::result_score;

void Result::ResultLoad()
{
    float u [4] = { 0.0f,1.0f,0.0f,1.0f };
    float v [4] = { 0.0f,0.0f,1.0f,1.0f };

    XMFLOAT2 uv [4] = { { 0.0f,0.0f},{1.0f,0.0f},{0.0f,1.0f},{1.0f,1.0f} };

    m_result.SetSRV(TextureMgr::result_game_over);
    m_result.SetUV(u , v);
    m_result.SetUV(uv);

    m_result_clear.SetSRV(TextureMgr::result_score);
    m_result_clear.SetUV(u , v);
    m_result_clear.SetUV(uv);

    m_go_title.LoadTexture("assets/UI/title_go.png");
    m_retry.LoadTexture("assets/UI/retry.png");
    m_choose_arrow.LoadTexture("assets/UI/choose.png");

    for (int i = 0; i < 8; i++)
    {
        if (i < 6)
        {
            m_score_num [i].LoadTexture("assets/UI/number.png");
        }

        m_small_color [i].LoadTexture("assets/UI/number.png");
        m_big_color [i].LoadTexture("assets/UI/number.png");
    }

    m_go_title_clear.LoadTexture("assets/UI/title_go.png");

}

void Result::ResultInit(ResultScore rs)
{
    // カメラの位置と注視点をセット
    CCamera::GetInstance()->m_camera_eye = { 0.0f , 0.0f , -50.0f };
    CCamera::GetInstance()->m_camera_lookat = { 0.0f , 0.0f , 0.0f };

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

    // スコアを6桁に分ける
    int score_num [6] {};

    score_num [0] = rs.score % 10;
    score_num [1] = (rs.score % 100) / 10;
    score_num [2] = (rs.score % 1000) / 100;
    score_num [3] = (rs.score % 10000) / 1000;
    score_num [4] = (rs.score % 100000) / 10000;
    score_num [5] = (rs.score % 1000000) / 100000;

    float u [4] = { 0.0f,1.0f,0.0f,1.0f };
    float v [4] = { 0.0f,0.0f,1.0f,1.0f };

    XMFLOAT2 uv [4] = { { 0.0f,0.0f},{1.0f,0.0f},{0.0f,1.0f},{1.0f,1.0f} };

    m_result.Init(0.0f , 0.0f , 0.0f , 70.0f , 70.0f , { 1.0f,1.0f,1.0f,1.0f });
    m_result.SetUV(u , v);
    m_result.SetUV(uv);

    m_result_clear.Init(0.0f , 0.0f , 0.0f , 57.0f , 33.0f , { 1.0f,1.0f,1.0f,1.0f });
    m_result_clear.SetUV(u , v);
    m_result_clear.SetUV(uv);

    m_go_title.Init(200 , 50 , { 1.0f,1.0f,1.0f,1.0f } , uv);
    m_go_title.SetPosition(800.0f , 500.0f , 0.0f);

    m_retry.Init(200 , 50 , { 1.0f,1.0f,1.0f,1.0f } , uv);
    m_retry.SetPosition(400.0f , 500.0f , 0.0f);

    m_choose_arrow.Init(40 , 50 , { 1.0f,1.0f,1.0f,1.0f } , uv);
    m_choose_arrow.SetPosition(260.0f , 500.0f , 0.0f);

    for (int i = 0; i < 8; i++)
    {
        if (i < 6)
        {
            m_score_num [i].Init(30 , 60 , { 1.0f,1.0f,1.0f,1.0f } , uv);
            m_score_num [i].SetPosition(800.0f - (i * 80) , 200.0f , 0.0f);
            m_score_num [i].ChangeNumberUV(score_num [i]);
            m_score_num [i].updateVbuffer();
        }

        m_small_num = rs.color [i] % 10;
        m_big_num = (rs.color [i] % 100) / 10;

        m_small_color [i].Init(30 , 60 , { 1.0f,1.0f,1.0f,1.0f } , uv);
        m_small_color [i].ChangeNumberUV(m_small_num);
        m_small_color [i].updateVbuffer();

        m_big_color [i].Init(30 , 60 , { 1.0f,1.0f,1.0f,1.0f } , uv);
        m_big_color [i].ChangeNumberUV(m_big_num);
        m_big_color [i].updateVbuffer();
    }

    // 初期位置を設定
    m_small_color [0].SetPosition(270.0f , 370.0f , 0.0f);
    m_small_color [1].SetPosition(680.0f , 370.0f , 0.0f);
    m_small_color [2].SetPosition(1070.0f , 370.0f , 0.0f);
    m_small_color [3].SetPosition(300.0f , 500.0f , 0.0f);
    m_small_color [4].SetPosition(700.0f , 500.0f , 0.0f);
    m_small_color [5].SetPosition(1100.0f , 500.0f , 0.0f);
    m_small_color [6].SetPosition(330.0f , 610.0f , 0.0f);
    m_small_color [7].SetPosition(730.0f , 610.0f , 0.0f);

    m_big_color [0].SetPosition(230.0f , 370.0f , 0.0f);
    m_big_color [1].SetPosition(640.0f , 370.0f , 0.0f);
    m_big_color [2].SetPosition(1030.0f , 370.0f , 0.0f);
    m_big_color [3].SetPosition(260.0f , 500.0f , 0.0f);
    m_big_color [4].SetPosition(660.0f , 500.0f , 0.0f);
    m_big_color [5].SetPosition(1060.0f , 500.0f , 0.0f);
    m_big_color [6].SetPosition(290.0f , 610.0f , 0.0f);
    m_big_color [7].SetPosition(690.0f , 610.0f , 0.0f);

    m_go_title_clear.Init(200 , 50 , { 1.0f,1.0f,1.0f,1.0f } , uv);
    m_go_title_clear.SetPosition(1150.0f , 670.0f , 0.0f);

    m_choose_pos = 0;
    m_choose_alpha_flg = false;
    m_choose_alpha_time = 1.0f;

    m_result_score = rs;
}

int Result::ResultUpdate()
{
    CDirectInput::GetInstance().GetKeyBuffer();

    // 矢印の縦移動
    if (m_result_score.result_judge == 0)
    {
        switch (m_choose_pos)
        {
            case 0:
                m_retry.SetColor({ 1.0f,1.0f,1.0f,m_choose_alpha_time });
                if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_RIGHT))
                {
                    m_retry.SetColor({ 1.0f,1.0f,1.0f,1.0f });
                    m_choose_arrow.SetPosition(660.0f , 500.0f , 0.0f);
                    m_choose_pos = 5;
                    m_choose_alpha_flg = false;
                    m_choose_alpha_time = 1.0f;
                }
                break;
            case 5:
                m_go_title.SetColor({ 1.0f,1.0f,1.0f,m_choose_alpha_time });
                if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_LEFT))
                {
                    m_go_title.SetColor({ 1.0f,1.0f,1.0f,1.0f });
                    m_choose_arrow.SetPosition(260.0f , 500.0f , 0.0f);
                    m_choose_pos = 0;
                    m_choose_alpha_flg = false;
                    m_choose_alpha_time = 1.0f;
                }
                break;
        }
    }
    else
    {
        m_choose_pos = 5;
    }

    XMFLOAT3 choose_pos = m_choose_arrow.GetPostion();

    // 選択されている所のアルファ値を変化
    if (m_choose_alpha_flg)
    {
        m_choose_alpha_time += 0.0005f;
        if (m_choose_alpha_time >= 1.0f)
        {
            m_choose_alpha_time = 1.0f;
            m_choose_alpha_flg = false;
        }
    }
    else
    {
        m_choose_alpha_time -= 0.0005f;
        if (m_choose_alpha_time <= 0.3f)
        {
            m_choose_alpha_time = 0.3f;
            m_choose_alpha_flg = true;
        }
    }

    m_go_title_clear.SetColor({ 1.0f,1.0f,1.0f,m_choose_alpha_time });

    m_go_title.updateVbuffer();
    m_retry.updateVbuffer();

    m_go_title_clear.updateVbuffer();

    if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_RETURN))
    {
        return m_choose_pos;
    }
    else
    {
        return 10;
    }
}

void Result::ResultDraw()
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

    // ゲームクリアとゲームオーバーで描画分け
    if (m_result_score.result_judge == 4)
    {
        m_result.DrawBillBoard(CCamera::GetInstance()->GetCameraMatrix());

        m_go_title.Draw();
        m_retry.Draw();
        m_choose_arrow.Draw();
    }
    else
    {
        m_result_clear.DrawBillBoard(CCamera::GetInstance()->GetCameraMatrix());

        for (int i = 0; i < 8; i++)
        {
            if (i < 6)
            {
                m_score_num [i].Draw();
            }
            m_small_color [i].Draw();
            if ((m_result_score.color [i] % 100) / 10 != 0)
            {
                m_big_color [i].Draw();
            }
        }

        m_go_title_clear.Draw();
    }

    // 描画後処理
    DX11AfterRender();

}

void Result::ResultFinalize()
{
}
