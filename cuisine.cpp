#include "cuisine.h"
#include <QDebug>

Cuisine *Cuisine::instance_ = 0;

Cuisine *Cuisine::getInstance() {
    if(!instance_)
        instance_ = new Cuisine;
    return instance_;
}

int Cuisine::rowCount(const QModelIndex & ) const {
    return orderList.size();
}

int Cuisine::columnCount(const QModelIndex &) const {
    return 5;
}

QVariant Cuisine::headerData(int section, Qt::Orientation orientation, int role) const {
    if(role == Qt::DisplayRole) {
        if(orientation == Qt::Horizontal) {
            switch(section) {
            case 0: return trUtf8("Дата");
            case 1: return trUtf8("Время");
            case 2: return trUtf8("Тип");
            case 3: return trUtf8("Название");
            case 4: return trUtf8("Количество");
            default: return QVariant();
            }
        } else {
            return section+1;
        }

    }
    return QVariant();
}

QVariant Cuisine::data ( const QModelIndex & index, int role ) const {
    if(role == Qt::DisplayRole) {
        switch(index.column()) {
        case 0:
            return orderList.at(index.row()).date.toString("dd MMMM yyyy");
        case 1:
            return orderList.at(index.row()).time.toString("HH:mm:ss");
        case 2:
            return DishList::getInstance()->getType(orderList.at(index.row()).dish);
        case 3:
            return orderList.at(index.row()).dish;
        case 4:
            return orderList.at(index.row()).count;
        default:
            return QVariant();
        }
    }
    return QVariant();
}


void Cuisine::addOrder(QString ord) {
    QStringList list = ord.split(",", QString::SkipEmptyParts);

    if(list.size() < 4)
        return;

    Order order;
    order.date = QDate::fromString(list.at(0).trimmed(), dateFormat);
    order.time = QTime::fromString(list.at(1).trimmed(), timeFormat);
    order.dish = list.at(2).trimmed();
    order.count = list.at(3).toInt();
    orderList << order;

    if(order.date < dateFrom)
        dateFrom = order.date;

    if(order.date > dateTo)
        dateTo = order.date;
}
