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

void Repository::delete_carte(const __gnu_cxx::__normal_iterator<const Carte *, vector<Carte>> &poz) {
    elemente.erase(poz);
}

void Repository::modify_carte(const Carte &carte, const Carte &c_de_mod) {
    auto book = std::find_if(elemente.begin(),elemente.end(), [&](const Carte& c){return c_de_mod == c;});
    *book=carte;
}

__gnu_cxx::__normal_iterator<const Carte *, vector<Carte>> Repository::search(const string &titlu) const{
    return std::find_if(elemente.begin(),elemente.end(), [titlu](const Carte& c){return titlu==c.getTitlu();});
}

/****************************************************************************************************************/

void FileRepository::read_from_file() {
    std::ifstream bookFile(this->path);
    if(!bookFile.is_open())
        throw Exception("Cannot open file "+path);
    string line;
    elemente.clear();
    while(getline(bookFile,line)){
        string title,author,type;
        int year;
        stringstream linestream(line);
        string current_atribute;
        int item_no=0;
        while(getline(linestream,current_atribute,',')){
            if (item_no == 0) title = current_atribute;
            if (item_no == 1)  author= current_atribute;
            if (item_no == 2) type = current_atribute;
            if (item_no == 3) year = stoi(current_atribute);
            item_no++;
        }
        Carte book=Carte(title,author,type,year);
        elemente.push_back(book);
    }
    bookFile.close();
}

void FileRepository::write_to_file() {
    std::ofstream bookFile(path);
    if(!bookFile.is_open())
        throw Exception("Cannot open file "+path);
    for(const auto& b: elemente)
        bookFile<<b.getTitlu()<<','<<b.getAutor()<<','<<b.getGen()<<','<<b.getAnul()<<std::endl;
    bookFile.close();
}

const vector<Carte> &FileRepository::get_carti() const {
    return Repository::get_carti();
}

void FileRepository::add_carte(const Carte &carte) {
    Repository::add_carte(carte);
    write_to_file();
}

void FileRepository::delete_carte(const __gnu_cxx::__normal_iterator<const Carte *, vector<Carte>> &poz) {
    Repository::delete_carte(poz);
    write_to_file();
}

const Carte &FileRepository::get_carte(const int &poz) const {
    return Repository::get_carte(poz);
}

void FileRepository::modify_carte(const Carte &carte, const Carte &c_de_mod) {
    Repository::modify_carte(carte, c_de_mod);
    write_to_file();
}

__gnu_cxx::__normal_iterator<const Carte *, vector<Carte>> FileRepository::search(const string &titlu) const {
    return Repository::search(titlu);
}

void FileRepository::reset_file_for_tests() {
    std::ofstream ofs(path);
}

/****************************************************************************************************************/
