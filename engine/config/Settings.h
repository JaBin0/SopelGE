#pragma once
// System headers
#include <any>
#include <string>
#include <unordered_map>
#include <cassert>

namespace Sopel {

/*! \brief Objet represent settings idiom within Sopel Game Engine */
class Settings {
    std::unordered_map<std::string, std::any> _settings;

    /*! \brief Constructor */
    Settings();

public:
    /*! \brief Static getter for the settings object */
    static Settings& instance();

    /*! \brief Destructor */
    ~Settings();
};

};