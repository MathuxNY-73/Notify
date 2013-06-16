//
//  article.cpp
//  LO21_Projet
//
//  Created by Anthony WEIBEL and Antoine POUILLAUDE on 07/05/13.
//  Copyright (c) 2013 Antoine POUILLAUDE. All rights reserved.
//


//#include <fstream>
//#include <QFile>
#include "article.h"


Article::Article(const QString& p):Note(p),text(""),widget(0),maxW(0){}
Article::Article(unsigned int i, const QString& ti, const QString& te): Note(i,ti),text(te),widget(0), maxW(0){}

Article::~Article()
{
    if(widget)
        delete widget;
}

const QString& Article::getText() const { return text; }

void Article::setText(const QString& t) {
    modified=true; text=t;
}

QString Article::ExportNote(Exports::ExportStrategy* es)
{
    return es->header(this)+es->exportNote(this)+es->footer(this);
}

QString Article::ExportAsPart(Exports::ExportStrategy* es, unsigned int tl)
{
    return es->exportNote(this,tl);
}

ArticleWidget* Article::getWidget(){
    if(maxW==0)
    {
        widget = new ArticleWidget(this);
        maxW++;
    }
    return widget;
}

QStandardItem* Article::getItem()
{
    if(!item)
        item = new QStandardItem(title);
    return item;
}
