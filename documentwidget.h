//
//  documentwidget.h
//  LO21_Projet
//
//  Created by Anthony WEIBEL and Antoine POUILLAUDE on 07/05/13.
//  Copyright (c) 2013 Antoine POUILLAUDE. All rights reserved.
//

#ifndef DOCUMENTWIDGET_H
#define DOCUMENTWIDGET_H

#include "notewidget.h"
#include "article.h"
#include "binary.h"
#include <QFile>
#include <QDir>
#include <QTextStream>

class Document;
class DocumentException;

class DocumentWidget : public NoteWidget
{
    //Macro
    Q_OBJECT

private:
    Document* document;
    QFrame* frame;
    QVBoxLayout* frame_layout;
    //QPushButton* save, *exp;
    //QTextEdit* fen;
    //QFile* file;
    //QTextStream* out;


public:
    explicit DocumentWidget(Document* d, QWidget* parent=0);
    Note* getNote(){}

public slots:
    void updateNote();
    void modification();
    /*
private slots:
    void giveExport();*/
};

#endif // DOCUMENTWIDGET_H
