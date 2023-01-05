#include "fade.h"
#include "CCamera.h"

Quad2D Fade::m_fade;
int Fade::m_fade_time;

void Fade::FadeInit()
{
    XMFLOAT3 fade_pos = CCamera::GetInstance()->m_camera_eye;
    fade_pos.z -= 10.0f;

    XMFLOAT2 uv [4] = { { 0.0f,0.0f},{1.0f,0.0f},{0.0f,1.0f},{1.0f,1.0f} };

    m_fade.Init(10000 , 10000 , { 0.0f,0.0f,0.0f,1.0f } , uv);
    m_fade.LoadTexture("assets/qube/white.png");
    m_fade.SetPosition(600.0f , 300.0f , 0.0f);

    m_fade_time = 0;

}

void Fade::FadeUpdate()
{
    if (m_fade_time < 500)
    {
        m_fade_time++;
        m_fade.SetColor({ m_fade_time / 1000.0f,m_fade_time / 1000.0f,m_fade_time / 1000.0f , 1.0f });
    }
}

void Fade::FadeDraw()
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

    if (m_fade_time < 500)
    {
        m_fade.updateVbuffer();
        m_fade.Draw();
    }
    // 描画後処理
    DX11AfterRender();
}

void Fade::FadeFinalize()
{
}
