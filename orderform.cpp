#include "orderform.h"

OrderForm::OrderForm(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);

    table->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
}
