#pragma once

#include "quad2d.h"

class Fade
{
public:

    static void FadeInit();
    static void FadeUpdate();
    static void FadeDraw();
    static void FadeFinalize();

    static int m_fade_time;

private:

    static Quad2D m_fade;

};
