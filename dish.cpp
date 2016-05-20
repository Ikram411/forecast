#include "dish.h"
#include <QObject>

DishList *DishList::instance_ = 0;

DishList *DishList::getInstance() {
    if(!instance_)
        instance_ = new DishList;
    return instance_;
}

Dish DishList::getDish(QString name) {
    foreach(Dish d, list)
        if(d.name == name)
            return d;
}

QString DishList::getType(QString name) {
    foreach(Dish d, list)
        if(d.name == name)
            return d.type;

    qDebug() << "unknown name" << name << list.size();
    return NULL;
}

QStringList DishList::getTypes() {
    QStringList typeList;
    foreach(Dish d, list)
        if(!typeList.contains(d.type))
            typeList << d.type;
    return typeList;
}

void DishList::init() {
    QList<Ingr> ingrs;

    ingrs.clear();
    ingrs << Ingr(QObject::trUtf8("алкоголь"), 100)
          << Ingr(QObject::trUtf8("помидоры"),  100)
          << Ingr(QObject::trUtf8("сыр"),  50)
          << Ingr(QObject::trUtf8("кура"),  50);
    list << Dish(QObject::trUtf8("алкоголь"),    QObject::trUtf8("цезарь"), ingrs);

    ingrs.clear();
    ingrs << Ingr(QObject::trUtf8("картофель"), 100)
          << Ingr(QObject::trUtf8("морковь"),  100)
          << Ingr(QObject::trUtf8("рыба"),  50);
    list << Dish(QObject::trUtf8("алкоголь"),    QObject::trUtf8("мимоза"), ingrs);

    ingrs.clear();
    ingrs << Ingr(QObject::trUtf8("картофель"), 100)
          << Ingr(QObject::trUtf8("морковь"),  100)
          << Ingr(QObject::trUtf8("колбаса"),  50);
    list << Dish(QObject::trUtf8("алкоголь"),    QObject::trUtf8("оливье"), ingrs);

    ingrs.clear();
    ingrs << Ingr(QObject::trUtf8("вода"), 500)
          << Ingr(QObject::trUtf8("рис"),  200);
    list << Dish(QObject::trUtf8("суп"),    QObject::trUtf8("харчо"), ingrs);

    ingrs.clear();
    ingrs << Ingr(QObject::trUtf8("вода"), 500)
          << Ingr(QObject::trUtf8("картофель"), 200);
    list << Dish(QObject::trUtf8("суп"),    QObject::trUtf8("борщ"), ingrs);

    ingrs.clear();
    ingrs << Ingr(QObject::trUtf8("вода"), 500)
          << Ingr(QObject::trUtf8("колбаса"), 100)
          << Ingr(QObject::trUtf8("оливки"), 20);
    list << Dish(QObject::trUtf8("суп"),    QObject::trUtf8("солянка"), ingrs);

    ingrs.clear();
    ingrs << Ingr(QObject::trUtf8("пельмени"), 250);
    list << Dish(QObject::trUtf8("второе"),    QObject::trUtf8("пельмени"), ingrs);

    ingrs.clear();
    ingrs << Ingr(QObject::trUtf8("фарш"), 150)
          << Ingr(QObject::trUtf8("картофель"), 200);
    list << Dish(QObject::trUtf8("второе"),    QObject::trUtf8("котлета"), ingrs);

    ingrs.clear();
    ingrs << Ingr(QObject::trUtf8("свинина"), 100)
          << Ingr(QObject::trUtf8("рис"), 200);
    list << Dish(QObject::trUtf8("второе"),    QObject::trUtf8("плов"), ingrs);

    ingrs.clear();
    ingrs << Ingr(QObject::trUtf8("свинина"), 200)
          << Ingr(QObject::trUtf8("картофель"), 200);
    list << Dish(QObject::trUtf8("второе"),    QObject::trUtf8("свинина"), ingrs);

    ingrs.clear();
    ingrs << Ingr(QObject::trUtf8("говядина"), 200)
          << Ingr(QObject::trUtf8("картофель"), 200);
    list << Dish(QObject::trUtf8("второе"),    QObject::trUtf8("говядина"), ingrs);

}
