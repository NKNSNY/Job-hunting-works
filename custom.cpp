#include "custom.h"
#include "Application.h"
#include "CCamera.h"
#include "CDirectInput.h"
#include "TextureMgr.h"

ID3D11ShaderResourceView * TextureMgr::custom_back;

void Custom::CustomLoad()
{
    float u [4] = { 0.0f,1.0f,0.0f,1.0f };
    float v [4] = { 0.0f,0.0f,1.0f,1.0f };

    XMFLOAT2 uv [4] = { { 0.0f,0.0f},{1.0f,0.0f},{0.0f,1.0f},{1.0f,1.0f} };

    m_custom.SetSRV(TextureMgr::custom_back);
    m_custom.SetUV(u , v);
    m_custom.SetUV(uv);

    for (int i = 0; i < 6; i++)
    {
        m_choose_box [i].LoadTexture("assets/stage/_choose.png");
    }

    m_go_play.LoadTexture("assets/UI/play.png");
    m_go_title.LoadTexture("assets/UI/title_go.png");
    m_arrow.LoadTexture("assets/UI/choose.png");
}

void Custom::CustomInit()
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

    float u [4] = { 0.0f,1.0f,0.0f,1.0f };
    float v [4] = { 0.0f,0.0f,1.0f,1.0f };

    XMFLOAT2 uv [4] = { { 0.0f,0.0f},{1.0f,0.0f},{0.0f,1.0f},{1.0f,1.0f} };

    m_custom.Init(0.0f , -13.5f , 0.0f , 57.5f , 60.0f , { 1.0f,1.0f,1.0f,1.0f });
    m_custom.SetUV(u , v);
    m_custom.SetUV(uv);

    for (int i = 0; i < 6; i++)
    {
        m_choose_box [i].Init(50 , 50 , { 1.0f,1.0f,1.0f,1.0f } , uv);
    }

    m_choose_box [0].SetPosition(897.0f , 78.0f , 0.0f);
    m_choose_box [1].SetPosition(897.0f , 181.0f , 0.0f);
    m_choose_box [2].SetPosition(897.0f , 288.0f , 0.0f);
    m_choose_box [3].SetPosition(897.0f , 380.0f , 0.0f);
    m_choose_box [4].SetPosition(897.0f , 465.0f , 0.0f);
    m_choose_box [5].SetPosition(897.0f , 550.0f , 0.0f);

    m_go_play.Init(200 , 50 , { 1.0f,1.0f,1.0f,1.0f } , uv);
    m_go_play.SetPosition(1100.0f , 650.0f , 0.0f);

    m_go_title.Init(200 , 50 , { 1.0f,1.0f,1.0f,1.0f } , uv);
    m_go_title.SetPosition(700.0f , 650.0f , 0.0f);

    m_arrow.Init(40 , 50 , { 1.0f,1.0f,1.0f,1.0f } , uv);
    m_arrow.SetPosition(970.0f , 650.0f , 0.0f);

    m_choose_pos = 0;
    m_choose_flg = false;
    m_choose_alpha_flg = false;
    m_choose_alpha_time = 1.0f;
    m_choose_height = 0;
    for (int i = 0; i < 6; i++)
    {
        m_choose_wight [i] = 2;
    }

    m_csp = { 5 , 10 , 1000 , 1000 , 5 , 5 };

}

CustomPlus Custom::CustomUpdate()
{
    CDirectInput::GetInstance().GetKeyBuffer();

    XMFLOAT3 box_pos = m_choose_box [m_choose_height].GetPostion();

    if (!m_choose_flg)
    {
        m_choose_box [m_choose_height].SetColor({ m_choose_alpha_time,m_choose_alpha_time,m_choose_alpha_time,1.0f });
    }

    // 横移動
    if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_RIGHT) && !m_choose_flg)
    {
        switch (m_choose_wight [m_choose_height])
        {
            case 0:
                if (m_choose_height == 0)
                {
                    box_pos.x = 897.0f;
                    m_choose_box [0].SetPosition(box_pos);
                    m_choose_wight [0] += 2;
                    m_csp.cs.stage_width = 5;
                }
                else
                {
                    box_pos.x = 728.0f;
                    m_choose_box [m_choose_height].SetPosition(box_pos);
                    m_choose_wight [m_choose_height]++;
                    switch (m_choose_height)
                    {
                        case 1:
                            m_csp.cs.stage_height = 7;
                            break;
                        case 2:
                            m_csp.cs.fall_distance = 700;
                            break;
                        case 3:
                            m_csp.cs.survival_time = 700;
                            break;
                        case 4:
                            m_csp.cs.fall_speed = 3;
                            break;
                        case 5:
                            m_csp.cs.qube_rate = 3;
                            break;
                    }
                }
                break;
            case 1:
                box_pos.x = 897.0f;
                m_choose_box [m_choose_height].SetPosition(box_pos);
                m_choose_wight [m_choose_height]++;
                switch (m_choose_height)
                {
                    case 1:
                        m_csp.cs.stage_height = 10;
                        break;
                    case 2:
                        m_csp.cs.fall_distance = 1000;
                        break;
                    case 3:
                        m_csp.cs.survival_time = 1000;
                        break;
                    case 4:
                        m_csp.cs.fall_speed = 5;
                        break;
                    case 5:
                        m_csp.cs.qube_rate = 5;
                        break;
                }
                break;
            case 2:
                if (m_choose_height == 0)
                {
                    box_pos.x = 1247.0f;
                    m_choose_box [0].SetPosition(box_pos);
                    m_choose_wight [0] += 2;
                    m_csp.cs.stage_width = 7;
                }
                else
                {
                    box_pos.x = 1069.0f;
                    m_choose_box [m_choose_height].SetPosition(box_pos);
                    m_choose_wight [m_choose_height]++;
                    switch (m_choose_height)
                    {
                        case 1:
                            m_csp.cs.stage_height = 15;
                            break;
                        case 2:
                            m_csp.cs.fall_distance = 1500;
                            break;
                        case 3:
                            m_csp.cs.survival_time = 1500;
                            break;
                        case 4:
                            m_csp.cs.fall_speed = 7;
                            break;
                        case 5:
                            m_csp.cs.qube_rate = 7;
                            break;
                    }
                }
                break;
            case 3:
                box_pos.x = 1247.0f;
                m_choose_box [m_choose_height].SetPosition(box_pos);
                m_choose_wight [m_choose_height]++;
                switch (m_choose_height)
                {
                    case 1:
                        m_csp.cs.stage_height = 20;
                        break;
                    case 2:
                        m_csp.cs.fall_distance = 2000;
                        break;
                    case 3:
                        m_csp.cs.survival_time = 2000;
                        break;
                    case 4:
                        m_csp.cs.fall_speed = 9;
                        break;
                    case 5:
                        m_csp.cs.qube_rate = 9;
                        break;
                }
                break;
            default:
                break;

        }
    }
    if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_LEFT) && !m_choose_flg)
    {
        switch (m_choose_wight [m_choose_height])
        {
            case 1:
                box_pos.x = 572.0f;
                m_choose_box [m_choose_height].SetPosition(box_pos);
                m_choose_wight [m_choose_height]--;
                switch (m_choose_height)
                {
                    case 1:
                        m_csp.cs.stage_height = 5;
                        break;
                    case 2:
                        m_csp.cs.fall_distance = 500;
                        break;
                    case 3:
                        m_csp.cs.survival_time = 500;
                        break;
                    case 4:
                        m_csp.cs.fall_speed = 1;
                        break;
                    case 5:
                        m_csp.cs.qube_rate = 1;
                        break;
                }
                break;
            case 2:
                if (m_choose_height == 0)
                {
                    box_pos.x = 572.0f;
                    m_choose_box [0].SetPosition(box_pos);
                    m_choose_wight [0] -= 2;
                    m_csp.cs.stage_width = 3;
                }
                else
                {
                    box_pos.x = 728.0f;
                    m_choose_box [m_choose_height].SetPosition(box_pos);
                    m_choose_wight [m_choose_height]--;
                    switch (m_choose_height)
                    {
                        case 1:
                            m_csp.cs.stage_height = 7;
                            break;
                        case 2:
                            m_csp.cs.fall_distance = 700;
                            break;
                        case 3:
                            m_csp.cs.survival_time = 700;
                            break;
                        case 4:
                            m_csp.cs.fall_speed = 3;
                            break;
                        case 5:
                            m_csp.cs.qube_rate = 3;
                            break;
                    }
                }
                break;
            case 3:
                box_pos.x = 897.0f;
                m_choose_box [m_choose_height].SetPosition(box_pos);
                m_choose_wight [m_choose_height]--;
                switch (m_choose_height)
                {
                    case 1:
                        m_csp.cs.stage_height = 10;
                        break;
                    case 2:
                        m_csp.cs.fall_distance = 1000;
                        break;
                    case 3:
                        m_csp.cs.survival_time = 1000;
                        break;
                    case 4:
                        m_csp.cs.fall_speed = 5;
                        break;
                    case 5:
                        m_csp.cs.qube_rate = 5;
                        break;
                }
                break;
            case 4:
                if (m_choose_height == 0)
                {
                    box_pos.x = 897.0f;
                    m_choose_box [0].SetPosition(box_pos);
                    m_choose_wight [0] -= 2;
                    m_csp.cs.stage_width = 5;
                }
                else
                {
                    box_pos.x = 1069.0f;
                    m_choose_box [m_choose_height].SetPosition(box_pos);
                    m_choose_wight [m_choose_height]--;
                    switch (m_choose_height)
                    {
                        case 1:
                            m_csp.cs.stage_height = 15;
                            break;
                        case 2:
                            m_csp.cs.fall_distance = 1500;
                            break;
                        case 3:
                            m_csp.cs.survival_time = 1500;
                            break;
                        case 4:
                            m_csp.cs.fall_speed = 7;
                            break;
                        case 5:
                            m_csp.cs.qube_rate = 7;
                            break;
                    }
                }
                break;
            default:
                break;

        }
    }

    if (m_choose_flg)
    {
        switch (m_choose_pos)
        {
            case 0:
                m_go_play.SetColor({ 1.0f,1.0f,1.0f,m_choose_alpha_time });
                if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_LEFT))
                {
                    m_go_play.SetColor({ 1.0f,1.0f,1.0f,1.0f });
                    m_arrow.SetPosition(570.0f , 650.0f , 0.0f);
                    m_choose_pos = 5;
                    m_choose_alpha_flg = false;
                    m_choose_alpha_time = 1.0f;
                }
                break;
            case 5:
                m_go_title.SetColor({ 1.0f,1.0f,1.0f,m_choose_alpha_time });
                if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_RIGHT))
                {
                    m_go_title.SetColor({ 1.0f,1.0f,1.0f,1.0f });
                    m_arrow.SetPosition(970.0f , 650.0f , 0.0f);
                    m_choose_pos = 0;
                    m_choose_alpha_flg = false;
                    m_choose_alpha_time = 1.0f;
                }
                break;
        }
    }

    m_go_play.updateVbuffer();
    m_go_title.updateVbuffer();

    // 縦移動
    if ((CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_UP)) &&
        (m_choose_height != 0) && !m_choose_flg)
    {
        m_choose_box [m_choose_height].SetColor({ 1.0f,1.0f,1.0f,1.0f });
        m_choose_height--;
        m_choose_alpha_flg = false;
        m_choose_alpha_time = 1.0f;
    }
    else if ((CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_UP)) &&
        (m_choose_flg))
    {
        m_choose_flg = false;
        m_go_play.SetColor({ 1.0f,1.0f,1.0f,1.0f });
        m_go_title.SetColor({ 1.0f,1.0f,1.0f,1.0f });
        m_choose_alpha_flg = false;
        m_choose_alpha_time = 1.0f;
    }

    if ((CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_DOWN)) &&
        (m_choose_height != 5))
    {
        m_choose_box [m_choose_height].SetColor({ 1.0f,1.0f,1.0f,1.0f });
        m_choose_height++;
        m_choose_alpha_flg = false;
        m_choose_alpha_time = 1.0f;
    }
    else if ((CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_DOWN)) &&
        (m_choose_height == 5 && !m_choose_flg))
    {
        m_choose_flg = true;
        m_choose_box [5].SetColor({ 1.0f,1.0f,1.0f,1.0f });
        m_arrow.SetPosition(970.0f , 650.0f , 0.0f);
        m_choose_pos = 0;
    }

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

    for (int i = 0; i < 6; i++)
    {
        m_choose_box [i].updateVbuffer();
    }

    if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_RETURN) && m_choose_flg)
    {
        m_csp.game_num = m_choose_pos;
        return m_csp;
    }
    else
    {
        m_csp.game_num = 10;
        return m_csp;
    }
}

void Custom::CustomDraw()
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

    m_custom.DrawBillBoard(CCamera::GetInstance()->GetCameraMatrix());

    for (int i = 0; i < 6; i++)
    {
        m_choose_box [i].Draw();
    }

    m_go_play.Draw();
    m_go_title.Draw();
    if (m_choose_flg)
    {
        m_arrow.Draw();
    }

    // 描画後処理
    DX11AfterRender();

}

void Custom::CustomFinalize()
{
}
