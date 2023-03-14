#include "stage/qube.h"
#include "dx11mathutil.h"
#include "ModelMgr.h"
#include "CCamera.h"
#include "TextureMgr.h"

ID3D11ShaderResourceView * TextureMgr::white_texture;

bool Qube::m_modelloadflg = false;

void Qube::Load()
{
    // �s�񏉊���
    DX11MtxIdentity(m_mtx);					// ���f����ǂݍ���

    bool sts = true;

    // �ǂݍ��݂��������Ă��Ȃ���Γǂݍ���
    if (Qube::m_modelloadflg == false)
    {
        // ���f���ǂݍ��݁i�L���[�u�j
        sts = ModelMgr::GetInstance().LoadModel(
            "assets/qube/qube.x" ,	// �t�@�C���� 
            "shader/vs.hlsl" ,				// ���_�V�F�[�_�[
            "shader/ps.hlsl" ,				// �s�N�Z���V�F�[�_�[
            "assets/qube/");				// �e�N�X�`���̊i�[�t�H���_
        if (!sts)
        {
            char str [128];
            sprintf_s<128>(str , "%s" , Qube::XfileName);
            MessageBox(nullptr , str , "load error" , MB_OK);
        }
        Qube::m_modelloadflg = true;
    }

    m_model = ModelMgr::GetInstance().GetModelPtr("assets/qube/qube.x");

    float u [4] = { 0.0f,1.0f,0.0f,1.0f };
    float v [4] = { 0.0f,0.0f,1.0f,1.0f };

    XMFLOAT2 uv [4] = { { 0.0f,0.0f},{1.0f,0.0f},{0.0f,1.0f},{1.0f,1.0f} };

    // �e�N�X�`���������i�r���{�[�h�j
    for (int i = 0; i < 6; i++)
    {
        switch (0)
        {
            case 0:
                m_qube_type = NORMAL_QUBE;
                m_qube_texture [i].SetSRV(TextureMgr::white_texture);
                break;
            case 1:
                m_qube_type = HEAL_QUBE;
                m_qube_texture [i].SetSRV(TextureMgr::white_texture);
                break;
        }
        m_qube_texture [i].Init(0.0f , 0.0f , 0.0f , 12.0f , 6.5f , { 1.0f,1.0f,1.0f,1.0f });
        m_qube_texture [i].SetUV(u , v);
        m_qube_texture [i].SetUV(uv);

        if (i != 5)
        {
            m_qube_alpha [i].SetSRV(TextureMgr::custom_back);
            m_qube_alpha [i].Init(0.0f , 0.0f , 0.0f , 12.0f , 6.5f , { 0.0f,0.0f,0.0f,0.0f });
            m_qube_alpha [i].SetUV(u , v);
            m_qube_alpha [i].SetUV(uv);
        }
    }

    m_qube_shadow.SetSRV(TextureMgr::result_game_over);
    m_qube_shadow.Init(0.0f , 0.0f , 0.0f , 0.0f , 0.0f , { 0.0f,0.0f,0.0f,0.5f });
    m_qube_shadow.SetUV(u , v);
    m_qube_shadow.SetUV(uv);

}

bool Qube::Init()
{
    m_fall_flg = false;

    m_shadow_create_flg = true;

    m_move_qube_time = 31;

    m_move_qube_flg = false;

    m_delete_fall_time = 0;
    m_delete_fall_flg = false;

    return true;
}

bool Qube::Update()
{
    m_survival_alpha = 1.0f - ((float) m_survival_time / (float) m_first_survival_time);

    if (m_delete_fall_time > 0)
    {
        m_delete_fall_time--;
        m_mtx._42 -= 0.5f;
    }

    return true;
}

bool Qube::Draw()
{
    XMFLOAT3 billboard_pos = { m_mtx._41,m_mtx._42,m_mtx._43 };

    // �ʒu�𒲐����ĕ`��
    m_qube_texture [0].SetPosition({ billboard_pos.x , billboard_pos.y , billboard_pos.z - 10.1f });      // �O
    m_qube_texture [0].DrawBillBoard(CCamera::GetInstance()->GetProjectionMatrix());
    m_qube_texture [1].SetPosition({ billboard_pos.x , billboard_pos.y , billboard_pos.z + 10.1f });      // ���
    m_qube_texture [1].DrawRotateBillBoard(CCamera::GetInstance()->GetProjectionMatrix() , 180.0f , 2);
    m_qube_texture [2].SetPosition({ billboard_pos.x + 10.1f , billboard_pos.y , billboard_pos.z });      // �E
    m_qube_texture [2].DrawRotateBillBoard(CCamera::GetInstance()->GetProjectionMatrix() , 270.0f , 2);
    m_qube_texture [3].SetPosition({ billboard_pos.x - 10.1f , billboard_pos.y , billboard_pos.z });      // ��
    m_qube_texture [3].DrawRotateBillBoard(CCamera::GetInstance()->GetProjectionMatrix() , 90.0f , 2);
    m_qube_texture [4].SetPosition({ billboard_pos.x , billboard_pos.y + 10.1f , billboard_pos.z });      // ��
    m_qube_texture [4].DrawRotateBillBoard(CCamera::GetInstance()->GetProjectionMatrix() , 90.0f , 1);
    m_qube_texture [5].SetPosition({ billboard_pos.x , billboard_pos.y - 10.1f , billboard_pos.z });      // ��
    m_qube_texture [5].DrawRotateBillBoard(CCamera::GetInstance()->GetProjectionMatrix() , 270.0f , 1);

    for (int i = 0; i < 5; i++)
    {
        m_qube_alpha [i].SetColor({ 0.0f,0.0f,0.0f,m_survival_alpha });
    }

    // �e�N�X�`���̏����O�ɓ\��
    m_qube_alpha [0].SetPosition({ billboard_pos.x , billboard_pos.y , billboard_pos.z - 10.2f });      // �O
    m_qube_alpha [0].DrawBillBoard(CCamera::GetInstance()->GetProjectionMatrix());
    m_qube_alpha [1].SetPosition({ billboard_pos.x , billboard_pos.y , billboard_pos.z + 10.2f });      // ���
    m_qube_alpha [1].DrawRotateBillBoard(CCamera::GetInstance()->GetProjectionMatrix() , 180.0f , 2);
    m_qube_alpha [2].SetPosition({ billboard_pos.x + 10.2f , billboard_pos.y , billboard_pos.z });      // �E
    m_qube_alpha [2].DrawRotateBillBoard(CCamera::GetInstance()->GetProjectionMatrix() , 270.0f , 2);
    m_qube_alpha [3].SetPosition({ billboard_pos.x - 10.2f , billboard_pos.y , billboard_pos.z });      // ��
    m_qube_alpha [3].DrawRotateBillBoard(CCamera::GetInstance()->GetProjectionMatrix() , 90.0f , 2);
    m_qube_alpha [4].SetPosition({ billboard_pos.x , billboard_pos.y - 10.2f , billboard_pos.z });      // ��
    m_qube_alpha [4].DrawRotateBillBoard(CCamera::GetInstance()->GetProjectionMatrix() , 270.0f , 1);

    m_qube_shadow.SetSize(m_shadow_size.x , m_shadow_size.y);

    // ��ɓ\��
    m_qube_shadow.SetPosition({ billboard_pos.x , billboard_pos.y + 10.2f , billboard_pos.z });      // ��
    m_qube_shadow.DrawRotateBillBoard(CCamera::GetInstance()->GetProjectionMatrix() , 90.0f , 1);

    m_model->Draw(m_mtx);

    return true;
}

bool Qube::Draw(int not_billboard_draw)
{
    m_model->Draw(m_mtx);

    return true;
}

void Qube::Finalize()
{
}

bool Qube::ColorUpdate(int color_num)
{
    XMFLOAT4 color {};

    switch (color_num)
    {
        case 1:
            color = { 1.0f,1.0f,1.0f,1.0f };
            break;
        case 2:
            color = { 1.0f,0.5f,0.0f,1.0f };
            break;
        case 3:
            color = { 1.0f,1.0f,0.0f,1.0f };
            break;
        case 4:
            color = { 0.0f,1.0f,0.0f,1.0f };
            break;
        case 5:
            color = { 0.0f,1.0f,0.5f,1.0f };
            break;
        case 6:
            color = { 0.0f,1.0f,1.0f,1.0f };
            break;
        case 7:
            color = { 0.0f,0.0f,1.0f,1.0f };
            break;
        case 8:
            color = { 0.5f,0.0f,1.0f,1.0f };
            break;
        case 9:
            color = { 1.0f,0.0f,0.0f,1.0f };
            break;

        default:
            color = { 1.0f,0.0f,0.0f,1.0f };
            break;
    }

    for (int i = 0; i < 6; i++)
    {
        switch (m_qube_type)
        {
            case NORMAL_QUBE:
                m_qube_texture [i].SetColor(color);
                break;
            case HEAL_QUBE:
                m_qube_texture [i].ChangeColor(10);
                break;
        }
    }

    return true;
}

bool Qube::ShadowUpdate(int fall_distance , int first_fall_distance)
{
    float shadow_rate = 1.0f - ((float) fall_distance / (float) first_fall_distance);

    m_shadow_size.x = 12.0f * shadow_rate;
    m_shadow_size.y = 6.5f * shadow_rate;

    return true;
}

bool Qube::ChangeTexture(QubeType qube_type)
{
    for (int i = 0; i < 6; i++)
    {
        switch (qube_type)
        {
            case NORMAL_QUBE:
                m_qube_type = NORMAL_QUBE;
                m_qube_texture [i].SetSRV(TextureMgr::white_texture);
                break;
            case HEAL_QUBE:
                m_qube_type = HEAL_QUBE;
                m_qube_texture [i].SetColor({ 0.0f,0.0f,0.0f,1.0f });
                m_qube_texture [i].SetSRV(TextureMgr::white_texture);
                break;
        }
    }

    return true;
}

bool Qube::SetPos(DirectX::XMFLOAT3 pos)
{
    m_mtx._41 = pos.y;
    m_mtx._42 = pos.z;
    m_mtx._43 = pos.x;

    return true;
}

bool Qube::SetFall(int fall_distance , int survival_time , int fall_speed)
{
    m_fall_distance = fall_distance;
    m_survival_time = survival_time;
    m_fall_speed = fall_speed;
    m_first_survival_time = survival_time;
    m_first_fall_distance = fall_distance;

    return true;
}

bool Qube::SetRot(DirectX::XMFLOAT3 rot)
{
    XMFLOAT4X4 mtx {};
    XMFLOAT3 pos {};

    DX11MakeWorldMatrix(mtx , rot , pos);
    DX11MtxMultiply(m_mtx , mtx , m_mtx);

    return true;
}

void Qube::SetQubeStatus(Qube qube)
{
    m_mtx = qube.m_mtx;

    m_fall_distance = qube.m_fall_distance;
    m_survival_time = qube.m_survival_time;
    m_fall_speed = qube.m_fall_speed;
    m_fall_flg = qube.m_fall_flg;
    m_first_survival_time = qube.m_first_survival_time;
    m_first_fall_distance = qube.m_first_fall_distance;
    m_shadow_create_flg = qube.m_shadow_create_flg;
    m_move_qube_flg = qube.m_move_qube_flg;
    m_qube_type = qube.m_qube_type;
}