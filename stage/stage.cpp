#include <stdlib.h>
#include <vector>

#include "CDirectInput.h"
#include "stage.h"

int Stage::m_stage [20][7][7] {};
int Stage::m_stage_width {};
int Stage::m_stage_hight {};
int Stage::m_stage_bottom {};
int Stage::m_stage_top [7][7] {};
int Stage::m_random_width {};
int Stage::m_random_hight {};
int Stage::m_random_top {};
int Stage::m_create_bottom {};
int Stage::m_stage_color {};
bool Stage::m_stage_color_flg_x [20][7] {};
bool Stage::m_stage_color_flg_y [20][7] {};
bool Stage::m_stage_color_reset_flg {};
int Stage::m_next_add_score {};
int Stage::m_now_add_score {};

std::vector<Qube> g_stage_qube;

bool Stage::Init(int stage_width , int stage_hight , int fall_time , int survival_time , int fall_speed)
{
    m_stage_width = stage_width;
    m_stage_hight = stage_hight;

    // 全てのキューブを初期化
    for (int i = 0; i < m_stage_hight; i++)
    {
        for (int y = 0; y < m_stage_width; y++)
        {
            for (int x = 0; x < m_stage_width; x++)
            {
                m_stage [i][y][x] = 0;
                g_stage_qube.emplace_back();
                g_stage_qube [GetQubeNumber(x , i , y)].Init(0);
                g_stage_qube [GetQubeNumber(x , i , y)].SetFall(fall_time + i * 20.0f , survival_time , fall_speed);
                g_stage_qube [GetQubeNumber(x , i , y)].SetPos({ 0.0f + -y * 20.0f , 0.0f + x * 20.0f , fall_time + i * 20.0f });

                if (i == m_stage_hight - 1)
                {
                    g_stage_qube [GetQubeNumber(x , i , y)].m_shadow_create_flg = false;
                }
            }

            m_stage_color_flg_x [i][y] = false;
            m_stage_color_flg_y [i][y] = false;
        }
    }

    g_stage_qube [32].ChangeTexture(HEAL_QUBE);

    // 一番下は通常ブロックを表示
    for (int y = 0; y < m_stage_width; y++)
    {
        for (int x = 0; x < m_stage_width; x++)
        {
            // 1は通常
            m_stage [0][y][x] = 1;
            g_stage_qube [GetQubeNumber(x , 0 , y)].SetFall(0 , survival_time , 0);
            g_stage_qube [GetQubeNumber(x , 0 , y)].SetPos({ 0.0f + -y * 20.0f , 0.0f + x * 20.0f , 0.0f });
            m_stage_top [y][x] = 0;
        }
    }

    //m_stage [1][1][2] = 1;
    //g_stage_qube [32].m_fall_distance = 0;
    //g_stage_qube [32].SetPos({ -20.0f,40.0f,20.0f });
    //m_stage_top [1][2] = 1;

    //m_stage [2][1][2] = 1;
    //g_stage_qube 57].SetFall(0 , survival_time , 0);
    //g_stage_qube [57].SetPos({ -20.0f,40.0f,40.0f });
    //m_stage_top [1][2] = 2;


    m_stage_bottom = 0;
    m_create_bottom = 0;
    m_stage_color = 2;
    m_stage_color_reset_flg = false;
    m_next_add_score = 40;
    m_now_add_score = 10;

    return true;
}

bool Stage::Update()
{
    bool stage_fall_flg = false;

    // ブロックを時間で消滅
    for (int y = 0; y < m_stage_width; y++)
    {
        for (int x = 0; x < m_stage_width; x++)
        {
            g_stage_qube [GetQubeNumber(x , m_stage_bottom , y)].m_survival_time--;
            if (g_stage_qube [GetQubeNumber(x , m_stage_bottom , y)].m_survival_time == 0)
            {
                m_stage [m_stage_bottom][y][x] = -2;
                stage_fall_flg = true;
            }
        }
    }

    // 一番下が上がる
    if (stage_fall_flg)
    {
        m_stage_bottom++;
        m_create_bottom = 0;
        m_stage_color_reset_flg = true;
    }

    int stage_top {};
    int qube_fall_time;

    // ブロックの落下
    for (int y = 0; y < m_stage_width; y++)
    {
        for (int x = 0; x < m_stage_width; x++)
        {
            stage_top = m_stage_top [y][x];

            if (g_stage_qube [GetQubeNumber(x , stage_top , y)].m_fall_flg)
            {
                g_stage_qube [GetQubeNumber(x , stage_top , y)].m_fall_distance -=
                    g_stage_qube [GetQubeNumber(x , stage_top , y)].m_fall_speed;
                qube_fall_time = g_stage_qube [GetQubeNumber(x , stage_top , y)].m_fall_distance;
                // 落下し終えたか？
                if (qube_fall_time < stage_top * 20)
                {
                    if (m_stage [stage_top][y][x] == 0)
                    {
                        m_stage [stage_top][y][x] = 1;
                    }

                    g_stage_qube [GetQubeNumber(x , stage_top , y)].m_fall_distance = 0;
                    qube_fall_time = stage_top * 20;
                    g_stage_qube [GetQubeNumber(x , stage_top , y)].m_fall_flg = false;
                }
                g_stage_qube [GetQubeNumber(x , stage_top , y)].SetPos({ 0.0f + -y * 20.0f , 0.0f + x * 20.0f , (float) qube_fall_time });
            }
        }
    }

    for (int i = 0; i < m_stage_hight; i++)
    {
        for (int y = 0; y < m_stage_width; y++)
        {
            for (int x = 0; x < m_stage_width; x++)
            {
                if (g_stage_qube [GetQubeNumber(x , i , y)].m_shadow_create_flg)
                {
                    g_stage_qube [GetQubeNumber(x , i , y)].ShadowUpdate(g_stage_qube [GetQubeNumber(x , i + 1 , y)].m_fall_distance ,
                        g_stage_qube [GetQubeNumber(x , i + 1 , y)].m_first_fall_distance);
                }

                // キューブは移動している？
                if (g_stage_qube [GetQubeNumber(x , i , y)].m_move_qube_time < 31)
                {
                    XMFLOAT3 start_pos {};
                    start_pos.x = g_stage_qube [GetQubeNumber(x , i , y)].m_before_qube_pos.x *
                        (1.0f - g_stage_qube [GetQubeNumber(x , i , y)].m_move_qube_time / 30.0f);
                    start_pos.y = g_stage_qube [GetQubeNumber(x , i , y)].m_before_qube_pos.y;
                    //start_pos.y = g_stage_qube [GetQubeNumber(x , i , y)].m_before_qube_pos.y *
                    //    (1.0f - g_stage_qube [GetQubeNumber(x , i , y)].m_move_qube_time / 30.0f);
                    start_pos.z = g_stage_qube [GetQubeNumber(x , i , y)].m_before_qube_pos.z *
                        (1.0f - g_stage_qube [GetQubeNumber(x , i , y)].m_move_qube_time / 30.0f);

                    XMFLOAT3 end_pos {};
                    end_pos.x = g_stage_qube [GetQubeNumber(x , i , y)].m_after_qube_pos.x *
                        g_stage_qube [GetQubeNumber(x , i , y)].m_move_qube_time / 30.0f;
                    end_pos.y = g_stage_qube [GetQubeNumber(x , i , y)].m_after_qube_pos.y;
                    //end_pos.y = g_stage_qube [GetQubeNumber(x , i , y)].m_after_qube_pos.y *
                    //    g_stage_qube [GetQubeNumber(x , i , y)].m_move_qube_time / 30.0f;
                    end_pos.z = g_stage_qube [GetQubeNumber(x , i , y)].m_after_qube_pos.z *
                        g_stage_qube [GetQubeNumber(x , i , y)].m_move_qube_time / 30.0f;

                    g_stage_qube [GetQubeNumber(x , i , y)].SetPos({ start_pos.z + end_pos.z , start_pos.x + end_pos.x , start_pos.y });

                    g_stage_qube [GetQubeNumber(x , i , y)].m_move_qube_time++;

                    // キューブの移動終了
                    if (g_stage_qube [GetQubeNumber(x , i , y)].m_move_qube_time == 31)
                    {
                        XMFLOAT3 swap_pos {};
                        swap_pos.x = g_stage_qube [GetQubeNumber(x , i , y)].m_after_qube_pos.x / 20;
                        swap_pos.y = g_stage_qube [GetQubeNumber(x , i , y)].m_after_qube_pos.y / 20;
                        swap_pos.z = g_stage_qube [GetQubeNumber(x , i , y)].m_after_qube_pos.z / -20;

                        m_stage [(int) swap_pos.y][(int) swap_pos.z][(int) swap_pos.x] = m_stage [i][y][x];

                        QubeType qube_type = g_stage_qube [GetQubeNumber(swap_pos)].m_qube_type;
                        g_stage_qube [GetQubeNumber(swap_pos)].ChangeTexture(g_stage_qube [GetQubeNumber(x , i , y)].m_qube_type);
                        g_stage_qube [GetQubeNumber(x , i , y)].ChangeTexture(qube_type);

                        if (g_stage_qube [GetQubeNumber(x , i , y)].m_move_qube_flg)
                        {
                            g_stage_qube [GetQubeNumber(x , i , y)].m_fall_flg = true;
                            g_stage_qube [GetQubeNumber(x , i , y)].SetPos({ 0.0f + -y * 20.0f , 0.0f + x * 20.0f ,
                                g_stage_qube [GetQubeNumber(x , i , y)].m_fall_distance + i * 20.0f });
                            g_stage_qube [GetQubeNumber(x , i , y)].m_move_qube_flg = false;
                        }
                        else
                        {
                            g_stage_qube [GetQubeNumber(x , i , y)].SetPos({ 0.0f + -y * 20.0f , 0.0f + x * 20.0f ,
                                g_stage_qube [GetQubeNumber(x , i  ,y)].m_fall_distance + i * 20.0f });
                        }
                        m_stage [i][y][x] = 1;
                    }
                }
                g_stage_qube [GetQubeNumber(x , i , y)].Update();
            }
        }
    }

    return true;
}

bool Stage::Draw()
{
    for (int i = m_stage_bottom; i < 4 + m_stage_bottom; i++)
    {
        for (int y = 0; y < m_stage_width; y++)
        {
            for (int x = 0; x < m_stage_width; x++)
            {
                if (m_stage [i][y][x] > 0)
                {
                    g_stage_qube [GetQubeNumber(x , i , y)].ColorUpdate(m_stage [i][y][x]);
                    g_stage_qube [GetQubeNumber(x , i , y)].Draw();
                }
            }
        }
    }

    return true;
}

void Stage::Finalize()
{
}

bool Stage::StageRateUpdate(int stage_qube_rate)
{
    int rand_stage [7][7] {};

    int stage_rate = ((pow(m_stage_width , 2) * stage_qube_rate) / 10.0f) + 0.1f;

    int stage_bottom {};

    if (g_stage_qube [GetQubeNumber(m_random_width , m_random_top , m_random_hight)].m_fall_distance == 0)
    {
        for (int y = 0; y < m_stage_width; y++)
        {
            for (int x = 0; x < m_stage_width; x++)
            {
                if (m_stage [m_stage_bottom + m_create_bottom][y][x] > 0)
                {
                    stage_bottom++;
                }
            }
        }

        if (stage_bottom == pow(m_stage_width , 2))
        {
            m_create_bottom++;
        }

        // 使いまわし
        stage_bottom = 0;

        for (int i = 0; i < stage_rate; i++)
        {
            while (1)
            {
                m_random_width = rand() % m_stage_width;
                m_random_hight = rand() % m_stage_width;
                stage_bottom = rand() % 51;

                if (stage_bottom < 50)
                {
                    stage_bottom = 0;
                }
                else
                {
                    stage_bottom = 1;
                }

                if ((rand_stage [m_random_hight][m_random_width] == 0 &&
                    m_stage_top [m_random_hight][m_random_width] < (m_stage_hight - 1) &&
                    m_stage_top [m_random_hight][m_random_width] < ((m_stage_bottom + 4) - 1)) &&
                    (m_stage_top [m_random_hight][m_random_width] < m_stage_bottom + (stage_bottom + m_create_bottom)))
                {
                    rand_stage [m_random_hight][m_random_width] = 1;
                    m_stage_top [m_random_hight][m_random_width]++;
                    m_random_top = m_stage_top [m_random_hight][m_random_width];
                    m_stage [m_random_top][m_random_hight][m_random_width] = 1;
                    g_stage_qube [GetQubeNumber(m_random_width , m_random_top , m_random_hight)].m_fall_flg = true;
                    break;
                }
                else if ((rand_stage [m_random_hight][m_random_width] == 0 &&
                    m_stage_top [m_random_hight][m_random_width] == (m_stage_hight - 1) ||
                    m_stage_top [m_random_hight][m_random_width] == (((m_stage_bottom + 4) - 1))) ||
                    (m_stage_top [m_random_hight][m_random_width] > m_stage_bottom + (stage_bottom + m_create_bottom)))
                {
                    break;
                }
            }
        }
    }

    return true;
}

ReturnUI Stage::ChangeColor(DirectX::XMFLOAT3 stage_player_pos)
{
    ReturnUI return_num {};

    int stage_color_num {};

    if (m_stage_color_reset_flg)
    {
        for (int i = m_stage_bottom; i < m_stage_hight; i++)
        {
            for (int y = 0; y < m_stage_width; y++)
            {
                for (int x = 0; x < m_stage_width; x++)
                {
                    if (m_stage [i][y][x] == m_stage_color)
                    {
                        m_stage [i][y][x] = 2;
                    }
                    m_stage_color_flg_x [i][y] = false;
                    m_stage_color_flg_y [i][y] = false;
                }
            }
        }
        m_stage_color = 2;
        m_stage_color_reset_flg = false;
    }

    if (m_stage [(int) stage_player_pos.y][(int) stage_player_pos.z][(int) stage_player_pos.x] == 1)
    {
        m_stage [(int) stage_player_pos.y][(int) stage_player_pos.z][(int) stage_player_pos.x] = m_stage_color;
        return_num.stage_score = m_now_add_score;
        if (g_stage_qube [GetQubeNumber(stage_player_pos)].m_qube_type == HEAL_QUBE)
        {
            return_num.player_hp = 5000;
            g_stage_qube [GetQubeNumber(stage_player_pos)].ChangeTexture(NORMAL_QUBE);
        }
    }

    for (int i = 0; i < m_stage_hight; i++)
    {
        for (int y = 0; y < m_stage_width; y++)
        {
            for (int x = 0; x < m_stage_width; x++)
            {
                if (m_stage [i][y][x] == m_stage_color)
                {
                    stage_color_num++;
                }
            }

            if ((stage_color_num == m_stage_width) && (!m_stage_color_flg_x [i][y]))
            {
                for (int i_i = 0; i_i < m_stage_hight; i_i++)
                {
                    for (int y_y = 0; y_y < m_stage_width; y_y++)
                    {
                        for (int x_x = 0; x_x < m_stage_width; x_x++)
                        {
                            if (m_stage [i_i][y_y][x_x] == m_stage_color)
                            {
                                m_stage [i_i][y_y][x_x] = m_stage_color + 1;
                            }
                        }
                    }
                }
                m_stage_color++;
                m_stage_color_flg_x [i][y] = true;
            }
            stage_color_num = 0;
        }
        for (int y = 0; y < m_stage_width; y++)
        {
            for (int x = 0; x < m_stage_width; x++)
            {
                if (m_stage [i][x][y] == m_stage_color)
                {
                    stage_color_num++;
                }
            }

            if ((stage_color_num == m_stage_width) && (!m_stage_color_flg_y [i][y]))
            {
                for (int i_i = 0; i_i < m_stage_hight; i_i++)
                {
                    for (int y_y = 0; y_y < m_stage_width; y_y++)
                    {
                        for (int x_x = 0; x_x < m_stage_width; x_x++)
                        {
                            if (m_stage [i_i][y_y][x_x] == m_stage_color)
                            {
                                m_stage [i_i][y_y][x_x] = m_stage_color + 1;
                            }
                        }
                    }
                }
                m_stage_color++;
                m_stage_color_flg_y [i][y] = true;
            }
            stage_color_num = 0;
        }


    }

    return return_num;
}

bool Stage::ChangeQubePos(DirectX::XMFLOAT3 before_pos , DirectX::XMFLOAT3 after_pos)
{
    bool over_flg = false;

    if (after_pos.x >= m_stage_width)
    {
        over_flg = true;
    }
    else if (after_pos.x <= -1)
    {
        over_flg = true;
    }
    if (after_pos.z >= m_stage_width)
    {
        over_flg = true;
    }
    else if (after_pos.z <= -1)
    {
        over_flg = true;
    }

    // 動かす位置の高さは低いか
    if (!over_flg)
    {
        if (((m_stage_top [(int) after_pos.z][(int) after_pos.x] - m_stage_top [(int) before_pos.z][(int) before_pos.x] == -2) &&
            (g_stage_qube [GetQubeNumber(after_pos)].m_fall_flg)) ||
            ((m_stage_top [(int) after_pos.z][(int) after_pos.x] - m_stage_top [(int) before_pos.z][(int) before_pos.x] == -1) &&
                (g_stage_qube [GetQubeNumber(after_pos.x , after_pos.y - 1 , after_pos.z)].m_fall_flg)))
        {
            after_pos.y -= 1;
        }
    }

    XMFLOAT3 b_poss {};
    b_poss.x = before_pos.x * 20;
    b_poss.y = before_pos.y * 20;
    b_poss.z = -before_pos.z * 20;

    XMFLOAT3 a_poss {};
    a_poss.x = after_pos.x * 20;
    a_poss.y = after_pos.y * 20;
    a_poss.z = -after_pos.z * 20;

    // 動かす位置にいるキューブの設定

    // 動かす位置にキューブは落ちているか
    if (g_stage_qube [GetQubeNumber(before_pos.x , before_pos.y + 1 , before_pos.z)].m_fall_flg)
    {
        g_stage_qube [GetQubeNumber(before_pos)].m_move_qube_flg = true;
        g_stage_qube [GetQubeNumber(before_pos)].m_fall_distance =
            g_stage_qube [GetQubeNumber(before_pos.x , before_pos.y + 1 , before_pos.z)].m_fall_distance;

        g_stage_qube [GetQubeNumber(before_pos.x , before_pos.y + 1 , before_pos.z)].m_fall_distance =
            g_stage_qube [GetQubeNumber(before_pos.x , before_pos.y + 1 , before_pos.z)].m_first_fall_distance;
        g_stage_qube [GetQubeNumber(before_pos.x , before_pos.y + 1 , before_pos.z)].m_fall_flg = false;
        g_stage_qube [GetQubeNumber(before_pos.x , before_pos.y + 1 , before_pos.z)].SetPos({ b_poss.z,b_poss.x,b_poss.y + 20 });
    }
    else
    {
        g_stage_qube [GetQubeNumber(before_pos)].m_fall_distance = g_stage_qube [GetQubeNumber(before_pos)].m_first_fall_distance;
    }

    g_stage_qube [GetQubeNumber(before_pos)].m_fall_flg = false;
    g_stage_qube [GetQubeNumber(before_pos)].m_before_qube_pos = b_poss;
    g_stage_qube [GetQubeNumber(before_pos)].m_after_qube_pos = a_poss;
    g_stage_qube [GetQubeNumber(before_pos)].m_move_qube_time = 0;

    // 動かされた先にいるキューブ設定

    if (!over_flg)
    {
        // 動かされた先にキューブは落ちてきていたか
        if (g_stage_qube [GetQubeNumber(after_pos)].m_fall_flg)
        {
            g_stage_qube [GetQubeNumber(after_pos.x , after_pos.y + 1 , after_pos.z)].m_fall_distance =
                g_stage_qube [GetQubeNumber(after_pos)].m_fall_distance;
            g_stage_qube [GetQubeNumber(after_pos.x , after_pos.y + 1 , after_pos.z)].m_fall_flg = true;
        }

        g_stage_qube [GetQubeNumber(after_pos)].m_fall_distance = 0;
        g_stage_qube [GetQubeNumber(after_pos)].m_fall_flg = false;
        g_stage_qube [GetQubeNumber(after_pos)].SetPos({ a_poss.z , a_poss.x , a_poss.y });

        m_stage_top [(int) before_pos.z][(int) before_pos.x]--;

        m_stage [(int) after_pos.y][(int) after_pos.z][(int) after_pos.x] = 0;

        m_stage_top [(int) after_pos.z][(int) after_pos.x]++;
    }
    else
    {
        m_stage_top [(int) before_pos.z][(int) before_pos.x]--;
    }

    return false;
}

bool Stage::CrushPlayer(DirectX::XMFLOAT3 stage_player_pos , int move_time)
{
    if (move_time == 31)
    {
        if ((m_stage_top [(int) stage_player_pos.z][(int) stage_player_pos.x] == stage_player_pos.y) &&
            (!g_stage_qube [GetQubeNumber(stage_player_pos)].m_fall_flg))
        {
            return true;
        }
    }
    else
    {
        //if ((m_stage_top [(int) stage_player_pos.z][(int) stage_player_pos.x] == stage_player_pos.y) &&
        //    (!g_stage_qube [GetQubeNumber(stage_player_pos)].m_fall_flg) &&
        //    (g_stage_qube [GetQubeNumber(stage_player_pos)].m_move_qube_flg))
        //{
        //    return true;
        //}

    }


    return false;
}

int Stage::GetStageTop(int y , int x)
{
    return m_stage_top [y][x];
}

bool Stage::GetStageFallFlg(int y , int x)
{
    bool flg {};

    float stage_top = m_stage_top [y][x];

    flg = g_stage_qube [GetQubeNumber(x , stage_top , y)].m_fall_flg;

    return flg;
}
