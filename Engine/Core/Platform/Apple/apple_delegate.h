//
// Created by yabai on 2023/01/11.
//

#ifndef MACHI_ENGINE_APPLE_DELEGATE_H
#define MACHI_ENGINE_APPLE_DELEGATE_H
#include "Graphics/machi_graphics.h"
namespace Machi{


    class MachiMTKViewDelegate : public MTK::ViewDelegate
    {
    public:
        MachiMTKViewDelegate(MTL::Device* pDevice );
        virtual ~MachiMTKViewDelegate() override;
        virtual void drawInMTKView( MTK::View* pView ) override;

    private:
        Renderer* _pRenderer;
    };

    class MachiAppDelegate: public NS::ApplicationDelegate
    {
    public:
        ~MachiAppDelegate();

        NS::Menu* createMenuBar();

        virtual void applicationWillFinishLaunching( NS::Notification* pNotification ) override;
        virtual void applicationDidFinishLaunching( NS::Notification* pNotification ) override;
        virtual bool applicationShouldTerminateAfterLastWindowClosed( NS::Application* pSender ) override;

    private:
        NS::Window* _pWindow;
        MTK::View* _pMtkView;
        MTL::Device* _pDevice;
        MachiMTKViewDelegate* _pViewDelegate = nullptr;
    };

}

#endif //MACHI_ENGINE_APPLE_DELEGATE_H
