#include "title.h"
#include "CCamera.h"
#include "Application.h"
#include "CLight.h"
#include "CDirectInput.h"
#include "TextureMgr.h"

constexpr XMFLOAT3 qube_end_pos = { 45.0f,0.0f,10.0f };
constexpr XMFLOAT3 title_end_pos = { 650.0f,300.0f,0.0f };

ID3D11ShaderResourceView * TextureMgr::title_back;

void Title::TitleInit()
{
    // �J�����̈ʒu�ƒ����_���Z�b�g
    CCamera::GetInstance()->m_camera_eye = { 0.0f , 0.0f , -50.0f };
    CCamera::GetInstance()->m_camera_lookat = { 0.0f , 0.0f , 0.0f };

    // �J�����̎l�����̈ʒu�Ɖ�]�̎��Ԃ�ݒ�
    CCamera::GetInstance()->m_camera_pos = 1;
    CCamera::GetInstance()->m_camera_move_time = 11;
    CCamera::GetInstance()->m_camera_y_move_time = 11;

    CCamera::GetInstance()->m_camera_move_flg = false;
    CCamera::GetInstance()->m_camera_y_move_flg = false;

    CCamera::GetInstance()->Init(
        10.0f ,							// �j�A�N���b�v
        10000.0f ,						// �t�@�[�N���b�v
        XM_PI / 5.0f ,					// ����p
        static_cast<float>(Application::CLIENT_WIDTH) ,		// �X�N���[����
        static_cast<float>(Application::CLIENT_HEIGHT) ,		// �X�N���[���̍���
        CCamera::GetInstance()->m_camera_eye , CCamera::GetInstance()->m_camera_lookat , { 0.0f,1.0f,0.0f });

    // ���s�������Z�b�g
    DX11LightInit(
        DirectX::XMFLOAT4(1 , 1 , -1 , 0));

    // �^�C�g���̃L���[�u������
    m_title_qube.Init(0);
    m_title_qube.SetPos({ 45.0f,0.0f,10.0f });
    m_title_qube.SetRot({ 0.0f,45.0f,0.0f });
    m_title_qube.SetRot({ -15.0f,0.0f,-15.0f });

    // �^�C�g���Ɣw�i������
    float u [4] = { 0.0f,1.0f,0.0f,1.0f };
    float v [4] = { 0.0f,0.0f,1.0f,1.0f };

    XMFLOAT2 uv [4] = { { 0.0f,0.0f},{1.0f,0.0f},{0.0f,1.0f},{1.0f,1.0f} };

    m_background.SetSRV(TextureMgr::title_back);
    m_background.Init(0.0f , 0.0f , 100.0f , 200.0f , 100.0f , { 1.0f,1.0f,1.0f,1.0f });
    m_background.SetUV(u , v);
    m_background.SetUV(uv);

    // UI�B�̏�����
    m_title.Init(600 , 150 , { 1.0f,1.0f,1.0f,1.0f } , uv);
    m_title.LoadTexture("assets/UI/title.png");
    m_title.SetPosition(650.0f , 300.0f , 0.0f);

    m_normal_play.Init(200 , 50 , { 1.0f,1.0f,1.0f,1.0f } , uv);
    m_normal_play.LoadTexture("assets/UI/normal_play.png");
    m_normal_play.SetPosition(600.0f , 500.0f , 0.0f);

    m_custom_play.Init(200 , 50 , { 1.0f,1.0f,1.0f,1.0f } , uv);
    m_custom_play.LoadTexture("assets/UI/custom_play.png");
    m_custom_play.SetPosition(600.0f , 570.0f , 0.0f);

    m_challenge_play.Init(200 , 50 , { 1.0f,1.0f,1.0f,1.0f } , uv);
    m_challenge_play.LoadTexture("assets/UI/challenge_play.png");
    m_challenge_play.SetPosition(600.0f , 640.0f , 0.0f);

    m_choose_arrow.Init(40 , 50 , { 1.0f,1.0f,1.0f,1.0f } , uv);
    m_choose_arrow.LoadTexture("assets/UI/choose.png");
    m_choose_arrow.SetPosition(470.0f , 500.0f , 0.0f);

    m_choose_pos = 0;
    m_choose_move_flg = true;
    m_choose_alpha_flg = false;
    m_choose_alpha_time = 1.0f;

    m_ready_flg = false;
    m_preparation_num = rand() % 2;

}

int Title::TitleUpdate()
{
    CDirectInput::GetInstance().GetKeyBuffer();

    // ���̏c�ړ�
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

    // ���̉��ړ�
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

    // �I������Ă��鏊�̃A���t�@�l��ω�
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

    // �`��O����
    DX11BeforeRender(col);

    XMFLOAT4X4 mtx;

    // �v���W�F�N�V�����ϊ��s��擾
    mtx = CCamera::GetInstance()->GetProjectionMatrix();
    DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::PROJECTION , mtx);

    // �r���[�ϊ��s����擾
    mtx = CCamera::GetInstance()->GetCameraMatrix();
    DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::VIEW , mtx);

    m_title_qube.Draw(0);

    m_background.DrawBillBoard(CCamera::GetInstance()->GetCameraMatrix());

    m_title.Draw();
    m_normal_play.Draw();
    m_custom_play.Draw();
    m_challenge_play.Draw();
    if (m_ready_flg)
    {
        m_choose_arrow.Draw();
    }

    // �`��㏈��
    DX11AfterRender();

}

void Title::TitleFinalize()
{
}

void Title::TitlePreparationData()
{
    // ���ꂼ��̎�ނ̏����f�[�^

    switch (m_preparation_num)
    {
        case 0:
            m_qube_move_time = 1000;
            m_title_move_time = 1000;

            m_qube_pos = { 45.0f,0.0f,110.0f };
            m_title_pos = { 650.0f,0.0f,0.0f };
            break;
        case 1:
            m_qube_move_time = 1000;
            m_title_move_time = 1000;

            m_qube_pos = { 45.0f,-100.0f,10.0f };
            m_title_pos = { -350.0f,300.0f,0.0f };
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
        default:    // �ړ����Ȃ���
            m_qube_move_time = 0;
            m_title_move_time = 0;
            break;
    }

    m_title_qube.SetPos(m_qube_pos);
    m_title.SetPosition(m_title_pos);

    // �ړ����I�����@�������́@���L�[�������ꂽ
    if ((m_qube_move_time <= 0 && m_title_move_time <= 0) ||
        ((CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_LEFT)) ||
            (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_RIGHT)) ||
            (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_UP)) ||
            (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_DOWN))))
    {
        m_title_qube.SetPos(qube_end_pos);
        m_title.SetPosition(title_end_pos);
        m_ready_flg = true;
    }
}
