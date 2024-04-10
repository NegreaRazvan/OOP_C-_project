#pragma once
#include "../MyList/Vector.h"
#include "../Domain/Carte.h"
#include <algorithm>
using std::copy;

//using std::vector;

class Repository {
private:
    Vector<Carte> elemente;
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
      [[nodiscard]] const Vector<Carte> & get_carti() const;

      /**
       * se returneaza o carte de pe o pozitie
       * @param poz - pozitia de pe care se va returna cartea
       * @return cartea pe pe pozitia poz
       * pre: poz sa fie valid
       */
      [[nodiscard]] const Carte & get_carte(const int &poz) const;

      /**
       * copiaza lista curenta din repo
       * pre: -
       * @return o copie a liste din repo
       */
      [[nodiscard]] Vector<Carte> copy_list() const;

      /**
       * adauga o carte in lista din repo
       * @param carte - cartea care va urma sa fie adaugata
       * pre - carte valida
       */
      void add_carte(const Carte & carte);

      /**
       * sterge o carte de pe o pozitie
       * @param poz - pozitia de pe care va fi stearsa cartea
       * pre: poz - valida
       */
      void delete_carte(const int &poz);

      /**
       * modifica o carte de pe o pozitie
       * @param carte - cartea cu care se inlocuieste
       * @param poz - pozitie pe care se inlocuieste cartea
       * pre: carte- valida
       *      poz - pozitie valida
       */
      void modify_carte(const Carte &carte, const int& poz);

      /**
       * cauta o carte dupa titlu
       * @param titlu - string
       * @return pozitia pe care se afla cartea
       * pre: titlu valid
       */
      [[nodiscard]] int search(const string &titlu) const;

};
