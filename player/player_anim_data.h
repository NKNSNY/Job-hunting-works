#pragma once

#include "player_anim.h"
#include "dx11mathutil.h"

class PlayerAnimData
{
public:

    static DirectX::XMFLOAT4X4 GetLocalData(PlayerAnimation::ANIMATIONNUM anim_num , DirectX::XMFLOAT4X4 local_mtx , int parts_num);


private:

    static DirectX::XMFLOAT4X4 GetData_Standby(DirectX::XMFLOAT4X4 local_mtx , int parts_num);
    static DirectX::XMFLOAT4X4 GetData_Walk(DirectX::XMFLOAT4X4 local_mtx , int parts_num);
    static DirectX::XMFLOAT4X4 GetData_Climb(DirectX::XMFLOAT4X4 local_mtx , int parts_num);

    static DirectX::XMFLOAT3 m_local_pos_data;
    static DirectX::XMFLOAT3 m_local_angle_data;


};
