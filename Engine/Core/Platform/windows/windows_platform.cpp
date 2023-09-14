//MIT License 
//Copyright(c) 2022 fabyday
// 
// 
//Permission is hereby granted, free of charge, to any person
//obtaining a copy of this softwareand associated documentation
//files(the "Software"), to deal in the Software without
//restriction, including without limitation the rights to use,
//copy, modify, merge, publish, distribute, sublicense, and /or sell
//copies of the Software, and to permit persons to whom the
//Software is furnished to do so, subject to the following
//conditions :
//
//The above copyright noticeand this permission notice shall be
//included in all copies or substantial portions of the Software.
// 
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
//EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
//OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
//NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
//HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
//WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
//FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
//OTHER DEALINGS IN THE SOFTWARE.
//#include <Application/application.h>
//#include <Graphics/GraphicManager.h>
//#include <OS/OS.h>
#include "windows_platform.h"
#include "common.h"
#include "types.h"
#include <stdexcept>
#include <Logger/Logger.h>
#include <Application/application.h>
namespace Machi {
    namespace Platform {
    WindowsPlatform* g_platform = nullptr;
    struct OSContext WindowsPlatform::ctx_ = { 0 };
     HWND WindowsPlatform::hwnd_ = nullptr;

    }
};
using namespace Machi::Platform;

bool 
//WindowsPlatform::initialize(Machi::Application* app) {
    //if(app != nullptr)
        //m_app = app;
WindowsPlatform::initialize(Machi::Application* app) {
    // window initialize.
    
    if(app != nullptr)
        m_app = app;
    
    //, , ,
    const struct OSContext* context = &WindowsPlatform::ctx_;
    //const struct OSContext* context = nullptr;


    const MWCHAR* app_name = app->get_appname().c_str();

    WNDCLASSEX windowClass = { 0 };
    windowClass.cbSize = sizeof(WNDCLASSEX);
    windowClass.style = CS_HREDRAW | CS_VREDRAW;
    windowClass.lpfnWndProc = WindowsPlatform::WindowProc;
    windowClass.hInstance = *(context->hInstance);
    windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    windowClass.lpszClassName = app_name;

    RegisterClassEx(&windowClass);
    
    RECT windowRect = { app->get_x_pos(), app->get_y_pos(), static_cast<MLONG>(app->get_width()), static_cast<MLONG>(app->get_height())};


    AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE);

    // Create the window and store a handle to it.
    HWND _handle = CreateWindow(
        windowClass.lpszClassName,
        app_name,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        windowRect.right - windowRect.left,
        windowRect.bottom - windowRect.top,
        nullptr,        // We have no parent window.
        nullptr,        // We aren't using menus.
        *(context->hInstance),
        NULL);
    //&app);


    if (_handle == nullptr) {
        int x = GetLastError();
        return false;

    }

    //Machi::Logger::MLogger::get_instance().info(MACHI_DEFAULT_CONSOLE_LOGGER_NAME, "window handle is successfully initialized.");
    WindowsPlatform::set_HWND(_handle);
    ShowWindow(_handle, context->nCmdShow);


    app->initialize();
    return true;
}


LRESULT 
WindowsPlatform::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    //Application* app = reinterpret_cast<Application*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
    Logger::MLogger& logger = Logger::MLogger::get_instance();

    switch (message)
    {
    case WM_CREATE:
    {
        // Save the DXSample* passed in to CreateWindow.
        LPCREATESTRUCT pCreateStruct = reinterpret_cast<LPCREATESTRUCT>(lParam);
        SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pCreateStruct->lpCreateParams));
    }
    return 0;
    case WM_QUIT:
    {
        logger.debug(MACHI_DEFAULT_FILE_LOGGER_NAME, "received quit message.");
    }
        return 0;
    case WM_DESTROY: 
    {
        PostQuitMessage(0);
        logger.info(MACHI_DEFAULT_FILE_LOGGER_NAME, "received destroyed message.");
        return 0;
    }
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);



        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

        EndPaint(hWnd, &ps);
    }
    case WM_KEYDOWN:
    case WM_KEYUP:
        // input manager will handle this.
        return 0;
    case WM_MOUSEHWHEEL:
    case WM_MOUSEHOVER:
    case WM_MOUSEACTIVATE:
    case WM_MOUSEFIRST:
    case WM_MOUSELEAVE:
    case WM_MOUSEWHEEL:
        //input manager will handle this;
        return 0;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

}

bool 
WindowsPlatform::_run_logic() {
    // Main sample loop.
    MSG msg = {};
    while (msg.message != WM_QUIT){
        // Process any messages in the queue.
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)){
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        m_app->_run_logic();
    }

    return true;
}
MTIME WindowsPlatform::get_cur_time() {
    return timeGetTime();
}



// de-allocate resources.
bool 
WindowsPlatform::_finalize() {

    //spdlog::info("finalized...");
    //Logger::MLogger::get_instance().info(MACHI_DEFAULT_CONSOLE_LOGGER_NAME, "finalized...");


    return true;
}



bool 
WindowsPlatform::run(int agrc, char** argv) {
    if (!_run_logic())
        return false;
    return true;

}

OSContext* WindowsPlatform::get_context()
{
    return &WindowsPlatform::ctx_;
}

