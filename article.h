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
#include <QFile>
#include <QString>
#include <QTextStream>
//#include <QApplication> //Toutes les lignes suivantes sont à décommenter sous Qt. Elles sont commentées parce que sinon sous XCode cela ne fonctionne pas.
#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include "note.h"
#include "exports.h"
#include "notewidget.h"
//#include "notefactory.h"

class ArticleException{
public:
    ArticleException(const QString& message):info(message){}
    QString getInfo() const { return info; }
private:
    QString info;
};

class Article : public Note {
    //friend class ArticleFactory;
    //friend Article* ArticleFactory::buildNoteCopy(const Article&); //copain pour pouvoir créer des notes par recopie dans les Factories
private:
    //Attributs
    QString text;
    
    //Constructeurs de recopie
    Article(const Article&);
    Article& operator=(const Article&);
    //void load();
    
public:
    //Constructeurs
    Article(const QString& path):Note(path),text(""){}
    Article(unsigned int i, const QString& ti, const QString& te): Note(i,ti),text(te){}
    
    //Destructeur
    ~Article(){}
    
    //Methodes inlines
    const QString& getText() const { return text; }
    
    //Methodes non-inlines
    void setText(const QString& t);

    QString ExportAsPart(Exports::ExportStrategy* es, unsigned int tl) const;
    //QTextStream& operator<<(QTextStream& f, const Article& a);
};


#endif // ARTICLE_H
