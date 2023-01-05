#include "TextureMgr.h"

bool TextureMgr::TextureLoad()
{
    ID3D11Device * dev = GetDX11Device();
    ID3D11DeviceContext * devcontext = GetDX11DeviceContext();

    CreateSRVfromFile("assets/qube/white.png" , dev , devcontext ,
        nullptr , &white_texture);

    CreateSRVfromFile("assets/UI/number.png" , dev , devcontext ,
        nullptr , &number_texture);

    CreateSRVfromFile("assets/UI/title_back.png" , dev , devcontext ,
        nullptr , &title_back);

    //CreateSRVfromFile("assets/qube/�Ó�wanted.png" , dev , devcontext ,
        //nullptr , &kato_hideyuki);

    dev->Release();
    devcontext->Release();

    return true;
}

bool TextureMgr::TexutureFinalize()
{
    white_texture->Release();
    number_texture->Release();
    title_back->Release();

    return true;
}
