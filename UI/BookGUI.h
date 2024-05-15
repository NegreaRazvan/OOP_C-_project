#pragma once
#include "QtWidgets"
#include "../Service/Service.h"

class BookGUI : public QWidget{
private:
    Service service;
    QListWidget* lst;
    QPushButton* addButton = new QPushButton{" &Add "};
    QPushButton* deleteButton = new QPushButton{" &Delete "};
    QPushButton* modifyButton = new QPushButton{" &Modify "};
    QPushButton* sortButton = new QPushButton{" &Sort "};

    QAction* action_sort1 = new QAction(" &Ascending ",this);
    QAction* action_sort2 = new QAction(" &Descending ",this);
    QAction* action_sort3 = new QAction(" &Ascending ",this);
    QAction* action_sort4 = new QAction(" &Descending ",this);
    QAction* action_sort5 = new QAction(" &Ascending ",this);
    QAction* action_sort6 = new QAction(" &Descending ",this);

    QPushButton* filterButton = new QPushButton{" &Filter "};

    QAction* action_filter1 = new QAction(" &By Title ",this);
    QAction* action_filter2 = new QAction(" &By Year ",this);

    QPushButton* generateBooksButton = new QPushButton{" &GenerateBooks "};
    QPushButton* cartButton = new QPushButton{" &Cart "};
    QPushButton* reportButton = new QPushButton{" &Report "};
    QListWidget* popup = new QListWidget;
    int nrOfPopups = 0;

    QShortcut* undo = new QShortcut(this);
    QShortcut* resetList = new QShortcut(this);

    QLineEdit* txtSearch = new QLineEdit;
    QLineEdit* txtTitle = new QLineEdit;
    QLineEdit* txtAuthor = new QLineEdit;
    QLineEdit* txtGenre = new QLineEdit;
    QLineEdit* txtYear = new QLineEdit;

    void initGUI();
    void initConnect();
    void ui_show_list();
    void onTrigger();

    void adjustPopup();
    void resizeEvent(QResizeEvent* event);
    void moveEvent(QMoveEvent* event);

public:
    explicit BookGUI(Service &serv): service(serv){
        lst = new QListWidget;
        ui_show_list();
        initConnect();
        initGUI();
    }

};

class CartWindow: public QWidget{
private:
    Service &service;
    QListWidget* lst = new QListWidget;

    QPushButton* addButton = new QPushButton{" &Add "};
    QPushButton* emptyButton = new QPushButton{ " &Empty cart "};
    QPushButton* generateRandomButton = new QPushButton{ " &Generate random nr of books "};
    QPushButton* exportButton = new QPushButton{" &Export "};
    QLineEdit* txtTitle = new QLineEdit;
    QLineEdit* txtRandom = new QLineEdit;
    QLineEdit* txtPath = new QLineEdit;
    QWidgetAction* txtRandomAction = new QWidgetAction(this);
    QWidgetAction* txtPathAction = new QWidgetAction(this);

    void ui_show_list();
    void initGui();
    void initConnect();

public:
    explicit CartWindow(Service &serv, QWidget* parent): service(serv), QWidget{parent, Qt::Window}{};
    void initEverything(){
        ui_show_list();
        initConnect();
        initGui();
    }
};



