#include "Service.h"
#include "../Exception/Exception.h"

const vector<Carte> &Service::service_get_carti() const {
    vector <Carte> v = repository.get_carti();
    if (v.empty())
        throw Exception("Lista goala!\n");
    return repository.get_carti();
}

void Service::service_add_carte(const string &titlu, const string &autor, const string &gen, const int &an) {
    Carte carte = Carte(titlu,autor,gen,an);
//    auto i = std::find(repository.get_carti().begin(),repository.get_carti().end(), carte);
//    if (i==repository.get_carti().end())
//        throw std::runtime_error("Cartea deja apare in lista!\n");
    auto position = repository.search(titlu);
    if(position!=repository.get_carti().end())
        throw Exception("Cartea se afla deja in lista!\n");
    repository.add_carte(carte);
    auto* u = new UndoAdd(carte,repository);
    undo_action.push_back(u);
}

void Service::service_delete_carte(const string &titlu) {
    auto position = repository.search(titlu);
    if(position==repository.get_carti().end())
        throw Exception("Cartea nu se afla in lista!\n");
    auto* u = new UndoDelete(*repository.search(titlu),repository);
    undo_action.push_back(u);
    repository.delete_carte(position);
    auto poz = std::find_if(cos.get_all_carti().begin(),cos.get_all_carti().end(), [titlu](const Carte& c){return titlu==c.getTitlu();});
    if (poz!=cos.get_all_carti().end()) {
        cos.delete_carte(poz);
    }
}

void Service::service_modify_carte(const string &titlu, const string &autor, const string &gen, const int &an) {
    Carte carte = Carte(titlu,autor,gen,an);
    auto position = repository.search(titlu);
    if(position==repository.get_carti().end())
        throw Exception("Cartea nu se afla in lista!\n");
    auto* u = new UndoModify(carte,*position,repository);
    undo_action.push_back(u);
    repository.modify_carte(carte,*position);
    auto poz = std::find_if(cos.get_all_carti().begin(),cos.get_all_carti().end(), [titlu](const Carte& c){return titlu==c.getTitlu();});
    if (poz!=cos.get_all_carti().end()) {
        cos.modify_carte(carte, *poz);
    }
}

Carte Service::service_search(const string &titlu) const {
    auto position = repository.search(titlu);
    if(position==repository.get_carti().end())
        throw Exception("Cartea nu se afla in lista!\n");
    return *position;
}

vector<Carte> Service::service_filter(const string &titlu) const{
    vector <Carte> v=repository.get_carti(), v_copy;
    std::copy_if(v.begin(), v.end(), std::back_inserter(v_copy),[=](const Carte& c){return c.getTitlu()==titlu;});
    return v_copy;
}

vector<Carte> Service::service_filter(const int &an) const{
    vector <Carte> v=repository.get_carti(), v_copy;
    std::copy_if(v.begin(), v.end(), std::back_inserter(v_copy),[=](const Carte& c){return c.getAnul()==an;});
    return v_copy;
}

vector<Carte> Service::sort_lambda(const int &var, const bool &ordine) const {
    vector <Carte> v=repository.get_carti();
    switch (var) {
        case 1:
            std::sort(v.begin(), v.end(),[ordine](const Carte &c1, const Carte &c2){if(c1.getTitlu()<=c2.getTitlu()) return ordine; return !(ordine);});
            break;
        case 2:
            std::sort(v.begin(), v.end(),[ordine](const Carte &c1, const Carte &c2){if(c1.getAutor()<=c2.getAutor()) return ordine; return !(ordine);});
            break;
        case 3:
            std::sort(v.begin(), v.end(), [ordine](const Carte &c1, const Carte &c2){if(c1.getAnul()<c2.getAnul())return ordine;else if(c1.getAnul()==c2.getAnul())if(c1.getGen()<=c2.getGen())return ordine;return !(ordine);});
            break;
    }
    return v;
}

const vector<Carte> &Service::service_get_carti_cos() const {
    vector <Carte> v = cos.get_all_carti();
    if (v.empty())
        throw Exception("Lista goala!\n");
    return cos.get_all_carti();
}

void Service::service_add_carte_cos(const string &titlu) {
    auto carte = service_search(titlu);
    for(const auto & c : cos.get_all_carti())
        if(c==carte)
            throw Exception("Cartea deja apare in cos!\n");

    cos.add_carte_to_cos(carte);
    notify();
}

void Service::service_empty_cos() {
    if(cos.get_all_carti().empty())
        throw Exception("Cos deja gol!");
    cos.empty_cos();
    notify();
}

void Service::service_export_cos(const string &path) {
    if(!cos.get_all_carti().size())
        throw Exception("Cosul este gol!");
    cos.export_carti(path);

}

//void Service::clear_all_files(const vector<string> &paths) {
//    for(const auto & path: paths)
//        cos.empty_file(path);
//}

int Service::generate_books(const int &nr_of_books) {
    int nr_of_books_added_to_the_list = 0;
    if(nr_of_books>repository.get_carti().size()-cos.get_all_carti().size())
        throw Exception("Nu mai sunt destule carti pentru a adauga in cos");
    for(int i = 0; i < nr_of_books; i++) {
        bool ok = true;
        std::mt19937 mt{std::random_device{}()};
        std::uniform_int_distribution<> dist(0, repository.get_carti().size() - 1);
        int rndNr = dist(mt);
        for(const auto & c : cos.get_all_carti())
            if(c==repository.get_carte(rndNr))
                ok= false;
        if(ok) {
            nr_of_books_added_to_the_list++;
            cos.add_carte_to_cos(repository.get_carte(rndNr));
        }
    }
    notify();
    return nr_of_books_added_to_the_list;
}

map<string,int> Service::raport_genuri() const {
    map<string,int> raport ;
    for(const auto& carte: repository.get_carti())
        raport[carte.getGen()]++;
    return raport;
}

void Service::undo() {
    if(undo_action.empty())
        throw Exception("Undo unavailable!");
    undo_action.back()->doUndo();
    auto u = undo_action.back();
    undo_action.pop_back();
    delete u;
}







