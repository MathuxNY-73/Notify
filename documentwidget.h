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

class Document;
class DocumentException;

class DocumentWidget : public NoteWidget
{
    //Macro
    Q_OBJECT

private:
    Document* document;
    QPushButton* save;

public:
    DocumentWidget(Document* d, QWidget* parent=0);
    Note* getNote(){}

public slots:
    void updateNote();
    void modification();
private slots:
};

#endif // DOCUMENTWIDGET_H
