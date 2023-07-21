//
// Created by yabai on 2023/01/19.
//

#ifndef MACHI_ENGINE_OBJECT_H
#define MACHI_ENGINE_OBJECT_H
#include "components_config.h"
// All Components' super class

#include "ComponentManager.h"
#include <memory>
#include <stdexcept>
#include <Platform/types.h>
namespace Machi{
    namespace Components {

        class MACHI_COMPONENTS_API MObject {
            
            std::weak_ptr<ComponentManager> m_component_manger_ptr;
            
            MSTRING m_name;
            Entity m_entity;


        public:
            
            MObject(std::shared_ptr<ComponentManager> manager) {
                m_component_manger_ptr = manager;
                if(manager)
                    m_entity = manager->create_entity();
                else {
                    throw std::runtime_error("wrong memory pointer error");
                }
            }

            ~MObject() {
                get_component_manager_ptr()->remove_all_components_from_entity(m_entity);
                get_component_manager_ptr()->destroy_entity(m_entity);
            }

            inline std::shared_ptr<ComponentManager> get_component_manager_ptr() {
                std::shared_ptr<ComponentManager> p_manager = m_component_manger_ptr.lock();
                if (!p_manager)
                    throw std::runtime_error("ptr is nullptr");
                return p_manager;
            }


            virtual void initialize() {};
            
            virtual void update() {};
            
            virtual void fixed_update() {};// fixed time update. 

            virtual void finalize() {};
            
            template<typename T>
            T& add_component() {
                get_component_manager_ptr()->add_component<T>(this->m_entity);
            }
            
            template <typename T, typename ...Args>
            T& add_component(Args... args) {
                get_component_manager_ptr()->add_component<T>(this->m_entity, std::forward<Args>(args)...);
            }

            template <typename T>
            T& get_component() {
                return get_component_manager_ptr()->get();
            }
            template <typename T>
            bool has_component() {
                return get_component_manager_ptr()->has_component<T>();
            }

            template<typename T>
            void remove_component() {
                //get_component_manager_ptr()->remove_all_components()
            }



        };
    }
}
#endif //MACHI_ENGINE_OBJECT_H