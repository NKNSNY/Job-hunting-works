#pragma once

struct CustomStatus
{
    int stage_width;            // ステージの幅（3～7）
    int stage_height;           // ステージの高さ（5～20）
    int fall_distance;           // キューブの落下距離（500～2000）
    int survival_time;          // キューブの生存時間（500～2000）
    int fall_speed;              // キューブの落下速度（1～9）
    int qube_rate;              // キューブの落下割合（1～9）
};

// ゲームの状態を追加
struct CustomPlus
{
    CustomStatus cs;
    int game_num;             // ゲームの状態
};
