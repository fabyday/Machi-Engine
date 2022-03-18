
//
// Created by rohjihyun on 2022/03/15.
//


#include <string>
#define UNIVERSAL_APPLICATION AppleApplication


class UNIVERSAL_APPLICATION{


public:
    using string = std::string;
    virtual ~UNIVERSAL_APPLICATION() {};

    bool run(int argc, char** argv);

    static UNIVERSAL_APPLICATION* get_instance() {
        if (app_ == nullptr) {
            app_ = new UNIVERSAL_APPLICATION();
        }
        return app_;
    };

private:
    static UNIVERSAL_APPLICATION* app_;
    string app_name_;
    time_t time_;

protected:
    virtual bool update();
    virtual bool fixed_update();
    virtual bool render();

};
