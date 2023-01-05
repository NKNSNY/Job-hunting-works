#pragma once

#include <vector>

#include "qube.h"

struct ReturnUI
{
    int player_hp;
    int stage_score;
    int color_change_score;
};

class Stage
{
public:

    // �X�e�[�W�̕��A�����A���������A�������ԁA�������x����́i����@�� 7�@���� 20�j
    static bool Init(int stage_width , int stage_hight , int fall_time , int survival_time , int fall_speed);
    static bool Update();
    static bool Draw();
    static void Finalize();

    // �ݒ肵���������L���[�u������
    static bool StageRateUpdate(int stage_qube_rate);
    // �v���C���[�̈ʒu�̐F��ς���
    static ReturnUI ChangeColor(DirectX::XMFLOAT3 stage_player_pos);
    // �v���C���[�����������L���[�u�����ւ���
    static bool ChangeQubePos(DirectX::XMFLOAT3 before_pos , DirectX::XMFLOAT3 after_pos);
    // �v���C���[���ׂ���Ă��邩
    static bool CrushPlayer(DirectX::XMFLOAT3 stage_player_pos , int move_time);

    // �X�e�[�W�̃g�b�v���擾
    static int GetStageTop(int y , int x);
    // �L���[�u���������I���Ă邩�擾
    static bool GetStageFallFlg(int y , int x);

private:

    // �L���[�u�̔ԍ����擾(���� , ���� , �c��)
    static int GetQubeNumber(DirectX::XMFLOAT3 number)
    {
        return (number.z * m_stage_width) + number.x + (number.y * pow(m_stage_width , 2));
    }
    // �L���[�u�̔ԍ����擾(���� , ���� , �c��)
    static int GetQubeNumber(float number_x , float number_y , float number_z)
    {
        return (number_z * m_stage_width) + number_x + (number_y * pow(m_stage_width , 2));
    }

    // �X�e�[�W�̑傫���@[����][�c��][����]
    static int m_stage [20][7][7];

    static int m_stage_width;           // �X�e�[�W�̉���
    static int m_stage_hight;           // �X�e�[�W�̏c��

    static int m_stage_bottom;         // �X�e�[�W�̌��݂̈�ԉ�
    static int m_stage_top [7][7];    // �X�e�[�W�̌��݂̍����̏��

    static int m_random_width;        // ���̗����ʒu
    static int m_random_hight;        // �c�̗����ʒu
    static int m_random_top;          // �����_���őI�΂ꂽ�ʒu�̍���

    static int m_create_bottom;      // ���������̏�����グ�Ă���

    static int m_stage_color;          // ���݂̃X�e�[�W�̐F
    static bool m_stage_color_flg_x [20][7];        // �����̐F��ς���t���O
    static bool m_stage_color_flg_y [20][7];        // �c���̐F��ς���t���O
    static bool m_stage_color_reset_flg;             // �F�����Z�b�g����t���O

    static int m_next_add_score;                      // �F���ς�������ɑ����鐔�l
    static int m_now_add_score;                       // ���݂̑�����X�R�A

};