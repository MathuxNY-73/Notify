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
#include "factories.h"


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
    QMap<QString, NoteFactory*> factories;
    QMap<QString, Exports::ExportStrategy*> strategies;
    
    //Constructeurs
    NoteManager():notes(QSet<Note*>()),path(""),factories(NoteFactory::getFactories()),strategies(Exports::ExportStrategy::getExport()){
    }  //Je subodore que c'est quelque chose comme cela.

    NoteManager(const QString& p):notes(QSet<Note*>()),path(p){}
    
    //Destructeur
    ~NoteManager(){}
    
    //Constructeurs de recopie
    NoteManager(const NoteManager& nm);
    NoteManager& operator=(const NoteManager& nm);
    
public:
    //Methodes inlines
    QString getPath() const {return path;}
    void setPath(const QString& p) {path=p;}
    
    //Methodes non-inlines
    Exports::ExportStrategy* getStrategy(const QString& n);
    Note* getNote(unsigned int i) const;
    void addNote(Note* n);
    void deleteNote(Note* n);
    QString getFilename(unsigned int i) const;
    void load(const QString& newPath);
    void load();
    void reset();
    Note* loadNote(unsigned int i);
    static bool exist() {return instance!=0;}
    void saveState() const;
    QMap<QString, NoteFactory*> getFactory() const
    {
        return factories;
    }

    //Singleton
    static NoteManager& getInstance();
    static void releaseInstance();


    //Iterateur non constant
    class Iterator {

    private:
        //Copain
        friend class NoteManager;

        //Attributs
        QSet<Note*>::iterator it;

        //Constructeur
        Iterator(QSet<Note*>::iterator c):it(c){}

    public:
        //Constructeur
        Iterator():it(){}

        //Methodes inlines
        Note* operator*() const {return *it;}
        bool operator!=(const Iterator& c) const {return it!=c.it;}
        Iterator& operator++() {++it; return *this;}
        Iterator operator++(int){
            Iterator* tmp=this;
            ++it;
            return *tmp;
        }
    };
    Iterator begin(){
        return Iterator(notes.begin());
    }
    Iterator end(){
        return Iterator(notes.end());
    }

    //Iterateur constant
    class Const_Iterator {

    private:
        //Copain
        friend class NoteManager;

        //Attributs
        QSet<Note*>::const_iterator it;

        //Constructeur
        Const_Iterator(QSet<Note*>::const_iterator c):it(c){}

    public:
        //Constructeur
        Const_Iterator():it(){}

        //Methodes inlines
        Note* operator*() const {return *it;}
        bool operator!=(const Const_Iterator& c) const {return it!=c.it;}
        Const_Iterator& operator++() {++it; return *this;}
        Const_Iterator operator++(int){
            Const_Iterator* tmp=this;
            ++it;
            return *tmp;
        }
    };
    Const_Iterator cbegin() const{
        return Const_Iterator(notes.cbegin());
    }
    Const_Iterator cend() const{
        return Const_Iterator(notes.cend());
    }
    
};

#endif // NOTEMANAGER_H
