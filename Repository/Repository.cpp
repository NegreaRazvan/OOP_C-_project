#include "Repository.h"

const vector<Carte> &Repository::get_carti() const {
    return elemente;
}

const Carte &Repository::get_carte(const int &poz) const {
    return elemente.at(poz);
}

vector<Carte> Repository::copy_list() const {
    return elemente;
}

void Repository::add_carte(const Carte &carte) {
    elemente.push_back(carte);
}

void Repository::delete_carte(const int &poz) {
    elemente.erase(elemente.begin()+poz);
}

void Repository::modify_carte(const Carte &carte, const int& poz) {
    elemente[poz] = carte;
}

int Repository::search(const string &titlu) const{
//    std::find_if(elemente.begin(),elemente.end(), [titlu](const Carte& c){return titlu==c.getTitlu();});
    for(int i = 0 ; i < elemente.size(); i++)
        if(titlu == elemente.at(i).getTitlu())
            return i;
    return -1;
}


