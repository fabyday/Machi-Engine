

#define UNIVERSAL_APPLICATION public WinApplication


class WinApplication {


public:
	using string = std::string;
	virtual ~WinApplication() {};

	bool run(int argc, char** argv);

	static WinApplication* get_instance() {
		if (app_ == nullptr) {
			app_ = new WinApplication;
		}
		return app_;
	};

private:
	static WinApplication* app_;
	string app_name_;
	time_t time_;

protected:
	virtual bool update();
	virtual bool fixed_update();
	virtual bool render();

};
