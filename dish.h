#ifndef DISH_H
#define DISH_H

#include <QString>
#include <QStringList>
#include <QTime>
#include <QDate>
#include <QDebug>

struct Ingr {
    Ingr(QString n, int c) {name = n, count = c;}
    QString name;
    int count;
};

struct Dish {
    Dish(QString t, QString n) {type = t; name = n;}
    Dish(QString t, QString n, QList<Ingr> i) {
        type = t;
        name = n;
        ingredients = i;
    }
    QString type;
    QString name;
    QList<Ingr> ingredients;
};

class DishList
{
private:
    static DishList *instance_;

public:
    static DishList *getInstance();
    void init();

    QList<Dish> list;

    Dish getDish(QString name);

    QString getType(QString name);
    QStringList getTypes();
};



#endif // DISH_H
