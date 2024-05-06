#include "Carte.h"
#include "../Exception/Exception.h"


const string &Carte::getTitlu() const {
    return titlu;
}

void Carte::setTitlu(const string &titlu) {
    this->titlu = titlu;
}

const string &Carte::getAutor() const {
    return autor;
}

void Carte::setAutor(const string &autor) {
    this->autor = autor;
}

const string &Carte::getGen() const {
    return gen;
}

void Carte::setGen(const string &gen) {
    this->gen = gen;
}

const int &Carte::getAnul() const {
    return anul;
}

void Carte::setAnul(const int &anul) {
    this->anul = anul;
}

Carte::Carte(const string &titlu, const string &autor, const string &gen,const int& anul) : titlu(titlu), autor(autor), gen(gen), anul(anul) { valideazaCarte(*this);}


string Carte::valideazaCarte(const Carte &c){
    string error;
    if (c.getAnul() < 0)
        error+="An invalid!\n";
    if(c.getAutor().empty())
        error+="Autor invalid!\n";
    if(c.getGen().empty())
        error+="Gen invalid!\n";
    if (c.getTitlu().empty())
        error+="Titlu invalid!\n";
    if(!error.empty())
        throw Exception(error);
    return error;
}

bool Carte::operator==(const Carte &c) const {
    if(titlu==c.titlu && autor==c.autor && gen ==c.gen && anul == c.anul)
        return true;
    return false;
}

Carte& Carte::operator=(const Carte &c) {
    titlu=c.titlu;
    autor=c.autor;
    gen=c.gen;
    anul=c.anul;
    return *this;
}



//Carte Carte::operator=(const Carte &c) {
//    return Carte(c.getTitlu(), c.getAutor(), c.getGen(),c.getAnul());
//}
