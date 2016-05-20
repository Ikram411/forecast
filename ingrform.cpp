#include <QProcess>
#include <QFile>
#include <QTextStream>
#include "ingrform.h"

IngrForm::IngrForm(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);

    connect(dateFrom, SIGNAL(dateChanged(QDate)), SLOT(slotIngrUpdateModel()));
    connect(dateTo, SIGNAL(dateChanged(QDate)), SLOT(slotIngrUpdateModel()));
    connect(pbForecast, SIGNAL(clicked()), SLOT(slotForecast()));
}

void IngrForm::slotIngrUpdateModel() {
    tableView->reset();
    ingrModel.ingrList.clear();

    foreach(Order o, Cuisine::getInstance()->orderList) {
        if(o.date > dateTo->date() || o.date < dateFrom->date())
            continue;

        Dish dish = DishList::getInstance()->getDish(o.dish);
        foreach(Ingr i1, dish.ingredients) {
            bool add = 1;

            for(int i=0; i<ingrModel.ingrList.size(); i++) {
                if(i1.name == ingrModel.ingrList[i].name) {
                    add = 0;
                    ingrModel.ingrList[i].count += i1.count*o.count;
                }
            }
            if(add) {
                ingrModel.ingrList << i1;
                ingrModel.ingrList.last().count *= o.count;
            }
        }
    }
    tableView->setModel(&ingrModel);
}

void IngrForm::slotForecast() {
    forecastView->reset();
    forecastModel.ingrList.clear();

    foreach(Ingr i, ingrModel.ingrList) {
        QFile fin(trUtf8("data/in.csv"));
        fin.open(QIODevice::WriteOnly);
        QTextStream strin(&fin);
        strin << sbP->value();
        strin << sbQ->value();
        strin << sbD->value();
        strin << 7;
        fin.close();

        QProcess proc;
        proc.start(trUtf8("deploy.exe"));
        proc.waitForFinished();

        QFile fout(trUtf8("data/out.csv"));
        fin.open(QIODevice::ReadOnly);
        QTextStream strout(&fout);
        double v;
        strout >> v;
        fin.close();

        forecastModel.ingrList << i;
        forecastModel.ingrList.last().count = i.count/10;
    }

    forecastView->setModel(&forecastModel);
}

int IngrModel::rowCount(const QModelIndex & ) const {
    return ingrList.size();
}

int IngrModel::columnCount(const QModelIndex &) const {
    return 2;
}

QVariant IngrModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if(role == Qt::DisplayRole) {
        if(orientation == Qt::Horizontal) {
            switch(section) {
            case 0: return trUtf8("Продукт");
            case 1: return trUtf8("Количество");
            default: return QVariant();
            }
        } else {
            return section+1;
        }

    }
    return QVariant();
}

QVariant IngrModel::data ( const QModelIndex & index, int role ) const {
    if(role == Qt::DisplayRole) {
        switch(index.column()) {
        case 0: return ingrList.at(index.row()).name;
        case 1: return ingrList.at(index.row()).count;
        default: return QVariant();
        }
    }
    return QVariant();
}

