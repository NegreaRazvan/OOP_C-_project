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
    for(int i = 0; i < repository.get_carti().size(); i++)
        if(repository.get_carti().at(i)==carte)
            throw Exception("Cartea deja apare in lista!\n");
    repository.add_carte(carte);
}

void Service::service_delete_carte(const string &titlu) {
    int position = repository.search(titlu);
    if(position==-1)
        throw Exception("Cartea nu se afla in lista!\n");
    repository.delete_carte(position);
    int poz, ok=0;
    for(int i = 0 ; i < cos.get_all_carti().size(); i++)
        if(titlu == cos.get_all_carti().at(i).getTitlu()) {
            poz = i;
            ok = 1;
        }
    if (ok)
        cos.delete_carte(poz);
}

void Service::service_modify_carte(const string &titlu, const string &autor, const string &gen, const int &an) {
    Carte carte = Carte(titlu,autor,gen,an);
    int position = repository.search(carte.getTitlu());
    if(position==-1)
        throw Exception("Cartea nu se afla in lista!\n");
    int poz, ok=0;
    repository.modify_carte(carte, position);
    for(int i = 0 ; i < cos.get_all_carti().size(); i++)
        if(titlu == cos.get_all_carti().at(i).getTitlu()) {
            poz = i;
            ok = 1;
        }
    if (ok)
        cos.modify_carte(carte,poz);
}

Carte Service::service_search(const string &titlu) const {
    int position = repository.search(titlu);
    if(position==-1)
        throw Exception("Cartea nu se afla in lista!\n");
    return repository.get_carte(position);
}

vector<Carte> Service::service_filter(const string &titlu) const{
    vector <Carte> v, v_copy;
    vector <Carte> V;
    for(const auto & i : repository.get_carti())
        v.push_back(i);
    std::copy_if(v.begin(), v.end(), std::back_inserter(v_copy),[=](const Carte& c){return c.getTitlu()==titlu;});
    for(const auto & i : v_copy)
        V.push_back(i);
    return V;
}

vector<Carte> Service::service_filter(const int &an) const{
    vector <Carte> v, v_copy;
    vector <Carte> V;
    for(const auto & i : repository.get_carti())
        v.push_back(i);
    std::copy_if(v.begin(), v.end(), std::back_inserter(v_copy),[=](const Carte& c){return c.getAnul()==an;});
    for(const auto & i : v_copy)
        V.push_back(i);
    return V;
}

vector<Carte> Service::sort_lambda(const int &var, const bool &ordine) const {
    vector <Carte> v;
    vector <Carte> V;
    auto it = repository.get_carti().begin();
    for(const auto & i : repository.get_carti())
        v.push_back(i);
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
    for(int i = 0; i < repository.get_carti().size(); i++)
        V.push_back(v.at(i));
    return V;

}

const vector<Carte> &Service::service_get_carti_cos() const {
    vector <Carte> v = cos.get_all_carti();
    if (v.empty())
        throw Exception("Lista goala!\n");
    return cos.get_all_carti();
}

void Service::service_add_carte_cos(const string &titlu) {
    int poz = repository.search(titlu);
    Carte carte = repository.get_carte(poz);
    for(const auto & c : cos.get_all_carti())
        if(c==carte)
            throw Exception("Cartea deja apare in cos!\n");
    cos.add_carte_to_cos(carte);
}

void Service::service_empty_cos() {
    if(cos.get_all_carti().empty())
        throw Exception("Cos deja gol!");
    cos.empty_cos();
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
    return nr_of_books_added_to_the_list;
}





