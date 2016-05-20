#ifndef GRAPHFORM_H
#define GRAPHFORM_H

#include <QWidget>
#include "ui_graphform.h"
#include "qcustomplot/qcustomplot.h"

class GraphForm : public QWidget, public Ui::GraphForm
{
    Q_OBJECT
    
public:
    explicit GraphForm(QWidget *parent = 0);
    
    QCustomPlot plot;

};

#endif // GRAPHFORM_H
