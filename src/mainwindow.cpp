#include "mainwindow.h"
#include "../ui_mainwindow.h"

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

void MainWindow::setMaxLocalErr(double maxLocalError)
{
    ui->textEdit_4->setText(QString::number(maxLocalError, 'f', 12));
}

void MainWindow::CreateTable(const QVector<double>& h, const QVector<double>& t, const QVector<double>& x1, const QVector<double>& x2,
                             const QVector<std::size_t>& div_vec, const QVector<std::size_t>& doubling_vec) {
    ui->table->setColumnCount(6);
    ui->table->setRowCount(t.size());
    ui->table->setHorizontalHeaderLabels(QStringList() << "h" << "t" << "x1" << "x2" << "div" << "double");
    for(std::size_t row = 0; row < t.size(); row++) {
        QString th = QString::number(h[row], 'f', 8);
        QTableWidgetItem *item0 = new QTableWidgetItem(th);
        ui->table->setItem(row, 0, item0);
        QString ti = QString::number(t[row], 'f', 8);
        QTableWidgetItem *item1 = new QTableWidgetItem(ti);
        ui->table->setItem(row, 1, item1);
        QString x1i = QString::number(x1[row], 'f', 8);
        QTableWidgetItem *item2 = new QTableWidgetItem(x1i);
        ui->table->setItem(row, 2, item2);
        QString x2i = QString::number(x2[row], 'f', 8);
        QTableWidgetItem *item3 = new QTableWidgetItem(x2i);
        ui->table->setItem(row, 3, item3);
        QString div_veci = QString::number(div_vec[row]);
        QTableWidgetItem *item4 = new QTableWidgetItem(div_veci);
        ui->table->setItem(row, 4, item4);
        QString doubling_veci = QString::number(doubling_vec[row]);
        QTableWidgetItem *item5 = new QTableWidgetItem(doubling_veci);
        ui->table->setItem(row, 5, item5);
    }
    ui->table->show();
}

void MainWindow::CreateTable(const QVector<double>& h, const QVector<double>& t, const QVector<double>& x1, const QVector<double>& x2,
                             const QVector<double>& x3, const QVector<std::size_t>& div_vec, const QVector<std::size_t>& doubling_vec) {
    ui->table->setColumnCount(7);
    ui->table->setRowCount(t.size());
    ui->table->setHorizontalHeaderLabels(QStringList() << "h" << "t" << "x1" << "x2" << "x3" << "div" << "double");
    for(std::size_t row = 0; row < t.size(); row++) {
        QString th = QString::number(h[row], 'f', 8);
        QTableWidgetItem *item0 = new QTableWidgetItem(th);
        ui->table->setItem(row, 0, item0);
        QString ti = QString::number(t[row], 'f', 8);
        QTableWidgetItem *item1 = new QTableWidgetItem(ti);
        ui->table->setItem(row, 1, item1);
        QString x1i = QString::number(x1[row], 'f', 8);
        QTableWidgetItem *item2 = new QTableWidgetItem(x1i);
        ui->table->setItem(row, 2, item2);
        QString x2i = QString::number(x2[row], 'f', 8);
        QTableWidgetItem *item3 = new QTableWidgetItem(x2i);
        ui->table->setItem(row, 3, item3);
        QString x3i = QString::number(x3[row], 'f', 8);
        QTableWidgetItem *item4 = new QTableWidgetItem(x3i);
        ui->table->setItem(row, 4, item4);
        QString div_veci = QString::number(div_vec[row]);
        QTableWidgetItem *item5 = new QTableWidgetItem(div_veci);
        ui->table->setItem(row, 5, item5);
        QString doubling_veci = QString::number(doubling_vec[row]);
        QTableWidgetItem *item6 = new QTableWidgetItem(doubling_veci);
        ui->table->setItem(row, 6, item6);
    }
    ui->table->show();
}

void MainWindow::CreateTable(const QVector<double>& h, const QVector<double>& t, const QVector<double>& x1, const QVector<double>& x2,
                             const QVector<double>& x3, const QVector<std::size_t>& div_vec, const QVector<std::size_t>& doubling_vec, 
                                                    const QVector<double>& localError) {
    // auto div_vec = div_vec_.empty() ? std::vector(t.size(), 0) : QVector::fromStdVector(div_vec_);
    // auto doubling_vec = doubling_vec_.empty() ? std::vector(t.size(), 0) : QVector::fromStdVector(doubling_vec_);
    // auto localError = QVector::fromStdVector(localError_);
    ui->table->setColumnCount(8);
    ui->table->setRowCount(t.size());
    ui->table->setHorizontalHeaderLabels(QStringList() << "h" << "t" << "x1" << "x2" << "x3" << "div" << "double" << "local_error");
    for(std::size_t row = 0; row < t.size(); row++) {
        QString th = QString::number(h[row], 'f', 8);
        QTableWidgetItem *item0 = new QTableWidgetItem(th);
        ui->table->setItem(row, 0, item0);
        QString ti = QString::number(t[row], 'f', 8);
        QTableWidgetItem *item1 = new QTableWidgetItem(ti);
        ui->table->setItem(row, 1, item1);
        QString x1i = QString::number(x1[row], 'f', 8);
        QTableWidgetItem *item2 = new QTableWidgetItem(x1i);
        ui->table->setItem(row, 2, item2);
        QString x2i = QString::number(x2[row], 'f', 8);
        QTableWidgetItem *item3 = new QTableWidgetItem(x2i);
        ui->table->setItem(row, 3, item3);
        QString x3i = QString::number(x3[row], 'f', 8);
        QTableWidgetItem *item4 = new QTableWidgetItem(x3i);
        ui->table->setItem(row, 4, item4);
        QString div_veci = QString::number(div_vec[row]);
        QTableWidgetItem *item5 = new QTableWidgetItem(div_veci);
        ui->table->setItem(row, 5, item5);
        QString doubling_veci = QString::number(doubling_vec[row]);
        QTableWidgetItem *item6 = new QTableWidgetItem(doubling_veci);
        ui->table->setItem(row, 6, item6);
        QString localErrori = QString::number(localError[row]);
        QTableWidgetItem *item7 = new QTableWidgetItem(localErrori);
        ui->table->setItem(row, 7, item7);
    }
    ui->table->show();
}

void MainWindow::CreateTable(const QVector<double>& h, const QVector<double>& t, const QVector<double>& x1, const QVector<double>& x2) {
    ui->table->setColumnCount(4);
    ui->table->setRowCount(t.size());
    ui->table->setHorizontalHeaderLabels(QStringList() << "h" << "t" << "x1" << "x2");
    for(std::size_t row = 0; row < t.size(); row++) {
        QString th = QString::number(h[row], 'f', 8);
        QTableWidgetItem *item0 = new QTableWidgetItem(th);
        ui->table->setItem(row, 0, item0);
        QString ti = QString::number(t[row], 'f', 8);
        QTableWidgetItem *item1 = new QTableWidgetItem(ti);
        ui->table->setItem(row, 1, item1);
        QString x1i = QString::number(x1[row], 'f', 8);
        QTableWidgetItem *item2 = new QTableWidgetItem(x1i);
        ui->table->setItem(row, 2, item2);
        QString x2i = QString::number(x2[row], 'f', 8);
        QTableWidgetItem *item3 = new QTableWidgetItem(x2i);
        ui->table->setItem(row, 3, item3);
    }
    ui->table->show();
}

void MainWindow::CreateTable(const QVector<double>& h, const QVector<double>& t, const QVector<double>& x1, const QVector<double>& x2, const QVector<double>& x3) {
    ui->table->setColumnCount(5);
    ui->table->setRowCount(t.size());
    ui->table->setHorizontalHeaderLabels(QStringList() << "h" << "t" << "x1" << "x2" << "x3");
    for(std::size_t row = 0; row < t.size(); row++) {
        QString th = QString::number(h[row], 'f', 8);
        QTableWidgetItem *item0 = new QTableWidgetItem(th);
        ui->table->setItem(row, 0, item0);
        QString ti = QString::number(t[row], 'f', 8);
        QTableWidgetItem *item1 = new QTableWidgetItem(ti);
        ui->table->setItem(row, 1, item1);
        QString x1i = QString::number(x1[row], 'f', 8);
        QTableWidgetItem *item2 = new QTableWidgetItem(x1i);
        ui->table->setItem(row, 2, item2);
        QString x2i = QString::number(x2[row], 'f', 8);
        QTableWidgetItem *item3 = new QTableWidgetItem(x2i);
        ui->table->setItem(row, 3, item3);
        QString x3i = QString::number(x3[row], 'f', 8);
        QTableWidgetItem *item4 = new QTableWidgetItem(x3i);
        ui->table->setItem(row, 4, item4);
    }
    ui->table->show();
}


void MainWindow::CreateTable(const QVector<double>& h, const QVector<double>& t, const QVector<double>& x1,
                             const QVector<std::size_t>& div_vec, const QVector<std::size_t>& doubling_vec) {
    ui->table->setColumnCount(5);
    ui->table->setRowCount(t.size());
    ui->table->setHorizontalHeaderLabels(QStringList() << "h" << "t" << "x1" << "div" << "double");
    for(std::size_t row = 0; row < t.size(); row++) {
        QString th = QString::number(h[row], 'f', 8);
        QTableWidgetItem *item0 = new QTableWidgetItem(th);
        ui->table->setItem(row, 0, item0);
        QString ti = QString::number(t[row], 'f', 8);
        QTableWidgetItem *item1 = new QTableWidgetItem(ti);
        ui->table->setItem(row, 1, item1);
        QString x1i = QString::number(x1[row], 'f', 16);
        QTableWidgetItem *item2 = new QTableWidgetItem(x1i);
        ui->table->setItem(row, 2, item2);
        QString div_veci = QString::number(div_vec[row]);
        QTableWidgetItem *item3 = new QTableWidgetItem(div_veci);
        ui->table->setItem(row, 3, item3);
        QString doubling_veci = QString::number(doubling_vec[row]);
        QTableWidgetItem *item4 = new QTableWidgetItem(doubling_veci);
        ui->table->setItem(row, 4, item4);
    }
    ui->table->show();
}

void MainWindow::CreateTable(const QVector<double>& h, const QVector<double>& t, const QVector<double>& x1) {
    ui->table->setColumnCount(3);
    ui->table->setRowCount(t.size());
    ui->table->setHorizontalHeaderLabels(QStringList() << "h" << "t" << "x1");
    for(std::size_t row = 0; row < t.size(); row++) {
        QString th = QString::number(h[row], 'f', 8);
        QTableWidgetItem *item0 = new QTableWidgetItem(th);
        ui->table->setItem(row, 0, item0);
        QString ti = QString::number(t[row], 'f', 8);
        QTableWidgetItem *item1 = new QTableWidgetItem(ti);
        ui->table->setItem(row, 1, item1);
        QString x1i = QString::number(x1[row], 'f', 16);
        QTableWidgetItem *item2 = new QTableWidgetItem(x1i);
        ui->table->setItem(row, 2, item2);
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

void MainWindow::Maketx3(const QVector<double>& t, const QVector<double>& x3) {
    // create graph and assign data to it:
    ui->x1x2->setInteraction(QCP::iRangeDrag, true);
    ui->x1x2->setInteraction(QCP::iRangeZoom, true);
    ui->x1x2->addGraph();
    ui->x1x2->graph(0)->setData(t, x3);
    // give the axes some labels:
    ui->x1x2->xAxis->setLabel("t");
    ui->x1x2->yAxis->setLabel("x3");
    // set axes ranges, so we see all data:
    ui->x1x2->xAxis->setRange(-20, 20);
    ui->x1x2->yAxis->setRange(-20, 20);
    ui->x1x2->replot();
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

void MainWindow::MakeStepPlot(const QVector<double> &t, const QVector<double> &h)
{
    // create graph and assign data to it:
    ui->stepPlot->setInteraction(QCP::iRangeDrag, true);
    ui->stepPlot->setInteraction(QCP::iRangeZoom, true);
    ui->stepPlot->addGraph();
    ui->stepPlot->graph(0)->setData(t, h);
    // localErrPlotthe axes some labels:
    ui->stepPlot->xAxis->setLabel("t");
    ui->stepPlot->yAxis->setLabel("h");
    // set localErrPlotxes ranges, so we see all data:
    ui->stepPlot->xAxis->setRange(-20, 20);
    ui->stepPlot->yAxis->setRange(-20, 20);
    ui->stepPlot->replot();
}

void MainWindow::MakeLocalErrPlot(const QVector<double>& t, const QVector<double>& localErr)
{ 
    // create graph and assign data to it:
    ui->localErrPlot->setInteraction(QCP::iRangeDrag, true);
    ui->localErrPlot->setInteraction(QCP::iRangeZoom, true);
    ui->localErrPlot->addGraph();
    ui->localErrPlot->graph(0)->setData(t, localErr);
    // localErrPlotthe axes some labels:
    ui->localErrPlot->xAxis->setLabel("t");
    ui->localErrPlot->yAxis->setLabel("localErr");
    // set localErrPlotxes ranges, so we see all data:
    ui->localErrPlot->xAxis->setRange(-20, 20);
    ui->localErrPlot->yAxis->setRange(-20, 20);
    ui->localErrPlot->replot();
}



void MainWindow::setDoubling(int doublingCount) {
    ui->textEdit->setText(QString::number(doublingCount));
}

void MainWindow::setDivide(int divideCount) {
    ui->textEdit_2->setText(QString::number(divideCount));
}

void MainWindow::setRightPartCalc(int rightPartCalc) {
    ui->textEdit_3->setText(QString::number(rightPartCalc));
}
