//
//  editorspace.h
//  LO21_Projet
//
//  Created by Anthony WEIBEL and Antoine POUILLAUDE on 09/06/13.
//  Copyright (c) 2013 Antoine POUILLAUDE. All rights reserved.
//

#ifndef EDITORSPACE_H
#define EDITORSPACE_H


#include <QWidget>
//#include <QMainWindow>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QApplication>
#include <QLineEdit>
#include <QObject>
#include <QTextEdit>
#include <QScrollArea>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QTableWidget>
#include <QFileDialog>
#include <QSet>
#include <QStack>
#include "notemanager.h"
#include "notewidget.h"

class Workspace;

class Editorspace : public QWidget
{
    //Macro
    Q_OBJECT

private:
    QTabWidget* onglets;
    QTextEdit* HEdit,*TXEdit,*TxtEdit;
    QVBoxLayout* layout;
    QVBoxLayout* layout_HTML,*layout_TeX,*layout_Text,*layout_Editor;
    QScrollArea* scroll_HTML,*scroll_TeX,*scroll_Text,*scroll_Editor;
    QFileDialog* explorer;
    QStack<NoteWidget*> widgetList;
    QFrame* container;
    QPushButton* save;
    //QTextEdit* fen;
    //QFile* file;
    //QTextStream* out;

    //Singleton
    static Editorspace* instance;
    explicit Editorspace(QWidget *parent=0);
    ~Editorspace();
    Editorspace(const Editorspace& es);
    Editorspace& operator=(const Editorspace& es);

public:

    QVBoxLayout* getLayout() {return layout;}
    void addWidget(Note* n);
    void clearEditor();

    static Editorspace& getInstance(QWidget* parent=0);
    static void releaseInstance();

  //Slots

public slots:
    void changementOnglet(int i);
    void sauvegarder();
    void clear();
/*
private slots:
    void changementOnglet(int);
*/
/*    //signal
signals:
    void mod();
*/
};

#endif // EDITORSPACE_H
