#include <Application/application.h>

class AppDelegate : public NS::ApplicationDelegate
{
public:
    ~MyAppDelegate();

    NS::Menu* createMenuBar();

    virtual void applicationWillFinishLaunching( NS::Notification* pNotification ) override;
    virtual void applicationDidFinishLaunching( NS::Notification* pNotification ) override;
    virtual bool applicationShouldTerminateAfterLastWindowClosed( NS::Application* pSender ) override;

private:
    NS::Window* _pWindow;
    MTK::View* _pMtkView;
    MTL::Device* _pDevice;
    MyMTKViewDelegate* _pViewDelegate = nullptr;
};



void AppDelegate::applicationDidFinishLaunching(int *pNotification) {}

bool AppDelegate::applicationShouldTerminateAfterLastWindowClosed(int *pSender) {}

void AppDelegate::applicationWillFinishLaunching(int *pNotification) {}

int *AppDelegate::createMenuBar() {}