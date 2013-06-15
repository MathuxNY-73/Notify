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


void load(const QString& path){}


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
        {
            modified=true;
            notes<<n;
        }
    }
    catch(DocumentException& e){
        std::cout<<"Fatal Error:"<<e.getInfo().toStdString()<<"\n";  //To be modified to display a warning on the screen.
    }
}

//Cette fonction va ajouter une Note au document. Attention, je n'ai pas le cas où la note est déjà dans la list. 
//Nota : Comment faire en sorte que l'on ne puisse pas inlcure un document dans un autre ?
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
        }
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


QString Document::ExportAsPart(Exports::ExportStrategy* es, unsigned int tl) {
    return es->exportNote(this,tl);
}

QString Document::ExportNote(Exports::ExportStrategy* es)
{
    return es->header(this)+es->exportNote(this)+es->footer(this);
}

DocumentWidget* Document::getWidget()
{
    if(maxW==0)
    {
        widget = new DocumentWidget(this);
        maxW++;
    }
    return widget;
}

bool Document::notin(const Note& n) const
{
    if(this->getId()==n.getId())
        return false;
    Document::constIterator it;
    for (it=this->begin() ; it!=this->end() ; ++it)
        if((*it)->getId()==n.getId())
            return false;
    return true;
}

QStandardItem* Document::getItem()
{
    if(!item)
    {
        item = new QStandardItem(title);
    }
    Iterator it;
    for(it=begin() ; it!=end() ; ++it)
        item->appendRow((*it)->getItem());
    return item;
}
