//
//  note.h
//  LO21_Projet
//
//  Created by Anthony WEIBEL and Antoine POUILLAUDE on 07/05/13.
//  Copyright (c) 2013 Antoine POUILLAUDE. All rights reserved.
//

#ifndef NOTE_H
#define NOTE_H

#include <iostream>
#include <QString>
#include <QTextStream>

/*
class Article;
class Document;
class NotesManager;
class NotesException;
class Binary;
class Video;
class Image;
class Audio;*/

namespace Exports {
    class ExportStrategy;
}

class NoteWidget;

//Classe pour la gestion des exceptions
class NotesException{
    
public:
    NotesException(const QString& message):info(message){}
    QString getInfo() const { return info; }
    
private:
    QString info;
};

//Definition de la classe Note
class Note {
    
private:
    //Attributs privés
    unsigned int id;
    
protected:
    //Attributs protégés
    QString title;
    QString path;
    bool loaded;
    bool modified;
    
public:
    //Constructeurs
    Note(const QString& p):title(""), path(p), modified(false){};
    Note(unsigned int i, const QString& t):id(i),title(t){}
    
    //Methodes inlines
    unsigned int getId() const {return this->id;}
    QString getTitle() const {return this->title;}
    void setTitle(const QString& t)
    {
        modified=true;
        title=t;
    }
    bool isModify() const {return modified;}
    void setModify(bool m){ modified=true;}
    
    //Methodes non-inlines
    void addSubNote(Note* n);
    void addSubNote(Note* n, unsigned int id);
    void removeSubNote(unsigned int id);
    Note* getSubNote(unsigned int id) const;
    

    //TODO
    
    //QString ExportNote(ExportStrategy* es) const ;		Class ExportStrategy not yet implemented
    virtual QString ExportAsPart(Exports::ExportStrategy* es, unsigned int tl) const =0;		//Class ExportStrategy not yet implemented
    //virtual void load(const QString& path) =0;

    //Cela ne marche pas mais je le garde tout de même
    //Ceci est un test afin de pouvoir afficher les notes contenues dans un document
    virtual NoteWidget* getWidget()=0;

};

#endif // NOTE_H
