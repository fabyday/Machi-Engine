//MIT License 
//Copyright(c) 2022 fabyday
// 
// 
//Permission is hereby granted, free of charge, to any person
//obtaining a copy of this softwareand associated documentation
//files(the "Software"), to deal in the Software without
//restriction, including without limitation the rights to use,
//copy, modify, merge, publish, distribute, sublicense, and /or sell
//copies of the Software, and to permit persons to whom the
//Software is furnished to do so, subject to the following
//conditions :
//
//The above copyright noticeand this permission notice shall be
//included in all copies or substantial portions of the Software.
// 
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
//EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
//OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
//NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
//HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
//WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
//FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
//OTHER DEALINGS IN THE SOFTWARE.
#include <Platform/entry.h>
#include <IO/ObjReader.h>
#include <Components/Renderer.h>
class NewApp : public Machi::Application {
public:

	



};




Machi::Application* machi_main(int argc, char** argv) {

//    return nullptr;
	//Machi::Application* ret = Machi::Application::get_instance()
		//->set_name(L"Machi-AS-WELL")
		//->set_resolution(1280, 960, false);
	Machi::Application* ret = NewApp::get_instance()
		->set_name(L"Machi-AS-WELL")
		->set_resolution(1280, 960, false);
	Machi::IO::OBJReader reader; 
	
	//MSTRING test = L"D:/project/Machi-Engine/Engine/Resources/data/mesh""bunny/bunny.obj";
	MSTRING test = MESH_RESOURCE_DIRECTORY"teapot/teapot.obj";
	Machi::Geometry::Mesh* mesh;
	int tt = -1;
	reader.read_mesh(test, &mesh, tt);

	Machi::Components::MeshRendererComponent* renderer = new Machi::Components::MeshRendererComponent;

	renderer->add_meshes(mesh);
	ret->set_renderer(renderer);
	renderer->initialize();

	

	return ret;


}