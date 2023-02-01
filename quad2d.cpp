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

// 使用する頂点シェーダー名
const char * vsfilename [] = {
    "shader/vsquad2d.hlsl"
};

// 使用するピクセルシェーダー名
const char * psfilename [] = {
    "shader/psquad2d.hlsl"
};

// 矩形の初期化
bool Quad2D::Init(uint32_t width ,
    uint32_t height ,
    DirectX::XMFLOAT4 color ,
    DirectX::XMFLOAT2 * uv)
{

    DX11MtxIdentity(m_worldmtx);	// 初期姿勢

    // ピクセルシェーダーを生成
    bool sts = ShaderHashmap::GetInstance()->SetPixelShader(psfilename [0]);
    if (!sts)
    {
        MessageBox(nullptr , "SetPixelShader error" , "error" , MB_OK);
        return false;
    }

    // 頂点データの定義
    D3D11_INPUT_ELEMENT_DESC layout [] =
    {
        { "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
    };

    // エレメント数
    unsigned int numElements = ARRAYSIZE(layout);

    // 頂点シェーダーを生成
    sts = ShaderHashmap::GetInstance()->SetVertexShader(
        vsfilename [0] ,			// 頂点シェーダーファイル名
        layout ,					// 頂点レイアウト
        numElements);			// エレメント数

    // 頂点初期化
    updateVertex(width , height , color , uv);

    // デバイスを取得
    ID3D11Device * device;
    device = GetDX11Device();

    // 頂点バッファを生成
    sts = CreateVertexBufferWrite(
        device ,						// デバイスオブジェクト
        sizeof(Quad2D::Vertex) ,		// １頂点当たりバイト数
        4 ,							// 頂点数
        m_vertex ,					// 頂点データ格納メモリ先頭アドレス
        &m_vertexbuffer				// 頂点バッファ
    );
    if (!sts)
    {
        MessageBox(nullptr , "CreateVertexBuffer error" , "error" , MB_OK);
        return false;
    }

    // インデックスバッファを生成
    uint32_t index [4] = { 0,1,2,3 };

    sts = CreateIndexBuffer(
        device ,						// デバイスオブジェクト
        4 ,							// インデックス数
        index ,						// インデックス格納メモリ先頭アドレス
        &m_indexbuffer				// インデックスバッファ
    );
    if (!sts)
    {
        MessageBox(nullptr , "CreateIndexBuffer error" , "error" , MB_OK);
        return false;
    }

    // ビューポートサイズセット
    SetViewPortSize(DX11GetScreenWidth() , DX11GetScreenHeight());

    m_color_time = 0;

    return true;
}

// 描画
void Quad2D::Draw()
{
    // デバイスコンテキストを取得
    ID3D11DeviceContext * devcontext;
    devcontext = GetDX11DeviceContext();

    // テクスチャをセット
    devcontext->PSSetShaderResources(0 , 1 , m_srv.GetAddressOf());

    // 座標変換用の行列をセット
    DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::WORLD , m_worldmtx);

    unsigned int stride = sizeof(Quad2D::Vertex);	// ストライドをセット（１頂点当たりのバイト数）
    unsigned  offset = 0;						// オフセット値をセット

    // 頂点バッファをデバイスコンテキストへセット
    devcontext->IASetVertexBuffers(
        0 ,									// スタートスロット
        1 ,									// 頂点バッファ個数
        m_vertexbuffer.GetAddressOf() ,		// 頂点バッファの先頭アドレス
        &stride ,							// ストライド
        &offset);							// オフセット

    // インデックスバッファをデバイスコンテキストへセット
    devcontext->IASetIndexBuffer(
        m_indexbuffer.Get() ,				// インデックスバッファ
        DXGI_FORMAT_R32_UINT ,				// フォーマット
        0);									// オフセット

    // トポロジーをセット
    devcontext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

    // 頂点シェーダー、ピクセルシェーダー取得
    ID3D11VertexShader * vs;
    vs = ShaderHashmap::GetInstance()->GetVertexShader(vsfilename [0]);
    ID3D11PixelShader * ps;
    ps = ShaderHashmap::GetInstance()->GetPixelShader(psfilename [0]);

    // 頂点レイアウト取得
    ID3D11InputLayout * layout;
    layout = ShaderHashmap::GetInstance()->GetVertexLayout(vsfilename [0]);

    devcontext->VSSetShader(vs , nullptr , 0);
    devcontext->GSSetShader(nullptr , nullptr , 0);
    devcontext->HSSetShader(nullptr , nullptr , 0);
    devcontext->DSSetShader(nullptr , nullptr , 0);
    devcontext->PSSetShader(ps , nullptr , 0);

    // 頂点フォーマットをセット
    devcontext->IASetInputLayout(layout);

    // ドローコール発行
    devcontext->DrawIndexed(
        4 ,						// インデックス数
        0 ,						// 開始インデックス
        0);						// 基準頂点インデックス
}

void Quad2D::UnInit()
{

}

// 拡大、縮小
void Quad2D::SetScale(float sx , float sy , float sz)
{
    DX11MtxScale(sx , sy , sz , m_worldmtx);
}

// 位置をセット
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

// Z軸回転
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

// 頂点データ更新
void Quad2D::updateVertex(uint32_t width ,
    uint32_t height ,
    DirectX::XMFLOAT4 color ,
    DirectX::XMFLOAT2 * uv)
{

    m_width = static_cast<float>(width);
    m_height = static_cast<float>(height);

    Quad2D::Vertex	v [4] = {
        // 座標													// カラー	// UV	
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

// 頂点バッファ更新
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

    // 座標
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
