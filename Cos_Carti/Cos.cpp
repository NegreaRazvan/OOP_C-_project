#include "Cos.h"

//void Cos::empty_file(const string& path_export) {
//    ofstream ofs;
//    ofs.open(path_export, ofstream::trunc);
//    ofs.close();
//}

void Cos::empty_cos() {
    cos_carti.clear();
}

void Cos::add_carte_to_cos(const Carte &carte) {
    cos_carti.push_back(carte);
}

void Cos::export_carti(const string& path_export) const {
    ofstream fout(path_export);
    for(const auto& c: cos_carti)
        fout<<c.getTitlu()<<','<<c.getAutor()<<','<<c.getGen()<<','<<c.getAnul()<<'\n';
    fout.close();
}

const vector<Carte>& Cos::get_all_carti() const {
    return cos_carti;
}

void Cos::delete_carte(const __gnu_cxx::__normal_iterator<const Carte *, vector<Carte>> &poz) {
    cos_carti.erase(poz);
}

void Cos::modify_carte(const Carte &carte, const Carte& c_de_mod) {
    auto book = std::find_if(cos_carti.begin(),cos_carti.end(), [&](const Carte& c){return c_de_mod == c;});
    *book=carte;
}


