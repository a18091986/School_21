#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QPrinter>
#include <QVector>
#include <QMainWindow>
#include "Controller/controller.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    double xBegin, xEnd, h, X;
    QVector<double> x,y;

    s21::Controller ex;
    int check_error = 0;
    char total_string[255] = {'\0'};
    QString str = NULL;
    double total = 0;
    const char* str_1 = NULL;

private slots:
    void calculate();
    void on_buttonAC_clicked();
    void on_buttonGraph_clicked();
};

#endif // MAINWINDOW_H
