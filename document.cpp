//
//  document.cpp
//  LO21_Projet
//
//  Created by Anthony WEIBEL and Antoine POUILLAUDE on 07/05/13.
//  Copyright (c) 2013 Antoine POUILLAUDE. All rights reserved.
//

#include "document.h"
#include <fstream>
#include <iostream>
#include <QFile>
#include <QList>


//Les deux fonctions qui suivent sont des constructeurs de recopie cependant on ne les utilisent pas pour le moment.

/*Document::Document(const Document& m):      //I wonder why we have implemented this function
notes(m.notes),Note(m.id,l.title)
{}
*/
/*
Document& Document::operator=(const Document& m){   //Idem for that function
    if (this!=&m){
        notes=m.notes;
        id=m.id;                //Since Id is private in the class Note we cannot give it a value here.
        title=m.title;
    }
    return *this;
}
*/

void load(const QString& path){}

//QString ExportNote(ExportStrategy* es) const {}
//QString ExportAsPart(ExportStrategy* es, unsigned int tl) const{}

//Cette fonction va ajouter une Note au document. Attention, je n'ai pas le cas où la note est déjà dans la list.
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
            notes<<n;
    }
    catch(DocumentException& e){
        std::cout<<"Fatal Error:"<<e.getInfo().toStdString()<<"\n";  //To be modified to display a warning on the screen.
    }
}

//Cette fonction va ajouter une Note au document. Attention, je n'ai pas le cas où la note est déjà dans la list.
void Document::addSubNote(Note* n, unsigned int id){
    try{
        QList<Note*>::const_iterator it;
        for(it = notes.begin() ; it!=notes.end() ; ++it)
            if((*it)->getId()==id)
                throw DocumentException("The note you are trying to add to the document is already in the document. Why are you so stupid ?");
        if(id==this->getId())
            throw DocumentException("You are trying to put a document in itself dude. Why are you so stupid ?");
        else
            notes<<n;
    }
    catch(DocumentException& e){
        std::cout<<"Fatal Error:"<<e.getInfo().toStdString()<<"\n";  //To be modified to display a warning on the screen.
    }
}

//Cette fonction supprime les notes en prenant leur id
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
    it=notes.end();
    for(it = notes.begin() ; it!=notes.end() ; ++it)
        if((*it)->getId()==id)
            break;
    
    try{
        if(it==notes.end())
            throw DocumentException("The note you are trying to remove is not in the document. Why are you so stupid ?");
        else
            notes.erase(it);
    }
    catch(DocumentException& e){
        std::cout<<"Fatal Error:"<<e.getInfo().toStdString()<<"\n";  //To be modified to display a warning on the screen.
    }
}

//Cette va renvoyer la note correspondant à l'id donné en argument.
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
