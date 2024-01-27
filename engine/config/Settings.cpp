// System headers
#include <iostream>
// Own headers
#include <Settings.h>

namespace Sopel {

Settings& Settings::instance() {
    static Settings _instance;
    return _instance;
}

Settings::Settings() {
    std::cout << __PRETTY_FUNCTION__ << std::endl;

    _settings.insert({"width", 1280.0f});
    // _settings.insert("height", 720.0f);
}

Settings::~Settings() {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}



};
