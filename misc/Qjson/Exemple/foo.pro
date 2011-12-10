#-------------------------------------------------
#
# Project created by QtCreator 2009-09-04T17:14:19
#
#-------------------------------------------------

QT       -= gui

TARGET = foo
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

QJSON_PATH = C:\\Libs\\qjson
INCLUDEPATH += $${QJSON_PATH}\\include
LIBS += -L$${QJSON_PATH}\\lib -lqjson0

#INCLUDEPATH += C:\Libs\Qjson\qjson\include\QJson

#LIBS += -LC:\Libs\Qjson\qjson\include\QJson -lqjson

SOURCES += main.cpp
