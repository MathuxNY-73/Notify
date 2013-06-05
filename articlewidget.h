//
//  articlewidget.h
//  LO21_Projet
//
//  Created by Anthony WEIBEL and Antoine POUILLAUDE on 07/05/13.
//  Copyright (c) 2013 Antoine POUILLAUDE. All rights reserved.
//

#ifndef ARTICLEWIDGET_H
#define ARTICLEWIDGET_H

#include "notewidget.h"
#include "article.h"

class ArticleWidget : public NoteWidget
{
    //Macro
    Q_OBJECT

private:
    QTextEdit* text;
    QPushButton* save;
    Article* article;

public:
    explicit ArticleWidget(Article* a,QWidget* parent=0);
    Note* getNote(){}

   //Slots
public slots:
    void updateNote();
private slots:
    void enableSave();
};
#endif // ARTICLEWIDGET_H
