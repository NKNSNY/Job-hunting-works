//*****************************************************************************
//!	@file	Application.cpp
//!	@brief	
//!	@note	アプリケーションクラス
//!	@author	
//*****************************************************************************

//-----------------------------------------------------------------------------
//	Include header files.
//-----------------------------------------------------------------------------
#include <Crtdbg.h>
#include <Windows.h>
#include <chrono>
#include <thread>
#include "Application.h"
#include "CWindow.h"
#include "macro.h"
#include "dx11_init.h"
#include "game.h"
#include "title.h"
#include "fade.h"
#include "result.h"
#include "custom.h"
#include "custom_status.h"
#include "result_score.h"

//-----------------------------------------------------------------------------
// スタティック　メンバー
//-----------------------------------------------------------------------------
const char * Application::WINDOW_TITLE = "神は細部に宿る";
const char * Application::WINDOW_CLASS_NAME = "win32app";

const uint32_t		Application::WINDOW_STYLE_WINDOWED = (WS_VISIBLE | WS_CAPTION | WS_SYSMENU);
const uint32_t		Application::WINDOW_EX_STYLE_WINDOWED = (0);
const uint32_t		Application::WINDOW_STYLE_FULL_SCREEN = (WS_VISIBLE | WS_POPUP);
const uint32_t		Application::WINDOW_EX_STYLE_FULL_SCREEN = (0);

const uint32_t		Application::CLIENT_WIDTH = 1280;
const uint32_t		Application::CLIENT_HEIGHT = 720;

uint32_t			Application::SYSTEM_WIDTH = 0;
uint32_t			Application::SYSTEM_HEIGHT = 0;

const float			Application::FPS = 60;

enum AppState
{
    TITLE_INIT ,
    TITLE ,
    GAME_INIT ,
    GAME ,
    CUSTOM_INIT ,
    CUSTOM ,
    RESULT_INT ,
    RESULT ,
};

AppState app_state;

//==============================================================================
//!	@fn		CApplication
//!	@brief	コンストラクタ
//!	@param	
//!	@retval	
//==============================================================================
Application::Application() : m_SystemCounter(0)
{
}

//==============================================================================
//!	@fn		~Application
//!	@brief	デストラクタ
//!	@param	
//!	@retval	
//==============================================================================
Application :: ~Application()
{
    Dispose();
}

//==============================================================================
//!	@fn		GetInstance
//!	@brief	インスタンス取得
//!	@param	
//!	@retval	インスタンス
//==============================================================================
Application * Application::Instance()
{
    static Application Instance;

    return &Instance;
}

//==============================================================================
//!	@fn		InitSystemWH
//!	@brief	システム領域の幅と高さを初期化
//!	@param	
//!	@retval	
//==============================================================================
void Application::InitSystemWH()
{

}

//==============================================================================
//!	@fn		Init
//!	@brief	初期化
//!	@param	インスタンスハンドル
//!	@retval	
//==============================================================================
bool Application::Init(HINSTANCE h_Instance)
{
    // メモリーリークを検出
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    // コンソールを割り当てる
    AllocConsole();

    // 標準出力の割り当て
    freopen_s(&m_fp , "CON" , "w" , stdout);

    // 幅と高さ初期化
    InitSystemWH();

    // ウインドウ作成
    CWindow * window = CWindow::Instance();
    window->RegisterClass(h_Instance , WINDOW_CLASS_NAME , CS_OWNDC);

    window->SetWindow(h_Instance ,
        WINDOW_STYLE_WINDOWED ,
        WINDOW_EX_STYLE_WINDOWED ,
        NULL ,
        CLIENT_WIDTH + SYSTEM_WIDTH ,
        CLIENT_HEIGHT + SYSTEM_HEIGHT ,
        WINDOW_CLASS_NAME ,
        WINDOW_TITLE ,
        false);

    // HWND
    m_hWnd = window->GetHandle();

    //
    m_hInst = h_Instance;
    return true;
}

//==============================================================================
//!	@fn		Dispose
//!	@brief  終了処理
//!	@param	
//!	@retval	
//==============================================================================
void Application::Dispose()
{
    // 標準出力クローズ
    fclose(m_fp);
    // コンソール開放
    ::FreeConsole();

    return;
}

//==============================================================================
//!	@fn		MainLoop
//!	@brief	メインループ
//!	@param	
//!	@retval	メッセージID
//==============================================================================
unsigned long Application::MainLoop()
{
    MSG		msg;
    ZeroMemory(&msg , sizeof(msg));

    CWindow * window = CWindow::Instance();

    uint64_t current_time = 0;
    uint64_t last_time = 0;

    // DX11初期化
    SystemInit();

    uint64_t delta_time = current_time - last_time;
    int64_t sleep_time = 16666 - delta_time;

    app_state = TITLE_INIT;

    Title title;
    Result result;
    Custom custom;
    int game_num = 10;
    CustomPlus csp = { 5 , 10 , 1000 , 1000 , 5 , 2 , 10 };
    //CustomPlus csp = { 5 , 100 , 1000 , 500 , 10 , 10 , 10 };
    ResultScore rs = { 0,0,0,0,0,0,0,0,0,0 };

    title.TitleLoad();
    result.ResultLoad();
    custom.CustomLoad();
    GameLoad();

    // タイマ解像度をミリ秒に
    ::timeBeginPeriod(1);

    // ゲームループ
    while (window->ExecMessage())
    {
        switch (app_state)
        {
            // タイトルの初期化
            case TITLE_INIT:
                title.TitleInit();
                title.TitlePreparationData();
                app_state = TITLE;
                csp = { 5 , 10 , 1000 , 1000 , 5 , 2 , 10 };
                Fade::FadeInit();
                break;
                // タイトル処理
            case TITLE:
                if (!title.m_ready_flg)
                {
                    title.TitlePreparation();
                }
                else
                {
                    game_num = title.TitleUpdate();
                }

                if (Fade::m_fade_time < 500)
                {
                    Fade::FadeUpdate();
                    Fade::FadeDraw();
                    break;
                }

                title.TitleDraw();
                break;
                // ゲームの初期処理
            case GAME_INIT:
                Fade::FadeInit();
                Fade::FadeDraw();
                GameInit(csp.cs);
                app_state = GAME;
                break;
                // ゲーム本編
            case GAME:

                if (Fade::m_fade_time < 500)
                {
                    Fade::FadeUpdate();
                    Fade::FadeDraw();
                    break;
                }

                // timeGetTime関数は、ミリ秒単位でシステム時刻を取得します。 
                // システム時間は、Windowsを起動してからの経過時間です。
                current_time = ::timeGetTime();

                last_time = current_time;

                GameInput(delta_time);		// ｹﾞｰﾑ入力	
                rs = GameUpdate(delta_time);		// ｹﾞｰﾑ更新
                GameRender(delta_time);		// ｹﾞｰﾑ描画

                game_num = rs.result_judge;

                if (sleep_time > 0)
                {
                    float tt = sleep_time / 1000.0f;
                    //			printf("sleep:%f \n", tt);
                    std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(tt)));
                    //指定した相対時間だけ現スレッドをブロックする (function template)
                }
                break;
            case CUSTOM_INIT:
                custom.CustomInit();
                app_state = CUSTOM;
                break;
            case CUSTOM:
                csp = custom.CustomUpdate();
                game_num = csp.game_num;
                custom.CustomDraw();
                break;

            case RESULT_INT:
                result.ResultInit(rs);
                app_state = RESULT;
                Fade::FadeInit();
                break;
            case RESULT:
                if (Fade::m_fade_time < 500)
                {
                    Fade::FadeUpdate();
                    Fade::FadeDraw();
                    break;
                }

                game_num = result.ResultUpdate();
                result.ResultDraw();
                break;
        }

        switch (game_num)
        {
            // ゲーム開始
            case 0:
                app_state = GAME_INIT;
                game_num = 10;
                break;
                // カスタム画面
            case 1:
                app_state = CUSTOM_INIT;
                game_num = 10;
                break;
                // チャレンジ画面
            case 2:
                game_num = 10;
                break;
                // ゲームクリア
            case 3:
                app_state = RESULT_INT;
                game_num = 10;
                break;
                // ゲームオーバー
            case  4:
                app_state = RESULT_INT;
                game_num = 10;
                break;
                // タイトル画面
            case 5:
                app_state = TITLE_INIT;
                game_num = 10;
                break;
            default:
                break;
        }

    }

    // タイマ解像度を元に戻す
    ::timeEndPeriod(1);

    // ゲームの終了処理
    GameDispose();

    SystemFinalize();

    return window->GetMessage();
}

//==============================================================================
//!	@fn		Input
//!	@brief	キー入力
//!	@param	
//!	@retval	
//==============================================================================
void Application::Input(uint64_t deltataime)
{
}

//==============================================================================
//!	@fn		Update
//!	@brief	更新
//!	@param	
//!	@retval	
//==============================================================================
void Application::Update(uint64_t deltataime)
{
    // システムカウンタ
    m_SystemCounter++;
}

//==============================================================================
//!	@fn		Render
//!	@brief	描画
//!	@param	
//!	@retval	
//==============================================================================
void Application::Render(uint64_t deltatime)
{
}

//==============================================================================
//!	@fn		GetHWnd
//!	@brief	HWND 取得
//!	@param	
//!	@retval	HWND
//==============================================================================
HWND Application::GetHWnd()
{
    return m_hWnd;
}

//==============================================================================
//!	@fn		GetHInst
//!	@brief	HINSTANCE 取得
//!	@param	
//!	@retval	HINSTANCE
//==============================================================================
HINSTANCE Application::GetHInst()
{
    return m_hInst;
}

//******************************************************************************
//	End of file.
//******************************************************************************
