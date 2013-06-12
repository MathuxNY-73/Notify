TEMPLATE = app
TARGET = Notify

QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

HEADERS += \
    article.h \
    note.h \
    document.h \
    binary.h \
    notemanager.h \
    exports.h \
    notewidget.h \
    articlewidget.h \
    documentwidget.h \
    binarywidget.h \
    editorspace.h \
    mainwindow.h \
    workspace.h \
    tagmanager.h

SOURCES += \
    article.cpp \
    note.cpp \
    document.cpp \
    main.cpp \
    binary.cpp \
    notemanager.cpp \
    exports.cpp \
    notewidget.cpp \
    articlewidget.cpp \
    documentwidget.cpp \
    binarywidget.cpp \
    editorspace.cpp \
    mainwindow.cpp \
    workspace.cpp \
    tagmanager.cpp

FORMS += \
    mainwindow.ui
