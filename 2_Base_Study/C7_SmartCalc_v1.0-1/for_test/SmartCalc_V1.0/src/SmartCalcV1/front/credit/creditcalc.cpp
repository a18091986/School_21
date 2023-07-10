#include "../headers/creditcalc.h"

#include "ui_creditcalc.h"

CreditCalc::CreditCalc(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::CreditCalc) {
  ui->setupUi(this);

  setSelectComboBoxStyle(ui->comboBox_months);
  setSelectComboBoxStyle(ui->comboBox_payType);
  setSelectComboBoxStyle(ui->comboBox_yearMonth);

  connect(ui->pushButton_getResult, SIGNAL(clicked()), this,
          SLOT(calculateResults()));
}

CreditCalc::~CreditCalc() { delete ui; }

void CreditCalc::setSelectComboBoxStyle(QComboBox* comboBox) {
  comboBox->view()->window()->setWindowFlags(
      Qt::Popup | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
  comboBox->view()->window()->setAttribute(Qt::WA_TranslucentBackground);
}

void CreditCalc::calculateResults() {
  CreditInput input = initInput();
  CreditOutput out = creditCalculator(input);
  ui->label_resOverpay->setText(QString::number(out.overpay, 'f', 2));
  ui->label_resTotal->setText(QString::number(out.total_credit, 'f', 2));
  if (out.annuity) {
    ui->label_resMonthly->setText(QString::number(out.max_monthly, 'f', 2));
    adjustFont(ui->label_resMonthly);
  } else {
    QString temp = QString::number(out.min_monthly, 'f', 2) + " ... " +
                   QString::number(out.max_monthly, 'f', 2);
    ui->label_resMonthly->setText(temp);
    adjustFont(ui->label_resMonthly);
  }
}
void CreditCalc::adjustFont(QLabel* label) {
  QFont font = label->font();
  font.setPointSize(20);
  label->setFont(font);
  QFontMetrics fontMetrics(font);
  int textWidth = fontMetrics.horizontalAdvance(label->text());
  int labelWidth = label->width();

  if (textWidth > labelWidth - 20) {
    int fontSize = font.pointSize();
    while (textWidth > labelWidth - 20 && fontSize > 12) {
      fontSize--;
      font.setPointSize(fontSize);
      fontMetrics = QFontMetrics(font);
      textWidth = fontMetrics.horizontalAdvance(label->text());
    }
    label->setFont(font);
  }
}

CreditInput CreditCalc::initInput() {
  CreditInput input = {0};
  input.annuity = payTypeParse();
  input.total_loan = ui->spinBox_total->value();
  input.term = ui->spinBox_term->value();
  input.yearly = termTypeParse();
  input.interest = ui->doubleSpinBox_interest->value();
  input.curr_year = ui->spinBox_year->value();
  input.curr_month = monthParse();
  return input;
}

int CreditCalc::payTypeParse() {
  QString selectedText = ui->comboBox_payType->currentText();
  int res = 0;
  if (selectedText == "Аннуитетный") {
    res = 1;
  }
  return res;
}

int CreditCalc::termTypeParse() {
  QString selectedText = ui->comboBox_yearMonth->currentText();
  int res = 0;
  if (selectedText == "Года") {
    res = 1;
  }
  return res;
}

int CreditCalc::monthParse() {
  QString selectedText = ui->comboBox_months->currentText();
  QString months[] = {"Январь",   "Февраль", "Март",   "Апрель",
                      "Май",      "Июнь",    "Июль",   "Август",
                      "Сентябрь", "Октябрь", "Ноябрь", "Декабрь"};
  int myValue = 0;
  for (int i = 0; i < 12; i++) {
    if (selectedText == months[i]) {
      myValue = i + 1;
      break;
    }
  }
  return myValue;
}
