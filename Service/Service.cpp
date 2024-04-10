#include "Service.h"

const Vector<Carte> &Service::service_get_carti() const {
    Vector <Carte> v = repository.get_carti();
    if (v.empty())
        throw std::runtime_error("Lista goala!\n");
    return repository.get_carti();
}

void Service::service_add_carte(const string &titlu, const string &autor, const string &gen, const int &an) {
    Carte carte = Carte(titlu,autor,gen,an);
//    auto i = std::find(repository.get_carti().begin(),repository.get_carti().end(), carte);
//    if (i==repository.get_carti().end())
//        throw std::runtime_error("Cartea deja apare in lista!\n");
    for(int i = 0; i < repository.get_carti().size(); i++)
        if(repository.get_carti().at(0)==carte)
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

Vector<Carte> Service::service_filter(const string &titlu) const{
    vector <Carte> v, v_copy;
    Vector <Carte> V;
    for(const auto & i : repository.get_carti())
        v.push_back(i);
    std::copy_if(v.begin(), v.end(), std::back_inserter(v_copy),[=](const Carte& c){return c.getTitlu()==titlu;});
    for(const auto & i : v_copy)
        V.push_back(i);
    return V;
}

Vector<Carte> Service::service_filter(const int &an) const{
    vector <Carte> v, v_copy;
    Vector <Carte> V;
    for(const auto & i : repository.get_carti())
        v.push_back(i);
    std::copy_if(v.begin(), v.end(), std::back_inserter(v_copy),[=](const Carte& c){return c.getAnul()==an;});
    for(const auto & i : v_copy)
        V.push_back(i);
    return V;
}

Vector<Carte> Service::sort_lambda(const int &var, const bool &ordine) const {
    vector <Carte> v;
    Vector <Carte> V;
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



