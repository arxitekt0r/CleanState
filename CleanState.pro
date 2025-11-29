QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
TEMPLATE = app
TARGET = CleanState

INCLUDEPATH += src

SOURCES += \
    src/main.cpp \
    src/core/ApplicationController.cpp \
    src/ui/MainWindow.cpp \
    src/ui/pages/StatusPage.cpp \
    src/ui/pages/ProtectionPage.cpp \
    src/ui/pages/LogsPage.cpp \
    src/ui/pages/SettingsPage.cpp

HEADERS += \
    src/core/ApplicationController.h \
    src/ui/MainWindow.h \
    src/ui/pages/StatusPage.h \
    src/ui/pages/ProtectionPage.h \
    src/ui/pages/LogsPage.h \
    src/ui/pages/SettingsPage.h

FORMS +=
