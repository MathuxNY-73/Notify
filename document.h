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
    QList<Note*> notes; //This QList implement the design pattern Composite.

    //We could also have used std::List<Note*> but QList is simpler to use.
    Document(const Document& m);
    Document& operator=(const Document& m);
public:
    Document(unsigned int id, const QString& t);
    Document(unsigned int id, const QString& t, const QList<Note*>& listNote);
    ~Document() {}
    void load(const QString& path);
    Note* getSubNote(unsigned int i) const;
    //QString ExportNote(ExportStrategy* es) const;     Class ExportStrategy not yet implemented
    //QString ExportAsPart(ExportStrategy* es, unsigned int tl) const;      Class ExportStrategy not yet implemented
    void addSubNote(Note* n);
    void addSubNote(Note* n, unsigned int id);
    void removeSubNote(unsigned int id);
};

#endif // DOCUMENT_H
