#pragma once

#include <d3d11.h>

#include "Shader.h"
#include "DX11util.h"

// �e�N�X�`�����ɓǂݍ��݁A���������󂯂�
class TextureMgr
{
public:

    // �ǂݍ��݁i�h��x�h�����Ăяo���j
    static bool TextureLoad();

    static ID3D11ShaderResourceView * white_texture;        // �L���[�u�̃e�N�X�`�� 1
    //static ID3D11ShaderResourceView * kato_hideyuki;

};