#ifndef INGRFORM_H
#define INGRFORM_H

#include <QWidget>
#include "ui_ingrform.h"
#include "cuisine.h"

class IngrModel : public QAbstractTableModel
{
public:
    int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    QList<Ingr> ingrList;
};

class IngrForm : public QWidget, public Ui::IngrForm
{
    Q_OBJECT
    
public:
    explicit IngrForm(QWidget *parent = 0);
    
    IngrModel ingrModel;
    IngrModel forecastModel;

public slots:
    void slotIngrUpdateModel();
    void slotForecast();

};

#endif // INGRFORM_H
