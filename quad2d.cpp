#include	<d3d11.h>
#include	<DirectXMath.h>
#include	<wrl/client.h>
#include	<string>
#include	"dx11mathutil.h"
#include	"dx11util.h"
#include	"Shader.h"
#include	"shaderhashmap.h"
#include	"DX11Settransform.h"
#include	"quad2d.h"

// comptr
using Microsoft::WRL::ComPtr;

// �g�p���钸�_�V�F�[�_�[��
const char * vsfilename [] = {
    "shader/vsquad2d.hlsl"
};

// �g�p����s�N�Z���V�F�[�_�[��
const char * psfilename [] = {
    "shader/psquad2d.hlsl"
};

// ��`�̏�����
bool Quad2D::Init(uint32_t width ,
    uint32_t height ,
    DirectX::XMFLOAT4 color ,
    DirectX::XMFLOAT2 * uv)
{

    DX11MtxIdentity(m_worldmtx);	// �����p��

    // �s�N�Z���V�F�[�_�[�𐶐�
    bool sts = ShaderHashmap::GetInstance()->SetPixelShader(psfilename [0]);
    if (!sts)
    {
        MessageBox(nullptr , "SetPixelShader error" , "error" , MB_OK);
        return false;
    }

    // ���_�f�[�^�̒�`
    D3D11_INPUT_ELEMENT_DESC layout [] =
    {
        { "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
    };

    // �G�������g��
    unsigned int numElements = ARRAYSIZE(layout);

    // ���_�V�F�[�_�[�𐶐�
    sts = ShaderHashmap::GetInstance()->SetVertexShader(
        vsfilename [0] ,			// ���_�V�F�[�_�[�t�@�C����
        layout ,					// ���_���C�A�E�g
        numElements);			// �G�������g��

    // ���_������
    updateVertex(width , height , color , uv);

    // �f�o�C�X���擾
    ID3D11Device * device;
    device = GetDX11Device();

    // ���_�o�b�t�@�𐶐�
    sts = CreateVertexBufferWrite(
        device ,						// �f�o�C�X�I�u�W�F�N�g
        sizeof(Quad2D::Vertex) ,		// �P���_������o�C�g��
        4 ,							// ���_��
        m_vertex ,					// ���_�f�[�^�i�[�������擪�A�h���X
        &m_vertexbuffer				// ���_�o�b�t�@
    );
    if (!sts)
    {
        MessageBox(nullptr , "CreateVertexBuffer error" , "error" , MB_OK);
        return false;
    }

    // �C���f�b�N�X�o�b�t�@�𐶐�
    uint32_t index [4] = { 0,1,2,3 };

    sts = CreateIndexBuffer(
        device ,						// �f�o�C�X�I�u�W�F�N�g
        4 ,							// �C���f�b�N�X��
        index ,						// �C���f�b�N�X�i�[�������擪�A�h���X
        &m_indexbuffer				// �C���f�b�N�X�o�b�t�@
    );
    if (!sts)
    {
        MessageBox(nullptr , "CreateIndexBuffer error" , "error" , MB_OK);
        return false;
    }

    // �r���[�|�[�g�T�C�Y�Z�b�g
    SetViewPortSize(DX11GetScreenWidth() , DX11GetScreenHeight());

    m_color_time = 0;

    return true;
}

// �`��
void Quad2D::Draw()
{
    // �f�o�C�X�R���e�L�X�g���擾
    ID3D11DeviceContext * devcontext;
    devcontext = GetDX11DeviceContext();

    // �e�N�X�`�����Z�b�g
    devcontext->PSSetShaderResources(0 , 1 , m_srv.GetAddressOf());

    // ���W�ϊ��p�̍s����Z�b�g
    DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::WORLD , m_worldmtx);

    unsigned int stride = sizeof(Quad2D::Vertex);	// �X�g���C�h���Z�b�g�i�P���_������̃o�C�g���j
    unsigned  offset = 0;						// �I�t�Z�b�g�l���Z�b�g

    // ���_�o�b�t�@���f�o�C�X�R���e�L�X�g�փZ�b�g
    devcontext->IASetVertexBuffers(
        0 ,									// �X�^�[�g�X���b�g
        1 ,									// ���_�o�b�t�@��
        m_vertexbuffer.GetAddressOf() ,		// ���_�o�b�t�@�̐擪�A�h���X
        &stride ,							// �X�g���C�h
        &offset);							// �I�t�Z�b�g

    // �C���f�b�N�X�o�b�t�@���f�o�C�X�R���e�L�X�g�փZ�b�g
    devcontext->IASetIndexBuffer(
        m_indexbuffer.Get() ,				// �C���f�b�N�X�o�b�t�@
        DXGI_FORMAT_R32_UINT ,				// �t�H�[�}�b�g
        0);									// �I�t�Z�b�g

    // �g�|���W�[���Z�b�g
    devcontext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

    // ���_�V�F�[�_�[�A�s�N�Z���V�F�[�_�[�擾
    ID3D11VertexShader * vs;
    vs = ShaderHashmap::GetInstance()->GetVertexShader(vsfilename [0]);
    ID3D11PixelShader * ps;
    ps = ShaderHashmap::GetInstance()->GetPixelShader(psfilename [0]);

    // ���_���C�A�E�g�擾
    ID3D11InputLayout * layout;
    layout = ShaderHashmap::GetInstance()->GetVertexLayout(vsfilename [0]);

    devcontext->VSSetShader(vs , nullptr , 0);
    devcontext->GSSetShader(nullptr , nullptr , 0);
    devcontext->HSSetShader(nullptr , nullptr , 0);
    devcontext->DSSetShader(nullptr , nullptr , 0);
    devcontext->PSSetShader(ps , nullptr , 0);

    // ���_�t�H�[�}�b�g���Z�b�g
    devcontext->IASetInputLayout(layout);

    // �h���[�R�[�����s
    devcontext->DrawIndexed(
        4 ,						// �C���f�b�N�X��
        0 ,						// �J�n�C���f�b�N�X
        0);						// ����_�C���f�b�N�X
}

void Quad2D::UnInit()
{

}

// �g��A�k��
void Quad2D::SetScale(float sx , float sy , float sz)
{
    DX11MtxScale(sx , sy , sz , m_worldmtx);
}

// �ʒu���Z�b�g
void Quad2D::SetPosition(float x , float y , float z)
{
    m_worldmtx._41 = x;
    m_worldmtx._42 = y;
    m_worldmtx._43 = z;
}

void Quad2D::SetPosition(DirectX::XMFLOAT3 xyz)
{
    m_worldmtx._41 = xyz.x;
    m_worldmtx._42 = xyz.y;
    m_worldmtx._43 = xyz.z;
}

void Quad2D::SetUV(XMFLOAT2 * texture_uv)
{
    for (int i = 0; i < 4; i++)
    {
        m_vertex [i].tex = texture_uv [i];
    }
}

void Quad2D::SetRotationY(float angle)
{
    DX11MtxRotationY(angle , m_worldmtx);
}

// Z����]
void Quad2D::SetRotation(float angle)
{
    DX11MtxRotationZ(angle , m_worldmtx);
}

void Quad2D::SetColor(DirectX::XMFLOAT4 color)
{
    for (int i = 0; i < 4; i++)
    {
        m_vertex [i].color = color;
    }
}

// ���_�f�[�^�X�V
void Quad2D::updateVertex(uint32_t width ,
    uint32_t height ,
    DirectX::XMFLOAT4 color ,
    DirectX::XMFLOAT2 * uv)
{

    m_width = static_cast<float>(width);
    m_height = static_cast<float>(height);

    Quad2D::Vertex	v [4] = {
        // ���W													// �J���[	// UV	
        XMFLOAT3(-m_width / 2.0f,	-m_height / 2.0f, 0.0f),	color,		uv [0],
        XMFLOAT3(m_width / 2.0f,	-m_height / 2.0f, 0.0f),	color,		uv [1],
        XMFLOAT3(-m_width / 2.0f,	 m_height / 2.0f, 0.0f),	color,		uv [2],
        XMFLOAT3(m_width / 2.0f,	 m_height / 2.0f, 0.0f),	color,		uv [3]
    };

    for (int i = 0; i < 4; i++)
    {
        m_vertex [i] = v [i];
    }
}

// ���_�o�b�t�@�X�V
void Quad2D::updateVbuffer()
{
    D3D11_MAPPED_SUBRESOURCE pData;
    HRESULT hr = GetDX11DeviceContext()->Map(m_vertexbuffer.Get() , 0 , D3D11_MAP_WRITE_DISCARD , 0 , &pData);
    if (SUCCEEDED(hr))
    {
        memcpy_s(pData.pData , pData.RowPitch , (void *) (m_vertex) , sizeof(Quad2D::Vertex) * 4);
        GetDX11DeviceContext()->Unmap(m_vertexbuffer.Get() , 0);
    }
}

void Quad2D::ChangeRainbowColor()
{
    if (m_color_time == 0)
    {
        m_vertex [0].color = { 1.0f,0.0f,0.0f,1.0f };
        m_vertex [1].color = { 0.0f,1.0f,0.0f,1.0f };
        m_vertex [2].color = { 0.0f,0.0f,1.0f,1.0f };
        m_vertex [3].color = { 1.0f,0.0f,0.0f,1.0f };
    }
    if (m_color_time >= 1 && m_color_time < 101)
    {
        m_vertex [0].color.x -= 0.01f;
        m_vertex [0].color.y += 0.01f;
        m_vertex [1].color.y -= 0.01f;
        m_vertex [1].color.z += 0.01f;
        m_vertex [2].color.z -= 0.01f;
        m_vertex [2].color.x += 0.01f;
        m_vertex [3].color.x -= 0.01f;
        m_vertex [3].color.y += 0.01f;
    }
    else if (m_color_time >= 101 && m_color_time < 201)
    {
        m_vertex [0].color.y -= 0.01f;
        m_vertex [0].color.z += 0.01f;
        m_vertex [1].color.z -= 0.01f;
        m_vertex [1].color.x += 0.01f;
        m_vertex [2].color.x -= 0.01f;
        m_vertex [2].color.y += 0.01f;
        m_vertex [3].color.y -= 0.01f;
        m_vertex [3].color.z += 0.01f;
    }
    else if (m_color_time >= 201 && m_color_time < 301)
    {
        m_vertex [0].color.z -= 0.01f;
        m_vertex [0].color.x += 0.01f;
        m_vertex [1].color.x -= 0.01f;
        m_vertex [1].color.y += 0.01f;
        m_vertex [2].color.y -= 0.01f;
        m_vertex [2].color.z += 0.01f;
        m_vertex [3].color.z -= 0.01f;
        m_vertex [3].color.x += 0.01f;
    }

    if (m_color_time >= 301)
    {
        m_color_time = 0;
    }

    m_color_time++;
}

void Quad2D::ChangeNumberUV(int uv_num)
{
    switch (uv_num)
    {
        case 0:
            m_vertex [0].tex = { 0.0f,0.05f };
            m_vertex [1].tex = { 0.15f,0.05f };
            m_vertex [2].tex = { 0.0f,0.46f };
            m_vertex [3].tex = { 0.15f,0.46f };
            break;
        case 1:
            m_vertex [0].tex = { 0.2f,0.05f };
            m_vertex [1].tex = { 0.35f,0.05f };
            m_vertex [2].tex = { 0.2f,0.46f };
            m_vertex [3].tex = { 0.35f,0.46f };
            break;
        case 2:
            m_vertex [0].tex = { 0.4f,0.05f };
            m_vertex [1].tex = { 0.55f,0.05f };
            m_vertex [2].tex = { 0.4f,0.46f };
            m_vertex [3].tex = { 0.55f,0.46f };
            break;
        case 3:
            m_vertex [0].tex = { 0.6f,0.05f };
            m_vertex [1].tex = { 0.75f,0.05f };
            m_vertex [2].tex = { 0.6f,0.46f };
            m_vertex [3].tex = { 0.75f,0.46f };
            break;
        case 4:
            m_vertex [0].tex = { 0.8f,0.05f };
            m_vertex [1].tex = { 0.95f,0.05f };
            m_vertex [2].tex = { 0.8f,0.46f };
            m_vertex [3].tex = { 0.95f,0.46f };
            break;
        case 5:
            m_vertex [0].tex = { 0.0f,0.58f };
            m_vertex [1].tex = { 0.15f,0.58f };
            m_vertex [2].tex = { 0.0f,1.0f };
            m_vertex [3].tex = { 0.15f,1.0f };
            break;
        case 6:
            m_vertex [0].tex = { 0.2f,0.58f };
            m_vertex [1].tex = { 0.35f,0.58f };
            m_vertex [2].tex = { 0.2f,1.0f };
            m_vertex [3].tex = { 0.35f,1.0f };
            break;
        case 7:
            m_vertex [0].tex = { 0.4f,0.58f };
            m_vertex [1].tex = { 0.55f,0.58f };
            m_vertex [2].tex = { 0.4f,1.0f };
            m_vertex [3].tex = { 0.55f,1.0f };
            break;
        case 8:
            m_vertex [0].tex = { 0.6f,0.58f };
            m_vertex [1].tex = { 0.75f,0.58f };
            m_vertex [2].tex = { 0.6f,1.0f };
            m_vertex [3].tex = { 0.75f,1.0f };
            break;
        case 9:
            m_vertex [0].tex = { 0.8f,0.58f };
            m_vertex [1].tex = { 0.95f,0.58f };
            m_vertex [2].tex = { 0.8f,1.0f };
            m_vertex [3].tex = { 0.95f,1.0f };
            break;

        default:
            m_vertex [0].tex = { 0.8f,0.58f };
            m_vertex [1].tex = { 0.95f,0.58f };
            m_vertex [2].tex = { 0.8f,1.0f };
            m_vertex [3].tex = { 0.95f,1.0f };
            break;
    }

}

void Quad2D::ChangeSize(int width , int height)
{
    m_width = static_cast<float>(width);
    m_height = static_cast<float>(height);

    // ���W
    XMFLOAT2 v [4] = {
        XMFLOAT2(-m_width / 2.0f,	-m_height / 2.0f),
        XMFLOAT2(m_width / 2.0f,	-m_height / 2.0f),
        XMFLOAT2(-m_width / 2.0f,	 m_height / 2.0f),
        XMFLOAT2(m_width / 2.0f,	 m_height / 2.0f),
    };

    for (int i = 0; i < 4; i++)
    {
        m_vertex [i].pos.x = v [i].x;
        m_vertex [i].pos.y = v [i].y;
    }
}
