//
//  workspace.cpp
//  LO21_Projet
//
//  Created by Anthony WEIBEL and Antoine POUILLAUDE on 11/06/13.
//  Copyright (c) 2013 Antoine POUILLAUDE. All rights reserved.
//

#include "workspace.h"
#include "mainwindow.h"
#include <QVariant>
#include <QModelIndex>

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

    //On créer la structure de base de tout fichier .workspace
    QDomElement root = xmlfile->createElement("workspace");
    xmlfile->appendChild(root);
    QDomElement notesNode = xmlfile->createElement("notes");
    QDomElement tagsNode = xmlfile->createElement("tags");
    root.appendChild(notesNode);
    root.appendChild(tagsNode);

    viewer->setHeaderHidden(false);
    viewer->setModel(model);
    viewer->setHorizontalScrollBar(scroll);
    viewer->setMinimumSize(100,150);
    viewer->setMaximumSize(150,400);
    viewer->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
    viewer->setSelectionMode(QAbstractItemView::ExtendedSelection);

    layout->addWidget(viewer);

    QObject::connect(viewer, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(getSelection(QModelIndex)));
}

Workspace::~Workspace()
{
    delete scroll;
    delete viewer;
    delete model;
    delete layout;
    Editorspace::releaseInstance();
    NoteManager::releaseInstance();
    delete xmlfile;
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
    NoteManager::Iterator it;
    for(it=NoteManager::getInstance().begin() ; it!=NoteManager::getInstance().end() ; ++it)
    {
        NoteItem* n= new NoteItem((*it)->getTitle(),(*it));
        n->setEditable(false);
        model->appendRow(n);
    }
}

void Workspace::addNote(Note* n)
{
    //On créer le noeud correspondant à la note.
    QDomElement createdNote=xmlfile->createElement("note");
    createdNote.setAttribute("id",n->getId());
    QString type =QString::fromStdString(typeid(*n).name());
    type.remove(0,1);
    createdNote.setAttribute("type",type);
    createdNote.setAttribute("title",n->getTitle());
    createdNote.setAttribute("path",n->getPath());
    QDomNodeList node_list=xmlfile->elementsByTagName("notes");
    QDomNode notesNode=node_list.at(0);
    if(notesNode.appendChild(createdNote)==0)
            throw MyException("Error while trying to add note");


    NoteManager::getInstance().addNote(n);
    NoteItem* a = new NoteItem(n->getTitle(),n);
    a->setEditable(false);
    model->appendRow(a);
    Editorspace::getInstance().addWidget(n);
}

void Workspace::addTag(const QString &t)
{
    //On créer le noeud correspondant à la note.
    QDomElement createdNote=xmlfile->createElement("tag");
    createdNote.setAttribute("name",t);
    QDomNodeList node_list=xmlfile->elementsByTagName("tags");
    QDomNode tagsNode=node_list.at(0);
    if(tagsNode.appendChild(createdNote)==0)
            throw Tags::TagManagerException("Error while trying to add tag");
}

void Workspace::getSelectedItem(QModelIndex index)
{
    try
    {
        NoteItem* itemNote = dynamic_cast<NoteItem*>(model->itemFromIndex(index));
        if(!itemNote)
            throw WorkspaceException("La conversion à échouée, impossible de réupérer la note à partir de l'item");
         Note* n=itemNote->getNote();
    }catch(WorkspaceException& e)
    {
        QMessageBox::critical(this,"Alert",e.getInfo());
        //return NULL;
    }
    //return *n;
}

void Workspace::getFile(const QString& path)
{
    QFile* file = new QFile(path+".workspace");
    if(!file->exists())
    {
        if(!file->open(QIODevice::ReadWrite))
            throw MyException("Error while creating the file.");
        QTextStream write(file);
        write.setCodec("UTF-8");
        write << "<?xml version='1.0' encoding='UTF-8'?>\n<workspace>\n"
        "<notes></notes>\n  <tags></tags>\n"
        "</workspace>";
        file->close();
    }
}

void Workspace::saveInFile()
{
    NoteManager::Iterator it;
    for(it=NoteManager::getInstance().begin() ; it!=NoteManager::getInstance().end() ; ++it)
    {
        (*it)->setPath(NoteManager::getInstance().getPath()+QString::number((*it)->getId())+".txt");
        (*it)->getWidget()->updateNote();
    }
    updateFile();
    QFile file(NoteManager::getInstance().getPath()+"test.workspace");
    QString update = "<?xml version='1.0' encoding='UTF-8'?> \n"+xmlfile->toString();
    if(!file.open(QIODevice::WriteOnly)){
        file.close();
        throw MyException("Error while writing in the file.");
    }
    QTextStream stream(&file);
    stream.setCodec("UTF-8");
    stream << update;
    file.close();
    for(it=NoteManager::getInstance().begin();it!=NoteManager::getInstance().end() ; ++it)
    {
        QFile file((*it)->getPath());
        if(file.exists() && (*it)->isModify())
            continue;
        QString s=(*it)->ExportNote(NoteManager::getInstance().getStrategy("save"));
        if(!file.open(QIODevice::WriteOnly))
            throw MyException("Ne parvient pas ouvrir le fichier "+ (*it)->getPath());
        QTextStream out(&file);
        out.setCodec("UTF-8");
        out<<(const QString&)s;
        file.close();
    }
}

void Workspace::updateFile()
{
    QDomNodeList node_list = xmlfile->elementsByTagName("notes");
    QDomElement notesNode = node_list.at(0).toElement();
    QDomNodeList nodeNotesList = notesNode.elementsByTagName("note");
    for(int i=0 ; i<nodeNotesList.size() ; i++)
    {
        QDomElement oldNote = nodeNotesList.at(i).toElement();
        QDomElement newNote = oldNote;
        int noteId = oldNote.attribute("id","-1").toInt();
        if(noteId<0)
            continue;
        Note* n;
        if(!(n=NoteManager::getInstance().getNote(noteId)))
        {
            notesNode.removeChild(oldNote);
            continue;
        }
        /*if(!n->isModify())
            continue;*/
        QString type =QString::fromStdString(typeid(*n).name());
        type.remove(0,1);
        newNote.setAttribute("id",n->getId());
        newNote.setAttribute("type",type);
        newNote.setAttribute("title",n->getTitle());
        newNote.setAttribute("path",n->getPath());

        notesNode.removeChild(notesNode.replaceChild(newNote,oldNote));
    }
}



void Workspace::clearAll()
{
    xmlfile->clear();
    model->clear();
    model->clear();
    viewer->setModel(model);
    emit clearOthers();
}

void Workspace::clear()
{
    clearAll();
}
