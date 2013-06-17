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
#include "notemanager.h"

/**
 * \fn Article::Article(const QString& p)
 * \brief Constructeur de l'article à partir du chemin
 * \param Chemin vers le fichier de note
 */
Article::Article(const QString& p):Note(p),text(""),widget(0),maxW(0){}

/**
 * \fn Article::Article(unsigned int i, const QString& ti, const QString& te)
 * \brief Constructeur d'un objet article
 * \param Identifiant de l'article
 * \param Titre de l'article
 * \param Text contenu dans l'article
 */
Article::Article(unsigned int i, const QString& ti, const QString& te): Note(i,ti),text(te),widget(0), maxW(0){}

/**
 * \fn Article::~Article()
 * \brief Destructeur de l'article
 */
Article::~Article()
{
    if(widget)
        delete widget;
}

/**
 * \fn const QString& Article::getText() const
 * \brief Récupérer le texte de l'article
 * \return Chaine de caractères contenant le texte de l'article
 */
const QString& Article::getText() const { return text; }

/**
 * \fn void Article::setText(const QString& t)
 * \brief Fixer le contenu de l'article
 * \param Chaine de caractères contenant le texte à mettre dans l'article
 */
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

/**
 * \fn ArticleWidget* Article::getWidget()
 * \brief Récupérer le widget correspondant à l'article
 * \return Pointeur vers le widget associé à l'article
 */
ArticleWidget* Article::getWidget(){
    if(maxW==0)
    {
        widget = new ArticleWidget(this);
        maxW++;
    }
    return widget;
}

/**
 * \fn Article& Article::getCopy()
 * \brief Récupérer une copie de l'article
 * \return Reférence vers le nouvel article.
 */
Article& Article::getCopy()
{
    Article* a=dynamic_cast<Article*>(NoteManager::getInstance().getFactory()["Article"]->buildNoteCopy());
    a->setText(text);
    return *a;
}
