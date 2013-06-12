//
//  workspace.cpp
//  LO21_Projet
//
//  Created by Anthony WEIBEL and Antoine POUILLAUDE on 11/06/13.
//  Copyright (c) 2013 Antoine POUILLAUDE. All rights reserved.
//

#include "workspace.h"

Workspace::Workspace(QWidget* parent):QWidget(parent),noteM(&NoteManager::getInstance()),items(QList<QStandardItem*>())
{
    //Allocation des widgets
    viewer = new QTreeView(this);
    layout = new QVBoxLayout(this);
    model= new QStandardItemModel();
    scroll = new QScrollBar(Qt::Horizontal,this);

    viewer->setHeaderHidden(false);
    viewer->setModel(model);
    viewer->setHorizontalScrollBar(scroll);
    viewer->setMinimumSize(100,150);
    viewer->setMaximumSize(150,400);
    viewer->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
    layout->addWidget(viewer);
}

Workspace::~Workspace()
{
    delete scroll;
    delete viewer;
    delete model;
    delete layout;
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
    {
        QStandardItem* n=(*it)->getItem();
        n->setEditable(false);
        items<<n;
    }
    model->appendRow(items);
}

void Workspace::setEditor(Editorspace *e)
{
    editor=e;
}

void Workspace::addNote(Note* n)
{
    noteM->addNote(n);
    QStandardItem* a;
    a = n->getItem();
    a->setEditable(false);
    model->appendRow(a);
    if(editor!=0)
        editor->addWidget(n);
}

