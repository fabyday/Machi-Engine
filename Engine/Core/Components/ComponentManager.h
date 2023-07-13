#pragma once
#include "components_config.h"
#include <entt/entt.hpp>
namespace Machi {
	namespace Components {

		
		typedef struct Entity { entt::entity m_entity; } Entity; // 

		class MACHI_COMPONENTS_API ComponentManager {
			entt::registry m_registry;




			ComponentManager() {
				//m_registry.create();
			}

		public:
			template<typename T>
			void add_component(T* component) {
				//m_registry.insert<T>(*component);
				entt::entity entity = m_registry.create();
				m_registry.emplace<T>(entity);
			}
			
			template <typename T, typename ...Args>
			void add_component(T* component, Args... components) {
				add_component(component);
				add_component(components...);
			}

			void serialize();
			void deserialize();

			inline void remove_all_components() { m_registry.clear(); };

		};
	}
}