#include <iostream>
#include <SGELevelEditor.h>

void SGELevelEditor::init()
{
    _window = Sopel::Window::CreateWindow(1280, 720, "SGELevelEditor");
    _renderer = std::make_unique<Sopel::OGL>((GLADloadfunc)_window->getProcAddress());
    //_renderer = SopelGE::OGL
}

void SGELevelEditor::run()
{
    std::cout << "Start program" << std::endl;
    while (!_window->shouldClose())
    {
        _renderer->startFrame(.0f);
        _window->update();
        
    }
}

// ============================== Main ==============================
int main ()
{
    std::cout << "SopelGE Level Editor" << std::endl;
    SGELevelEditor levelEditor;
    levelEditor.init();
    levelEditor.run();
    return 0;
}