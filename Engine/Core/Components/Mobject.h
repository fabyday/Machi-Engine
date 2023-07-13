//
// Created by yabai on 2023/01/19.
//

#ifndef MACHI_ENGINE_OBJECT_H
#define MACHI_ENGINE_OBJECT_H
#include "components_config.h"
// All Components' super class

#include "ComponentManager.h"
#include <memory>
#include <Platform/types.h>
namespace Machi{
    namespace Components {

        typedef struct Entity Entity;


        class MACHI_COMPONENTS_API MObject {
            
            std::weak_ptr<ComponentManager> m_component_manger_ptr;
            
            MSTRING m_name;


        public:
            MObject() :m_name(L"test"){};

            MObject(int i) {};

            MObject(std::shared_ptr<ComponentManager> manager) {
                m_component_manger_ptr = manager;
                /*std::shared_ptr<ComponentManager> p_manager = m_component_manger_ptr.lock();
                if (p_manager) {
                    p_manager->add_component(this);
                }*/
                //manager->add_component(this);
                //m_component_manger_ptr-> add_component(this);
            }

            virtual void update() {};
            
            virtual void fixed_update() {};// fixed time update.

            
            template<typename T>
            void add_component(T* component) {
                //ComponentManager
            }
            
            template <typename T, typename ...Args>
            void add_component(T* component, Args... components) {
                add_component(component);
                add_component(components...);
            }
            template<typename T>
            void remove_component(T* compoments) {};



        };
    }
}
#endif //MACHI_ENGINE_OBJECT_H