#pragma once
#include "../Repository/Repository.h"
#include "../Cos_Carti/Cos.h"
#include <vector>
#include <random>


using std::vector;

class Service {
private:
    Repository repository;
    Cos cos;
public:
    /**
       * Constructor default
       * returneaza: un service
       */
    Service() = default;
    /**
       * nu permite sa fie copiat service ul
       * @param service
       */
    Service (const Service &service) =delete;

    /**
       * returneaza toate cartile din lista din repo
       * pre: -
       * @return cartile din lista
       * raises: "Lista goala!\n" - daca lista e goala
       */
    [[nodiscard]] const vector<Carte> & service_get_carti() const;

    [[nodiscard]] const vector<Carte> & service_get_carti_cos() const;


    /**
     * adauga in lista element
     * @param titlu - string
     * @param autor - string
     * @param gen - string
     * @param an - int
     * pre: -
     * post: -
     * raises - "Cartea deja apare in lista!\n" - daca deja este cartea in lista
     */
    void service_add_carte(const string & titlu, const string & autor, const string & gen, const int & an);

    /**
     * sterge un element din lista
     * @param titlu - string
     * pre: -
     * post: -
     * raises - "Cartea nu se afla in lista!\n" - daca nu e elementul in lista
     */
    void service_delete_carte(const string &titlu);

    /**
     * modifica o carte din lista
     * @param titlu - string, titlul cartii la care facem modificari
     * @param autor - autorul cu care se modifica
     * @param gen - genul cu care se modifica
     * @param an - anul cu care se modifica
     * pre: -
     * post: -
     * raises: "Cartea nu se afla in lista!\n" -daca cartea nu e in lista
     */
    void service_modify_carte(const string &titlu, const string &autor, const string &gen, const int &an);

    /**
     * returneaza cartea cu un titlu
     * @param titlu - string, titlul cartii cautate
     * pre: -
     * @return prima carte cu titlul acesta
     * raises: "Cartea nu se afla in lista!\n" - daca nu se afla in lista copia
     */
    [[nodiscard]] Carte service_search(const string &titlu) const;

    /**
     * filtreaza elementele dupa un titlu dat
     * @param titlu - titlul dupa care se filtreaza
     * @return un vector cu elementele dorite
     */
    [[nodiscard]] vector<Carte> service_filter(const string &titlu) const;

    /**
     * filtreaza elementele dupa un an dat
     * @param an - an dupa care se filtreaza
     * @return un vector cu elementele dorite
     */
    [[nodiscard]] vector<Carte> service_filter(const int &an) const;

    /**
     * sorteaza elementele din lista
     * @param vector_copie - o copie a elementelor din lista
     * @param var - varianta de sortare care va fi folosita
     *            -1 - pt titlu
     *            -2 - pt autor
     *            -3 - pt an si gen
     * @param ordine - ordinea in care va fi sortat
     *               - true - pt crescator
     *               - false - pt descrescator
     * pre: -
     * post: -
     */
    [[nodiscard]] vector<Carte> sort_lambda(const int& var, const bool& ordine) const;

    void service_add_carte_cos(const string & titlu);

    void service_empty_cos();

    void service_export_cos(const string& path);

    void clear_all_files(const vector<string>& paths);

     int generate_books(const int& nr_of_books);

};



