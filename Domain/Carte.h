#pragma once
#include <string>
#include <stdexcept>
#include <iostream>

using std::string;

class Carte {
public:

    Carte()=default;
    /**
     * constructor pentru carte
     * @param titlu - string
     * @param autor -string
     * @param gen -string
     * @param anul -int
     * pre: -
     * post: o carte
     */
    Carte(const string &titlu, const string &autor, const string &gen,const int &anul);

//    Carte (const Carte& c){
//        std::cout<<"copiere\n";
//        titlu = c.titlu;
//        autor = c.autor;
//        gen = c.gen;
//        anul = c.anul;
//    };
//    💀
//    ~Carte(){
//        std::cout<<"destroy_child\n";
//    }

    /**
     * getter pentru titlu
     * @return titlul -string
     * pre: -
     */
    [[nodiscard]] const string &getTitlu() const;

    /**
     * setter pentru titlu
     * @param titlu - string cu care se inlocuieste curentul titlu
     * pre - titlu nevid
     * post -
     */
    void setTitlu(const string &titlu);

    /**
     * getter pentru autor
     * @return autor -string
     * pre: -
     */
    [[nodiscard]] const string &getAutor() const;

    /**
     * setter pentru autor
     * @param autor - string cu care se inlocuieste curentul autor
     * pre - autor nevid
     * post -
     */
    void setAutor(const string &autor);

    /**
     * getter pentru gen
     * @return gen - string
     * pre: -
     */
    [[nodiscard]] const string &getGen() const;

    /**
     * setter pentru gen
     * @param gen - string cu care se inlocuieste curentul gen
     * pre - gen nevid
     * post -
     */
    void setGen(const string &gen);

    /**
     * getter pentru an
     * @return anul - int
     * pre: -
     */
    [[nodiscard]] const int &getAnul() const;

    /**
     * setter pentru an
     * @param an - int cu care se inlocuieste curentul an
     * pre - an pozitiv
     * post -
     */
    void setAnul(const int &anul);

    bool operator==(const Carte& c) const;

    Carte& operator=(const Carte& c);

//    Carte operator=(const Carte& c);

private:
    string titlu;
    string autor;
    string gen;
    int anul;

    /**
     * verifica daca o carte primita este valida
     * @param c -carte
     * @return un string gol daca nu exista erori
     * raises: "An invalid!\n" - daca anul e negativ
     *          "Autor invalid!\n" - daca autorul e vid
     *          "Gen invalid!\n" - gen este vid
     *          "Titlu invalid!\n" - titlu este vid
     */
    static string valideazaCarte(const Carte &c);


};

