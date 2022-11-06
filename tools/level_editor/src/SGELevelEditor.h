#pragma once
#include <memory>
#include <WindowOGL.h>
#include <OGL.h>

class SGELevelEditor {
public: 
    void init();

    void run();

protected:
    std::unique_ptr<Sopel::IRenderer> _renderer;
    std::unique_ptr<Sopel::Window> _window;

};