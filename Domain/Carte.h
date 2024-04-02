#pragma once
#include <string>
#include <stdexcept>

using std::string;

class Carte {
public:

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

    /**
     * getter pentru titlu
     * @return titlul -string
     * pre: -
     */
    const string &getTitlu() const;

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
    const string &getAutor() const;

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
    const string &getGen() const;

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
    const int &getAnul() const;

    /**
     * setter pentru an
     * @param an - int cu care se inlocuieste curentul an
     * pre - an pozitiv
     * post -
     */
    void setAnul(const int &anul);

    bool operator==(const Carte& c) const;

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

