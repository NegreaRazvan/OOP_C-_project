#include "UI_Application.h"
#include "BookGUI.h"
#include "../Teste/Tests.h"

int run(int argc, char *argv[]){
    QApplication application(argc, argv);

    Repository repository;
    FileRepository repository1{"books.txt"};
    Service service{repository1};
    Tests t = Tests();
    t.run();
    BookGUI* w = new BookGUI(service);
    w->show();

    return QApplication::exec();

}