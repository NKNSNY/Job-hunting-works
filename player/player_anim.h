#pragma once

#include <DirectxMath.h>

class PlayerAnimation
{
public:

    // �A�j���[�V�����̎��
    enum ANIMATIONNUM
    {
        STANDBY ,           // �ҋ@
        WALK ,               // ����
        CLIMB ,              // �o��
        DESCEND ,          // �~���
        JUMP ,              // ��э~���
        SET ,                // �����A����
        HEAL ,               // ��
        DAMAGE ,           // �ׂ����
        BLACKHOLE        // �u���b�N�z�[��
    };

    // �A�j���[�V�����X�V����
    DirectX::XMFLOAT3 UpdateAngle(int parts);
    DirectX::XMFLOAT3 UpdateTrans(int parts);

    // �A�j���[�V�������w�肷��
    void SetAnim(ANIMATIONNUM anim_num);

    // �w�肳�ꂽ���Ԃ̃A�j���[�V����
    // �ǂ̃p�[�c��
    // 0 �Ŋp�x��Ԃ��A1 �ňʒu��Ԃ�
    DirectX::XMFLOAT3 GetStandby(int parts , int angle_trans);      // �ҋ@
    DirectX::XMFLOAT3 GetWalk(int parts , int angle_trans);          // ����
    DirectX::XMFLOAT3 GetClimb(int parts , int angle_trans);        // �o��

    // �ǂ̃A�j���[�V������
    ANIMATIONNUM m_anim_num;

    // ���݂̃A�j���[�V�����̎���
    int m_animation_time;

};
