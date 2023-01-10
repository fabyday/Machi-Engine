#include <Application/application.h>

#include "apple_delegate.h"



static NS::Application* g_pSharedApplication = nullptr;
Machi::apple_delegate g_app_delegate;



bool Machi::Application::_initialize(){
    NS::AutoreleasePool* pAutoreleasePool = NS::AutoreleasePool::alloc()->init();
    NS::Application* pSharedApplication = NS::Application::sharedApplication();
    pSharedApplication->setDelegate( &g_app_delegate );
    pSharedApplication->run();

    pAutoreleasePool->release();

    return true;
}
bool Machi::Application::_run_logic(){}

bool Machi::Application::_finalize(){

}
bool Machi::Application::run(int argc, char** argv){

}
