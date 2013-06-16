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
#include "modelManager.h"
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
#include <QListWidget>
#include <QComboBox>


/**
 * @brief The Workspace class
 */
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
    Note* selectedNote;

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

    void getFile(const QString& path);
    //void setWorkspace();
    void saveInFile();
    void updateFile();
    void addNote(Note* a);
    void addTag(const QString& t);
    void rootChange(Note* n);

public slots:
    void clear();
    void getSelectedItem(QModelIndex intdex);
    void updateNoteModel();

signals:
    void clearOthers();
    void clearEditor();

};

/**
 * @brief The DocumentAddNoteDialog class
 */
class DocumentAddNoteDialog : public QDialog
{
    Q_OBJECT
private:
    QComboBox box;
    Document* document;
    QMap<QListWidgetItem*,Document*> correspondance;
public:
    DocumentAddNoteDialog(Note* n,QWidget* parent=0);
    Document* getDocument() const { return document; }
public slots :
    void ok();
    void cancel();
};

/**
 * @brief The WorkspaceException class
 */

class WorkspaceException
{
    QString info;

public:
    WorkspaceException(const QString& message) throw() :info(message){}
    ~WorkspaceException() throw(){}
    QString getInfo() const { return info; }
};

#endif // WORKSPACE_H
