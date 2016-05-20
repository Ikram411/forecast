#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include "orderform.h"
#include "graphform.h"
#include "ingrform.h"
#include "cuisine.h"

class MainWindow : public QMainWindow, public Ui::MainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    
private:

    OrderForm orderForm;
    GraphForm graphForm;
    IngrForm ingrForm;

public slots:
    void slotLoadFile();
    void slotImit();
    void slotPlot();

};

#endif // MAINWINDOW_H
