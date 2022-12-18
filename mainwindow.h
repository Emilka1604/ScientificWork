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
    void CreateTable(const QVector<double>& t, const QVector<double>& x1, const QVector<double>& x2,
                                 const QVector<std::size_t>& div_vec, const QVector<std::size_t>& doubling_vec);
    void Maketx1(const QVector<double>& t, const QVector<double>& x1);
    void Maketx2(const QVector<double>& t, const QVector<double>& x2);
    void Makex1x2(const QVector<double>& x1, const QVector<double>& x2);
    ~MainWindow();

private:
    Ui::MainWindow *ui;


};
#endif // MAINWINDOW_H
