#pragma once
#include "../Service/Service.h"
#include <iostream>

class UI {
private:
    Service service;

    /**
     * adauga o carte
     */
    void ui_add_carte();

    /**
     * sterge o carte din lista
     */
    void ui_delete_carte();

    /**
     * modifica o carte din lista
     */
    void ui_modify_carte();

    /**
     * cauta o carte dupa un titlu
     */
    void ui_search();

    /**
     * filtreaza elementele dupa un criteriu
     */
    void ui_filter();

    /**
     * sorteaza elementele dupa un criteriu
     */
    void ui_sort();

    /**
     * arata toate elementele din lista
     */
    void ui_show_list();

    /**
     * genereaza niste carti pt utilizator, ca sa testeze functionalitatile
     * @param ales - true sau false, depinzand daca s-a apelat sau nu
     */
    void ui_generate_carti(bool &ales);

    void ui_add_carte_in_cos();

    void ui_empty_cos();

    void ui_generate_carti_in_cos();

    void ui_export_carti();

    void ui_show_cos();

    void ui_raport_genuri();

    void ui_undo();
    /**
     * comenzile oferite utilizatorului
     */
    static void commands();


public:
    /**
     * constructor default pt UI
     * returneaza un ui
     */
    UI(Service &serv) : service{serv}{};
    /**
     * nu permite sa se faca o copie la ui
     * @param ui - ui
     */
    UI (const UI &ui) =delete;

    /**
     * interfata in consola, cu toate optiunile oferite utilizatorului
     */
    void run();
};
