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
#include <QStandardItem>
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

    //Construction
    Note(const Note& n);
    Note& operator=(const Note& n);
    
protected:
    //Attributs protégés
    QString title;
    QString path;
    bool loaded;
    bool modified;

    QStandardItem* item;

public:
    //Constructeurs
    Note(const QString& p);
    Note(unsigned int i, const QString& t);
    ~Note();
    
    //Methodes inlines
    unsigned int getId() const {return this->id;}
    QString getTitle() const {return this->title;}
    void setTitle(const QString& t)
    {
        modified=true;
        title=t;
    }
    QString getPath() const {return this->path;}
    void setPath(const QString& p) {
        modified=true;
        path=p;
    }
    bool isModify() const {return modified;}
    void setModify(bool m){ modified=m;}
    
    //Methodes non-inlines
    void addSubNote(Note* n);
    void addSubNote(Note* n, unsigned int id);
    void removeSubNote(unsigned int id);
    Note* getSubNote(unsigned int id) const;
    
    
    //Methodes virtuelles pures ou pas
    virtual QString ExportNote(Exports::ExportStrategy* es) =0;		//Class ExportStrategy not yet implemented
    virtual QString ExportAsPart(Exports::ExportStrategy* es, unsigned int tl) =0;		//Class ExportStrategy not yet implemented
    //virtual void load(const QString& path) =0;
    virtual QStandardItem* getItem() =0;

    virtual NoteWidget* getWidget()=0;

};

#endif // NOTE_H
