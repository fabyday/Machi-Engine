#pragma once
#include "components_config.h"
#include <entt/entt.hpp>

namespace Machi {
	namespace Components {

		
		typedef entt::entity Entity; // 

		class MACHI_COMPONENTS_API ComponentManager {
			entt::registry m_registry;
			//Entity m_root_entity;



			ComponentManager() {
				//m_root_entity = m_registry.create();
			}

		public:
			Entity create_entity() {
				return m_registry.create();
			}
		
			template<typename T, typename ...Args>
			T& add_component(Entity entity, Args... args) {
				return m_registry.emplace<T>(entity, std::forward(args)...);
			}
			template<typename T>
			T& add_component(Entity entity) {
				return m_registry.emplace<T>(Entity entity);
			}
			/*template <typename T, typename ...Args>
			void add_component(T* component, Args... components) {
				add_component(component);
				add_component(components...);
			}*/

			


			void serialize();
			void deserialize();
			
			
			template <typename T>
			inline T& get_component(Entity entity) {
				return m_registry.get<T>(entity);
			}

			template <typename T>
			bool has_component() {
				return m_registry.has<T>();
			}


			inline void remove_all_components() { m_registry.clear(); };
			
			template<typename T>
			inline void remove_component(Entity entity) {
				m_registry.remove()
			}
		};
	}
}