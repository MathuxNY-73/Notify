//
//  workspace.h
//  LO21_Projet
//
//  Created by Anthony WEIBEL and Antoine POUILLAUDE on 11/06/13.
//  Copyright (c) 2013 Antoine POUILLAUDE. All rights reserved.
//



#ifndef WORKSPACE_H
#define WORKSPACE_H

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
 * \class Workspace : public QWidget
 * \brief Classe du workspace
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
    void clearAll();

public:

    static Workspace& getInstance(QWidget* parent=0);
    static void releaseInstance();

    void addNote(Note* a);
    void addTag(const QString& t);
    void updateFile();
    void saveInFile();
    void rootChange(Note* n);

public slots:
    void clear();
    void getSelectedItem(QModelIndex intdex);
    void updateNoteModel();

signals:

    /**
     * \fn clearOthers()
     * \brief Signal pour vider les widgets conteneurs
     */
    void clearOthers();

};

/**
 * \class  DocumentAddNoteDialog : public QDialog
 * \brief The DocumentAddNoteDialog class
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

    /**
     * \fn Document* getDocument() const ()
     * \brief Récupération du document
     * \return Retourne le document où l'on souhaite ajouter la note.
     */
    Document* getDocument() const { return document; }
public slots :

    void ok();
    void cancel();
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
