//
//  documentwidget.cpp
//  LO21_Projet
//
//  Created by Anthony WEIBEL and Antoine POUILLAUDE on 07/05/13.
//  Copyright (c) 2013 Antoine POUILLAUDE. All rights reserved.
//

#include "documentwidget.h"
#include "document.h"
#include "notewidget.h"
#include "exports.h"
#include <iostream>

/**
 * \fn DocumentWidget::DocumentWidget(Document* d, QWidget* parent)
 * \brief Constructeur des widgets de documents
 * \param Pointeur sur le document associé au Widget
 * \param Widget parent du widget de document
 */
DocumentWidget::DocumentWidget(Document* d, QWidget* parent):NoteWidget(d,parent),document(d)
{
    title->setText(d->getTitle());

    //Chargement de tous les widgets des notes contenues dans le document
    Document::Iterator it;
    for(it=d->begin() ; it!=d->end() ; ++it)
    {
        layout->addWidget((*it)->getWidget());
        QObject::connect((*it)->getWidget(),SIGNAL(mod()),this,SLOT(modification()));
    }
    QObject::connect(title,SIGNAL(textChanged(QString)),this,SLOT(modification()));
}

/**
 * \fn void DocumentWidget::updateNote()
 * \brief Mettre à jour le document associé.
 */
void DocumentWidget::updateNote()
{
    document->setTitle(title->text());
    Document::Iterator it;
    for(it=document->begin() ; it!=document->end() ; ++it)
        (*it)->getWidget()->updateNote();
    document->setModify(false);
}

/**
 * \fn void DocumentWidget::modification()
 * \brief Modification du document.
 */
void DocumentWidget::modification()
{
    document->setModify(true);
    emit mod();
}

/**
 * \fn Note* DocumentWidget::getNote()
 * \brief Retourne la partie Note du document
 * \return Pointeur sur la partie Note
 */
Note* DocumentWidget::getNote()
{
    return dynamic_cast<Note*>(document);
}
