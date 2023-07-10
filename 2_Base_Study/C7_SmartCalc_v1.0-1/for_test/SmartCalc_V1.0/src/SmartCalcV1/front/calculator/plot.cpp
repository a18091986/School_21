#include "../headers/mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::callPlotModule() {
  resultDisplayed = true;
  double xMin = double(ui->spinBox_xMin->value());
  double xMax = double(ui->spinBox_xMax->value());
  if (xMax - xMin > 0) {
    xMinBound = xMin;
    xMaxBound = xMax;
    QVector<double> xValues = calculateXValues(xMin, xMax);
    QByteArray inputBytes = ui->inputLine_calc->text().toUtf8();
    char *inputString = strdup(inputBytes.constData());
    Stack *input = initStack();
    if (convertInput(inputString, input)) {
      QVector<double> yValues = calculateYValues(xValues, input);
      plotGraph(xValues, yValues);
    } else {
      ui->inputLine_calc->setText("Invalid input");
    }
    freeStack(input);
    free(inputString);
  } else {
    ui->inputLine_calc->setText("Invalid x scope");
  }
}

QVector<double> MainWindow::calculateYValues(QVector<double> xValues,
                                             Stack *input) {
  QVector<double> output;
  int dotsAmount = xValues.size();
  bool UpdFirstY = false;
  output.resize(dotsAmount);
  for (int i = 0; i < dotsAmount; i++) {
    Stack *tempStack = copyStack(input);
    double x = xValues[i];
    double y = calcForGraph(x, tempStack);
    if (!UpdFirstY && !qIsNaN(y)) {
      UpdFirstY = true;
      yMinBound = y;
      yMaxBound = y;
    }

    if (fabs(y) > 1e6) {
      y = NAN;
    }
    if (i > 0 && fabs(fabs(y) - fabs(output[i - 1])) > 80) {
      output[i - 1] = NAN;
    }
    output[i] = y;

    freeStack(tempStack);
  }
  return output;
}

double MainWindow::calcForGraph(double x, Stack *input) {
  double result = 0.0f;
  char x_input[128] = {0};
  sprintf(x_input, "%.7lf", x);
  inputX(x_input, input);
  Stack *rpn = rpnConverter(input);
  reverseStack(rpn);
  if (calculation(rpn, &result)) {
    if (fabs(result) < 1e-9) {
      result = 0.0f;
    }
  } else {
    result = NAN;
  }
  free(rpn);
  return result;
}

QVector<double> MainWindow::calculateXValues(double xMin, double xMax) {
  QVector<double> output;
  double xRange = xMax - xMin;
  int dotsAmount = 100;
  double singleStep = xRange / dotsAmount;
  while (singleStep > 0.01 && dotsAmount < 100000) {
    dotsAmount *= 2;
    singleStep = xRange / dotsAmount;
  }
  output.resize(dotsAmount);
  for (int i = 0; i < dotsAmount; i++) {
    output[i] = xMin + (i * singleStep);
  }
  return output;
}

void MainWindow::plotGraph(QVector<double> xValues, QVector<double> yValues) {
  // Clear all existing graphs
  ui->plotWindow->clearGraphs();
  // Split the graph into segments
  QVector<QVector<double>> xSegments;
  QVector<QVector<double>> ySegments;
  QVector<int> segmentStartIndices;
  int currentSegmentStartIndex = 0;
  double previous = yValues[0];
  for (int i = 0; i < yValues.size(); i++) {
    if ((qIsInf(yValues[i]) || qIsNaN(yValues[i]))) {
      // Add the current segment to the list of segments
      if (!qIsNaN(previous)) {
        xSegments.append(xValues.mid(currentSegmentStartIndex,
                                     i - currentSegmentStartIndex));
        ySegments.append(yValues.mid(currentSegmentStartIndex,
                                     i - currentSegmentStartIndex));
        segmentStartIndices.append(currentSegmentStartIndex);
      }
      // Start a new segment
      currentSegmentStartIndex = i + 1;
    }
    previous = yValues[i];
  }
  // Add the last segment to the list of segments
  xSegments.append(xValues.mid(currentSegmentStartIndex));
  ySegments.append(yValues.mid(currentSegmentStartIndex));
  segmentStartIndices.append(currentSegmentStartIndex);

  // Add each segment to the plot as a separate graph
  int j = 0;
  for (int i = 0; i < xSegments.size(); i++) {
    if (xSegments[i].size() > 2) {
      if (j == 0) {
        yMinTemp = ySegments[i][0];
        yMaxTemp = ySegments[i][0];
      }
      updateBoundsY(ySegments[i]);
      ui->plotWindow->addGraph();
      ui->plotWindow->graph(j)->setPen(QPen(graphLineColor, 2));
      ui->plotWindow->graph(j)->setData(xSegments[i], ySegments[i]);
      j++;
    }
  }
  double yRange = (yMaxBound - yMinBound) * 10 / 100;
  if (yRange == 0) {
    yRange = 2;
  }
  double xRange = (xMaxBound - xMinBound) * 10 / 100;
  ui->plotWindow->xAxis->setRange(xMinBound - xRange, xMaxBound + xRange);
  ui->plotWindow->yAxis->setRange(yMinBound - yRange, yMaxBound + yRange);
  ui->plotWindow->replot();
}

void MainWindow::updateBoundsY(QVector<double> y) {
  for (int i = 0; i < y.size(); i++) {
    if (yMinBound > y[i] && !qIsInf(fabs(y[i])) && !qIsNaN(y[i])) {
      yMinTemp = yMinBound;
      yMinBound = y[i];
    }
    if (yMaxBound < y[i] && !qIsInf(fabs(y[i])) && !qIsNaN(y[i])) {
      yMaxTemp = yMaxBound;
      yMaxBound = y[i];
    }
  }
}

void MainWindow::stylizePlotWindow() {
  // Set the background color
  ui->plotWindow->setBackground(QBrush(backgroundColor));

  // Set the axis color and label color
  QPen axisPen(axisColor);
  axisPen.setWidth(1);
  ui->plotWindow->xAxis->setBasePen(axisPen);
  ui->plotWindow->yAxis->setBasePen(axisPen);
  ui->plotWindow->xAxis->setTickPen(axisPen);
  ui->plotWindow->yAxis->setTickPen(axisPen);
  ui->plotWindow->xAxis->setSubTickPen(axisPen);
  ui->plotWindow->yAxis->setSubTickPen(axisPen);
  ui->plotWindow->xAxis->setTickLabelColor(axisColor);
  ui->plotWindow->yAxis->setTickLabelColor(axisColor);
  ui->plotWindow->xAxis->setLabelColor(axisColor);
  ui->plotWindow->yAxis->setLabelColor(axisColor);
}
