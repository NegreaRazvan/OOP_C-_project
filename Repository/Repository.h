#pragma once
#include "../Domain/Carte.h"
#include <algorithm>
#include <vector>
#include <fstream>
#include "../Exception/Exception.h"
#include <sstream>
using std::copy;
using std::stringstream;


using std::vector;


class Repository_Interface {

public:

    virtual ~Repository_Interface() = default;

    [[nodiscard]]virtual const vector<Carte> & get_carti() const = 0;

    /**
     * se returneaza o carte de pe o pozitie
     * @param poz - pozitia de pe care se va returna cartea
     * @return cartea pe pe pozitia poz
     * pre: poz sa fie valid
     */
    [[nodiscard]]virtual const Carte & get_carte(const int &poz) const = 0;

    /**
     * copiaza lista curenta din repo
     * pre: -
     * @return o copie a liste din repo
     */
    [[nodiscard]] virtual vector<Carte> copy_list() const = 0;

    /**
     * adauga o carte in lista din repo
     * @param carte - cartea care va urma sa fie adaugata
     * pre - carte valida
     */
    virtual void add_carte(const Carte & carte) = 0;

    /**
     * sterge o carte de pe o pozitie
     * @param poz - pozitia de pe care va fi stearsa cartea
     * pre: poz - valida
     */
    virtual void delete_carte(const __gnu_cxx::__normal_iterator<const Carte *, vector<Carte>> &poz) = 0;

    /**
     * modifica o carte de pe o pozitie
     * @param carte - cartea cu care se inlocuieste
     * @param poz - pozitie pe care se inlocuieste cartea
     * pre: carte- valida
     *      poz - pozitie valida
     */
    virtual void modify_carte(const Carte &carte, const Carte &c_de_mod) = 0;

    /**
     * cauta o carte dupa titlu
     * @param titlu - string
     * @return pozitia pe care se afla cartea
     * pre: titlu valid
     */
    [[nodiscard]] virtual __gnu_cxx::__normal_iterator<const Carte *, vector<Carte>> search(const string &titlu) const = 0;

};



class Repository: public Repository_Interface{
protected:
    vector<Carte> elemente;
public:
      /**
       * Constructor default
       * returneaza: un repo
       */
      Repository() = default;
      /**
       * nu permite sa fie copiat repo ul
       * @param repo
       */
      Repository(const  Repository& repo) = delete;

      /**
       * returneaza toate cartile din lista din repo
       * pre: -
       * @return cartile din lista
       */
      [[nodiscard]]virtual const vector<Carte> & get_carti() const override;

      /**
       * se returneaza o carte de pe o pozitie
       * @param poz - pozitia de pe care se va returna cartea
       * @return cartea pe pe pozitia poz
       * pre: poz sa fie valid
       */
      [[nodiscard]]virtual const Carte & get_carte(const int &poz) const override;

      /**
       * copiaza lista curenta din repo
       * pre: -
       * @return o copie a liste din repo
       */
      [[nodiscard]] vector<Carte> copy_list() const override;

      /**
       * adauga o carte in lista din repo
       * @param carte - cartea care va urma sa fie adaugata
       * pre - carte valida
       */
      virtual void add_carte(const Carte & carte) override;

      /**
       * sterge o carte de pe o pozitie
       * @param poz - pozitia de pe care va fi stearsa cartea
       * pre: poz - valida
       */
      virtual void delete_carte(const __gnu_cxx::__normal_iterator<const Carte *, vector<Carte>> &poz) override;

      /**
       * modifica o carte de pe o pozitie
       * @param carte - cartea cu care se inlocuieste
       * @param poz - pozitie pe care se inlocuieste cartea
       * pre: carte- valida
       *      poz - pozitie valida
       */
      virtual void modify_carte(const Carte &carte, const Carte &c_de_mod) override;

      /**
       * cauta o carte dupa titlu
       * @param titlu - string
       * @return pozitia pe care se afla cartea
       * pre: titlu valid
       */
      [[nodiscard]] virtual __gnu_cxx::__normal_iterator<const Carte *, vector<Carte>> search(const string &titlu) const override;

};



class FileRepository: public Repository{
private:
    string path;

    void read_from_file();

    void write_to_file();

public:
    FileRepository(string filename):Repository(), path{filename}{
        read_from_file();
    };

    [[nodiscard]] const vector<Carte> & get_carti() const override;

    void add_carte(const Carte &carte) override;

    void delete_carte(const __gnu_cxx::__normal_iterator<const Carte *, vector<Carte>> &poz) override;

    [[nodiscard]] const Carte & get_carte(const int &poz) const override;

    void modify_carte(const Carte &carte, const Carte &c_de_mod) override;

    [[nodiscard]] __gnu_cxx::__normal_iterator<const Carte *, vector<Carte>> search(const std::string &titlu) const override;

    void reset_file_for_tests();
};
