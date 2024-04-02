#include "Service.h"

const vector<Carte> &Service::service_get_carti() const {
    vector <Carte> v = repository.get_carti();
    if (v.empty())
        throw std::runtime_error("Lista goala!\n");
    return repository.get_carti();
}

vector<Carte> Service::service_copy_list() const {
    return repository.copy_list();
}

void Service::service_add_carte(const string &titlu, const string &autor, const string &gen, const int &an) {
    Carte carte = Carte(titlu,autor,gen,an);
    for(auto c: repository.get_carti())
        if(c==carte)
            throw std::runtime_error("Cartea deja apare in lista!\n");
    repository.add_carte(carte);
}

void Service::service_delete_carte(const string &titlu) {
    int position = repository.search(titlu);
    if(position==-1)
        throw std::runtime_error("Cartea nu se afla in lista!\n");
    repository.delete_carte(position);
}

void Service::service_modify_carte(const string &titlu, const string &autor, const string &gen, const int &an) {
    Carte carte = Carte(titlu,autor,gen,an);
    int position = repository.search(carte.getTitlu());
    if(position==-1)
        throw std::runtime_error("Cartea nu se afla in lista!\n");
    repository.modify_carte(carte, position);
}

Carte Service::service_search(const string &titlu) const {
    int position = repository.search(titlu);
    if(position==-1)
        throw std::runtime_error("Cartea nu se afla in lista!\n");
    return repository.get_carte(position);
}

vector<Carte> Service::service_filter(const string &titlu) const{
    vector <Carte> v;
    std::copy_if(repository.get_carti().begin(), repository.get_carti().end(), std::back_inserter(v),[=](const Carte& c){return c.getTitlu()==titlu;});
    return v;
}

vector<Carte> Service::service_filter(const int &an) const{
    vector <Carte> v;
    std::copy_if(repository.get_carti().begin(), repository.get_carti().end(), std::back_inserter(v),[=](const Carte& c){return c.getAnul()==an;});
    return v;
}

void Service::sort_lambda(vector<Carte> &vector_copie, const int &var, const bool &ordine) const {
    switch (var) {
        case 1:
            std::sort(vector_copie.begin(), vector_copie.end(),[ordine](const Carte &c1, const Carte &c2){if(c1.getTitlu()<=c2.getTitlu()) return ordine; return !(ordine);});
            break;
        case 2:
            std::sort(vector_copie.begin(), vector_copie.end(),[ordine](const Carte &c1, const Carte &c2){if(c1.getAutor()<=c2.getAutor()) return ordine; return !(ordine);});
            break;
        case 3:
            std::sort(vector_copie.begin(), vector_copie.end(), [ordine](const Carte &c1, const Carte &c2){if(c1.getAnul()<c2.getAnul())return ordine;else if(c1.getAnul()==c2.getAnul())if(c1.getGen()<=c2.getGen())return ordine;return !(ordine);});
            break;
    }

}



