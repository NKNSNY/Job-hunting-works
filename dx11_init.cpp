#include "dx11_init.h"
#include <time.h>
#include "DX11util.h"
#include "Application.h"
#include "CDirectInput.h"
#include "TextureMgr.h"


void SystemInit()
{
    srand((unsigned int) time(NULL));

    // DX11初期化
    DX11Init(
        Application::Instance()->GetHWnd() ,
        Application::CLIENT_WIDTH ,
        Application::CLIENT_HEIGHT ,
        false);

    // アルファブレンド有効化
    TurnOnAlphablend();

    // DirectT INPUT 初期化
    CDirectInput::GetInstance().Init(
        Application::Instance()->GetHInst() ,
        Application::Instance()->GetHWnd() ,
        Application::CLIENT_WIDTH ,
        Application::CLIENT_HEIGHT);

    TextureMgr::TextureLoad();


}

void SystemFinalize()
{
    TextureMgr::TexutureFinalize();

    DX11Uninit();
}
