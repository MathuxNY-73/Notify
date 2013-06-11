//
//  notemanagerwidget.cpp
//  LO21_Projet
//
//  Created by Anthony WEIBEL and Antoine POUILLAUDE on 11/05/13.
//  Copyright (c) 2013 Antoine POUILLAUDE. All rights reserved.
//

#include "workspace.h"
Workspace::Workspace(QWidget* parent,NoteManager* nm):QWidget(parent),noteM(nm),items(QList<QStandardItem*>())
{
    //Allocation des widgets
    viewer = new QListView(this);
    //hierarchy = new QAbstractItemModel(this);
}

Workspace::~Workspace()
{
    delete viewer;
    delete viewer;
    delete hierarchy;
}

void Workspace::setWorkspace(NoteManager *nm)
{
    try{
        if(noteM!=0)
            throw WorkspaceException("Une instance de workspace existe déjà");
        else
            noteM=nm;
    }
    catch(WorkspaceException& e)
    {
        QMessageBox::information(this,"Warning",e.getInfo());
    }
    if(noteM->begin()!=noteM->end())
    {
        loadWorkspace();
    }
}

void Workspace::loadWorkspace()
{
    NoteManager::Const_Iterator it;
    for(it=noteM->cbegin() ; it!=noteM->cend() ; ++it)
        items<<(*it)->load();
}


