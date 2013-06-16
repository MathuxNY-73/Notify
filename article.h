//
//  article.h
//  LO21_Projet
//
//  Created by Anthony WEIBEL and Antoine POUILLAUDE on 07/05/13.
//  Copyright (c) 2013 Antoine POUILLAUDE. All rights reserved.
//

#ifndef ARTICLE_H
#define ARTICLE_H

#include <iostream>
#include "note.h"
#include "exports.h"
#include "articlewidget.h"

class ArticleException{
public:
    ArticleException(const QString& message):info(message){}
    QString getInfo() const { return info; }
private:
    QString info;
};

class Article : public Note {
    
private:
    //Attributs
    QString text;
    ArticleWidget* widget;
    unsigned int maxW;

    //Constructeurs de recopie
    Article(const Article&);
    Article& operator=(const Article&);
    
public:
    //Constructeurs
    Article(const QString& path);
    Article(unsigned int i, const QString& ti, const QString& te);
    
    //Destructeur
    ~Article();
    
    //Methodes inlines

    
    //Methodes non-inlines
    void setText(const QString& t);
    const QString& getText() const;

    QString ExportNote(Exports::ExportStrategy *es);
    QString ExportAsPart(Exports::ExportStrategy* es, unsigned int tl);
    //QTextStream& operator<<(QTextStream& f, const Article& a);



    //Ceci est un test afin de pouvoir afficher les notes contenues dans un document
    ArticleWidget* getWidget();
};


#endif // ARTICLE_H
