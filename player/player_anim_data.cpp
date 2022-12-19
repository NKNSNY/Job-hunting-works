#include "player_anim_data.h"

DirectX::XMFLOAT3 PlayerAnimData::m_local_pos_data;
DirectX::XMFLOAT3 PlayerAnimData::m_local_angle_data;

DirectX::XMFLOAT4X4 PlayerAnimData::GetLocalData(PlayerAnimation::ANIMATIONNUM anim_num ,
    DirectX::XMFLOAT4X4 local_mtx , int parts_num)
{
    switch (anim_num)
    {
        case PlayerAnimation::STANDBY:
            local_mtx = GetData_Standby(local_mtx , parts_num);
            break;
        case PlayerAnimation::WALK:
            local_mtx = GetData_Walk(local_mtx , parts_num);
            break;
        case PlayerAnimation::CLIMB:
            local_mtx = GetData_Climb(local_mtx , parts_num);
            break;
        case PlayerAnimation::DESCEND:
            break;
        case PlayerAnimation::JUMP:
            break;
        case PlayerAnimation::SET:
            break;
        case PlayerAnimation::HEAL:
            break;
        case PlayerAnimation::DAMAGE:
            break;
        case PlayerAnimation::BLACKHOLE:
            break;
    }

    return local_mtx;
}

DirectX::XMFLOAT4X4 PlayerAnimData::GetData_Standby(DirectX::XMFLOAT4X4 local_mtx , int parts_num)
{
    switch (parts_num)
    {
        case 0:
            return local_mtx;
            break;
        case 1:
            m_local_pos_data = { 0.0f , 1.3f , -0.3f };
            m_local_angle_data = { 0.0f , 0.0f , 0.0f };
            break;
        case 2:
            m_local_pos_data = { 0.0f , 4.5f , 0.0f };
            m_local_angle_data = { 0.0f , 0.0f , 0.0f };
            break;
        case 3:
            m_local_pos_data = { 2.0f , 4.0f , -0.8f };
            m_local_angle_data = { -20.0f , 0.0f , -10.0f };
            break;
        case 4:
            m_local_pos_data = { -2.0f , 4.0f , -0.8f };
            m_local_angle_data = { -20.0f , 0.0f , 10.0f };
            break;
        case 5:
            m_local_pos_data = { 0.9f , -0.3f , 0.0f };
            m_local_angle_data = { 0.0f , 0.0f , 0.0f };
            break;
        case 6:
            m_local_pos_data = { -0.9f , -0.1f , 0.0f };
            m_local_angle_data = { 0.0f , 0.0f , 0.0f };
            break;
        case 7:
            m_local_pos_data = { 1.9f , -2.5f , 0.0f };
            m_local_angle_data = { 30.0f , 0.0f , -20.0f };
            break;
        case 8:
            m_local_pos_data = { -2.0f , -2.6f , 0.0f };
            m_local_angle_data = { 30.0f , 0.0f , 20.0f };
            break;
        case 9:
            m_local_pos_data = { 0.5f , -4.4f , 0.0f };
            m_local_angle_data = { 0.0f , 0.0f , 0.0f };
            break;
        case 10:
            m_local_pos_data = { -0.5f , -4.7f , 0.0f };
            m_local_angle_data = { 0.0f , 0.0f , 0.0f };
            break;
        case 11:
            m_local_pos_data = { 1.8f , -1.3f , 1.0f };
            m_local_angle_data = { 0.0f , 0.0f , 0.0f };
            break;
        case 12:
            m_local_pos_data = { -1.8f , -1.1f , 1.0f };
            m_local_angle_data = { 0.0f , 0.0f , 0.0f };
            break;
        case 13:
            m_local_pos_data = { 0.3f , -3.7f , -0.5f };
            m_local_angle_data = { 0.0f , 0.0f , 0.0f };
            break;
        case 14:
            m_local_pos_data = { -0.3f , -3.5f , -0.5f };
            m_local_angle_data = { 0.0f , 0.0f , 0.0f };
            break;
        case 15:
            m_local_pos_data = { 0.0f , 0.0f , 0.0f };
            m_local_angle_data = { 0.0f , 0.0f , 0.0f };
            break;
    }

    DX11MakeWorldMatrix(local_mtx , m_local_angle_data , m_local_pos_data);

    return local_mtx;
}

DirectX::XMFLOAT4X4 PlayerAnimData::GetData_Walk(DirectX::XMFLOAT4X4 local_mtx , int parts_num)
{
    switch (parts_num)
    {
        case 0:
            return local_mtx;
            break;
        case 1:
            m_local_pos_data = { 0.0f , 1.3f , -0.3f };
            m_local_angle_data = { 0.0f , 0.0f , 0.0f };
            break;
        case 2:
            m_local_pos_data = { 0.0f , 4.5f , 0.0f };
            m_local_angle_data = { 0.0f , 0.0f , 0.0f };
            break;
        case 3:
            m_local_pos_data = { 2.0f , 4.0f , -0.8f };
            m_local_angle_data = { -10.0f , 0.0f , -10.0f };
            break;
        case 4:
            m_local_pos_data = { -2.0f , 4.0f , -0.8f };
            m_local_angle_data = { -10.0f , 0.0f , 10.0f };
            break;
        case 5:
            m_local_pos_data = { 0.9f , -0.3f , 0.0f };
            m_local_angle_data = { 0.0f , 0.0f , 0.0f };
            break;
        case 6:
            m_local_pos_data = { -0.9f , -0.1f , 0.0f };
            m_local_angle_data = { 0.0f , 0.0f , 0.0f };
            break;
        case 7:
            m_local_pos_data = { 1.9f , -2.5f , 0.0f };
            m_local_angle_data = { 20.0f , 0.0f , -30.0f };
            break;
        case 8:
            m_local_pos_data = { -2.0f , -2.6f , 0.0f };
            m_local_angle_data = { 20.0f , 0.0f , 30.0f };
            break;
        case 9:
            m_local_pos_data = { 0.5f , -4.4f , 0.0f };
            m_local_angle_data = { 0.0f , 0.0f , 0.0f };
            break;
        case 10:
            m_local_pos_data = { -0.5f , -4.7f , 0.0f };
            m_local_angle_data = { 0.0f , 0.0f , 0.0f };
            break;
        case 11:
            m_local_pos_data = { 1.8f , -1.3f , 1.0f };
            m_local_angle_data = { 0.0f , 0.0f , 10.0f };
            break;
        case 12:
            m_local_pos_data = { -1.8f , -1.1f , 1.0f };
            m_local_angle_data = { 0.0f , 0.0f , -10.0f };
            break;
        case 13:
            m_local_pos_data = { 0.3f , -3.7f , -0.5f };
            m_local_angle_data = { 0.0f , 0.0f , 0.0f };
            break;
        case 14:
            m_local_pos_data = { -0.3f , -3.5f , -0.5f };
            m_local_angle_data = { 0.0f , 0.0f , 0.0f };
            break;
        case 15:
            m_local_pos_data = { 0.0f , 0.0f , 0.0f };
            m_local_angle_data = { 0.0f , 0.0f , 0.0f };
            break;
    }

    DX11MakeWorldMatrix(local_mtx , m_local_angle_data , m_local_pos_data);

    return local_mtx;
}

DirectX::XMFLOAT4X4 PlayerAnimData::GetData_Climb(DirectX::XMFLOAT4X4 local_mtx , int parts_num)
{

    DX11MakeWorldMatrix(local_mtx , m_local_angle_data , m_local_pos_data);

    return local_mtx;
}
