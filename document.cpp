//
//  document.cpp
//  LO21_Projet
//
//  Created by Anthony WEIBEL and Antoine POUILLAUDE on 07/05/13.
//  Copyright (c) 2013 Antoine POUILLAUDE. All rights reserved.
//

#include "document.h"
#include "exports.h"
#include <fstream>
#include <iostream>
#include <QFile>
#include <QList>
#include"notemanager.h"

/**
 * \fn void load(const QString& path)
 * \brief Charger le document
 * \param Chemin vers le fichier de la note.
 * \bug Non définie
 *  Cette fonction va charger le document depuis le fichier.
 */
void load(const QString& path){}

/**
 * \fn Note* Document::getSubNote(unsigned int id) const
 * \brief Récupérer une note du document
 * \param Identifiant de la Note que l'on souhaite récupérer.
 * \return Pointeur sur la note récupérée.
 */
Note* Document::getSubNote(unsigned int id) const{
    QList<Note*>::const_iterator it;
    for(it = notes.begin() ; it!=notes.end() ; ++it)
        if((*it)->getId()==id)
            break;
    try{
        if(it==notes.end())
            throw DocumentException("The note you are trying to select is not in the document. Why are you so stupid ?");
    }
    catch(DocumentException& e){
        std::cout<<"Fatal Error:"<<e.getInfo().toStdString()<<"\n";  //To be modified to display a warning on the screen.
        return NULL;
    }
    return *it;
}

/**
 * \fn void Document::addSubNote(Note* n)
 * \brief Ajouter une note au document
 * \param Pointeur sur la note que l'on souhaite associer au document.
 */
void Document::addSubNote(Note* n)
{
    try{
        QList<Note*>::const_iterator it;
        for(it = notes.begin() ; it!=notes.end() ; ++it)
            if((*it)->getId()==n->getId())
                throw DocumentException("The note you are trying to add to the document is already in the document. Why are you so stupid ?");
        if(n->getId()==this->getId())
            throw DocumentException("You are trying to put a document in itself dude. Why are you so stupid ?");
        else
        {
            modified=true;
            notes<<n;
        }
    }
    catch(DocumentException& e){
        std::cout<<"Fatal Error:"<<e.getInfo().toStdString()<<"\n";
    }
}

/**
 * \fn void Document::addSubNote(Note* n, unsigned int id)
 * \brief Ajouter une note au document avec son id
 * \param Pointeur sur la note que l'on souhaite associer au document
 * \param Identifiant de la note à ajouter.
 */
void Document::addSubNote(Note* n, unsigned int id){
    try{
        QList<Note*>::const_iterator it;
        for(it = notes.begin() ; it!=notes.end() ; ++it)
            if((*it)->getId()==id)
                throw DocumentException("The note you are trying to add to the document is already in the document. Why are you so stupid ?");
        if(id==this->getId())
            throw DocumentException("You are trying to put a document in itself dude. Why are you so stupid ?");
        else
        {
            modified=true;
            notes<<n;
            item->appendRow(n->getCopy().getItem());
        }
    }
    catch(DocumentException& e){
        std::cout<<"Fatal Error:"<<e.getInfo().toStdString()<<"\n";  //To be modified to display a warning on the screen.
    }
}

/**
 * \fn void Document::removeSubNote(unsigned int id)
 * \brief Supprimer une note du document
 * \param Identifiant de la note à supprimer.
 */
void Document::removeSubNote(unsigned int id){
    try{
        if(notes.size()<=0)
            throw DocumentException("The list is empty. Why are you so stupid ?");
    }
    catch (DocumentException &e){
        std::cout<<"Fatal Error:"<<e.getInfo().toStdString()<<"\n";  //To be modified to display a warning on the screen.
        return;
    }
    QList<Note*>::iterator it;
    for(it = notes.begin() ; it!=notes.end() ; ++it)
        if((*it)->getId()==id)
            break;
    try{
        if(it==notes.end())
            throw DocumentException("The note you are trying to remove is not in the document. Why are you so stupid ?");
        else
        {
            modified=true;
            notes.erase(it);
        }
    }
    catch(DocumentException& e){
        std::cout<<"Fatal Error:"<<e.getInfo().toStdString()<<"\n";  //To be modified to display a warning on the screen.
    }
}

/**
 * \fn QString Document::ExportAsPart(Exports::ExportStrategy* es, unsigned int tl)
 * \brief Exporter le document en tant que partie.
 * \param Pointeur sur la stratégie à utiliser
 * \param Niveau de titre
 * \return Chaine de caractère issue de l'exportation
 */
QString Document::ExportAsPart(Exports::ExportStrategy* es, unsigned int tl) {
    return es->exportNote(this,tl);
}

/**
 * \fn QString Document::ExportNote(Exports::ExportStrategy* es)
 * \brief Exporter le document.
 * \param Pointeur sur la stratégie à utiliser.
 * \return Chaine de caractère issue de l'exportation
 */
QString Document::ExportNote(Exports::ExportStrategy* es)
{
    return es->header(this)+es->exportNote(this)+es->footer(this);
}

/**
 * \fn DocumentWidget* Document::getWidget()
 * \brief Création du widget associé au document.
 * \return Widget correspondant au document.
 */
DocumentWidget* Document::getWidget()
{
  /*  if(modified)
        if(maxW)
        {
            delete widget;
            maxW--;
        }*/
        if(maxW==0)
        {
            widget = new DocumentWidget(this);
            maxW++;
        }
    return widget;
}

/**
 * \fn QStandardItem* Document::getItem()
 * \brief Récupérer l'item associé au Document
 * \return Item standard correspondant au document dans le MVC mis en place.
 */
QStandardItem* Document::getItem()
{
    if(!item)
    {
        item = new QStandardItem(title);
        item->setAccessibleDescription(QString::number(getId()));
    }
    Iterator it;
    for(it=begin() ; it!=end() ; ++it)
        item->appendRow((*it)->getItem());
    return item;
}

/**
 * \fn Document& Document::getCopy()
 * \brief Copier document
 * \return Nouveau document copier à partir du document appelant la méthode.
 */
Document& Document::getCopy(){
    Document* d=dynamic_cast<Document*>(NoteManager::getInstance().getFactory()["Document"]->buildNoteCopy());
    Document::Iterator it;
    for(it=begin() ; it!=end() ; ++it)
    {
        Note* note=&((*it)->getCopy());
        d->addSubNote(note,note->getId());
    }
    return *d;
}
