#include <engine_macro.h>
#include <string>



class MACHI_API Application{
	

protected:
	virtual bool update();
	virtual bool fixed_update();
	virtual bool render();
	
	
public :
	using string = std::string;
	virtual ~Application();

	bool run(int argc, char** argv);


private:
	string app_name_;

};