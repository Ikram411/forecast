#include "graphform.h"

GraphForm::GraphForm(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);

    plot.xAxis->setLabel(trUtf8("Время"));
    plot.yAxis->setLabel(trUtf8("Количество"));
    plot.setInteractions(0);
    plot.xAxis->setAutoTicks(true);
    plot.yAxis->setAutoTicks(true);
    plot.xAxis->setRange(1, 24);

    layout()->addWidget(&plot);
    ((QVBoxLayout*)layout())->setStretch(1, 1);
}
