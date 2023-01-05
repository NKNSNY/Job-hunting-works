#include "dx11_init.h"
#include <time.h>
#include "DX11util.h"
#include "Application.h"
#include "CDirectInput.h"
#include "TextureMgr.h"


void SystemInit()
{
    srand((unsigned int) time(NULL));

    // DX11������
    DX11Init(
        Application::Instance()->GetHWnd() ,
        Application::CLIENT_WIDTH ,
        Application::CLIENT_HEIGHT ,
        false);

    // �A���t�@�u�����h�L����
    TurnOnAlphablend();

    // DirectT INPUT ������
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
