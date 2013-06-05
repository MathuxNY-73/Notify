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
#include "document.h"
#include "article.h"
#include "binary.h"

class DocumentWidget : public NoteWidget
{
    //Macro
    Q_OBJECT

private:
    Document* document;

public:
    DocumentWidget(Document* d, QWidget* parent=0);
};

#endif // DOCUMENTWIDGET_H
