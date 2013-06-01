//
//  document.h
//  LO21_Projet
//
//  Created by Anthony WEIBEL and Antoine POUILLAUDE on 07/05/13.
//  Copyright (c) 2013 Antoine POUILLAUDE. All rights reserved.
//

#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <iostream>
#include <QString>
#include <QList>
#include <QTextStream>
#include "note.h"

class DocumentException{
public:
    DocumentException(const QString& message):info(message){}
    QString getInfo() const { return info; }
private:
    QString info;
};

class Document : public Note {
    
private:
    //Attributs
    QList<Note*> notes; //This QList implement the design pattern Composite.
    //We could also have used std::List<Note*> but QList is simpler to use.
    
    //Constructeur de recopie
    Document(const Document& m);
    Document& operator=(const Document& m);
    
public:
    //Constructeurs
    Document(unsigned int i, const QString& t):Note(i,t),notes(QList<Note*>()){}
    Document(unsigned int i, const QString& t, const QList<Note*>& listNote):Note(i,t){
        notes=QList<Note*>();
        QList<Note*>::const_iterator it;                 //Il faudra vérifier si le const est justifié et correct ici.
        for(it=listNote.begin() ; it!=listNote.end() ; ++it)
            notes<<(*it);
    }
    Document(const QString& p):Note(p), notes(QList<Note*>()){}
    
    //Destructeur
    ~Document() {}
    
    //Methodes inlines
    
    //Autres methodes non-inline
    void load(const QString& path);
    Note* getSubNote(unsigned int i) const;
    void addSubNote(Note* n);
    void addSubNote(Note* n, unsigned int id);
    void removeSubNote(unsigned int id);
    
    
    //TODO
    //QString ExportNote(ExportStrategy* es) const;     Class ExportStrategy not yet implemented
    //QString ExportAsPart(ExportStrategy* es, unsigned int tl) const;      Class ExportStrategy not yet implemented
};

#endif // DOCUMENT_H
