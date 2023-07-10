/**
 * @file creditcalc.h
 * @brief Contains the declaration of the CreditCalc class.
 */
#ifndef SRC_SMARTCALCV1_FRONT_HEADERS_CREDITCALC_H_
#define SRC_SMARTCALCV1_FRONT_HEADERS_CREDITCALC_H_

#ifdef __cplusplus
extern "C" {
#endif
#include "../../back/headers/credit.h"
#ifdef __cplusplus
}
#endif

#include <QAbstractItemView>
#include <QMainWindow>

#include "QtWidgets"

namespace Ui {
class CreditCalc;
}

/**
 * @class CreditCalc
 * @brief A class that represents the credit calculator application.
 *
 * This class provides the functionality for calculating credit payments based
 * on user input.
 */
class CreditCalc : public QMainWindow {
  Q_OBJECT

 public:
  /**
   * @brief Constructs a new CreditCalc object.
   *
   * @param parent The parent widget.
   */
  explicit CreditCalc(QWidget* parent = nullptr);
  /**
   * @brief Destroys the CreditCalc object.
   */
  ~CreditCalc();

 private:
  Ui::CreditCalc* ui;
 private slots:

  /**
   * @brief Sets the style of a combo box to match the application's design.
   *
   * @param comboBox The combo box to style.
   */
  void setSelectComboBoxStyle(QComboBox* comboBox);

  /**
   * @brief Calculates the credit results based on user input and updates the
   * UI.
   */
  void calculateResults();

  /**
   * @brief Initializes a CreditInput object based on user input.
   *
   * @return The initialized CreditInput object.
   */
  CreditInput initInput();

  /**
   * @brief Parses the selected payment type from the UI.
   *
   * @return 1 if "Аннуитетный" is selected, 0 otherwise.
   */
  int payTypeParse();

  /**
   * @brief Parses the selected month from the UI.
   *
   * @return The selected month as an integer (1-12).
   */
  int monthParse();

  /**
   * @brief Parses the selected term type from the UI.
   *
   * @return 1 if "Года" is selected, 0 otherwise.
   */
  int termTypeParse();

  /**
   * @brief Adjusts the font size of a label to fit its contents within its
   * bounds.
   *
   * @param label The label to adjust.
   */
  void adjustFont(QLabel* label);
};

#endif  // SRC_SMARTCALCV1_FRONT_HEADERS_CREDITCALC_H_
