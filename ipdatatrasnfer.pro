QT += core
QT -= gui
QT += network

TARGET = ipdatatrasnfer
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../qt-raw-udp/build/release/ -lRawUDPlib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../qt-raw-udp/build/debug/ -lRawUDPlib
else:unix: LIBS += -L$$PWD/../qt-raw-udp/build/ -lRawUDPlib

INCLUDEPATH += $$PWD/../qt-raw-udp
DEPENDPATH += $$PWD/../qt-raw-udp
