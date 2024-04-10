#include "Teste/Tests.h"
#include "UI/UI.h"


int main() {
    UI ui = UI();
    Tests t = Tests();
    t.run();
    ui.run();

    return 0;
}
