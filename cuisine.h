#ifndef CUISINE_H
#define CUISINE_H

#include <QAbstractTableModel>
#include "dish.h"

const QString dateFormat = QObject::trUtf8("dd-MM-yyyy");
const QString timeFormat = QObject::trUtf8("HH:mm:ss");

struct Order {
    QDate date;
    QTime time;
    QString dish;
    int count;
};

class Cuisine: public QAbstractTableModel
{
private:
    static Cuisine *instance_;

public:
    static Cuisine *getInstance();

    QList<Order> orderList;
    QDate dateFrom, dateTo;

    int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    void clear() {
        orderList.clear();
        dateFrom = QDate(3000, 1, 1);
        dateTo = QDate(2000, 1, 1);
    }

    void addOrder(QString);
};

#endif // CUISINE_H
