#include "../headers/mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::basicInputLineUI() {
  QLabel* curLabel = ui->inputLine_calc;
  if (!switchField) {
    curLabel = ui->inputLine_inputX;
  }
  QPushButton* button = (QPushButton*)sender();
  QString buttonText = button->text();

  if (buttonText == QString::fromUtf8("÷")) {
    buttonText = "/";
  } else if (buttonText == QString::fromUtf8("×")) {
    buttonText = "*";
  } else if (buttonText == QString::fromUtf8("π")) {
    buttonText = "Pi";
  } else if (buttonText == "X") {
    buttonText = "x";
  }

  if (resultDisplayed && switchField) {
    if (simpleOperationCheck(buttonText) && buttonText != ".") {
      clearInputLine();
    } else {
      resultDisplayed = false;
    }
  }

  QString inputString = curLabel->text();

  if (inputString == "0" &&
      (simpleOperationCheck(buttonText) || buttonText == "-") &&
      buttonText != ".") {
    inputString = buttonText;
  } else {
    inputString.append(buttonText);
  }
  if (switchField || inputLimitationX(buttonText)) {
    curLabel->setText(inputString);
    adjustLabelFontSize(curLabel);
  }
}

void MainWindow::trigonometryInputLineUI() {
  QPushButton* button = (QPushButton*)sender();
  QString buttonText = button->text();
  if (resultDisplayed) {
    clearInputLine();
  }
  QString inputString = ui->inputLine_calc->text();
  if (inputString == "0") {
    inputString = buttonText;
  } else {
    inputString.append(buttonText);
  }
  inputString.append("(");

  switchField = true;
  ui->inputLine_calc->setText(inputString);
  adjustLabelFontSize(ui->inputLine_calc);
}

void MainWindow::clearInputLine() {
  QLabel* curLabel = ui->inputLine_calc;
  if (!switchField) {
    curLabel = ui->inputLine_inputX;
  }
  QFont font = curLabel->font();
  if (resultDisplayed && switchField) {
    resultDisplayed = false;
  }
  font.setPointSize(40);
  curLabel->setFont(font);
  curLabel->setText("0");
}

void MainWindow::switchInputField() {
  switchField = !switchField;
  if (switchField) {
    ui->pushButton_switch->setText("Input X");
  } else {
    ui->pushButton_switch->setText("Input Main");
  }

  toggleLabelVisibility();
  blinkTimer->start(500);
  blinkDurationTimer->start(2000);
}

void MainWindow::backspaceInputLine() {
  QLabel* curLabel = ui->inputLine_calc;
  if (!switchField) {
    curLabel = ui->inputLine_inputX;
  }
  QString inputString = curLabel->text();
  if (resultDisplayed) {
    resultDisplayed = false;
  }
  if (inputString.length() > 0) {
    inputString.chop(1);
    if (inputString.length() == 0) {
      inputString = "0";
    }
    curLabel->setText(inputString);

    // Check if the new text width is smaller than the label width
    QFontMetrics fm(curLabel->font());
    QRect textRect = fm.boundingRect(inputString);
    int labelWidth = curLabel->width();
    if (textRect.width() < labelWidth - 50) {
      // Decrease the font size to fit the text
      QFont font = curLabel->font();
      int fontSize = font.pointSize();
      while (textRect.width() < labelWidth - 50 && fontSize < 40) {
        fontSize++;
        font.setPointSize(fontSize);
        fm = QFontMetrics(font);
        textRect = fm.boundingRect(inputString);
      }
      curLabel->setFont(font);
    }
  }
}

void MainWindow::adjustLabelFontSize(QLabel* label) {
  QFont font = label->font();
  QFontMetrics fontMetrics(font);

  int textWidth = fontMetrics.horizontalAdvance(label->text());
  int labelWidth = label->width();

  if (textWidth > labelWidth - 20) {
    int fontSize = font.pointSize();
    while (textWidth > labelWidth - 20 && fontSize > 15) {
      fontSize--;
      font.setPointSize(fontSize);
      fontMetrics = QFontMetrics(font);
      textWidth = fontMetrics.horizontalAdvance(label->text());
    }
    label->setFont(font);
  }
}

bool MainWindow::simpleOperationCheck(QString button) {
  bool res = true;
  if (button == "^" || button == "/" || button == "*" || button == "-" ||
      button == "+" || button == "mod") {
    res = false;
  }
  return res;
}

bool MainWindow::inputLimitationX(QString button) {
  bool res = simpleOperationCheck(button);
  if (button == "x" || button == "(" || button == ")") {
    res = false;
  }
  return res;
}

void MainWindow::toggleLabelVisibility() {
  if (switchField) {
    ui->inputLine_calc->setVisible(!ui->inputLine_calc->isVisible());
    if (!ui->inputLine_calc->isVisible()) {
      ui->inputLine_inputX->setVisible(true);
    }
  } else {
    ui->inputLine_inputX->setVisible(!ui->inputLine_inputX->isVisible());
    if (!ui->inputLine_inputX->isVisible()) {
      ui->inputLine_calc->setVisible(true);
    }
  }
}

void MainWindow::stopBlinking() {
  blinkTimer->stop();
  if (switchField) {
    ui->inputLine_calc->setVisible(true);
  } else {
    ui->inputLine_inputX->setVisible(true);
  }
}
