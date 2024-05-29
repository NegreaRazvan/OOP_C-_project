//
// Created by Razvan on 5/28/2024.
//
#pragma once
#ifndef C___OOP_QT_MYMODEL_H
#define C___OOP_QT_MYMODEL_H
#include <QAbstractTableModel>
#include "../Domain/Carte.h"
#include <vector>
using std::vector;

class MyTableModel : public QAbstractTableModel{
private:
    vector<Carte> list;
public:
    MyTableModel(const vector<Carte>& elemente);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;

    int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    [[nodiscard]] QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    void setElemente(const vector<Carte>& elemente);
};


#endif //C___OOP_QT_MYMODEL_H
