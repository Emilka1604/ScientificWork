QT += core gui widgets printsupport
CONFIG += c++11
TARGET = sci-work
TEMPLATE = app
DEFINES += QCUSTOMPLOT_USE_LIBRARY
CONFIG += release

INCLUDE_DIR = include
SOURCE_DIR = src

INCLUDEPATH += $$INCLUDE_DIR/

CONFIG(debug, release|debug) {
  win32:QCPLIB = qcustomplotd2
  else: QCPLIB = qcustomplotd
} else {
  win32:QCPLIB = qcustomplot2
  else: QCPLIB = qcustomplot
}
LIBS += -L./ -l$$QCPLIB

HEADERS += $$INCLUDE_DIR/BaseMethod.h \
           $$INCLUDE_DIR/Eiler.h \
           $$INCLUDE_DIR/EilerImplicit.h \
           $$INCLUDE_DIR/EilerImplicit2on2.h \
           $$INCLUDE_DIR/EilerImplicit3on3.h \
           $$INCLUDE_DIR/EilerImplicitAnyDim.h \
           $$INCLUDE_DIR/Kutta-Mersen.h \
           $$INCLUDE_DIR/mainwindow.h \
           $$INCLUDE_DIR/Newton.h \
           $$INCLUDE_DIR/Rado2A.h \
           $$INCLUDE_DIR/Runge-Kutt.h \
           $$INCLUDE_DIR/switcher.h
SOURCES += $$SOURCE_DIR/EilerImplicit.cpp \
           $$SOURCE_DIR/EilerImplicit2on2.cpp \
           $$SOURCE_DIR/EilerImplicit3on3.cpp \
           $$SOURCE_DIR/EilerImplicitAnyDim.cpp \
           $$SOURCE_DIR/EilerImplicitAnyDim2on2.cpp \
           $$SOURCE_DIR/EilerImplicitAnyDim3on3.cpp \
           $$SOURCE_DIR/Explicit3on3.cpp \
           $$SOURCE_DIR/main.cpp \
           $$SOURCE_DIR/mainwindow.cpp \
           $$SOURCE_DIR/NewtonTest.cpp \
           $$SOURCE_DIR/ScalarEqualation.cpp \
           $$SOURCE_DIR/test.cpp \
           $$SOURCE_DIR/VecTest.cpp \

FORMS += mainwindow.ui

CONFIG(debug, release|debug) {
target.files = build/debug/$${TARGET}.exe
} else {
target.files = build/release/$${TARGET}.exe
}
target.path = build
INSTALLS += target