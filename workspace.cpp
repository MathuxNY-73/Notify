//
//  workspace.cpp
//  LO21_Projet
//
//  Created by Anthony WEIBEL and Antoine POUILLAUDE on 11/06/13.
//  Copyright (c) 2013 Antoine POUILLAUDE. All rights reserved.
//

#include "workspace.h"

Workspace* Workspace::Instance=0;

Workspace& Workspace::getInstance(QWidget* parent)
{
    if(!Instance)
        Instance = new Workspace(parent);
    return *Instance;
}

void Workspace::releaseInstance()
{
    if(Instance)
        delete Instance;
    Instance=0;
}

Workspace::Workspace(QWidget* parent):QWidget(parent)
{
    //Allocation des widgets
    xmlfile= new QDomDocument("workspace");
    viewer = new QTreeView(this);
    layout = new QVBoxLayout(this);
    model= new QStandardItemModel();
    scroll = new QScrollBar(Qt::Horizontal,this);
    afficheSelection = new QPushButton("Afficher la selection",this);

    viewer->setHeaderHidden(false);
    viewer->setModel(model);
    viewer->setHorizontalScrollBar(scroll);
    viewer->setMinimumSize(100,150);
    viewer->setMaximumSize(150,400);
    viewer->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
    viewer->setSelectionMode(QAbstractItemView::ExtendedSelection);

    layout->addWidget(viewer);
    layout->addWidget(afficheSelection);

    QObject::connect(afficheSelection,SIGNAL(clicked()),this,SLOT(getSelection()));
}

Workspace::~Workspace()
{
    delete scroll;
    delete viewer;
    delete model;
    delete layout;
    delete afficheSelection;
    Editorspace::releaseInstance();
    NoteManager::releaseInstance();
}

void Workspace::setWorkspace()
{
    if(NoteManager::getInstance().begin()!=NoteManager::getInstance().end())
    {
        loadWorkspace();
    }
}

void Workspace::loadWorkspace()
{
    NoteManager::Const_Iterator it;
    for(it=NoteManager::getInstance().cbegin() ; it!=NoteManager::getInstance().cend() ; ++it)
    {
        QStandardItem* n=(*it)->getItem();
        n->setEditable(false);
        model->appendRow(n);
        items.insert(model->indexFromItem(n),(*it)->getId());
    }
}

void Workspace::addNote(Note* n)
{
    NoteManager::getInstance().addNote(n);
    QStandardItem* a;
    a = n->getItem();
    a->setEditable(false);
    model->appendRow(a);
    items.insert(model->indexFromItem(a),n->getId());
    QMessageBox::information(&Tags::TagManagerWidget::getInstance(), "Adding element"," L'élment de type"+QString::fromStdString(typeid(*n).name())+" a été ajoute avec l'id "+QString::number(n->getId()));
    Editorspace::getInstance().addWidget(n);
}

/*QSet<Note*>& Workspace::getSelectedNote() const
{
    QSet<Note*>* selectedNotes = new QSet<Note*>();
    QItemSelectionModel *selection = viewer->selectionModel();
    QModelIndexList listeSelections = selection->selectedIndexes();
    for (int i = 0 ; i < listeSelections.size() ; i++)
    {
        QVariant elementSelectionne = model->data(listeSelections[i], Qt::DisplayRole);
        unsigned int idSelect=items[elementSelectionne.toModelIndex()];
        *selectedNotes<<NoteManager::getInstance().getNote(idSelect);
    }
    return *selectedNotes;
}

void Workspace::getSelection()
{
    QSet<Note*>* selectedNotes = new QSet<Note*>();
    QItemSelectionModel *selection = viewer->selectionModel();
    QModelIndexList listeSelections = selection->selectedIndexes();
    QString selectedItems="";
    for (int i = 0 ; i < listeSelections.size() ; i++)
    {
        QVariant elementSelectionne = model->data(listeSelections[i], Qt::DisplayRole);
        selectedItems+="1 : "+NoteManager::getInstance().getNote(idSelect)->getTitle()+"  "+QString::number(idSelect)+"\n";
    }
    QMessageBox::information(&Tags::TagManagerWidget::getInstance(), "Eléments sélectionnés", selectedItems);
    return *selectedNotes;
}*/

void Workspace::getFile(const QString& path)
{
   /* destruct();
    QFile file(path+"/\.workspace");
    if(!file.exists())
    {
        //On crée un nouveau
    }*/
    return;
}

void Workspace::destruct()
{
    xmlfile->clear();
    model->clear();
    items.clear();
    //editor->clear();
}
