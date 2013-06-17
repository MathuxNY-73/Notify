//
//  notemanager.cpp
//  LO21_Projet
//
//  Created by Anthony WEIBEL and Antoine POUILLAUDE on 07/05/13.
//  Copyright (c) 2013 Antoine POUILLAUDE. All rights reserved.
//

#include <fstream>
#include <QFile>
#include "workspace.h"
#include "notemanager.h"
#include "note.h"
#include "article.h"
#include "document.h"

/**
 * \brief Pointeur sur l'unique instance du Note Manager
 */
NoteManager* NoteManager::instance=0;

/**
 * \fn NoteManager& NoteManager::getInstance()
 * \brief Fonction qui permet de récupérer une instance du Note Manager
 * \return Retourne une reférence sur l'instance du NoteManager.
 */
NoteManager& NoteManager::getInstance(){
    if (!instance)
        instance=new NoteManager();
    return *instance;
}

/**
 * \fn void NoteManager::releaseInstance()
 * \brief Fonction qui libère et supprime l'instance de Note Manager si celle ci existe.
 */
void NoteManager::releaseInstance(){
    if (instance)
        delete instance;
    instance=0;
}

/**
 * \fn  Exports::ExportStrategy* NoteManager::getStrategy(const QString& n)
 * \brief Méthode servant à récupérer la strategie d'exportation correspondant au paramètre.
 * \param Nom de l'export
 * \return Pointeur sur l'export.
 */
Exports::ExportStrategy* NoteManager::getStrategy(const QString& n)
{
    QMap<QString,Exports::ExportStrategy*>::Iterator it;
    try
    {
        if(strategies.isEmpty())
            throw NoteManagerException("Il n'existe aucun export");
        it=strategies.find(n);
        if(it==strategies.end())
            throw NoteManagerException("Il n'existe aucun export avec cette denomination");
        else
            return *it;
    }
    catch (NoteManagerException& e)
    {
        QMessageBox::warning(&Workspace::getInstance(),"Error",e.getInfo());
        return 0;
    }
}

/**
 * \fn Note* NoteManager::getNote(unsigned int i) const
 * \brief Cette méthode sert à récupérer une note grâce à son identifiant.
 * \param L'identifiant de la note à récupérer
 * \return Un pointeur sur la note recherchée.
 */
Note* NoteManager::getNote(unsigned int i) const{
    QSet<Note*>::const_iterator it;
    for(it = notes.begin() ; it!=notes.end() ; ++it)
        if((*it)->getId()==i)
            break;
        if(it==notes.end())
            return 0;
    return *it;
}

/**
 * \fn void NoteManager::addNote(Note* n)
 * \brief Methode servant à ajouter une note au Note Manager
 * \param Un pointeur sur la note que l'on souhaite ajouter.
 */
void NoteManager::addNote(Note* n){
    try{
        if(notes.contains(n))
            throw NoteManagerException("The note you are trying to add in NoteManager is already in the set. Why are you so stupid ?");
        else
            notes<<n;
    }
    catch(NoteManagerException& e){
        QMessageBox::warning(&Workspace::getInstance(),"Error",e.getInfo());
    }

}

/**
 * \fn void NoteManager::deleteNote(Note* n)
 * \brief Méthode servant à supprimer une note du Note Manager
 * \param Pointeur sur la note à supprimer.
 */
void NoteManager::deleteNote(Note* n){
    try{
        if(notes.size()<=0)
            throw DocumentException("The list is empty. Why are you so stupid ?");
    }
    catch (NoteManagerException &e){
        std::cout<<"Fatal Error:"<<e.getInfo().toStdString()<<"\n";  //To be modified to display a warning on the screen.
        return;
    }
    try{
        if(!notes.contains(n))
            throw NoteManagerException("The note you are trying to delete is not in the list. Why are you so stupid ?");
        else
        {
            QSet<Note*>::iterator it;
            for(it = notes.begin() ; it!=notes.end() ; ++it)
                if((*it)->getId()==n->getId())
                    break;
            notes.erase(it);
        }
    }
    catch(NoteManagerException& e){
        QMessageBox::warning(&Workspace::getInstance(),"Error",e.getInfo());
    }
}

/**
 * \fn  QString NoteManager::getFilename(unsigned int i) const
 * \brief Fonction qui sert à récupérer les chemins d'une note.
 * \param Identifiant de la note dont on souhaite connaîtere le chemin
 * \return Le chemein vers la note.
 */
QString NoteManager::getFilename(unsigned int i) const{
    QSet<Note*>::const_iterator it;
    for(it = notes.begin() ; it!=notes.end() ; ++it)
        if((*it)->getId()==i)
            break;
    try{
        if(it==notes.end())
            throw NoteManagerException("The note you are trying to select is not in the document. Why are you so stupid ?");
        else
             return (*it)->getPath();
    }
    catch(NoteManagerException& e){
        QMessageBox::warning(&Workspace::getInstance(),"Error",e.getInfo());
        return "";
    }
}

/**
 * \fn void NoteManager::load(const QString& newPath)
 * \brief Fonction servant à charger un NoteManager depuis un fichier sur le disque
 * \param Chemin vers le fichier .workspace correspondant.
 * \bug Non définie
 */
void NoteManager::load(const QString& newPath){}

/**
 * \fn void NoteManager::reset()
 * \brief Fonction servant à restaurer le Note Manager depuis un historique.
 * \bug Non définie
 */
void NoteManager::reset(){}

/**
 * \fn Note* NoteManager::loadNote(unsigned int i)
 * \brief Fonction servant à charger une note grâce à son id.
 * \bug Non définie
 */
Note* NoteManager::loadNote(unsigned int i){}
