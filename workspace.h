//
//  workspace.h
//  LO21_Projet
//
//  Created by Anthony WEIBEL and Antoine POUILLAUDE on 11/06/13.
//  Copyright (c) 2013 Antoine POUILLAUDE. All rights reserved.
//



#ifndef WORKSPACE_H
#define WORKSPACE_H

#include "notemanager.h"
#include "notewidget.h"
#include "editorspace.h"
#include "tagmanager.h"
#include <QTreeView>
#include <QScrollBar>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QtXML/QDomDocument>
#include <QtXml/QDomElement>
#include <QtXml/QDomNode>
#include <QtXml/QDomNodeList>


class Workspace : public QWidget
{
    //Macro
    Q_OBJECT

private:
    QVBoxLayout* layout;
    QTreeView* viewer;
    QScrollBar* scroll;
    QStandardItemModel* model;
    QDomDocument* xmlfile;


    //Singleton
    static Workspace* Instance;
    explicit Workspace(QWidget* parent=0);
    ~Workspace();
    Workspace(const Workspace& ws);
    Workspace& operator=(const Workspace& ws);

    //Methodes privées
    void loadWorkspace();
    void clearAll();

public:

    static Workspace& getInstance(QWidget* parent=0);
    static void releaseInstance();

    QSet<Note*>& getSelectedNote() const;

    void getFile(const QString& path);
    void setWorkspace();
    void saveInFile();
    void updateFile();
    void addNote(Note* a);
    void addTag(const QString& t);

public slots:
    void clear();
    void getSelectedItem(QModelIndex intdex);

signals:
    void clearOthers();

};

class NoteItem : public QStandardItem
{
private:
    Note* note;
public:
    NoteItem(const QString& title, Note* n):QStandardItem(title),note(n){}
    ~NoteItem(){}
    Note* getNote() const{ return note;}
};

class WorkspaceException
{
    QString info;

public:
    WorkspaceException(const QString& message) throw() :info(message){}
    ~WorkspaceException() throw(){}
    QString getInfo() const { return info; }
};

#endif // WORKSPACE_H
