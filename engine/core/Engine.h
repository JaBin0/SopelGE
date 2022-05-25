#pragma once
// System headers
#include <iostream>
// Own headers


namespace Sopel {
// Defines
#define VERSION 0.001

class Engine {
public:
    Engine();
    virtual ~Engine();

    /** Contains current version of the Game engine. */
    static const float version;
};
};