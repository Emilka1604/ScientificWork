#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::CreateTable(const QVector<double>& t, const QVector<double>& x1, const QVector<double>& x2,
                             const QVector<std::size_t>& div_vec, const QVector<std::size_t>& doubling_vec) {
    ui->table->setColumnCount(5);
    ui->table->setRowCount(t.size());
//    ui->table->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
//    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Name"));
//    model->setHeaderData(2, Qt::Horizontal, QObject::tr("City"));
//    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Country"));
    for(std::size_t row = 0; row < t.size(); row++) {

        QString ti = QString::number(t[row], 'f', 8);
        QTableWidgetItem *item1 = new QTableWidgetItem(ti);
        ui->table->setItem(row, 0, item1);
        QString x1i = QString::number(x1[row], 'f', 8);
        QTableWidgetItem *item2 = new QTableWidgetItem(x1i);
        ui->table->setItem(row, 1, item2);
        QString x2i = QString::number(x2[row], 'f', 8);
        QTableWidgetItem *item3 = new QTableWidgetItem(x2i);
        ui->table->setItem(row, 2, item3);
        QString div_veci = QString::number(div_vec[row]);
        QTableWidgetItem *item4 = new QTableWidgetItem(div_veci);
        ui->table->setItem(row, 3, item4);
        QString doubling_veci = QString::number(doubling_vec[row]);
        QTableWidgetItem *item5 = new QTableWidgetItem(doubling_veci);
        ui->table->setItem(row, 4, item5);

    }
    ui->table->show();
}

void MainWindow::Maketx1(const QVector<double>& t, const QVector<double>& x1) {
    // create graph and assign data to it:
    ui->tx1->setInteraction(QCP::iRangeDrag, true);
    ui->tx1->setInteraction(QCP::iRangeZoom, true);
    ui->tx1->addGraph();
    ui->tx1->graph(0)->setData(t, x1);
    // give the axes some labels:
    ui->tx1->xAxis->setLabel("t");
    ui->tx1->yAxis->setLabel("x1");
    // set axes ranges, so we see all data:
    ui->tx1->xAxis->setRange(-20, 20);
    ui->tx1->yAxis->setRange(-20, 20);
    ui->tx1->replot();
}

void MainWindow::Maketx2(const QVector<double>& t, const QVector<double>& x2) {
    // create graph and assign data to it:
    ui->tx2->setInteraction(QCP::iRangeDrag, true);
    ui->tx2->setInteraction(QCP::iRangeZoom, true);
    ui->tx2->addGraph();
    ui->tx2->graph(0)->setData(t, x2);
    // give the axes some labels:
    ui->tx2->xAxis->setLabel("t");
    ui->tx2->yAxis->setLabel("x2");
    // set axes ranges, so we see all data:
    ui->tx2->xAxis->setRange(-20, 20);
    ui->tx2->yAxis->setRange(-20, 20);
    ui->tx2->replot();
}

void MainWindow::Makex1x2(const QVector<double>& x1, const QVector<double>& x2) {
    // create graph and assign data to it:
    ui->x1x2->setInteraction(QCP::iRangeDrag, true);
    ui->x1x2->setInteraction(QCP::iRangeZoom, true);
    QCPCurve *curve = new QCPCurve(ui->x1x2->xAxis, ui->x1x2->yAxis);
    QVector<QCPCurveData> curveData(x1.size());
    for(std::size_t i = 0; i < x1.size(); ++i) {
        curveData[i] = QCPCurveData(i, x1[i], x2[i]);
    }
    curve->data()->set(curveData, true);
    ui->x1x2->addGraph();
    //ui->x1x2->graph(0)->setData(x1, x2);
    // give the axes some labels:
    ui->x1x2->xAxis->setLabel("x1");
    ui->x1x2->yAxis->setLabel("x2");
    // set axes ranges, so we see all data:
    ui->x1x2->xAxis->setRange(-20, 20);
    ui->x1x2->yAxis->setRange(-20, 20);
    ui->x1x2->replot();
}
