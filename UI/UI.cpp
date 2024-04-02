#include "UI.h"

void UI::run() {
    bool ales = false;
    while(true){
        int optiune;
        commands();
        std::cout<<"\nAlege o optiune: ";
        std::cin>>optiune;
        if (optiune==0)
            return;
        switch (optiune) {
            case 1:
                ui_add_carte();
                break;
            case 2:
                ui_delete_carte();
                break;
            case 3:
                ui_modify_carte();
                break;
            case 4:
                ui_search();
                break;
            case 5:
                ui_filter();
                break;
            case 6:
                ui_sort();
                break;
            case 7:
                ui_generate_carti(ales);
                break;
            case 8:
                ui_show_list();
                break;
            default:
                std::cout<<std::endl<<"Invalid command";
        }
    }
}



void UI::ui_add_carte() {
    int an;
    string titlu, autor,gen;
    std::cout<<"Titlul: ";
    std::cin>>titlu;
    std::cout<<"Autor: ";
    std::cin>>autor;
    std::cout<<"Gen: ";
    std::cin>>gen;
    std::cout<<"Anul: ";
    std::cin>>an;
    try{
        service.service_add_carte(titlu,autor,gen,an);
        std::cout<<"\n<<Carte adaugata cu succes!>>\n";
    }catch (std::runtime_error &e){
        std::cout<<std::endl<<e.what();
    }
}

void UI::ui_delete_carte() {
    string titlu;
    std::cout<<"Titlul: ";
    std::cin>>titlu;
    try{
        service.service_delete_carte(titlu);
        std::cout<<"\n<<Carte stearsa cu succes!>>\n";
    }catch (std::runtime_error &e){
        std::cout<<std::endl<<e.what();
    }
}

void UI::ui_modify_carte() {
    int an;
    string titlu, autor,gen;
    std::cout<<"Titlul: ";
    std::cin>>titlu;
    std::cout<<"Autor: ";
    std::cin>>autor;
    std::cout<<"Gen: ";
    std::cin>>gen;
    std::cout<<"Anul: ";
    std::cin>>an;
    try{
        service.service_modify_carte(titlu,autor,gen,an);
        std::cout<<"\n<<Carte modificata cu succes!>>\n";
    }catch (std::runtime_error &e){
        std::cout<<std::endl<<e.what();
    }
}

void UI::ui_search() {
    string titlu;
    std::cout<<"Titlul: ";
    std::cin>>titlu;
    try{
        Carte c = service.service_search(titlu);
        std::cout<<"\n{Titlu} "<<c.getTitlu()<<" {Autor} "<<c.getAutor()<<" {Gen} "<<c.getGen()<<" {Anul} "<<c.getAnul()<<std::endl;
    }catch (std::runtime_error &e){
        std::cout<<std::endl<<e.what();
    }
}

void UI::ui_filter() {
    std::cout<<"\n1.Filter dupa titlu\n2.Filter dupa an\nAlege o optiune: ";
    int opt;
    vector<Carte> v;
    std::cin>>opt;
    while (true) {
        switch (opt) {
            case 1: {
                string titlu;
                std::cout << "Titlul: ";
                std::cin >> titlu;
                v = service.service_filter(titlu);
                break;
            }
            case 2: {
                int an;
                std::cout << "Anul: ";
                std::cin >> an;
                v = service.service_filter(an);
                break;
            }
            default:
                std::cout << "Invalid command!";
        }
        if(opt==1 || opt==2)
            break;
    }
    for(const auto & c : v)
        std::cout<<"\n{Titlu} "<<c.getTitlu()<<" {Autor} "<<c.getAutor()<<" {Gen} "<<c.getGen()<<" {Anul} "<<c.getAnul()<<std::endl;
}

void UI::ui_sort() {
    int opt, ord;
    vector<Carte> v = service.service_copy_list();
    while (true) {
        std::cout<<"\n1.Sort dupa titlu\n2.Sort dupa autor\n3.Sort dupa an si gen\nAlege optiune: ";
        std::cin>>opt;
        switch (opt) {
            case 1: {
                std::cout<<"\n1.Crescator\n2.Descrescator\nAlege: ";
                std::cin>>ord;
                if(ord==1)
                    service.sort_lambda(v,1,true);
                else
                    if(ord==2)
                        service.sort_lambda(v,1, false);
                    else
                        std::cout<<"\nInvalid command\n";
                break;
            }
            case 2: {
                std::cout<<"\n1.Crescator\n2.Descrescator\nAlege: ";
                std::cin>>ord;
                if(ord==1)
                    service.sort_lambda(v,2,true);
                else
                    if(ord==2)
                        service.sort_lambda(v,2, false);
                    else
                        std::cout<<"\nInvalid command\n";
                break;
            }
            case 3: {
                std::cout<<"\n1.Crescator\n2.Descrescator\nAlege: ";
                std::cin>>ord;
                if(ord==1)
                    service.sort_lambda(v,3,true);
                else
                    if(ord==2)
                        service.sort_lambda(v,3, false);
                    else
                        std::cout<<"\nInvalid command\n";
                break;
            }
            default:
                std::cout << "\nInvalid command\n";
        }
        if((opt==1 || opt==2 || opt ==3)&&(ord==1||ord==2))
            break;
    }
    for(const auto & c : v)
        std::cout<<"\n{Titlu} "<<c.getTitlu()<<" {Autor} "<<c.getAutor()<<" {Gen} "<<c.getGen()<<" {Anul} "<<c.getAnul()<<std::endl;
}

void UI::commands() {
    std::cout<<"\n0.Exit\n1.Add carte\n2.Delete carte\n3.Modify carte\n4.Search carte\n5.Filter\n6.Sort\n7.Generate carti\n8.Show list\n";
}

void UI::ui_show_list() {
    vector<Carte> v ;
    try{
        v = service.service_get_carti();
    }catch (std::runtime_error &e){
        std::cout<<std::endl<<e.what();
    }
    for(const auto & c : v)
        std::cout<<"\n{Titlu} "<<c.getTitlu()<<" {Autor} "<<c.getAutor()<<" {Gen} "<<c.getGen()<<" {Anul} "<<c.getAnul()<<std::endl;

}

void UI::ui_generate_carti(bool &ales) {
    if(!ales) {
        service.service_add_carte("To Kill a Mockingbird", "Harper Lee", "Fiction", 1960);
        service.service_add_carte("The Great Gatsby", "F. Scott Fitzgerald", "Fiction", 1925);
        service.service_add_carte("The Catcher in the Rye", "J.D. Salinger", "Coming-of-Age", 1951);
        service.service_add_carte("1984", "George Orwell", "Dystopian", 1949);
        service.service_add_carte("Harry Potter and the Philosopher's Stone", "J.K. Rowling", "Fantasy", 1997);
        ales = true;
    }else
        std::cout<<"\nCarti deja inregistrate in lista!\n";
}
