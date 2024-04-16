#pragma once
#include <vector>
#include "../Domain/Carte.h"
#include <fstream>

using std::vector;
using std::ofstream;

class Cos {
private:
    vector<Carte> cos_carti;

public:

//    void empty_file(const string& path_export);

    Cos()=default;

    void empty_cos();

    void add_carte_to_cos(const Carte& carte);

    void export_carti(const string& path_export) const;

    [[nodiscard]] const vector<Carte> &get_all_carti() const;

    void delete_carte(const int &poz);

    void modify_carte(const Carte &carte, const int& poz);

    [[nodiscard]] int search(const string &titlu) const;
};


