#include "Teste/Tests.h"
#include "UI/UI.h"

int main() {
    Repository repository;
    FileRepository repository1{"books.txt"};
    Service service{repository1};
    UI ui = UI(service);
    Tests t = Tests();
    t.run();
    ui.run();





    return 0;
}
