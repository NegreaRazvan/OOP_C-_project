#pragma once
#include <iostream>


template <typename TElement>
class Iterator;

template <typename TElement>
class Vector {
private:
    TElement* elemente;
    int lungime;
    int capacitate;

    void resize();

    void downsize();

public:
    Vector();

    Vector(const Vector<TElement>& v);

    ~Vector();

    void push_back(const TElement &elem);

    const TElement & at(const int &pozitie) const;

    void erase(const int& poz);

    [[nodiscard]] const int & size() const;

    [[nodiscard]] bool empty() const;

    TElement& operator[](const int& index);

    Vector<TElement>& operator=(const Vector<TElement>& vec);

    friend class Iterator<TElement>;

    Iterator<TElement> begin() const;
    Iterator<TElement> end() const;

};

template<typename TElement>
Vector<TElement>& Vector<TElement>::operator=(const Vector<TElement>& vec) {
    delete[] elemente;
    elemente= new TElement[vec.capacitate];
    for(int i = 0; i < vec.size(); i++)
        elemente[i]=vec.at(i);
    lungime=vec.lungime;
    capacitate=vec.capacitate;
    return *this;
}

template<typename TElement>
TElement &Vector<TElement>::operator[](const int &index) {
    return elemente[index];
}

template<typename TElement>
void Vector<TElement>::resize() {
    int nCap = 2 * capacitate;
    TElement* newElemens = new TElement[nCap];
    for (int i = 0; i < lungime; i++)
        newElemens[i] = elemente[i];
    delete[] elemente;
    elemente = newElemens;
    capacitate = nCap;
}

template<typename TElement>
void Vector<TElement>::downsize() {
    int nCap = capacitate/2;
    TElement* newElemens = new TElement[nCap];
    for (int i = 0; i < lungime; i++)
        newElemens[i] = elemente[i];
    delete[] elemente;
    elemente = newElemens;
    capacitate = nCap;
}

///rule of 3
template<typename TElement>
Vector<TElement>::Vector() : lungime{0}, capacitate{4},elemente(new TElement[4]) {
}

///rule of 3
template<typename TElement>
Vector<TElement>::Vector(const Vector<TElement> &v) {
    elemente = new TElement[v.capacitate];
    this->lungime = v.lungime;
    this->capacitate =v.capacitate;
    for(int i = 0 ; i < this->lungime; i++)
        elemente[i] = v.at(i);
}

///rule of 3
template<typename TElement>
Vector<TElement>::~Vector() {
    delete[] elemente;
}

template<typename TElement>
void Vector<TElement>::push_back(const TElement &elem) {
    if(lungime==capacitate)
        resize();
    elemente[lungime]=elem;
    lungime++;
}

template<typename TElement>
const TElement & Vector<TElement>::at(const int &pozitie) const {
    if (pozitie>=lungime||pozitie<0)
        throw std::out_of_range("Index out of range");
    return elemente[pozitie];
}

template<typename TElement>
void Vector<TElement>::erase(const int& poz) {
    if(poz<0||poz>=lungime)
        throw std::out_of_range("Index out of range");
    if(lungime==capacitate/2)
        downsize();
    for(int i = poz; i < lungime-1; i++)
        elemente[i]=at(i+1);
    lungime--;
}

template<typename TElement>
bool Vector<TElement>::empty() const {
    if(lungime==0)
        return true;
    return false;
}

template<typename TElement>
const int & Vector<TElement>::size() const {
    return lungime;
}

template<typename TElement>
Iterator<TElement> Vector<TElement>::end() const {
    return Iterator<TElement>(*this,lungime);
}

template<typename TElement>
Iterator<TElement> Vector<TElement>::begin() const {
    return Iterator<TElement>(*this, 0);
}




/***********************************************************************/





template<typename TElement>
class Iterator {
private:
    const Vector<TElement>& vect;
    int curent;

public:
    Iterator(const Vector<TElement>& v,int poz) noexcept;
    bool valid() const;
    TElement& element() const;
    void next();
    TElement& operator*();
    Iterator<TElement>& operator++();
    bool operator==(const Iterator<TElement> &it);
    bool operator!=(const Iterator<TElement> &it);

};

template<typename TElement>
Iterator<TElement>::Iterator(const Vector<TElement> &v, int poz) noexcept : curent(poz), vect(v) {}

template<typename TElement>
bool Iterator<TElement>::valid() const {
    if(curent<0||curent>=vect.size())
        return false;
    return true;
}


template<typename TElement>
void Iterator<TElement>::next() {
    curent++;
}

template<typename TElement>
TElement &Iterator<TElement>::element() const {
    return vect.elemente[curent];
}

template<typename TElement>
TElement &Iterator<TElement>::operator*() {
    return element();
}

template<typename TElement>
Iterator<TElement> &Iterator<TElement>::operator++() {
    next();
    return *this;
}

template<typename TElement>
bool Iterator<TElement>::operator==(const Iterator<TElement>& it) {
    return curent==it.curent;

}

template<typename TElement>
bool Iterator<TElement>::operator!=(const Iterator<TElement> &it) {
    return curent != it.curent;
}

