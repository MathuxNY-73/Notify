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
#include "note.h"
#include "exports.h"
#include "documentwidget.h"

/**
 * \class DocumentException
 * \brief Classe des exceptions de Document
 */
class DocumentException{
public:
    DocumentException(const QString& message):info(message){}
    QString getInfo() const { return info; }
private:
    QString info;
};

/**
 * \class Document : public Note
 * \brief Classe de document
 */
class Document : public Note {
    
private:
    //Attributs
    QList<Note*> notes;
    DocumentWidget* widget;
    unsigned int maxW;

    //Constructeur de recopie
    Document(const Document& m);
    Document& operator=(const Document& m);
    

public:
    //Constructeurs
    Document(unsigned int i, const QString& t):Note(i,t),notes(QList<Note*>()),widget(0),maxW(0){}
    Document(unsigned int i, const QString& t, const QList<Note*>& listNote):Note(i,t),widget(0),maxW(0){
        notes=QList<Note*>();
        QList<Note*>::const_iterator it;                 //Il faudra vérifier si le const est justifié et correct ici.
        for(it=listNote.begin() ; it!=listNote.end() ; ++it)
            notes<<(*it);
    }
    
    //Destructeur
    ~Document()
    {
        if(widget)
            delete widget;
    }


    //Autres methodes non-inline
    void load(const QString& path);
    Note* getSubNote(unsigned int i) const;
    void addSubNote(Note* n);
    void addSubNote(Note* n, unsigned int id);
    void removeSubNote(unsigned int id);

    QString ExportNote(Exports::ExportStrategy* es);
    QString ExportAsPart(Exports::ExportStrategy* es, unsigned int tl);
    
    DocumentWidget* getWidget();
    QStandardItem* getItem();
    Document& getCopy();

    /**
     * \class Iterator
     * \brief Classe Iterator de Document
     */
    class Iterator {   //Cette classe va servir dans les exports afin de pouvoir accéder aux notes
        
    private:
        //Copain
        friend class Document;
        
        //Attributs
        QList<Note*>::iterator it;
        
        //Constructeur
        Iterator(QList<Note*>::iterator c):it(c){}
        
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
    
    /**
     * \class constIterator
     * \brief Classe Iterator const.
     */
    class constIterator {   //Cette classe va servir dans les exports afin de pouvoir accéder aux notes
        
    private:
        //Copain
        friend class Document;
        
        //Attributs
        QList<Note*>::const_iterator it;
        
        //Constructeur
        constIterator(QList<Note*>::const_iterator c):it(c){}
        
    public:
        //Constructeur
        constIterator():it(){}
        
        //Methodes inlines
        const Note* operator*() const {return *it;}
        bool operator!=(const constIterator& c) const {return it!=c.it;}
        constIterator& operator++() {++it; return *this;}
        constIterator operator++(int){
            constIterator* tmp=this;
            ++it;
            return *tmp;
        }
        
    };
    constIterator begin() const{
        return constIterator(notes.constBegin());
    }
    constIterator end() const{
        return constIterator(notes.constEnd());
    }
};

#endif // DOCUMENT_H
