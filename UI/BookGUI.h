#pragma once
#include "QtWidgets"
#include "../Service/Service.h"
#include "../UI/Observer.h"
#include "../UI/MyModel.h"
#include <QListView>
#include <QAbstractTableModel>

class BookGUI : public QWidget{
private:
    Service service;
    vector<QPushButton*> BUTS;
    QHBoxLayout* Main = new QHBoxLayout{};
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
    int nr;

    QShortcut* undo = new QShortcut(this);
    QShortcut* resetList = new QShortcut(this);

    QLineEdit* txtSearch = new QLineEdit;
    QLineEdit* txtTitle = new QLineEdit;
    QLineEdit* txtAuthor = new QLineEdit;
    QLineEdit* txtGenre = new QLineEdit;
    QLineEdit* txtYear = new QLineEdit;

    MyTableModel* model = new MyTableModel(vector<Carte> ());
    QListView* lst_view= new QListView{};

    void initGUI();
    void initConnect();
    void ui_show_list(MyTableModel* model, const vector<Carte>& v);
    void onTrigger();
    void Report_Buttons();

    void adjustPopup();
    void resizeEvent(QResizeEvent* event);
    void moveEvent(QMoveEvent* event);

public:
    explicit BookGUI(Service &serv): service(serv){
        lst= new QListWidget;
        initGUI();
        initConnect();
        try {
            ui_show_list(model, service.service_get_carti());
        }catch (Exception &e){

        }
        Report_Buttons();
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
    QPushButton* crud= new QPushButton{" &Crud "};
    QPushButton* readOnly= new QPushButton{ " &Read "};

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

/****************************************************************************************************/

class CosCRUDGUI: public QWidget, public Observer{
private:
    Service& service;
    MyTableModel* model = new MyTableModel(vector<Carte> ());
    QListView* lst_view= new QListView{};
    QPushButton* gen = new QPushButton{" &Generate "};
    QLineEdit* txtRandom = new QLineEdit;
    QWidgetAction* txtRandomAction = new QWidgetAction(this);
    QPushButton* goleste = new QPushButton{" &Goleste "};

    void initGui();
    void connect();
    void update() override;
public:
    explicit CosCRUDGUI(Service &service) : service(service), QWidget() {update();connect();initGui();}


};

/****************************************************************************************************/


class CosReadOnlyGUI: public QWidget, public Observer{
private:
    Service& service;


    void update() override;
    void paintEvent(QPaintEvent* ev) override{
        vector<Carte> books;
        try{
            books = service.service_get_carti_cos();
        }catch (Exception &e){

        }
        QPainter p{this};
        int x=0,y=0;
        for(auto c: books) {
            std::mt19937 mt{std::random_device{}()};
            std::uniform_int_distribution<> dist(0, 60);
            x = dist(mt);
            std::mt19937 mt1{std::random_device{}()};
            std::uniform_int_distribution<> dist1(0, 60);
            y = dist(mt1);
            p.drawRect(x,y, 20,10);
        }
    }
public:
    explicit CosReadOnlyGUI(Service &service) : service(service) {}

};

