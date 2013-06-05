TEMPLATE = app
TARGET = Notify

CONFIG += x86 x86_64

QT += core gui
LIBS += /Users/Antoine/Qt5.0.2/5.0.2/Src/qtbase/lib
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

HEADERS += \
    article.h \
    note.h \
    document.h \
    binary.h \
    notemanager.h \
    exports.h \
    notewidget.h

SOURCES += \
    article.cpp \
    note.cpp \
    document.cpp \
    main.cpp \
    binary.cpp \
    notemanager.cpp \
    exports.cpp \
    notewidget.cpp

