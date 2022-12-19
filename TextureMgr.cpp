#include "TextureMgr.h"

bool TextureMgr::TextureLoad()
{
    ID3D11Device * dev = GetDX11Device();
    ID3D11DeviceContext * devcontext = GetDX11DeviceContext();

    CreateSRVfromFile("assets/qube/white.png" , dev , devcontext ,
        nullptr , &white_texture);

    //CreateSRVfromFile("assets/qube/‰Ã“¡wanted.png" , dev , devcontext ,
        //nullptr , &kato_hideyuki);

    dev->Release();
    devcontext->Release();

    return true;
}
