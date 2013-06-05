//
//  NoteWidget.h
//  LO21_Projet
//
//  Created by Anthony WEIBEL and Antoine POUILLAUDE on 07/05/13.
//  Copyright (c) 2013 Antoine POUILLAUDE. All rights reserved.
//

#ifndef NOTEWIDGET_H
#define NOTEWIDGET_H

#include <QWidget>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QApplication> //Toutes les lignes suivantes sont à décommenter sous Qt. Elles sont commentées parce que sinon sous XCode cela ne fonctionne pas.
#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include "note.h"


class NoteWidget : public QWidget
{
    //Macro
    //Q_OBJECT
private:
    QLineEdit* title;
    QVBoxLayout* layout;

public:
    explicit NoteWidget(QWidget *parent=0);
    //virtual Note* getNote()=0;

    //Slots
/*public slots:
    virtual void updateNote();
private slots:
    void titleChanged(QString q);*/

};

#endif // NOTEWIDGET_H
