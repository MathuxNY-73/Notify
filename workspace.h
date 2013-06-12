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
#include <QTreeView>
#include <QScrollBar>
#include <QStandardItem>

class Workspace : public QWidget
{
    //Macro
    Q_OBJECT

private:
    NoteManager* noteM;
    QVBoxLayout* layout;
    QTreeView* viewer;
    QScrollBar* scroll;
    QStandardItemModel* model;
    QList<QStandardItem*> items;
    Editorspace* editor;

    void loadWorkspace();

public:
    explicit Workspace(QWidget* parent=0);
    ~Workspace();
    void setWorkspace(NoteManager* nm);
    void setEditor(Editorspace* e);

public slots:
    void addNote(Note* a);

};

class WorkspaceException
{
    QString info;

public:
    WorkspaceException(const QString& message):info(message){}
    QString getInfo() const { return info; }
};

#endif // WORKSPACE_H
