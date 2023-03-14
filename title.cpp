#include "title.h"
#include "CCamera.h"
#include "Application.h"
#include "CDirectInput.h"
#include "TextureMgr.h"

constexpr XMFLOAT3 qube_end_pos = { 45.0f,0.0f,10.0f };
constexpr XMFLOAT3 title_end_pos = { 650.0f,300.0f,0.0f };

ID3D11ShaderResourceView * TextureMgr::title_back;

void Title::TitleLoad()
{
    m_title_qube.Load();

    // タイトルと背景初期化
    float u [4] = { 0.0f,1.0f,0.0f,1.0f };
    float v [4] = { 0.0f,0.0f,1.0f,1.0f };

    XMFLOAT2 uv [4] = { { 0.0f,0.0f},{1.0f,0.0f},{0.0f,1.0f},{1.0f,1.0f} };

    m_background.SetSRV(TextureMgr::title_back);
    m_background.SetUV(u , v);
    m_background.SetUV(uv);

    // UI達の初期化
    m_title.LoadTexture("assets/UI/title.png");
    m_normal_play.LoadTexture("assets/UI/normal_play.png");
    m_custom_play.LoadTexture("assets/UI/custom_play.png");
    m_challenge_play.LoadTexture("assets/UI/challenge_play.png");
    m_choose_arrow.LoadTexture("assets/UI/choose.png");
    m_title_cover.LoadTexture("assets/UI/title.png");

}

void Title::TitleInit()
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

    // タイトルのキューブ初期化
    m_title_qube.Init();
    m_title_qube.SetPos({ 45.0f,0.0f,10.0f });
    m_title_qube.SetRot({ 0.0f,45.0f,0.0f });
    m_title_qube.SetRot({ -15.0f,0.0f,-15.0f });

    // タイトルと背景初期化
    float u [4] = { 0.0f,1.0f,0.0f,1.0f };
    float v [4] = { 0.0f,0.0f,1.0f,1.0f };

    XMFLOAT2 uv [4] = { { 0.0f,0.0f},{1.0f,0.0f},{0.0f,1.0f},{1.0f,1.0f} };

    m_background.Init(0.0f , 0.0f , 100.0f , 200.0f , 100.0f , { 1.0f,1.0f,1.0f,1.0f });
    m_background.SetUV(u , v);
    m_background.SetUV(uv);

    // UI達の初期化
    m_title.Init(600 , 150 , { 1.0f,1.0f,1.0f,1.0f } , uv);
    m_title.SetPosition(650.0f , 300.0f , 0.0f);

    m_normal_play.Init(200 , 50 , { 1.0f,1.0f,1.0f,1.0f } , uv);
    m_normal_play.SetPosition(600.0f , 500.0f , 0.0f);

    m_custom_play.Init(200 , 50 , { 1.0f,1.0f,1.0f,1.0f } , uv);
    m_custom_play.SetPosition(600.0f , 570.0f , 0.0f);

    m_challenge_play.Init(200 , 50 , { 1.0f,1.0f,1.0f,1.0f } , uv);
    m_challenge_play.SetPosition(600.0f , 640.0f , 0.0f);

    m_choose_arrow.Init(40 , 50 , { 1.0f,1.0f,1.0f,1.0f } , uv);
    m_choose_arrow.SetPosition(470.0f , 500.0f , 0.0f);

    m_title_cover.Init(600 , 150 , { 1.0f,1.0f,1.0f,0.0f } , uv);
    m_title_cover.SetPosition(9999.0f , 9999.0f , 0.0f);

    m_choose_pos = 0;
    m_choose_move_flg = true;
    m_choose_alpha_flg = false;
    m_choose_alpha_time = 1.0f;

    m_ready_flg = false;
    m_preparation_num = rand() % 10;
}

int Title::TitleUpdate()
{
    CDirectInput::GetInstance().GetKeyBuffer();

    // 矢印の縦移動
    switch (m_choose_pos)
    {
        case 0:
            m_normal_play.SetColor({ 1.0f,1.0f,1.0f,m_choose_alpha_time });
            if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_DOWN))
            {
                m_normal_play.SetColor({ 1.0f,1.0f,1.0f,1.0f });
                m_choose_arrow.SetPosition(470.0f , 570.0f , 0.0f);
                m_choose_pos++;
                m_choose_move_flg = true;
                m_choose_alpha_flg = false;
                m_choose_alpha_time = 1.0f;
            }
            break;
        case 1:
            m_custom_play.SetColor({ 1.0f,1.0f,1.0f,m_choose_alpha_time });
            if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_UP))
            {
                m_custom_play.SetColor({ 1.0f,1.0f,1.0f,1.0f });
                m_choose_arrow.SetPosition(470.0f , 500.0f , 0.0f);
                m_choose_pos--;
                m_choose_move_flg = true;
                m_choose_alpha_flg = false;
                m_choose_alpha_time = 1.0f;
            }
            else if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_DOWN))
            {
                m_custom_play.SetColor({ 1.0f,1.0f,1.0f,1.0f });
                m_choose_arrow.SetPosition(470.0f , 640.0f , 0.0f);
                m_choose_pos++;
                m_choose_move_flg = true;
                m_choose_alpha_flg = false;
                m_choose_alpha_time = 1.0f;
            }
            break;
        case 2:
            m_challenge_play.SetColor({ 1.0f,1.0f,1.0f,m_choose_alpha_time });
            if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_UP))
            {
                m_challenge_play.SetColor({ 1.0f,1.0f,1.0f,1.0f });
                m_choose_arrow.SetPosition(470.0f , 570.0f , 0.0f);
                m_choose_pos--;
                m_choose_move_flg = true;
                m_choose_alpha_flg = false;
                m_choose_alpha_time = 1.0f;
            }
            break;
    }

    XMFLOAT3 choose_pos = m_choose_arrow.GetPostion();

    // 矢印の横移動
    if (m_choose_move_flg)
    {
        if (choose_pos.x < 480.0f)
        {
            choose_pos.x += 0.02f;
            if (choose_pos.x >= 480.0f)
            {
                choose_pos.x = 480.0f;
                m_choose_move_flg = false;
            }
            m_choose_arrow.SetPosition(choose_pos);
        }
    }
    else
    {
        if (choose_pos.x > 460.0f)
        {
            choose_pos.x -= 0.02f;
            if (choose_pos.x <= 460.0f)
            {
                choose_pos.x = 460.0f;
                m_choose_move_flg = true;
            }
            m_choose_arrow.SetPosition(choose_pos);
        }
    }

    // 選択されている所のアルファ値を変化
    if (m_choose_alpha_flg)
    {
        m_choose_alpha_time += 0.001f;
        if (m_choose_alpha_time >= 1.0f)
        {
            m_choose_alpha_time = 1.0f;
            m_choose_alpha_flg = false;
        }
    }
    else
    {
        m_choose_alpha_time -= 0.001f;
        if (m_choose_alpha_time <= 0.3f)
        {
            m_choose_alpha_time = 0.3f;
            m_choose_alpha_flg = true;
        }
    }

    m_normal_play.updateVbuffer();
    m_custom_play.updateVbuffer();
    m_challenge_play.updateVbuffer();

    if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_RETURN))
    {
        return m_choose_pos;
    }
    else
    {
        return 10;
    }

}

void Title::TitleDraw()
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

    m_title_qube.Draw(0);

    m_background.DrawBillBoard(CCamera::GetInstance()->GetCameraMatrix());

    m_title_cover.Draw();
    m_title.Draw();
    m_normal_play.Draw();
    m_custom_play.Draw();
    m_challenge_play.Draw();
    if (m_ready_flg)
    {
        m_choose_arrow.Draw();
    }

    // 描画後処理
    DX11AfterRender();

}

void Title::TitleFinalize()
{
}

void Title::TitlePreparationData()
{
    // それぞれの種類の初期データ

    switch (m_preparation_num)
    {
        // 上から下へ
        case 0:
            m_qube_move_time = 1000;
            m_title_move_time = 1000;

            m_qube_pos = { 45.0f,0.0f,110.0f };
            m_title_pos = { 650.0f,0.0f,0.0f };
            break;
            // 左から右へ
        case 1:
            m_qube_move_time = 1000;
            m_title_move_time = 1000;

            m_qube_pos = { 45.0f,-100.0f,10.0f };
            m_title_pos = { -350.0f,300.0f,0.0f };
            break;
            // 下から上へ
        case 2:
            m_qube_move_time = 1000;
            m_title_move_time = 1000;

            m_qube_pos = { 45.0f,0.0f,-490.5f };
            m_title_pos = { 650.0f,1300.0f,0.0f };
            break;
            // 斜法投射
        case 3:
            m_qube_move_time = 1010;
            m_title_move_time = 1000;

            m_qube_pos = { 45.0f,-100.0f,-463.5f };
            m_title_pos = title_end_pos;
            break;
            // 奥から手前へ
        case 4:
            m_qube_move_time = 1000;
            m_title_move_time = 1000;

            m_qube_pos = { 100.0f,0.0f,10.0f };
            m_title_pos = { 1650.0f,300.0f,0.0f };
            break;
            // カバーが下に移動する
        case 5:
            m_qube_move_time = 0;
            m_title_move_time = 2000;

            m_qube_pos = qube_end_pos;
            m_title_pos = title_end_pos;
            m_title_cover_pos = title_end_pos;
            break;
            // カバーが右に移動する
        case 6:
            m_qube_move_time = 0;
            m_title_move_time = 6000;

            m_qube_pos = qube_end_pos;
            m_title_pos = title_end_pos;
            m_title_cover_pos = title_end_pos;
            break;
            // カバーが真ん中に縮小する
        case 7:
            m_qube_move_time = 0;
            m_title_move_time = 5000;

            m_qube_pos = qube_end_pos;
            m_title_pos = title_end_pos;
            m_title_cover_pos = title_end_pos;
            break;
            // タイトルがY軸回転
        case 8:
            m_qube_move_time = 1000;
            m_title_move_time = 1000;

            m_qube_pos = qube_end_pos;
            m_title_pos = title_end_pos;
            m_title_cover_pos.z = 0.0f;     // 回転に利用
            break;
            // 失敗クロス
        case 9:
            m_qube_move_time = 1100;
            m_title_move_time = 1000;

            m_qube_pos = { 45.0f,90.0f,-460.0f };
            m_title_pos = { -100.0f,2000.0f,0.0f };
            m_title_cover_pos.z = 0.0f;     // 回転に利用
            break;
    }
}

void Title::TitlePreparation()
{
    CDirectInput::GetInstance().GetKeyBuffer();

    switch (m_preparation_num)
    {
        case 0:
            if (m_qube_move_time > 0)
            {
                m_qube_pos.z -= 0.1f;
                m_qube_move_time--;
            }
            if (m_title_move_time > 0)
            {
                m_title_pos.y += 0.3f;
                m_title_move_time--;
            }
            break;
        case 1:
            if (m_qube_move_time > 0)
            {
                m_qube_pos.y += 0.1f;
                m_qube_move_time--;
            }
            if (m_title_move_time > 0)
            {
                m_title_pos.x += 1.0f;
                m_title_move_time--;
            }
            break;
        case 2:
            if (m_qube_move_time > 0)
            {
                m_qube_pos.z += m_qube_move_time / 1000.0f;
                m_qube_move_time--;
            }
            if (m_title_move_time > 0)
            {
                m_title_pos.y -= 1.0f;
                m_title_move_time--;
            }
            break;
        case 3:
            if (m_qube_move_time > 10)
            {
                m_qube_pos.y += 0.1f;
                m_qube_pos.z += (m_qube_move_time - 10) / 1000.0f;
                m_qube_move_time--;
            }
            else if (m_qube_move_time > 0 && m_qube_move_time <= 10)
            {
                m_qube_pos.z -= 10 / (int) m_qube_move_time;
                m_qube_move_time--;
            }
            if (m_title_move_time > 0)
            {
                m_title.SetColor({ 1.0f,1.0f,1.0f,1.0f / m_title_move_time });
                m_title.updateVbuffer();
                m_title_move_time--;
            }
            break;
        case 4:
            if (m_qube_move_time > 0)
            {
                if (m_qube_move_time > 900)
                {
                    m_qube_pos.x -= 0.01f;
                }
                if (m_qube_move_time > 800 && m_qube_move_time <= 900)
                {
                    m_qube_pos.x -= 0.02f;
                }
                if (m_qube_move_time > 700 && m_qube_move_time <= 800)
                {
                    m_qube_pos.x -= 0.03f;
                }
                if (m_qube_move_time > 600 && m_qube_move_time <= 700)
                {
                    m_qube_pos.x -= 0.04f;
                }
                if (m_qube_move_time > 500 && m_qube_move_time <= 600)
                {
                    m_qube_pos.x -= 0.05f;
                }
                if (m_qube_move_time > 400 && m_qube_move_time <= 500)
                {
                    m_qube_pos.x -= 0.06f;
                }
                if (m_qube_move_time > 300 && m_qube_move_time <= 400)
                {
                    m_qube_pos.x -= 0.07f;
                }
                if (m_qube_move_time > 200 && m_qube_move_time <= 300)
                {
                    m_qube_pos.x -= 0.08f;
                }
                if (m_qube_move_time > 100 && m_qube_move_time <= 200)
                {
                    m_qube_pos.x -= 0.09f;
                }
                if (m_qube_move_time <= 100)
                {
                    m_qube_pos.x -= 0.1f;
                }

                m_qube_move_time--;
            }
            if (m_title_move_time > 0)
            {
                m_title_pos.x -= 1.0f;
                m_title_move_time--;
            }
            break;
        case 5:
            if (m_title_move_time > 0)
            {
                m_title_cover_pos.y += 0.05f;
                m_title_move_time--;
                m_title_cover.SetPosition(m_title_cover_pos);
                if (m_title_move_time != 0)
                {
                    m_title_cover.ChangeSize(600 , 150 * ((float) m_title_move_time / 2000.0f));
                }
                m_title_cover.updateVbuffer();
            }
            break;
        case 6:
            if (m_title_move_time > 0)
            {
                m_title_cover_pos.x += 0.1f;
                m_title_move_time--;
                m_title_cover.SetPosition(m_title_cover_pos);
            }
            break;
        case 7:
            if (m_title_move_time > 0)
            {
                m_title_cover.SetPosition(m_title_cover_pos);
                m_title_move_time--;
                m_title_cover.ChangeSize(600 * ((float) m_title_move_time / 5000.0f) , 150 * ((float) m_title_move_time / 5000.0f));
                m_title_cover.updateVbuffer();
            }
            break;
        case 8:
            if (m_qube_move_time > 0)
            {
                m_title_qube.SetRot({ 0.0f,10.0f,0.0f });
                m_qube_move_time--;
            }
            if (m_title_move_time > 0)
            {
                m_title_cover_pos.z += (float) m_title_move_time / 99.0f;
                m_title.SetRotation(m_title_cover_pos.z);
                m_title_move_time--;
            }
            break;
        case 9:
            if (m_qube_move_time > 100)
            {
                m_qube_pos.y -= 0.1f;
                m_qube_pos.z += (m_qube_move_time - 100) / 1050.0f;
                m_qube_move_time--;
            }
            else if (m_qube_move_time > 0 && m_qube_move_time <= 100)
            {
                m_qube_pos.y -= 0.1f + (m_qube_move_time / 1000.0f);
                m_qube_move_time--;
            }
            if (m_title_move_time > 0)
            {
                m_title_pos.x += 1.2f;
                m_title_pos.y -= 2.0f;
                m_title_cover_pos.z += (float) m_title_move_time / 100.0f;
                m_title.SetRotation(m_title_cover_pos.z);
                m_title.updateVbuffer();
                m_title_move_time--;
            }
            break;
        default:    // 移動しないよ
            m_qube_move_time = 0;
            m_title_move_time = 0;
            break;
    }

    m_title_qube.SetPos(m_qube_pos);
    m_title.SetPosition(m_title_pos);

    // 移動し終えた　もしくは　矢印キーが押された
    if ((m_qube_move_time <= 0 && m_title_move_time <= 0) ||
        ((CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_LEFT)) ||
            (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_RIGHT)) ||
            (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_UP)) ||
            (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_DOWN))))
    {
        if (m_preparation_num != 9)
        {
            m_title_qube.SetPos(qube_end_pos);
            m_title.SetPosition(title_end_pos);
            m_title.SetColor({ 1.0f,1.0f,1.0f,1.0f });
            m_title.updateVbuffer();
            m_title_cover.SetPosition({ 9999.0f,9999.0f,0.0f });
        }
        m_ready_flg = true;
    }
}
