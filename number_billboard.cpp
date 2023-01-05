#include "number_billboard.h"
#include "TextureMgr.h"
#include "CCamera.h"

ID3D11ShaderResourceView * TextureMgr::number_texture;

void Num_Billboard::Init()
{
    float u [4] = { 0.0f,1.0f,0.0f,1.0f };
    float v [4] = { 0.0f,0.0f,1.0f,1.0f };

    XMFLOAT2 uv [4] = { { 0.0f,0.0f},{1.0f,0.0f},{0.0f,1.0f},{1.0f,1.0f} };

    for (int i = 0; i < 6; i++)
    {
        m_number_billboard [i].SetSRV(TextureMgr::number_texture);
        m_number_billboard [i].Init(0.0f , -1000.0f , 0.0f , 3.0f , 3.0f , { 1.0f , 1.0f , 1.0f , 1.0f });
        m_number_billboard [i].SetUV(u , v);
        m_number_billboard [i].SetUV(uv);
    }

    m_draw_time = 0;

}

void Num_Billboard::Update(XMFLOAT3 player_pos , int camera_pos , int score)
{
    m_draw_time = 20;

    player_pos.x = player_pos.x * 20;
    player_pos.y = player_pos.y * 20;
    player_pos.z = -player_pos.z * 20;

    XMFLOAT3 add_pos {};

    switch (camera_pos)
    {
        case 1:
            add_pos.x = 1.5f;
            break;
        case 2:
            add_pos.z = 1.5f;
            break;
        case 3:
            add_pos.x = -1.5f;
            break;
        case 4:
            add_pos.z = -1.5f;
            break;
    }

    int score_num [6] {};

    score_num [0] = score % 10;
    score_num [1] = (score % 100) / 10;
    score_num [2] = (score % 1000) / 100;
    score_num [3] = (score % 10000) / 1000;
    score_num [4] = (score % 100000) / 10000;
    score_num [5] = (score % 1000000) / 100000;

    XMFLOAT2 uv [4];

    for (int i = 0; i < 6; i++)
    {
        switch (score_num [i])
        {
            case 0:
                uv [0] = { 0.0f,0.05f };
                uv [1] = { 0.15f,0.05f };
                uv [2] = { 0.0f,0.46f };
                uv [3] = { 0.15f,0.46f };
                break;
            case 1:
                uv [0] = { 0.2f,0.05f };
                uv [1] = { 0.35f,0.05f };
                uv [2] = { 0.2f,0.46f };
                uv [3] = { 0.35f,0.46f };
                break;
            case 2:
                uv [0] = { 0.4f,0.05f };
                uv [1] = { 0.55f,0.05f };
                uv [2] = { 0.4f,0.46f };
                uv [3] = { 0.55f,0.46f };
                break;
            case 3:
                uv [0] = { 0.6f,0.05f };
                uv [1] = { 0.75f,0.05f };
                uv [2] = { 0.6f,0.46f };
                uv [3] = { 0.75f,0.46f };
                break;
            case 4:
                uv [0] = { 0.8f,0.05f };
                uv [1] = { 0.95f,0.05f };
                uv [2] = { 0.8f,0.46f };
                uv [3] = { 0.95f,0.46f };
                break;
            case 5:
                uv [0] = { 0.0f,0.58f };
                uv [1] = { 0.15f,0.58f };
                uv [2] = { 0.0f,1.0f };
                uv [3] = { 0.15f,1.0f };
                break;
            case 6:
                uv [0] = { 0.2f,0.58f };
                uv [1] = { 0.35f,0.58f };
                uv [2] = { 0.2f,1.0f };
                uv [3] = { 0.35f,1.0f };
                break;
            case 7:
                uv [0] = { 0.4f,0.58f };
                uv [1] = { 0.55f,0.58f };
                uv [2] = { 0.4f,1.0f };
                uv [3] = { 0.55f,1.0f };
                break;
            case 8:
                uv [0] = { 0.6f,0.58f };
                uv [1] = { 0.75f,0.58f };
                uv [2] = { 0.6f,1.0f };
                uv [3] = { 0.75f,1.0f };
                break;
            case 9:
                uv [0] = { 0.8f,0.58f };
                uv [1] = { 0.95f,0.58f };
                uv [2] = { 0.8f,1.0f };
                uv [3] = { 0.95f,1.0f };
                break;

            default:
                uv [0] = { 0.8f,0.58f };
                uv [1] = { 0.95f,0.58f };
                uv [2] = { 0.8f,1.0f };
                uv [3] = { 0.95f,1.0f };
                break;
        }

        m_number_billboard [i].SetUV(uv);
    }

    if (score >= 10 && score < 100)
    {
        m_number_billboard [0].SetPosition(player_pos.x + add_pos.x , player_pos.y + 15.0f , player_pos.z - add_pos.z);
        m_number_billboard [1].SetPosition(player_pos.x - add_pos.x , player_pos.y + 15.0f , player_pos.z + add_pos.z);
        m_number_billboard [2].SetPosition(0.0f , -1000.0f , 0.0f);
        m_number_billboard [3].SetPosition(0.0f , -1000.0f , 0.0f);
        m_number_billboard [4].SetPosition(0.0f , -1000.0f , 0.0f);
        m_number_billboard [5].SetPosition(0.0f , -1000.0f , 0.0f);
    }
    if (score >= 100 && score < 1000)
    {
        m_number_billboard [0].SetPosition(player_pos.x + (add_pos.x * 2) , player_pos.y + 15.0f , player_pos.z - (add_pos.z * 2));
        m_number_billboard [1].SetPosition(player_pos.x , player_pos.y + 15.0f , player_pos.z);
        m_number_billboard [2].SetPosition(player_pos.x - (add_pos.x * 2) , player_pos.y + 15.0f , player_pos.z + (add_pos.z * 2));
        m_number_billboard [3].SetPosition(0.0f , -1000.0f , 0.0f);
        m_number_billboard [4].SetPosition(0.0f , -1000.0f , 0.0f);
        m_number_billboard [5].SetPosition(0.0f , -1000.0f , 0.0f);
    }
    if (score >= 1000 && score < 10000)
    {
        m_number_billboard [0].SetPosition(player_pos.x + (add_pos.x * 3) , player_pos.y + 15.0f , player_pos.z - (add_pos.z * 3));
        m_number_billboard [1].SetPosition(player_pos.x + add_pos.x , player_pos.y + 15.0f , player_pos.z - add_pos.z);
        m_number_billboard [2].SetPosition(player_pos.x - add_pos.x , player_pos.y + 15.0f , player_pos.z + add_pos.z);
        m_number_billboard [3].SetPosition(player_pos.x - (add_pos.x * 3) , player_pos.y + 15.0f , player_pos.z + (add_pos.z * 3));
        m_number_billboard [4].SetPosition(0.0f , -1000.0f , 0.0f);
        m_number_billboard [5].SetPosition(0.0f , -1000.0f , 0.0f);
    }
    if (score >= 10000 && score < 100000)
    {
        m_number_billboard [0].SetPosition(player_pos.x + (add_pos.x * 4) , player_pos.y + 15.0f , player_pos.z - (add_pos.z * 4));
        m_number_billboard [1].SetPosition(player_pos.x + (add_pos.x * 2) , player_pos.y + 15.0f , player_pos.z - (add_pos.z * 2));
        m_number_billboard [2].SetPosition(player_pos.x , player_pos.y + 15.0f , player_pos.z);
        m_number_billboard [3].SetPosition(player_pos.x - (add_pos.x * 2) , player_pos.y + 15.0f , player_pos.z + (add_pos.z * 2));
        m_number_billboard [4].SetPosition(player_pos.x - (add_pos.x * 4) , player_pos.y + 15.0f , player_pos.z + (add_pos.z * 4));
        m_number_billboard [5].SetPosition(0.0f , -1000.0f , 0.0f);
    }
    if (score >= 100000 && score < 1000000)
    {
        m_number_billboard [0].SetPosition(player_pos.x + (add_pos.x * 5) , player_pos.y + 15.0f , player_pos.z - (add_pos.z * 5));
        m_number_billboard [1].SetPosition(player_pos.x + (add_pos.x * 3) , player_pos.y + 15.0f , player_pos.z - (add_pos.z * 3));
        m_number_billboard [2].SetPosition(player_pos.x + add_pos.x , player_pos.y + 15.0f , player_pos.z - add_pos.z);
        m_number_billboard [3].SetPosition(player_pos.x - add_pos.x , player_pos.y + 15.0f , player_pos.z + add_pos.z);
        m_number_billboard [4].SetPosition(player_pos.x - (add_pos.x * 3) , player_pos.y + 15.0f , player_pos.z + (add_pos.z * 3));
        m_number_billboard [5].SetPosition(player_pos.x - (add_pos.x * 5) , player_pos.y + 15.0f , player_pos.z + (add_pos.z * 5));
    }



}

void Num_Billboard::Draw()
{
    if (m_draw_time > 0)
    {
        for (int i = 0; i < 6; i++)
        {
            m_number_billboard [i].DrawBillBoard(CCamera::GetInstance()->GetCameraMatrix());
        }
        m_draw_time--;
    }
}

void Num_Billboard::Finalize()
{
}
