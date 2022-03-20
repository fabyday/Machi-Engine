#include "components.h"
class GraphicsContext; // implements it in Platform. opaque type.



class GraphicManager {
// Platform dependents
private : 
	GraphicsContext* context_;

	GraphicManager(GraphicsContext* ctx);

	virtual void initialize();
	virtual void update();
	virtual void render();
	virtual void destroy();


public : 
	static GraphicManager* get_instance();
	void draw();

	Buffer* make_buffer();
	BufferView* make_buffer_view(Buffer& buf);
	


};