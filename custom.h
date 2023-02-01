#pragma once

#include "CBillBoard.h"
#include "quad2d.h"
#include "custom_status.h"

class Custom
{
public:

    void CustomLoad();

    void CustomInit();
    CustomPlus CustomUpdate();
    void CustomDraw();
    void CustomFinalize();

private:

    CBillBoard m_custom;

    Quad2D m_choose_box [6];

    Quad2D m_go_play;
    Quad2D m_go_title;
    Quad2D m_arrow;

    int m_choose_pos;
    bool m_choose_flg;
    bool m_choose_alpha_flg;         // true�̓v���X , false�̓}�C�i�X
    float m_choose_alpha_time;      // alpha�l�𑝌�
    int m_choose_height;               // �ǂ���I��ł���̂��i�c�j
    int m_choose_wight [6];           // �ǂ���I��ł���̂��i���j

    CustomPlus m_csp;

};