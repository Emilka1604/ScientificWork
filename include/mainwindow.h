#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void CreateTable(const QVector<double>& h, const QVector<double>& t, const QVector<double>& x1, const QVector<double>& x2,
                                 const QVector<std::size_t>& div_vec, const QVector<std::size_t>& doubling_vec);
    void CreateTable(const QVector<double>& h, const QVector<double>& t, const QVector<double>& x1, const QVector<double>& x2);
    void CreateTable(const QVector<double>& h, const QVector<double>& t, const QVector<double>& x1, const QVector<double>& x2, const QVector<double>& x3);
    void CreateTable(const QVector<double>& h, const QVector<double>& t, const QVector<double>& x1,
                                 const QVector<std::size_t>& div_vec, const QVector<std::size_t>& doubling_vec);
    void CreateTable(const QVector<double>& h, const QVector<double>& t, const QVector<double>& x1);
    void Maketx3(const QVector<double>& t, const QVector<double>& x3);
    void Maketx1(const QVector<double>& t, const QVector<double>& x1);
    void Maketx2(const QVector<double>& t, const QVector<double>& x2);
    void Makex1x2(const QVector<double>& x1, const QVector<double>& x2);
    void MakeStepPlot(const QVector<double>& t, const QVector<double>& h);
    void MakeLocalErrPlot(const QVector<double>& t, const QVector<double>& localErr);
    void CreateTable(const QVector<double>& h, const QVector<double>& t, const QVector<double>& x1, const QVector<double>& x2,
                                 const QVector<double>& x3, const QVector<std::size_t>& div_vec, const QVector<std::size_t>& doubling_vec);

    void CreateTable(const QVector<double>& h, const QVector<double>& t, const QVector<double>& x1, const QVector<double>& x2,
                             const QVector<double>& x3, const QVector<std::size_t>& div_vec, const QVector<std::size_t>& doubling_vec, 
                                                    const QVector<double>& localError);
    void setDoubling(int doublingCount);
    void setDivide(int divideCount);
    void setRightPartCalc(int rightPartCalc);
    void setMaxLocalErr(double maxLocalError);
    ~MainWindow();

private:
    Ui::MainWindow *ui;


};
#endif // MAINWINDOW_H
