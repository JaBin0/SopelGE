#include <iostream>
#include <SGELevelEditor.h>

void SGELevelEditor::run()
{
    std::cout << "Start program" << std::endl;
}

// ============================== Main ==============================
int main ()
{
    std::cout << "SopelGE Level Editor" << std::endl;
    SGELevelEditor levelEditor;
    levelEditor.run();
}