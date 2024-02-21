QT       += core gui
 QT += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Model/model.cpp \
    Model/validation.cpp \
    View/main.cpp \
    View/mainwindow.cpp \
    qcustomplot.cpp

HEADERS += \
     Controller/controller.h \
     Model/model.h \
     View/mainwindow.h \
     qcustomplot.h


FORMS += \
    View/mainwindow.ui \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

SUBDIRS += \
     View/s21_calculator_2.0.pro
