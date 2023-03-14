#pragma once

#include <d3d11.h>

#include "Shader.h"
#include "DX11util.h"

// テクスチャを先に読み込み、メモリを空ける
class TextureMgr
{
public:

    // 読み込み（”一度”だけ呼び出し）
    static bool TextureLoad();
    static bool TexutureFinalize();

    static ID3D11ShaderResourceView * white_texture;        // キューブのテクスチャ 1
    static ID3D11ShaderResourceView * number_texture;      // 数字のテクスチャ
    static ID3D11ShaderResourceView * title_back;             // タイトルの背景
    static ID3D11ShaderResourceView * result_game_over;    // ゲームオーバー
    static ID3D11ShaderResourceView * custom_back;          // カスタム画面
    static ID3D11ShaderResourceView * result_score;         // リザルト画面
    //static ID3D11ShaderResourceView * kato_hideyuki;

};