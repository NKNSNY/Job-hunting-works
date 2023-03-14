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
    static bool TexutureFinalize();

    static ID3D11ShaderResourceView * white_texture;        // �L���[�u�̃e�N�X�`�� 1
    static ID3D11ShaderResourceView * number_texture;      // �����̃e�N�X�`��
    static ID3D11ShaderResourceView * title_back;             // �^�C�g���̔w�i
    static ID3D11ShaderResourceView * result_game_over;    // �Q�[���I�[�o�[
    static ID3D11ShaderResourceView * custom_back;          // �J�X�^�����
    static ID3D11ShaderResourceView * result_score;         // ���U���g���
    //static ID3D11ShaderResourceView * kato_hideyuki;

};