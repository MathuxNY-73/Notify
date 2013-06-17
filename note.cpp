//
//  notes.cpp
//  LO21_Projet
//
//  Created by Anthony WEIBEL and Antoine POUILLAUDE on 07/05/13.
//  Copyright (c) 2013 Antoine POUILLAUDE. All rights reserved.
//

#include "note.h"
#include "article.h"
#include <fstream>
#include <QFile>

/**
 * \fn  Note::Note(const QString& p)
 * \brief Constructeur de Note à partir d'un fichier
 * \param Chemin vers le fichier de la note à construire
 */
Note::Note(const QString& p):title(""),path(p), modified(true){}

/**
 * \fn Note::Note(unsigned int i, const QString& t)
 * \brief Constructeur de Note à partir d'un identifiant et d'un titre
 * \param Identifiant de la note à créer
 * \param Titre de la Note à créer.
 */
Note::Note(unsigned int i, const QString& t):id(i),title(t),path(""),loaded(false),modified(true),item(0){}

/**
 * \fn Note::~Note()
 * \brief Destructeur de Note
 */
Note::~Note()
{
    delete item;
}

/**
 * \fn QStandardItem* Note::getItem()
 * \brief Récupérer l'item associé à la note.
 * \return L'item correspondant à la note.
 * Fonction retournant l'item correspondant à la Note dans le modèle mis en place dans le Workspace.
 */
QStandardItem* Note::getItem(){
    if(!item)
    {
        item = new QStandardItem(title);
        item->setAccessibleDescription(QString::number(getId()));
    }
    return item;
}
