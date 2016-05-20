#ifndef ORDERFORM_H
#define ORDERFORM_H

#include <QWidget>
#include "ui_orderform.h"

class OrderForm : public QWidget, public Ui::OrderForm
{
    Q_OBJECT
    
public:
    explicit OrderForm(QWidget *parent = 0);
};

#endif // ORDERFORM_H
