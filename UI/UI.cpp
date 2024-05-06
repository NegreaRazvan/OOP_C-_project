#include "UI.h"
#include "../Exception/Exception.h"

void UI::run() {
    bool ales = false;
    while(true){
        int optiune{0};
        commands();
        std::cout<<"\nAlege o optiune: ";
        std::cin>>optiune;
        if (optiune==0) {
//            clear_files();
            return;
        }
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
            case 9:
                ui_add_carte_in_cos();
                break;
            case 10:
                ui_empty_cos();
                break;
            case 11:
                ui_generate_carti_in_cos();
                break;
            case 12:
                ui_export_carti();
                break;
            case 13:
                ui_show_cos();
                break;
            case 14:
                ui_raport_genuri();
                break;
            case 15:
                ui_undo();
                break;
            default:
                std::cout<<std::endl<<"Invalid command";
        }
    }
}



void UI::ui_add_carte() {
    int an{0};
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
    }catch (Exception &e){
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
    }catch (Exception &e){
        std::cout<<std::endl<<e.what();
    }
}

void UI::ui_modify_carte() {
    int an{0};
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
    }catch (Exception &e){
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
    }catch (Exception &e){
        std::cout<<std::endl<<e.what();
    }
}

void UI::ui_filter() {
    std::cout<<"\n1.Filter dupa titlu\n2.Filter dupa an\nAlege o optiune: ";
    int opt{0};
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
                int an{0};
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
    int opt{0}, ord{0};
    vector<Carte> v;
    while (true) {
        std::cout<<"\n1.Sort dupa titlu\n2.Sort dupa autor\n3.Sort dupa an si gen\nAlege optiune: ";
        std::cin>>opt;
        switch (opt) {
            case 1: {
                std::cout<<"\n1.Crescator\n2.Descrescator\nAlege: ";
                std::cin>>ord;
                if(ord==1)
                    v = service.sort_lambda(1,true);
                else
                    if(ord==2)
                        v = service.sort_lambda(1, false);
                    else
                        std::cout<<"\nInvalid command\n";
                break;
            }
            case 2: {
                std::cout<<"\n1.Crescator\n2.Descrescator\nAlege: ";
                std::cin>>ord;
                if(ord==1)
                    v= service.sort_lambda(2,true);
                else
                    if(ord==2)
                        v=service.sort_lambda(2, false);
                    else
                        std::cout<<"\nInvalid command\n";
                break;
            }
            case 3: {
                std::cout<<"\n1.Crescator\n2.Descrescator\nAlege: ";
                std::cin>>ord;
                if(ord==1)
                    v=service.sort_lambda(3,true);
                else
                    if(ord==2)
                        v=service.sort_lambda(3, false);
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
    std::cout<<"\n0.Exit\n1.Add carte\n2.Delete carte\n3.Modify carte\n4.Search carte\n5.Filter\n6.Sort\n7.Generate carti\n8.Show list\n9.Adauga in cos\n10.Goleste cosul\n11.Adauga intamplator in cos\n12.Exporteaza cartile\n13.Arata cosul\n14.Raport\n15.Undo\n";
}

void UI::ui_show_list() {
    vector<Carte> v ;
    try{
        v = service.service_get_carti();
    }catch (Exception &e){
        std::cout<<std::endl<<e.what();
    }
    for(const auto & c : v)
        std::cout<<"\n{Titlu} "<<c.getTitlu()<<" {Autor} "<<c.getAutor()<<" {Gen} "<<c.getGen()<<" {Anul} "<<c.getAnul()<<std::endl;

}

void UI::ui_generate_carti(bool &ales) {
    vector<string> titles{"To Kill a Mockingbird","The Great Gatsby","The Catcher in the Rye","1984","Harry Potter and the Philosopher's Stone"};
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
        std::cout<<"\nOptiunea a fost deja aleasa odata!\n";
}

void UI::ui_add_carte_in_cos() {
    string titlu;
    std::cout<<"Titlul: ";
    std::cin>>titlu;
    try{
        service.service_add_carte_cos(titlu);
        std::cout<<"\n<<Carte adaugata cu succes!>>\n";
    }catch (Exception &e){
        std::cout<<std::endl<<e.what();
    }
}

void UI::ui_empty_cos() {
    try{
        service.service_empty_cos();
        std::cout<<"\n<<Cos golit!>>\n";
    }catch (Exception &e){
        std::cout<<std::endl<<e.what();
    }
}

void UI::ui_generate_carti_in_cos() {
    int rng,nr_added;
    std::cout<<"Numarul de carti: ";
    std::cin>>rng;
    try{
        nr_added = service.generate_books(rng);
        std::cout<<"\n<<Au fost adaugate "<<nr_added<<" carti>>\n";
    }catch (Exception &e){
        std::cout<<std::endl<<e.what();
    }
}

void UI::ui_export_carti() {
    string path;
    std::cout<<"Alege o destinatie: ";
    std::cin>>path;
    try{
        service.service_export_cos(path);
        std::cout<<"\n<<Cos exportat!>>\n";
    }catch (Exception &e){
        std::cout<<std::endl<<e.what();
    }
}

void UI::ui_show_cos() {
    vector<Carte> v ;
    try{
        v = service.service_get_carti_cos();
    }catch (Exception &e){
        std::cout<<std::endl<<e.what();
    }
    for(const auto & c : v)
        std::cout<<"\n{Titlu} "<<c.getTitlu()<<" {Autor} "<<c.getAutor()<<" {Gen} "<<c.getGen()<<" {Anul} "<<c.getAnul()<<std::endl;
}

void UI::ui_raport_genuri() {
    map <string,int> rap = service.raport_genuri();
    std::cout<<"Nr de aparitii a fiecarui gen: \n";
    for(const auto & g: rap)
        std::cout<<g.first<<": "<<g.second<<std::endl;
}

void UI::ui_undo() {
    try{
        service.undo();
        std::cout<<"\n<<Successfully undone>>\n";
    }
    catch (Exception &e){
        std::cout<<std::endl<<e.what()<<std::endl;
    }
}
