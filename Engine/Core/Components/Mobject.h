//
// Created by yabai on 2023/01/19.
//

#ifndef MACHI_ENGINE_OBJECT_H
#define MACHI_ENGINE_OBJECT_H
#include <Platform/config.h>
// All Components' super class
namespace Machi{
    namespace Components {
        class MACHI_API MObject {



            void update();
            void fixed_update();// fixed time update.
            void add_component();
            void add_components();
            

        };
    }
}
#endif //MACHI_ENGINE_OBJECT_H
