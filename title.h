#pragma once
#include "stage/qube.h"
#include "CBillBoard.h"
#include "quad2d.h"

class Title
{
public:

    void TitleInit();
    int TitleUpdate();
    void TitleDraw();
    void TitleFinalize();

    // �^�C�g����ʂ̃f�[�^
    void TitlePreparationData();
    // �^�C�g����ʂ̏���
    void TitlePreparation();

    bool m_ready_flg;                   // �^�C�g����ʂ̏������������Ă��邩

private:

    Qube m_title_qube;

    CBillBoard m_background;

    Quad2D m_title;
    Quad2D m_normal_play;
    Quad2D m_custom_play;
    Quad2D m_challenge_play;
    Quad2D m_choose_arrow;

    int m_choose_pos;
    bool m_choose_move_flg;         // true�̓v���X , false�̓}�C�i�X
    bool m_choose_alpha_flg;         // true�̓v���X , false�̓}�C�i�X
    float m_choose_alpha_time;      // alpha�l�𑝌�

    int m_preparation_num;          // �^�C�g����ʂ̎��
    int m_qube_move_time;           // �L���[�u�������鎞��
    int m_title_move_time;           // �^�C�g���������鎞��
    DirectX::XMFLOAT3 m_qube_pos;       // �ω����Ă����L���[�u�̈ʒu
    DirectX::XMFLOAT3 m_title_pos;      // �ω����Ă����^�C�g���̈ʒu

};
