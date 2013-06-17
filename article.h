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

/**
 * \class ArticleException
 * \brief Classes des exceptions des objets articles
 */
class ArticleException{
public:
    ArticleException(const QString& message):info(message){}
    QString getInfo() const { return info; }
private:
    QString info;
};

/**
 * \fn class Article : public Note
 * \brief Classe des objets articles
 */
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
    
    //Methodes non-inlines
    void setText(const QString& t);
    const QString& getText() const;
    Article& getCopy();

    QString ExportNote(Exports::ExportStrategy *es);
    QString ExportAsPart(Exports::ExportStrategy* es, unsigned int tl);

    ArticleWidget* getWidget();
};


#endif // ARTICLE_H
