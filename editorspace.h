//
//  workspace.h
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
    QFrame* container;
    NoteManager* noteM;
    QPushButton* save;
    Workspace* work;
    //QTextEdit* fen;
    //QFile* file;
    //QTextStream* out;


public:
    explicit Editorspace(QWidget *parent=0);
    QVBoxLayout* getLayout() {return layout;}
    void setWorkspace(Workspace* nm);
    void addWidget(Note* n);

  //Slots

public slots:
    void changementOnglet(int i);
    void sauvegarder();
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
