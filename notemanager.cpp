//
//  notemanager.cpp
//  LO21_Projet
//
//  Created by Anthony WEIBEL and Antoine POUILLAUDE on 07/05/13.
//  Copyright (c) 2013 Antoine POUILLAUDE. All rights reserved.
//

#include <fstream>
#include <QFile>
#include "note.h"
#include "notemanager.h"
#include "article.h"
#include "document.h"

NoteManager* NoteManager::instance=0; // pointeur sur l'unique instance

NoteManager* NoteManager::getInstance(){
    if (!instance)
        instance=new NoteManager();
    return instance;
}

void NoteManager::releaseInstance(){
    if (instance)
        delete instance;
    instance=0;
}

Note* NoteManager::getNote(unsigned int i) const{
    QSet<Note*>::const_iterator it;
    for(it = notes.begin() ; it!=notes.end() ; ++it)
        if((*it)->getId()==i)
            break;
    try{
        if(it==notes.end())
            throw NoteManagerException("The note you are trying to select is not in the document. Why are you so stupid ?");
    }
    catch(NoteManagerException& e){
        std::cout<<"Fatal Error:"<<e.getInfo().toStdString()<<"\n";  //To be modified to display a warning on the screen.
        return NULL;        //cette ligne provoque des erreurs.
    }
    return *it;
}

void NoteManager::addNote(Note* n){
    try{
        if(notes.contains(n))
            throw NoteManagerException("The note you are trying to add in NoteManager already exists. Why are you so stupid ?");
    }
    catch(NoteManagerException& e){
        std::cout<<"Fatal Error:"<<e.getInfo().toStdString()<<"\n";  //To be modified to display a warning on the screen.
    }
    
}

void NoteManager::deleteNote(Note* n){}
QString NoteManager::getFilename(unsigned int i) const{}
void NoteManager::load(const QString& newPath){}
void NoteManager::load(){}
void NoteManager::reset(){}
Note* NoteManager::loadNote(unsigned int i){}
void NoteManager::saveState() const{}


//Les deux fonctions suivantes servent à sauver les articles et les documents. Cependant, je pense que la fonctionnalité va être réalisée par la méthodes saveState.
/*
void NoteManager::saveArticle(Article& a){
    if (a.isModified()) {
        // Création d'un objet QFile
        QFile file(a.getFilename());
        // On ouvre notre fichier en lecture seule et on vérifie l'ouverture
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            throw NotesException("Erreur sauvegarde d'un article : impossible d'ouvrir un fichier en écriture");
        QTextStream flux(&file);
        flux<<a;
        file.close();
        a.modified=false;
    }
}

void NoteManager::saveDocument(Document& d){
    if (d.isModified()) {
        // Création d'un objet QFile
        QFile file(d.getFilename());
        // On ouvre notre fichier en lecture seule et on vérifie l'ouverture
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            throw NotesException("Erreur sauvegarde d'un document : impossible d'ouvrir un fichier en écriture");
        QTextStream flux(&file);
        flux<<d;
        file.close();
        d.modified=false;
    }
}
*/
