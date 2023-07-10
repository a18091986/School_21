#include <QApplication>
#include <QFontMetrics>
#include <QMenuBar>

#include "front/headers/creditcalc.h"
#include "front/headers/mainwindow.h"

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);
  QMenuBar* menuBar = new QMenuBar();
  QMenu* modeMenu = menuBar->addMenu("View mode");
  QAction* basicModeAction = modeMenu->addAction("Basic");
  QAction* creditModeAction = modeMenu->addAction("Credit");

  QWidget* calculatorUI = new MainWindow();
  QObject::connect(basicModeAction, &QAction::triggered, [&]() {
    if (calculatorUI) {
      delete calculatorUI;
    }
    calculatorUI = new MainWindow();
    calculatorUI->show();
  });
  QObject::connect(creditModeAction, &QAction::triggered, [&]() {
    if (calculatorUI) {
      delete calculatorUI;
    }
    calculatorUI = new CreditCalc();
    calculatorUI->show();
  });
  calculatorUI->show();
  int result = a.exec();
  if (calculatorUI) {
    delete calculatorUI;
  }
  delete menuBar;

  return result;
}
