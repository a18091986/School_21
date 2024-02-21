#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->buttonZero, SIGNAL(clicked()), this, SLOT(calculate()));
    connect(ui->buttonOne, SIGNAL(clicked()), this, SLOT(calculate()));
    connect(ui->buttonTwo, SIGNAL(clicked()), this, SLOT(calculate()));
    connect(ui->buttonThree, SIGNAL(clicked()), this, SLOT(calculate()));
    connect(ui->buttonFour, SIGNAL(clicked()), this, SLOT(calculate()));
    connect(ui->buttonFive, SIGNAL(clicked()), this, SLOT(calculate()));
    connect(ui->buttonSix, SIGNAL(clicked()), this, SLOT(calculate()));
    connect(ui->buttonSeven, SIGNAL(clicked()), this, SLOT(calculate()));
    connect(ui->buttonEight, SIGNAL(clicked()), this, SLOT(calculate()));
    connect(ui->buttonNine, SIGNAL(clicked()), this, SLOT(calculate()));
    connect(ui->buttonSqrt, SIGNAL(clicked()), this, SLOT(calculate()));
    connect(ui->buttonln, SIGNAL(clicked()), this, SLOT(calculate()));
    connect(ui->buttonmod, SIGNAL(clicked()), this, SLOT(calculate()));
    connect(ui->buttonSin, SIGNAL(clicked()), this, SLOT(calculate()));
    connect(ui->buttonCos, SIGNAL(clicked()), this, SLOT(calculate()));
    connect(ui->buttonTan, SIGNAL(clicked()), this, SLOT(calculate()));
    connect(ui->buttonAcos, SIGNAL(clicked()), this, SLOT(calculate()));
    connect(ui->buttonAsin, SIGNAL(clicked()), this, SLOT(calculate()));
    connect(ui->buttonAtan, SIGNAL(clicked()), this, SLOT(calculate()));
    connect(ui->buttonPow, SIGNAL(clicked()), this, SLOT(calculate()));
    connect(ui->buttonPlus, SIGNAL(clicked()), this, SLOT(calculate()));
    connect(ui->buttonMinus, SIGNAL(clicked()), this, SLOT(calculate()));
    connect(ui->buttonDot, SIGNAL(clicked()), this, SLOT(calculate()));
    connect(ui->buttonBracket1, SIGNAL(clicked()), this, SLOT(calculate()));
    connect(ui->buttonBracket2, SIGNAL(clicked()), this, SLOT(calculate()));
    connect(ui->buttonStar, SIGNAL(clicked()), this, SLOT(calculate()));
    connect(ui->buttonSlash, SIGNAL(clicked()), this, SLOT(calculate()));
    connect(ui->buttonX, SIGNAL(clicked()), this, SLOT(calculate()));
    connect(ui->buttonEqual, SIGNAL(clicked()), this, SLOT(calculate()));
    connect(ui->buttonLog, SIGNAL(clicked()), this, SLOT(calculate()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::calculate()
{
    double x = 0;

    QPushButton *button = (QPushButton*) sender();

    if(button->text() != "AC" && button->text() != "=")
    {
        ui->MainLine->setText(ui->MainLine->text() + button->text());
    }
    else if(button->text() == "=")
    {
        str = ui->MainLine->text();
        std::string s = str.toStdString();
        str_1 = s.c_str();
        x = ui->lineEdit->text().toDouble();

        if(!ex.Validation(str_1))
        {
            total = ex.Calculate(str_1, x);
            sprintf(total_string, "%.7lf", total);
            ui->MainLine->setText(total_string);
        }
        else
        {
            ui->MainLine->setText("input incorrect");
            check_error = 1;
        };
    }
}

void MainWindow::on_buttonAC_clicked()
{
    ui->MainLine->setText("");

    x.clear();
    y.clear();
    ui->widget->clearGraphs();
    ui->widget->clearItems();

    ui->widget->addGraph();
    ui->widget->graph(0)->addData(x,y);
    ui->widget->replot();

    check_error = 0;
}


void MainWindow::on_buttonGraph_clicked()
{
    QPushButton *button = (QPushButton*) sender();

    if(check_error)
    {
        ui->MainLine->setText("");
        check_error = 0;
    }

    if(button->text() != "Graph")
    {
        ui->MainLine->setText(ui->MainLine->text() + button->text());
    }
    else if (button->text() == "Graph"){

        x.clear();
        y.clear();
        ui->widget->clearGraphs();
        ui->widget->clearItems();

        ui->widget->addGraph();
        ui->widget->graph(0)->addData(x,y);
        ui->widget->replot();

        str = ui->MainLine->text();
        str_1 = str.toStdString().c_str();

        if(!ex.Validation(str_1))
        {
            h = 0.1;

            xBegin = -100; // у 1мил долгая комп.
            xEnd = 100;

            X = ui->MainLine->text().toDouble();

            ui->widget->xAxis->setRange(ui->lineXmin->text().toDouble(),ui->lineXmax->text().toDouble());    // видимая область виджета
            ui->widget->yAxis->setRange(ui->lineYmin->text().toDouble(),ui->lineYmax->text().toDouble());

            for (X = xBegin; X <= xEnd;  X += h) {
                x.push_back(X);
                total = ex.Calculate(str_1, X);
                y.push_back(total);
            }

            ui->widget->addGraph();
            ui->widget->graph(0)->addData(x,y);
            ui->widget->replot();
        }
        else
        {
            ui->MainLine->setText("input incorrect");
            check_error = 1;
        };

    }
}
