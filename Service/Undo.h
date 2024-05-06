#include "../Repository/Repository.h"

class Undo {
public:
    virtual void doUndo() = 0;
    virtual ~Undo() = default;
};

class UndoAdd: public Undo{
private:
    Carte book;
    Repository_Interface& repository;
public:
    UndoAdd(const Carte& b, Repository_Interface& r):book{b},repository{r}{};

    void doUndo () override {
        repository.delete_carte(repository.search(book.getTitlu()));
    }
};

class UndoDelete: public Undo{
private:
    Carte book;
    Repository_Interface& repository;
public:
    UndoDelete(const Carte& b, Repository_Interface& r):book{b},repository{r}{};

    void doUndo () override {
        repository.add_carte(book);
    }
};

class UndoModify: public Undo{
private:
    Carte modified_book, original_book;
    Repository_Interface& repository;
public:
    UndoModify(const Carte& m,const Carte& o, Repository_Interface& r):modified_book{m},original_book{o},repository{r}{};

    void doUndo () override {
        repository.modify_carte(original_book,modified_book);
    }
};

