#pragma once

#include "CBillBoard.h"
#include "quad2d.h"

class Result
{
public:

    void ResultLoad();

    // �Q�[���I�[�o�[��
    void ResultInit();
    int ResultUpdate();
    void ResultDraw();
    void ResultFinalize();

    // �Q�[���N���A��

private:

    CBillBoard m_result;

    Quad2D m_go_title;
    Quad2D m_retry;
    Quad2D m_choose_arrow;

    int m_choose_pos;
    bool m_choose_alpha_flg;         // true�̓v���X , false�̓}�C�i�X
    float m_choose_alpha_time;      // alpha�l�𑝌�

};
