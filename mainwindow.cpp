#include "mainwindow.h"
#include <QDir>
#include <QFileDialog>
#include <QPair>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setupUi(this);

    tabWidget->addTab(&orderForm, trUtf8("Заказы"));
    tabWidget->addTab(&graphForm, trUtf8("График"));
    tabWidget->addTab(&ingrForm,  trUtf8("Продукты"));

    connect(orderForm.pbLoad, SIGNAL(clicked()), SLOT(slotLoadFile()));
    connect(orderForm.pbImit, SIGNAL(clicked()), SLOT(slotImit()));
    connect(graphForm.pbPlot, SIGNAL(clicked()), SLOT(slotPlot()));

    orderForm.table->horizontalHeader()->setResizeMode(QHeaderView::Stretch);

    DishList::getInstance()->init();

}

void MainWindow::slotLoadFile() {
    QString name = QFileDialog::getOpenFileName(this,
                                                trUtf8("Окрыть"),
                                                QDir::currentPath(),
                                                trUtf8("Листы (*.csv)"));

    QFile file(name);
    if(!file.open(QIODevice::ReadOnly)) {
        qDebug() << "cannot open" << name;
        return;
    }

    Cuisine::getInstance()->clear();

    QTextStream stream(&file);
    while(!stream.atEnd())
        Cuisine::getInstance()->addOrder(stream.readLine());

    file.close();

    orderForm.table->setModel(Cuisine::getInstance());

    graphForm.cbDishes->clear();
    graphForm.cbDishes->addItems(DishList::getInstance()->getTypes());

    orderForm.sbCount->setValue(Cuisine::getInstance()->orderList.count());
    graphForm.dateFrom->setDate(Cuisine::getInstance()->dateFrom);
    graphForm.dateTo->setDate(Cuisine::getInstance()->dateTo);
    ingrForm.dateFrom->setDate(Cuisine::getInstance()->dateFrom);
    ingrForm.dateTo->setDate(Cuisine::getInstance()->dateTo);
}

void MainWindow::slotImit() {
    for(int i=0; i<1000; i++) {
        int j = qrand() % DishList::getInstance()->list.count();
        QString str = QString("%1,%2,%3,%4")
                .arg(QDate(2016, 3, 1 + (qrand() % 5)).toString(dateFormat))
                .arg(QTime(12 + (9 - (qrand() % 4)*(qrand() % 4)) , qrand() % 60, 0).toString(timeFormat))
                .arg(DishList::getInstance()->list.at(j).name)
                .arg(1 + (qrand()%5));
        Cuisine::getInstance()->addOrder(str);
    }

    orderForm.table->setModel(Cuisine::getInstance());
    graphForm.cbDishes->clear();
    graphForm.cbDishes->addItems(DishList::getInstance()->getTypes());

    orderForm.sbCount->setValue(Cuisine::getInstance()->orderList.count());
    graphForm.dateFrom->setDate(Cuisine::getInstance()->dateFrom);
    graphForm.dateTo->setDate(Cuisine::getInstance()->dateTo);
    ingrForm.dateFrom->setDate(Cuisine::getInstance()->dateFrom);
    ingrForm.dateTo->setDate(Cuisine::getInstance()->dateTo);
}


void MainWindow::slotPlot() {
    int num[24];
    for(int i=0; i<24; i++) num[i] = 0;

    foreach(Order o, Cuisine::getInstance()->orderList) {
        QDate date = o.date;

        if((graphForm.cbDishes->currentText() == DishList::getInstance()->getType(o.dish)) &&
                (graphForm.dateFrom->date() <= date) &&
                (graphForm.dateTo->date() >= date))
            num[o.time.hour()] += o.count;
    }

    QVector<double> valx, valy;

    int max = num[0];
    for(int i=0; i<24; i++) {
        valx << i+1;
        valy << num[i];
        max = max < num[i] ? num[i] : max;
    }


    if(graphForm.plot.plottableCount() > 0)
        graphForm.plot.removeGraph(0);
    QPen pen;
    pen.setColor(Qt::red);
    graphForm.plot.addGraph();
    graphForm.plot.graph(0)->setData(valx, valy);
    graphForm.plot.graph(0)->setVisible(true);
    graphForm.plot.graph(0)->setPen(pen);
    graphForm.plot.yAxis->setRange(0, max + 1);

    graphForm.plot.replot(QCustomPlot::rpImmediate);
}
