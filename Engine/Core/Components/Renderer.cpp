#include "Renderer.h"
#include <Graphics/GraphicManager.h>
void Machi::Components::MeshRendererComponent::initialize()
{
	Graphics::GraphicManager* manager = Graphics::GraphicManager::get_instance();
	m_renderer = manager->make_renderer();
	m_renderer->set_static_mesh(this->m_meshes[0]);

}
void Machi::Components::MeshRendererComponent::finalize()
{
}
void Machi::Components::MeshRendererComponent::add_material(Machi::Geometry::Material* mat)
{
}
void Machi::Components::MeshRendererComponent::add_meshes(Machi::Geometry::Mesh* mesh)
{
	m_meshes.emplace_back(mesh);
}
