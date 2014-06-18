#-------------------------------------------------
#
# Project created by QtCreator 2011-08-07T18:06:32
#
#-------------------------------------------------
TEMPLATE = app
QT       += core gui webkitwidgets widgets

TARGET = BetterLiving


mac: CONFIG -= app_bundle

SOURCES += main.cpp\
        mainwindow.cpp \
    InfoDispatcher.cpp \
    ImmoFetcher.cpp \
    ScriptRunnerBase.cpp

HEADERS  += mainwindow.hpp \
    InfoDispatcher.hpp \
    ImmoFetcher.hpp \
    ScriptRunnerBase.hpp

FORMS    += mainwindow.ui

RESOURCES   += BetterLiving.qrc






