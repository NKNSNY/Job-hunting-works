#include "result.h"
#include "Application.h"
#include "CCamera.h"
#include "CDirectInput.h"
#include "TextureMgr.h"

ID3D11ShaderResourceView * TextureMgr::result_game_over;

void Result::ResultLoad()
{
    float u [4] = { 0.0f,1.0f,0.0f,1.0f };
    float v [4] = { 0.0f,0.0f,1.0f,1.0f };

    XMFLOAT2 uv [4] = { { 0.0f,0.0f},{1.0f,0.0f},{0.0f,1.0f},{1.0f,1.0f} };

    m_result.SetSRV(TextureMgr::result_game_over);
    m_result.SetUV(u , v);
    m_result.SetUV(uv);

    m_go_title.LoadTexture("assets/UI/title_go.png");
    m_retry.LoadTexture("assets/UI/retry.png");
    m_choose_arrow.LoadTexture("assets/UI/choose.png");

}

void Result::ResultInit()
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

    m_result.Init(0.0f , 0.0f , 0.0f , 70.0f , 70.0f , { 1.0f,1.0f,1.0f,1.0f });
    m_result.SetUV(u , v);
    m_result.SetUV(uv);

    m_go_title.Init(200 , 50 , { 1.0f,1.0f,1.0f,1.0f } , uv);
    m_go_title.SetPosition(800.0f , 500.0f , 0.0f);

    m_retry.Init(200 , 50 , { 1.0f,1.0f,1.0f,1.0f } , uv);
    m_retry.SetPosition(400.0f , 500.0f , 0.0f);

    m_choose_arrow.Init(40 , 50 , { 1.0f,1.0f,1.0f,1.0f } , uv);
    m_choose_arrow.SetPosition(260.0f , 500.0f , 0.0f);

    m_choose_pos = 0;
    m_choose_alpha_flg = false;
    m_choose_alpha_time = 1.0f;

}

int Result::ResultUpdate()
{
    CDirectInput::GetInstance().GetKeyBuffer();

    // 矢印の縦移動
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

    m_go_title.updateVbuffer();
    m_retry.updateVbuffer();

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

    m_result.DrawBillBoard(CCamera::GetInstance()->GetCameraMatrix());
    m_go_title.Draw();
    m_retry.Draw();
    m_choose_arrow.Draw();

    // 描画後処理
    DX11AfterRender();

}

void Result::ResultFinalize()
{
}
