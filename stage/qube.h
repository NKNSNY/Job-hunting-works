#pragma once

#include "gameobject.h"
#include "CModel.h"
#include "CBillBoard.h"

// �L���[�u�̎��
enum QubeType
{
    NORMAL_QUBE ,
    HEAL_QUBE ,
};

class Qube :public GameObject
{
public:

    void Load();

    bool Init();
    bool Update();
    bool Draw();
    bool Draw(int not_billboard_draw);    // �L���[�u�����`��
    void Finalize();

    // �v���C���[�ɓ��܂ꂽ�Ƃ���̐F��ς���
    bool ColorUpdate(int color_num);
    // ��ɃL���[�u������Ȃ�e���ω�
    bool ShadowUpdate(int fall_distance , int first_fall_distance);
    // �ړ��ɂ��e�N�X�`���̕ύX
    bool ChangeTexture(QubeType qube_type);

    // �c���A�����A�����̏��œ����
    bool SetPos(DirectX::XMFLOAT3 pos);
    // ���������A�������ԁA�������x�̕ω���
    bool SetFall(int fall_distance , int survival_time , int fall_speed);
    // ��]����
    bool SetRot(DirectX::XMFLOAT3 rot);
    // �L���[�u�X�e�[�^�X�̓���ւ�
    void SetQubeStatus(Qube qube);

    int m_fall_distance;               // ��������
    int m_survival_time;              // �c���Ă��鎞��
    int m_fall_speed;                  // �������x
    bool m_fall_flg;                    // �������邩�ۂ�
    int m_first_survival_time;      // ���̎c���Ă鎞��
    int m_first_fall_distance;      // ���̗�������

    bool m_shadow_create_flg;     // �e���o�����ǂ���

    int m_delete_fall_time;          // �ޗ��ɗ����Ă�������
    bool m_delete_fall_flg;          // �ޗ��ɗ����邩�ǂ���

    DirectX::XMFLOAT3 m_before_qube_pos;        // �L���[�u�̓����O�̈ʒu
    DirectX::XMFLOAT3 m_after_qube_pos;         // �L���[�u�̓�������̈ʒu
    int m_move_qube_time;                              // �L���[�u�̐��`���

    bool m_move_qube_flg;                              // �������L���[�u�̈ʒu�ɃL���[�u�͗����ė��Ă��邩

    QubeType m_qube_type;                            // �L���[�u�̎��

    float m_survival_alpha;                            // ���X�ɍ����Ȃ��Ă���

    DirectX::XMFLOAT2 m_shadow_size;            // �e�̑傫��

private:

    const char * XfileName;

    static bool m_modelloadflg;

    CModel * m_model;

    CBillBoard m_qube_texture [6];          // �L���[�u�̃e�N�X�`��
    CBillBoard m_qube_alpha [5];             // ���Ԍo�߂ō�����
    CBillBoard m_qube_shadow;               // �����̉e

};