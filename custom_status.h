#pragma once

struct CustomStatus
{
    int stage_width;            // �X�e�[�W�̕��i3�`7�j
    int stage_height;           // �X�e�[�W�̍����i5�`20�j
    int fall_distance;           // �L���[�u�̗��������i500�`2000�j
    int survival_time;          // �L���[�u�̐������ԁi500�`2000�j
    int fall_speed;              // �L���[�u�̗������x�i1�`9�j
    int qube_rate;              // �L���[�u�̗��������i1�`9�j
};

// �Q�[���̏�Ԃ�ǉ�
struct CustomPlus
{
    CustomStatus cs;
    int game_num;             // �Q�[���̏��
};
