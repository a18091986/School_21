#include "../headers/mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->plotWindow->addGraph();
  resultDisplayed = false;
  switchField = true;

  // Create QColor objects using RGB values
  backgroundColor = QColor(0, 0, 0, 0);   // Black
  axisColor = QColor(255, 255, 255);      // White
  graphLineColor = QColor(241, 164, 60);  // Orange

  stylizePlotWindow();

  // Add a graph and set its line color to orange
  ui->plotWindow->setInteraction(QCP::iRangeDrag, true);
  ui->plotWindow->setInteraction(QCP::iRangeZoom, true);

  blinkTimer = new QTimer(this);
  blinkDurationTimer = new QTimer(this);
  blinkDurationTimer->setSingleShot(true);
  QPushButton *basic_buttons[] = {ui->pushButton_0,
                                  ui->pushButton_1,
                                  ui->pushButton_2,
                                  ui->pushButton_3,
                                  ui->pushButton_4,
                                  ui->pushButton_5,
                                  ui->pushButton_6,
                                  ui->pushButton_7,
                                  ui->pushButton_8,
                                  ui->pushButton_9,
                                  ui->pushButton_plus,
                                  ui->pushButton_minus,
                                  ui->pushButton_pow,
                                  ui->pushButton_left_bracket,
                                  ui->pushButton_right_bracket,
                                  ui->pushButton_mul,
                                  ui->pushButton_div,
                                  ui->pushButton_mod,
                                  ui->pushButton_dot,
                                  ui->pushButton_e,
                                  ui->pushButton_pi,
                                  ui->pushButton_x};

  QPushButton *trigonometry_buttons[] = {
      ui->pushButton_sin,  ui->pushButton_cos,  ui->pushButton_tan,
      ui->pushButton_asin, ui->pushButton_acos, ui->pushButton_atan,
      ui->pushButton_ln,   ui->pushButton_log,  ui->pushButton_sqrt};

  for (QPushButton *button : basic_buttons) {
    connect(button, SIGNAL(clicked()), this, SLOT(basicInputLineUI()));
  }
  for (QPushButton *button : trigonometry_buttons) {
    connect(button, SIGNAL(clicked()), this, SLOT(trigonometryInputLineUI()));
  }
  connect(ui->pushButton_AC, SIGNAL(clicked()), this, SLOT(clearInputLine()));
  connect(ui->pushButton_backspace, SIGNAL(clicked()), this,
          SLOT(backspaceInputLine()));
  connect(ui->pushButton_equal, SIGNAL(clicked()), this,
          SLOT(sendToCalculate()));
  connect(ui->pushButton_switch, SIGNAL(clicked()), this,
          SLOT(switchInputField()));
  connect(ui->pushButton_plot, SIGNAL(clicked()), this, SLOT(callPlotModule()));

  connect(blinkTimer, &QTimer::timeout, this,
          &MainWindow::toggleLabelVisibility);
  connect(blinkDurationTimer, &QTimer::timeout, this,
          &MainWindow::stopBlinking);
  blinkTimer->start(500);
  blinkDurationTimer->start(2000);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::sendToCalculate() {
  char calc_out[128] = {0};
  QByteArray inputBytes = ui->inputLine_calc->text().toUtf8();
  QByteArray inputBytesX = ui->inputLine_inputX->text().toUtf8();
  char *inputString = strdup(inputBytes.constData());
  char *inputX = strdup(inputBytesX.constData());
  calculator(inputString, inputX, calc_out);

  QString result = QString::fromUtf8(calc_out);
  ui->inputLine_calc->setText(result);
  adjustLabelFontSize(ui->inputLine_calc);
  switchField = false;
  clearInputLine();
  switchField = true;
  resultDisplayed = true;
  free(inputString);
}
