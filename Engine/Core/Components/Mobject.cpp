//
// Created by yabai on 2023/01/19.
//

#include "Mobject.h"
#include <entt/entt.hpp>



using namespace Machi::Components;



void test(ComponentManager* manager) {
	auto t = new MObject();
	manager->add_component(t);
}