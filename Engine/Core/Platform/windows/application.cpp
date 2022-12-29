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
#include <Application/application.h>
#include <Graphics/GraphicManager.h>
#include <OS/OS.h>
#include "os_native.h"
#include "common.h"
#include "types.h"
#include <stdexcept>
#include <spdlog/spdlog.h>


bool 
WindowsPlatform::initialize(Application& app) {
    // window initialize.
    const OSContext* context = OS::get_context();
    const MWCHAR* app_name =  app.get_appname().c_str();
    spdlog::info(L"app name : {}", app_name);




    WNDCLASSEX windowClass = { 0 };
    windowClass.cbSize = sizeof(WNDCLASSEX);
    windowClass.style = CS_HREDRAW | CS_VREDRAW;
    windowClass.lpfnWndProc = WindowsPlatform::WindowProc;
    windowClass.hInstance = *(context->hInstance);
    windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    windowClass.lpszClassName = app_name;

    RegisterClassEx(&windowClass);

    RECT windowRect = { app.get_x_pos(), app.get_y_pos(), static_cast<MLONG>(app.get_width()), static_cast<MLONG>(app.get_height()) };


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
        &app);

    if (_handle == nullptr) {
        int x = GetLastError();
        return false;

    }

    spdlog::info("window handle is successfully initialized.");
    WindowsPlatform::set_HWND(_handle);
    ShowWindow(_handle, context->nCmdShow);

    return true;
}


LRESULT 
WindowsPlatform::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    Application* app = reinterpret_cast<Application*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

    UINT uMsg  = message;
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);



        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

        EndPaint(hWnd, &ps);
    }
    return 0;

    
    }

    switch (message)
    {
    case WM_CREATE:
    {
        // Save the DXSample* passed in to CreateWindow.
        LPCREATESTRUCT pCreateStruct = reinterpret_cast<LPCREATESTRUCT>(lParam);
        SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pCreateStruct->lpCreateParams));
    }
    return 0;

    case WM_KEYDOWN:
        if (app)
        {
            //app->OnKeyDown(static_cast<UINT8>(wParam));
        }
        return 0;

    case WM_KEYUP:
        if (app)
        {
            //pSample->OnKeyUp(static_cast<UINT8>(wParam));
        }
        return 0;

    case WM_PAINT:
        if (app)
        {/*
            pSample->OnUpdate();
            pSample->OnRender();*/
        }
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    // Handle any messages the switch statement didn't.
    return DefWindowProc(hWnd, message, wParam, lParam);
}

bool 
Application::_run_logic() {
    // Main sample loop.
    MSG msg = {};
    while (msg.message != WM_QUIT)
    {
        // Process any messages in the queue.
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        GraphicManager::get_instance()->render();
    }
    return true;
}

bool
Application::_initialize() {
    if (!WindowsPlatform::initialize(*this)) // window platform initialize
        return false;

    // directX Graphics components initialize.
    try{

        GraphicManager::get_instance()->initialize(this);
    }
    catch (std::runtime_error e) {
        std::cerr << e.what() << std::endl;
        return false;
    }
    
    return true;
}

// de-allocate resources.
bool 
Application::_finalize() {


    return true;
}

bool 
Application::run(int agrc, char** argv) {
    if (!_initialize())
        return false;
    if (!_run_logic())
        return false;
    if(!_finalize())
        return false;
    
    return true;

}

