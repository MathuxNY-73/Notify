//
//  article.cpp
//  LO21_Projet
//
//  Created by Anthony WEIBEL and Antoine POUILLAUDE on 07/05/13.
//  Copyright (c) 2013 Antoine POUILLAUDE. All rights reserved.
//

#include "article.h"
#include <fstream>
#include <QFile>


void Article::setText(const QString& t) {
    modified=true; text=t;
}


//The two following functions are copy constructor. However these two function are not well ...
//... defined and does not fit the declaration given in the header file
/*
 Article::Article(const Article& a):
 title(a.title),filename(a.filename),text(a.text){}

 Article& Article::operator=(const Article& a){
 title=a.title; text=a.text; filename=a.filename;
 return *this;
 }

ArticleEditeur::ArticleEditeur(Article* art, QWidget *parent): QWidget(parent), article(art){
    titre = new QLineEdit(this);
    text = new QTextEdit(this);
    save = new QPushButton("Sauver", this);
    couche = new QVBoxLayout;
    couche->addWidget(titre);
    couche->addWidget(text);
    couche->addWidget(save);
    titre->setText(article->getTitle());
    text->setText(article->getText());
    setLayout(couche);
    QObject::connect(save, SIGNAL(clicked()), this, SLOT(saveArticle()));

    save->setEnabled(false);
    QObject::connect(titre, SIGNAL(textEdited(QString)), this, SLOT(activerSave(QString)));
    QObject::connect(text, SIGNAL(textChanged()), this, SLOT(activerSave()));
}

 void ArticleEditeur::saveArticle()
 {
 updateArticle();
 NotesManager::getInstance().saveArticle(*article);
 QMessageBox::information(this, "Sauvegarde", "Votre article a bien été sauvegardé...");
 }

 void ArticleEditeur::updateArticle()
 {
 article->setTitle(titre->text());
 article->setText(text->toPlainText());
 }

 void ArticleEditeur::activerSlot(QString str){
 save->setEnabled(true);
 }
 */
