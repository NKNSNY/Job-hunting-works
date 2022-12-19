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

    static ID3D11ShaderResourceView * white_texture;        // キューブのテクスチャ 1
    //static ID3D11ShaderResourceView * kato_hideyuki;

};