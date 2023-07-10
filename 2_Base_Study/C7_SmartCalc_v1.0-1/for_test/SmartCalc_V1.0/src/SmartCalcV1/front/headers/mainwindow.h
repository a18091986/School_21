/**
 * @file mainwindow.h
 * @brief Functions for handling the user interface of the calculator.
 */
#ifndef SRC_SMARTCALCV1_FRONT_HEADERS_MAINWINDOW_H_
#define SRC_SMARTCALCV1_FRONT_HEADERS_MAINWINDOW_H_

#ifdef __cplusplus
extern "C" {
#endif
#include "../../back/headers/calculator.h"
#ifdef __cplusplus
}
#endif

#include <QMainWindow>
#include <QPalette>
#include <QTimer>

#include "QtWidgets"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

/**
 * @class MainWindow
 * @brief A class that represents the main window of the calculator application.
 *
 * This class provides the functionality for the calculator UI, including input
 * handling, result display, and graphing.
 */
class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  /**
   * @brief Constructs a new MainWindow object.
   *
   * @param parent The parent widget.
   */
  explicit MainWindow(QWidget *parent = nullptr);
  /**
   * @brief Destroys the MainWindow object.
   */
  ~MainWindow();

 private:
  /**
   * @brief A pointer to the user interface object.
   */
  Ui::MainWindow *ui;

  /**
   * @brief A label that displays the current input.
   */
  QLabel *inputLabel;

  /**
   * @brief A timer used to blink the input label.
   */
  QTimer *blinkTimer;

  /**
   * @brief A timer used to control the duration of the blinking animation.
   */
  QTimer *blinkDurationTimer;

  /**
   * @brief The background color of the plot window.
   *
   * This color is set to transparent by default.
   */
  QColor backgroundColor;

  /**
   * @brief The color of the plot window's axes.
   *
   * This color is set to white by default.
   */
  QColor axisColor;

  /**
   * @brief The color of the graph lines.
   *
   * This color is set to orange by default.
   */
  QColor graphLineColor;

  /**
   * @brief A boolean flag indicating whether a result has been displayed.
   */
  bool resultDisplayed;

  /**
   * @brief A boolean flag indicating whether the input field has been switched.
   */
  bool switchField;

  /**
   * @brief The minimum x value for the graph.
   */
  double xMinBound;

  /**
   * @brief The maximum x value for the graph.
   */
  double xMaxBound;

  /**
   * @brief The minimum y value for the graph.
   */
  double yMinBound;

  /**
   * @brief The maximum y value for the graph.
   */
  double yMaxBound;

  /**
   * @brief A temporary variable used to calculate the minimum y value for the
   * graph.
   */
  double yMinTemp;

  /**
   * @brief A temporary variable used to calculate the maximum y value for the
   * graph.
   */
  double yMaxTemp;

  /**
   * @brief Calculates the result of the input expression for a given x value.
   *
   * @param x The x value to calculate the result for.
   * @param input The input expression in RPN format.
   * @return double The result of the input expression for the given x value.
   */
  double calcForGraph(double x, Stack *input);

  /**
   * @brief Calculates the x values for the graph based on the x range.
   *
   * @param xMin The minimum x value for the graph.
   * @param xMax The maximum x value for the graph.
   * @return QVector<double> The x values for the graph.
   */
  QVector<double> calculateXValues(double xMin, double xMax);

  /**
   * @brief Calculates the y values for the graph based on the input expression
   * and x values.
   *
   * @param xValues The x values for the graph.
   * @param input The input expression in RPN format.
   * @return QVector<double> The y values for the graph.
   */
  QVector<double> calculateYValues(QVector<double> xValues, Stack *input);

  /**
   * @brief Updates the y bounds for the graph based on the current y values.
   *
   * @param y The current y values for the graph.
   */
  void updateBoundsY(QVector<double> y);
 private slots:

  /**
   * @brief Handles button clicks for the basic input line.
   */
  void basicInputLineUI();

  /**
   * @brief Handles button clicks for the trigonometry input line.
   */
  void trigonometryInputLineUI();

  /**
   * @brief Clears the input line and resets the font size.
   */
  void clearInputLine();

  /**
   * @brief Deletes the last character in the input line.
   */
  void backspaceInputLine();

  /**
   * @brief Adjusts the font size of the given label to fit the text.
   *
   * @param label The label to adjust the font size of.
   */
  void adjustLabelFontSize(QLabel *label);

  /**
   * @brief Sends the input from the calculator to the calculate function and
   * displays the result.
   */
  void sendToCalculate();

  /**
   * @brief Checks if the given button is a simple operation.
   *
   * @param button The button text to check.
   * @return Returns true if the button is a simple operation, false otherwise.
   */
  bool simpleOperationCheck(QString button);

  /**
   * @brief Switches between the main input line and the input X line.
   */
  void switchInputField();

  /**
   * @brief Toggles the visibility of the input lines.
   */
  void toggleLabelVisibility();

  /**
   * @brief Stops the blinking animation and shows the input line.
   */
  void stopBlinking();

  /**
   * @brief Checks if the given button is allowed in the input X line.
   *
   * @param button The button text to check.
   * @return Returns true if the button is allowed in the input X line, false
   * otherwise.
   */
  bool inputLimitationX(QString button);

  /**
   * @brief Stylizes the plot window by setting the background color and axis
   * color.
   */
  void stylizePlotWindow();

  /**
   * @brief Plots the graph based on the x and y values.
   *
   * @param xValues The x values for the graph.
   * @param yValues The y values for the graph.
   */
  void plotGraph(QVector<double> xValues, QVector<double> yValues);

  /**
   * @brief Calls the plot module to plot a graph based on the input expression.
   */
  void callPlotModule();
};
#endif  // SRC_SMARTCALCV1_FRONT_HEADERS_MAINWINDOW_H_
