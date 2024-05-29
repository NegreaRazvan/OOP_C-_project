#include "MyModel.h"

MyTableModel::MyTableModel(const vector<Carte>& elemente) : QAbstractTableModel{}, list{ elemente } {}

int MyTableModel::rowCount(const QModelIndex& parent) const {
    return list.size();
}

int MyTableModel::columnCount(const QModelIndex& parent) const {
    return 4;
}

QVariant MyTableModel::data(const QModelIndex& index, int role) const {
    if (role == Qt::DisplayRole) {
        string output = "{Title} ";
        output+=list.at(index.row()).getTitlu();
        output+=" {Author} ";
        output+=list.at(index.row()).getAutor();
        output+=" {Genre} ";
        output+=list.at(index.row()).getGen();
        output+=" {Year} ";
        output+=std::to_string(list.at(index.row()).getAnul());
        return QString::fromStdString(output);
    }
    return QVariant();
}

void MyTableModel::setElemente(const vector<Carte>& v) {
    list = v;
    auto top = createIndex(0, 0);
    auto bottom = createIndex(rowCount(), columnCount());
    emit dataChanged(top, bottom);
}