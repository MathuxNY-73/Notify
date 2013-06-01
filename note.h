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

class Article;
class Document;
class NotesManager;
class NotesException;
class Binary;
class Video;
class Image;
class Audio;

QTextStream& operator<<(QTextStream& f, const Article& a);
QTextStream& operator<<(QTextStream& f, const Document& d);

class NotesException{
public:
    NotesException(const QString& message):info(message){}
    QString getInfo() const { return info; }
private:
    QString info;
};

class Note {
private:
    unsigned int id;
protected:
    QString title;
    QString path;
    bool loaded;
    bool modified;
public:
    Note(const QString& p):title(""), path(p), modified(true){};
    Note(unsigned int i, const QString& t):id(i),title(t){}
    unsigned int getId() const {return this->id;}
    QString getTitle() const {return this->title;}
    void setTitle(const QString& t)
    {
        modified=true;
        title=t;
    }
    bool isModify() const {return modified;}
    //QString ExportNote(ExportStrategy* es) const ;		Class ExportStrategy not yet implemented
    //virtual QString ExportAsPart(ExportStrategy* es, unsigned int tl) const =0;		Class ExportStrategy not yet implemented
    void addSubNote(Note* n);
    void addSubNote(Note* n, unsigned int id);
    void removeSubNote(unsigned int id);
    Note* getSubNote(unsigned int id) const;
    //virtual void load(const QString& path) =0;

};

#endif // NOTE_H
