#include "BookGUI.h"


void BookGUI::initGUI() {
    auto FirstColumn = new QVBoxLayout;
    auto search = new QFormLayout;
    setMinimumSize(1100,200);
    setLayout(Main);


    lst->setSelectionMode(QAbstractItemView::MultiSelection);
    search->addRow("",txtSearch);
    txtSearch->setPlaceholderText("Search...");
    FirstColumn->addLayout(search);
    FirstColumn->addWidget(lst);
    Main->addLayout(FirstColumn);

    auto SecondColumn = new QVBoxLayout;
    auto formLy = new QFormLayout;
    formLy->addRow("Title", txtTitle);
    formLy->addRow("Author", txtAuthor);
    formLy->addRow("Genre", txtGenre);
    formLy->addRow("Year", txtYear);
    SecondColumn->addLayout(formLy);

    ///buttons
    auto firstRow = new QHBoxLayout{},secondRow = new QHBoxLayout{};
    auto buttonRowContainer = new QVBoxLayout;
    firstRow->addWidget(addButton);
    firstRow->addWidget(deleteButton);
    firstRow->addWidget(modifyButton);
    auto menuSort = new QMenu;
    auto sortByTitle = menuSort->addMenu(" &Sort by title ");
    auto sortByAuthor = menuSort->addMenu(" &Sort by author ");
    auto sortByYandG = menuSort->addMenu(" &Sort by year and genre ");
    sortByTitle->addAction(action_sort1);
    sortByTitle->addAction(action_sort2);
    sortByAuthor->addAction(action_sort3);
    sortByAuthor->addAction(action_sort4);
    sortByYandG->addAction(action_sort5);
    sortByYandG->addAction(action_sort6);
    sortButton->setMenu(menuSort);
    firstRow->addWidget(sortButton);
    buttonRowContainer->addLayout(firstRow);
    auto menuFilter = new QMenu;
    menuFilter->addAction(action_filter1);
    menuFilter->addAction(action_filter2);
    filterButton->setMenu(menuFilter);
    secondRow->addWidget(filterButton);
    secondRow->addWidget(generateBooksButton);
    secondRow->addWidget(cartButton);
    secondRow->addWidget(reportButton);
    buttonRowContainer->addLayout(secondRow);

    SecondColumn->addLayout(buttonRowContainer);

    Main->addLayout(SecondColumn);

}

void BookGUI::Report_Buttons(){
    auto rep = service.raport_genuri();
    for(auto* b: this->BUTS){
        b->hide();
    }
    for(const auto& t: rep){

        QString str = QString::fromUtf8(t.first);
        auto but = new QPushButton(str);
        BUTS.push_back(but);
        Main->addWidget(but);
        QObject::connect(but,&QPushButton::clicked,[=](){
            QMessageBox::information(nullptr,"nr",QString::number(t.second));
        });
    }
}

void BookGUI::ui_show_list() {
    vector<Carte> books;
    try{
        books = service.service_get_carti();
    }catch (Exception &e){

    }

    for(const auto& book: books){
        string output = "{Title} ";
        output+=book.getTitlu();
        output+=" {Author} ";
        output+=book.getAutor();
        output+=" {Genre} ";
        output+=book.getGen();
        output+=" {Year} ";
        output+=std::to_string(book.getAnul());
        this->lst->addItem(QString::fromStdString(output));
    }
}

void BookGUI::onTrigger() {
        vector<Carte> v;
        v = service.sort_lambda(1,true);
        lst->clear();
        for(const auto& book: v){
            string output = "{Title} ";
            output+=book.getTitlu();
            output+=" {Author} ";
            output+=book.getAutor();
            output+=" {Genre} ";
            output+=book.getGen();
            output+=" {Year} ";
            output+=std::to_string(book.getAnul());
            this->lst->addItem(QString::fromStdString(output));
        }
}


void BookGUI::initConnect() {
    QObject::connect(txtSearch,&QLineEdit::returnPressed,[&](){
        auto title = txtSearch->text();
        try{
            Carte c = service.service_search(title.toStdString());
            QMessageBox::information(nullptr,"StatusReport", "Item was found in the list");
        }catch (Exception &e){
            QMessageBox::information(nullptr,"Exception", e.what());
        }
    });
    QObject::connect(addButton,&QPushButton::clicked,[&]() {
    try{
        auto title = txtTitle->text();
        auto author = txtAuthor->text();
        auto genre = txtGenre->text();
        int year;
        try {
            string::size_type idx;
            year = std::stoi(txtYear->text().toStdString(), &idx, 10);
            if (idx != txtYear->text().toStdString().size()) {
                throw Exception{txtYear->text().toStdString() + " is not a valid natural number!"};
            }
        }
        catch (std::invalid_argument &) {
            throw Exception{txtYear->text().toStdString() + " is not a valid natural number!"};
        }
        catch (std::out_of_range &) {
            throw Exception{txtYear->text().toStdString() + " the number is too big!"};
        }
        try {
            service.service_add_carte(title.toStdString(), author.toStdString(), genre.toStdString(), year);
            lst->clear();
            ui_show_list();
            txtTitle->clear();
            txtAuthor->clear();
            txtGenre->clear();
            txtYear->clear();
            Report_Buttons();
        } catch (Exception &e) {
            QMessageBox::information(nullptr, "Exception", e.what());
        }
    }
        catch (Exception &e){
            QMessageBox::information(nullptr,"Exception",e.what());
        }
    });
    QObject::connect(deleteButton, &QPushButton::clicked, [&](){
       auto selectedItem = lst->selectedItems();
        for(const auto &t: selectedItem){
            string title;
            int i = t->text().toStdString().find(' ');
            i++;
            while(i<t->text().toStdString().size()&&t->text().toStdString()[i]!='{'){
                title.push_back(t->text().toStdString()[i]);
                i++;
            }
            title.pop_back();
            service.service_delete_carte(title);
        }
        lst->clear();
        ui_show_list();
        Report_Buttons();
    });
    QObject::connect(modifyButton, &QPushButton::clicked, [&](){
        auto selectedItem = lst->selectedItems();
        string title;
        int nrOfSelectedItems=0;
        for(const auto &t: selectedItem){
            if(!nrOfSelectedItems) {
                int i = t->text().toStdString().find(' ');
                i++;
                while (i < t->text().toStdString().size() && t->text().toStdString()[i] != '{') {
                    title.push_back(t->text().toStdString()[i]);
                    i++;
                }
                title.pop_back();
            }
            nrOfSelectedItems++;
        }
        if(nrOfSelectedItems!=1) {
            QMessageBox::information(nullptr, "Exception", "Please select the right amount of items");
            return 1;
        }

        auto author = txtAuthor->text();
        auto genre = txtGenre->text();
        auto year = txtYear->text();
        try{
            service.service_modify_carte(title,author.toStdString(),genre.toStdString(),year.toInt());
            lst->clear();
            ui_show_list();
            txtAuthor->clear();
            txtGenre->clear();
            txtYear->clear();
            Report_Buttons();
        }catch (Exception &e){
            QMessageBox::information(nullptr,"Exception", e.what());
        }
        return 0;
    });

    connect(action_sort1, &QAction::triggered,this,&BookGUI::onTrigger);

    QObject::connect(action_sort2, &QAction::triggered,this,[&](){
        vector<Carte> v;
        v = service.sort_lambda(1, false);
        lst->clear();
        for(const auto& book: v){
            string output = "{Title} ";
            output+=book.getTitlu();
            output+=" {Author} ";
            output+=book.getAutor();
            output+=" {Genre} ";
            output+=book.getGen();
            output+=" {Year} ";
            output+=std::to_string(book.getAnul());
            this->lst->addItem(QString::fromStdString(output));
        }

    });

    QObject::connect(action_sort3, &QAction::triggered,this,[&](){
        vector<Carte> v;
        v = service.sort_lambda(2,true);
        lst->clear();
        for(const auto& book: v){
            string output = "{Title} ";
            output+=book.getTitlu();
            output+=" {Author} ";
            output+=book.getAutor();
            output+=" {Genre} ";
            output+=book.getGen();
            output+=" {Year} ";
            output+=std::to_string(book.getAnul());
            this->lst->addItem(QString::fromStdString(output));
        }

    });

    QObject::connect(action_sort4, &QAction::triggered,this,[&](){
        vector<Carte> v;
        v = service.sort_lambda(2, false);
        lst->clear();
        for(const auto& book: v){
            string output = "{Title} ";
            output+=book.getTitlu();
            output+=" {Author} ";
            output+=book.getAutor();
            output+=" {Genre} ";
            output+=book.getGen();
            output+=" {Year} ";
            output+=std::to_string(book.getAnul());
            this->lst->addItem(QString::fromStdString(output));
        }

    });

    QObject::connect(action_sort5, &QAction::triggered,this,[&](){
        vector<Carte> v;
        v = service.sort_lambda(3,true);
        lst->clear();
        for(const auto& book: v){
            string output = "{Title} ";
            output+=book.getTitlu();
            output+=" {Author} ";
            output+=book.getAutor();
            output+=" {Genre} ";
            output+=book.getGen();
            output+=" {Year} ";
            output+=std::to_string(book.getAnul());
            this->lst->addItem(QString::fromStdString(output));
        }

    });
    QObject::connect(action_sort6, &QAction::triggered,this,[&](){
        vector<Carte> v;
        v = service.sort_lambda(3, false);
        lst->clear();
        for(const auto& book: v){
            string output = "{Title} ";
            output+=book.getTitlu();
            output+=" {Author} ";
            output+=book.getAutor();
            output+=" {Genre} ";
            output+=book.getGen();
            output+=" {Year} ";
            output+=std::to_string(book.getAnul());
            this->lst->addItem(QString::fromStdString(output));
        }

    });

    QObject::connect(generateBooksButton, &QPushButton::clicked, [&](){
        vector<string> titles{"To Kill a Mockingbird","The Great Gatsby","The Catcher in the Rye","1984","Harry Potter and the Philosopher's Stone"};
        auto ales = false;
        for(const auto & t: titles)
            try{
                Carte c = service.service_search(t);
                ales = true;
            }catch (Exception &e) {
            }

        if(!ales) {
            service.service_add_carte("To Kill a Mockingbird", "Harper Lee", "Fiction", 1960);
            service.service_add_carte("The Great Gatsby", "F. Scott Fitzgerald", "Fiction", 1925);
            service.service_add_carte("The Catcher in the Rye", "J.D. Salinger", "Coming-of-Age", 1951);
            service.service_add_carte("1984", "George Orwell", "Dystopian", 1949);
            service.service_add_carte("Harry Potter and the Philosopher's Stone", "J.K. Rowling", "Fantasy", 1997);
            ales = true;
        }else
            QMessageBox::information(nullptr,"Exception","The option has already been triggered once");
        lst->clear();
        ui_show_list();
        Report_Buttons();
    });

    QObject::connect(action_filter1,&QAction::triggered, [&](){
        auto title = txtTitle->text();
        auto v = service.service_filter(title.toStdString());
        lst->clear();
        for(const auto& book: v){
            string output = "{Title} ";
            output+=book.getTitlu();
            output+=" {Author} ";
            output+=book.getAutor();
            output+=" {Genre} ";
            output+=book.getGen();
            output+=" {Year} ";
            output+=std::to_string(book.getAnul());
            this->lst->addItem(QString::fromStdString(output));
        }
        txtTitle->clear();
    });

    QObject::connect(action_filter2,&QAction::triggered, [this]() {
        try {
            int year;
        try {
            string::size_type idx;
            year = std::stoi(txtYear->text().toStdString(), &idx, 10);
            if (idx != txtYear->text().toStdString().size()) {
                throw Exception{txtYear->text().toStdString() + " is not a valid natural number!"};
            }
        }
        catch (std::invalid_argument &) {
            throw Exception{txtYear->text().toStdString() + " is not a valid natural number!"};
        }
        catch (std::out_of_range &) {
            throw Exception{txtYear->text().toStdString() + " the number is too big!"};
        }
        auto v = service.service_filter(year);
        lst->clear();
        for (const auto &book: v) {
            string output = "{Title} ";
            output += book.getTitlu();
            output += " {Author} ";
            output += book.getAutor();
            output += " {Genre} ";
            output += book.getGen();
            output += " {Year} ";
            output += std::to_string(book.getAnul());
            this->lst->addItem(QString::fromStdString(output));
        }
        txtYear->clear();
    }
        catch (Exception &e){
            QMessageBox::information(nullptr,"Exception",e.what());
        }
    });

    QObject::connect( reportButton, &QPushButton::clicked, [&](){
        nrOfPopups++;
        auto rep = service.raport_genuri();
        for(const auto & g: rep){
            string output = "";
            output+=g.first;
            output+=": ";
            output+=std::to_string(g.second);
            popup->addItem(QString::fromStdString(output));
        }

        popup->setWindowFlags(Qt::Window|Qt::FramelessWindowHint);
        popup->setVisible(!popup->isVisible());
        adjustPopup();
    });

    QObject::connect(cartButton, &QPushButton::clicked, [this](){
       CartWindow* cartWindow = new CartWindow(service,this);
       cartWindow->initEverything();
    });

    undo = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Z), this);
    QObject::connect(undo,&QShortcut::activated, this,[&](){
        try{
            service.undo();
            lst->clear();
            ui_show_list();
        }
        catch (Exception &e){
        }
    });
    resetList = new QShortcut(QKeySequence(Qt::Key_R),this);
    QObject::connect(resetList,&QShortcut::activated, this,[&](){
        lst->clear();
        ui_show_list();
    });
}

void BookGUI::adjustPopup() {
    if (!popup->isVisible()) {
        popup->clear();
        return;
    }
    QRect rect = reportButton->geometry();
    QPoint bottomLeft = this->mapToGlobal(rect.bottomLeft());
    popup->setGeometry(QRect(bottomLeft, QSize(rect.width(),200)));
}

void BookGUI::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    adjustPopup();
}

void BookGUI::moveEvent(QMoveEvent *event) {
    QWidget::moveEvent(event);
    adjustPopup();
}

/****************************************************************/

void CartWindow::ui_show_list() {
    vector<Carte> books;
    try{
        books = service.service_get_carti_cos();
    }catch (Exception &e){

    }

    for(const auto& book: books){
        string output = "{Title} ";
        output+=book.getTitlu();
        output+=" {Author} ";
        output+=book.getAutor();
        output+=" {Genre} ";
        output+=book.getGen();
        output+=" {Year} ";
        output+=std::to_string(book.getAnul());
        this->lst->addItem(QString::fromStdString(output));
    }
}

void CartWindow::initGui() {
    auto Main = new QVBoxLayout{};
    Main->addWidget(lst);
    setMinimumSize(500,200);
    setLayout(Main);

    auto SecondColumn = new QVBoxLayout;
    auto rows = new QFormLayout;
    rows->addRow("Title",txtTitle);
    SecondColumn->addLayout(rows);

    auto buttonRowContainer = new QVBoxLayout;
    auto firstRow = new QVBoxLayout,secondRow = new QVBoxLayout;
    firstRow->addWidget(addButton);
    firstRow->addWidget(emptyButton);
    buttonRowContainer->addLayout(firstRow);

    auto menu = new QMenu,menuPath = new QMenu;
    txtRandomAction->setDefaultWidget(txtRandom);
    txtRandom->setPlaceholderText("Insert a number...");
    menu->addAction(txtRandomAction);
    generateRandomButton->setMenu(menu);
    secondRow->addWidget(generateRandomButton);

    txtPath->setPlaceholderText("Insert a path...");
    txtPathAction->setDefaultWidget(txtPath);
    menuPath->addAction(txtPathAction);
    exportButton->setMenu(menuPath);
    secondRow->addWidget(exportButton);

    buttonRowContainer->addLayout(secondRow);
    SecondColumn->addLayout(buttonRowContainer);

    Main->addLayout(SecondColumn);

    show();
}

void CartWindow::initConnect() {
    QObject::connect(addButton,&QPushButton::clicked,[&]() {
        auto title = txtTitle->text();
        if(title.toStdString().empty())
            return 1;
        try {
            service.service_add_carte_cos(title.toStdString());
            lst->clear();
            ui_show_list();
            txtTitle->clear();
        } catch (Exception &e) {
            QMessageBox::information(nullptr, "Exception", e.what());
        }
        return 0;
    });

    QObject::connect(emptyButton,&QPushButton::clicked, [this](){
        lst->clear();
        try {
            service.service_empty_cos();
        }
        catch (Exception &e){

        }
    });

    QObject::connect(txtRandom,&QLineEdit::returnPressed,[&](){
        try {
            int nr_of_books;
            try {
                string::size_type idx;
                nr_of_books = std::stoi(txtRandom->text().toStdString(), &idx, 10);
                if (idx != txtRandom->text().toStdString().size()) {
                    throw Exception{txtRandom->text().toStdString() + " is not a valid natural number!"};
                }
            }
            catch (std::invalid_argument &) {
                throw Exception{txtRandom->text().toStdString() + " is not a valid natural number!"};
            }
            catch (std::out_of_range &) {
                throw Exception{txtRandom->text().toStdString() + " the number is too big!"};
            }
            try {
                service.generate_books(nr_of_books);
                lst->clear();
                ui_show_list();
                txtRandom->clear();
            } catch (Exception &e) {
                QMessageBox::information(nullptr, "Exception", e.what());
            }
        }catch (Exception &e){
            QMessageBox::information(nullptr,"Exception",e.what());
        }
    });
    QObject::connect(txtPath,&QLineEdit::returnPressed,[&](){
        auto path = txtPath->text();
        if(path.toStdString().empty())
            return 1;
        service.service_export_cos(path.toStdString());
        QMessageBox::information(nullptr, "Success", "The cart has been exported");
        txtPath->clear();
        return 0;
    });
}
