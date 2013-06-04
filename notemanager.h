//
//  notemanager.h
//  LO21_Projet
//
//  Created by Anthony WEIBEL and Antoine POUILLAUDE on 07/05/13.
//  Copyright (c) 2013 Antoine POUILLAUDE. All rights reserved.
//

#ifndef NOTEMANAGER_H
#define NOTEMANAGER_H

#include <iostream>
#include <QString>
#include <QTextStream>
#include <QMap>
#include <QSet>
#include "note.h"
#include "article.h"
#include "document.h"
#include "exports.h"


class NoteManagerException{
public:
    NoteManagerException(const QString& message):info(message){}
    QString getInfo() const { return info; }
private:
    QString info;
};

//Classe principale du Note Manager
class NoteManager {
    
private:
    //Attributs privés
    QSet<Note*> notes;
    static NoteManager* instance;
    QString path;
    //QMap<QString, NoteFactory*> factories;
    //QMap<QString, Exports::ExportStrategy*> strategies; ,strategies(Exports::ExportStrategy::getExport())
    
    //Constructeurs
    NoteManager():notes(QSet<Note*>()),path(""){}  //Je subodore que c'est quelque chose comme cela.
    NoteManager(const QString& p):notes(QSet<Note*>()),path(p){}
    
    //Destructeur
    ~NoteManager(){}
    
    //Constructeurs de recopie
    NoteManager(const NoteManager& nm);
    NoteManager& operator=(const NotesManager& nm);
    
public:
    //Methodes inlines
    QString getPath() const {return path;}
    void setPath(const QString& p) {path=p;}
    
    //Methodes non-inlines
    Note* getNote(unsigned int i) const;
    void addNote(Note* n);
    void deleteNote(Note* n);
    QString getFilename(unsigned int i) const;
    void load(const QString& newPath);
    void load();
    void reset();
    Note* loadNote(unsigned int i);
    static NoteManager* getInstance();
    static void releaseInstance();
    void saveState() const;
    
};

#endif // NOTEMANAGER_H
