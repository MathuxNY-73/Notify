//
//  notemanagerwidget.h
//  LO21_Projet
//
//  Created by Anthony WEIBEL and Antoine POUILLAUDE on 11/05/13.
//  Copyright (c) 2013 Antoine POUILLAUDE. All rights reserved.
//

#ifndef WORKSPACE_H
#define WORKSPACE_H

#include "note.h"
#include "notemanager.h"
#include "notewidget.h"
#include <QListView>
#include <QStandardItem>

class WorkspaceException
{
    QString info;

public:
    WorkspaceException(const QString& message):info(message){}
    QString getInfo() const { return info; }
};

class Workspace : public QWidget
{
    //Macro
    Q_OBJECT

private:
    NoteManager* noteM;
    QListView* viewer;
    QAbstractItemModel* hierarchy;
    QList<QStandardItem*> items;

    void loadWorkspace();

public:
    explicit Workspace(QWidget* parent=0, NoteManager* nm=0);
    ~Workspace();
    void setWorkspace(NoteManager* nm);

};

#endif // NOTEMANAGERWIDGET_H
