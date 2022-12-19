#include "player_anim.h"

using namespace DirectX;

DirectX::XMFLOAT3 PlayerAnimation::UpdateAngle(int parts)
{
    XMFLOAT3 return_angle {};

    switch (m_anim_num)
    {
        case PlayerAnimation::STANDBY:
            return_angle = GetStandby(parts , 0);
            break;
        case PlayerAnimation::WALK:
            return_angle = GetWalk(parts , 0);
            break;
        case PlayerAnimation::CLIMB:
            return_angle = GetClimb(parts , 0);
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

    return return_angle;
}

DirectX::XMFLOAT3 PlayerAnimation::UpdateTrans(int parts)
{
    XMFLOAT3 return_trans {};

    switch (m_anim_num)
    {
        case PlayerAnimation::STANDBY:
            return_trans = GetStandby(parts , 1);
            break;
        case PlayerAnimation::WALK:
            return_trans = GetWalk(parts , 1);
            break;
        case PlayerAnimation::CLIMB:
            return_trans = GetClimb(parts , 1);
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

    return return_trans;
}

void PlayerAnimation::SetAnim(ANIMATIONNUM anim_num)
{
    m_anim_num = anim_num;

    // アニメーションの時間を設定する
    switch (m_anim_num)
    {
        case PlayerAnimation::STANDBY:
            m_animation_time = 120;
            break;
        case PlayerAnimation::WALK:
            m_animation_time = 30;
            break;
        case PlayerAnimation::CLIMB:
            m_animation_time = 100;
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

}

DirectX::XMFLOAT3 PlayerAnimation::GetStandby(int parts , int angle_trans)
{
    XMFLOAT3 return_angle_trans {};

    // 角度
    if (angle_trans == 0)
    {
        switch (parts)
        {
            case 0:
                break;
            case 1:
                break;
            case 2:
                if (m_animation_time > 60)
                {
                    return_angle_trans = { 0.1f,0.0f,0.0f };
                }
                else
                {
                    return_angle_trans = { -0.1f,0.0f,0.0f };
                }
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                if (m_animation_time > 60)
                {
                    return_angle_trans = { -0.1f,0.0f,0.0f };
                }
                else
                {
                    return_angle_trans = { 0.1f,0.0f,0.0f };
                }
                break;
            case 6:
                if (m_animation_time > 60)
                {
                    return_angle_trans = { -0.1f,0.0f,0.0f };
                }
                else
                {
                    return_angle_trans = { 0.1f,0.0f,0.0f };
                }
                break;
            case 7:
                if (m_animation_time > 60)
                {
                    return_angle_trans = { 0.0f,0.0f,-0.1f };
                }
                else
                {
                    return_angle_trans = { 0.0f,0.0f,0.1f };
                }
                break;
            case 8:
                if (m_animation_time > 60)
                {
                    return_angle_trans = { 0.0f,0.0f,0.1f };
                }
                else
                {
                    return_angle_trans = { 0.0f,0.0f,-0.1f };
                }
                break;
            case 9:
                if (m_animation_time > 60)
                {
                    return_angle_trans = { 0.2f,0.0f,0.0f };
                }
                else
                {
                    return_angle_trans = { -0.2f,0.0f,0.0f };
                }
                break;
            case 10:
                if (m_animation_time > 60)
                {
                    return_angle_trans = { 0.2f,0.0f,0.0f };
                }
                else
                {
                    return_angle_trans = { -0.2f,0.0f,0.0f };
                }
                break;
            case 11:
                break;
            case 12:
                break;
            case 13:
                if (m_animation_time > 60)
                {
                    return_angle_trans = { -0.1f,0.0f,0.0f };
                }
                else
                {
                    return_angle_trans = { 0.1f,0.0f,0.0f };
                }
                break;
            case 14:
                if (m_animation_time > 60)
                {
                    return_angle_trans = { -0.1f,0.0f,0.0f };
                }
                else
                {
                    return_angle_trans = { 0.1f,0.0f,0.0f };
                }
                break;
        }
    }
    // 位置
    else
    {
        switch (parts)
        {
            case 0:
                break;
            case 1:
                if (m_animation_time > 60)
                {
                    return_angle_trans = { 0.0f,-0.002f,0.0f };
                }
                else
                {
                    return_angle_trans = { 0.0f,0.002f,0.0f };
                }
                break;
            case 2:
                if (m_animation_time > 60)
                {
                    return_angle_trans = { 0.0f,0.0f,0.0005f };
                }
                else
                {
                    return_angle_trans = { 0.0f,0.0f,-0.0005f };
                }
                break;
            case 3:
                if (m_animation_time > 60)
                {
                    return_angle_trans = { 0.0f,-0.002f,0.0f };
                }
                else
                {
                    return_angle_trans = { 0.0f,0.002f,0.0f };
                }
                break;
            case 4:
                if (m_animation_time > 60)
                {
                    return_angle_trans = { 0.0f,-0.003f,0.0f };
                }
                else
                {
                    return_angle_trans = { 0.0f,0.003f,0.0f };
                }
                break;
            case 5:
                if (m_animation_time > 60)
                {
                    return_angle_trans = { 0.0f,-0.003f,0.0f };
                }
                else
                {
                    return_angle_trans = { 0.0f,0.003f,0.0f };
                }
                break;
            case 6:
                if (m_animation_time > 60)
                {
                    return_angle_trans = { 0.0f,-0.003f,0.0f };
                }
                else
                {
                    return_angle_trans = { 0.0f,0.003f,0.0f };
                }
                break;
            case 7:
                break;
            case 8:
                break;
            case 9:
                if (m_animation_time > 60)
                {
                    return_angle_trans = { 0.0f,0.003f,-0.005f };
                }
                else
                {
                    return_angle_trans = { 0.0f,-0.003f,0.005f };
                }
                break;
            case 10:
                if (m_animation_time > 60)
                {
                    return_angle_trans = { 0.0f,0.003f,-0.005f };
                }
                else
                {
                    return_angle_trans = { 0.0f,-0.003f,0.005f };
                }
                break;
            case 11:
                break;
            case 12:
                break;
            case 13:
                if (m_animation_time > 60)
                {
                    return_angle_trans = { 0.0f,0.0f,0.005f };
                }
                else
                {
                    return_angle_trans = { 0.0f,0.0f,-0.005f };
                }
                break;
            case 14:
                if (m_animation_time > 60)
                {
                    return_angle_trans = { 0.0f,0.0f,0.005f };
                }
                else
                {
                    return_angle_trans = { 0.0f,0.0f,-0.005f };
                }
                break;
        }
    }

    return return_angle_trans;
}

DirectX::XMFLOAT3 PlayerAnimation::GetWalk(int parts , int angle_trans)
{
    XMFLOAT3 return_angle_trans {};

    if (angle_trans == 0)
    {
        switch (parts)
        {
            case 0:
                break;
            case 1:
                if (m_animation_time > 15)
                {
                    return_angle_trans = { 0.6f,0.0f,0.0f };
                }
                else
                {
                    return_angle_trans = { -0.6f,0.0f,0.0f };
                }
                break;
            case 2:
                if (m_animation_time > 15)
                {
                    return_angle_trans = { -0.6f,0.0f,0.0f };
                }
                else
                {
                    return_angle_trans = { 0.6f,0.0f,0.0f };
                }
                break;
            case 3:
                if (m_animation_time > 15)
                {
                    return_angle_trans = { 1.2f,0.0f,0.0f };
                }
                else
                {
                    return_angle_trans = { -1.2f,0.0f,0.0f };
                }
                break;
            case 4:
                if (m_animation_time > 15)
                {
                    return_angle_trans = { -2.0f,0.0f,0.0f };
                }
                else
                {
                    return_angle_trans = { 2.0f,0.0f,0.0f };
                }
                break;
            case 5:
                if (m_animation_time > 15)
                {
                    return_angle_trans = { -2.0f,0.0f,0.0f };
                }
                else
                {
                    return_angle_trans = {2.0f,0.0f,0.0f };
                }
                break;
            case 6:
                if (m_animation_time > 15)
                {
                    return_angle_trans = { 0.6f,0.0f,0.0f };
                }
                else
                {
                    return_angle_trans = { -0.6f,0.0f,0.0f };
                }
                break;
            case 7:
                break;
            case 8:
                break;
            case 9:
                if (m_animation_time > 15)
                {
                    return_angle_trans = { 1.4f,0.0f,0.0f };
                }
                else
                {
                    return_angle_trans = { -1.4f,0.0f,0.0f };
                }
                break;
            case 10:
                if (m_animation_time > 15)
                {
                    return_angle_trans = { 0.6f,0.0f,0.0f };
                }
                else
                {
                    return_angle_trans = { -0.6f,0.0f,0.0f };
                }
                break;
            case 11:
                break;
            case 12:
                break;
            case 13:
                break;
            case 14:
                break;
        }
    }
    else
    {
        switch (parts)
        {
            case 0:
                if (m_animation_time > 15)
                {
                    return_angle_trans = { 0.0f,-0.04f,0.0f };
                }
                else
                {
                    return_angle_trans = { 0.0f,0.04f,0.0f };
                }
                break;
            case 1:
                break;
            case 2:
                if (m_animation_time > 15)
                {
                    return_angle_trans = { 0.0f,0.0f,0.002f };
                }
                else
                {
                    return_angle_trans = { 0.0f,0.0f,-0.002f };
                }
                break;
            case 3:
                if (m_animation_time > 15)
                {
                    return_angle_trans = { 0.0f,-0.01f,0.0f };
                }
                else
                {
                    return_angle_trans = { 0.0f,0.01f,0.0f };
                }
                break;
            case 4:
                if (m_animation_time > 15)
                {
                    return_angle_trans = { 0.0f,-0.01f,0.0f };
                }
                else
                {
                    return_angle_trans = { 0.0f,0.01f,0.0f };
                }
                break;
            case 5:
                if (m_animation_time > 15)
                {
                    return_angle_trans = { 0.0f,0.04f,0.0f };
                }
                else
                {
                    return_angle_trans = { 0.0f,-0.04f,0.0f };
                }
                break;
            case 6:
                if (m_animation_time > 15)
                {
                    return_angle_trans = { 0.0f,0.04f,0.0f };
                }
                else
                {
                    return_angle_trans = { 0.0f,-0.04f,0.0f };
                }
                break;
            case 7:
                break;
            case 8:
                break;
            case 9:
                break;
            case 10:
                break;
            case 11:
                break;
            case 12:
                break;
            case 13:
                break;
            case 14:
                break;
        }
    }

    return return_angle_trans;

}

DirectX::XMFLOAT3 PlayerAnimation::GetClimb(int parts , int angle_trans)
{
    XMFLOAT3 return_angle_trans {};

    if (angle_trans == 0)
    {
        switch (parts)
        {
            case 0:
                break;
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                break;
            case 8:
                break;
            case 9:
                break;
            case 10:
                break;
            case 11:
                break;
            case 12:
                break;
            case 13:
                break;
            case 14:
                break;
        }
    }
    else
    {
        switch (parts)
        {
            case 0:
                break;
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                break;
            case 8:
                break;
            case 9:
                break;
            case 10:
                break;
            case 11:
                break;
            case 12:
                break;
            case 13:
                break;
            case 14:
                break;
        }
    }

    return return_angle_trans;
}
