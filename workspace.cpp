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
#include <string>

/**
 * @brief Workspace::Instance
 */

Workspace* Workspace::Instance=0;

/**
 * @brief Workspace::getInstance
 * @param parent
 * @return Workspace&
 */
Workspace& Workspace::getInstance(QWidget* parent)
{
    if(!Instance)
        Instance = new Workspace(parent);
    return *Instance;
}

/**
 * @brief Workspace::releaseInstance
 */
void Workspace::releaseInstance()
{
    if(Instance)
        delete Instance;
    Instance=0;
}

/**
 * @brief Workspace::Workspace
 * @param parent
 */
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
    viewer->setSelectionMode(QAbstractItemView::SingleSelection);

    layout->addWidget(viewer);

    QObject::connect(viewer, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(getSelectedItem(QModelIndex)));
}

/**
 * @brief Workspace::~Workspace
 */
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

/**
 * @brief Workspace::setWorkspace
 */
/*void Workspace::setWorkspace()
{
    if(NoteManager::getInstance().begin()!=NoteManager::getInstance().end())
    {
        loadWorkspace();
    }
}*/

/**
 * @brief Workspace::loadWorkspace
 */
void Workspace::updateNoteModel()
{
    NoteManager::Iterator it;
    for(it=NoteManager::getInstance().begin() ; it!=NoteManager::getInstance().end() ; ++it)
    {
        QStandardItem* n = (*it)->getItem();
        model->appendRow(n);
    }
}

/**
 * @brief Workspace::addNote
 * @param n
 */
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
    QStandardItem* a = n->getItem();
    a->setEditable(false);
    model->appendRow(a);
    Editorspace::getInstance().addWidget(n);
}

/**
 * @brief Workspace::addTag
 * @param t
 */
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
/**
 * @brief Workspace::getSelectedItem
 * @param index
 */
void Workspace::getSelectedItem(QModelIndex index)
{
    unsigned int id;
    try
    {
        QString idNote = model->itemFromIndex(index)->accessibleDescription();
        if(idNote=="")
            throw WorkspaceException("La conversion à échouée, impossible de réupérer la note à partir de l'item");
        id = idNote.toUInt();
    }catch(WorkspaceException& e)
    {
        QMessageBox::critical(this,"Alert",e.getInfo());
        return;
    }
    QString type =QString::fromStdString(typeid(*(NoteManager::getInstance().getNote(id))).name());
    type.remove(0,1);
    QMessageBox::information(this,"Info","La note selectionnée est "+NoteManager::getInstance().getNote(id)->getTitle()+" avec l'id "+QString::number(id)+" de type : "+type);
    Editorspace::getInstance().addWidget(NoteManager::getInstance().getNote(id));
}

/**
 * @brief Workspace::saveInFile
 */
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

/**
 * @brief Workspace::updateFile
 */

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
/*
class DocumentAddDialog : public QDialog {
    Q_OBJECT
private :
    QComboBox comboBox;
    QString noteId;
public :
    DocumentAddDialog(Document *resource, QWidget* parent = 0);
    const QString& getNoteId() const { return noteId; }
public slots :
    void ok();
    void cancel();
};*/

/**
 * @brief Workspace::rootChange
 * @param n
 */

void Workspace::rootChange(Note* n)
{
    DocumentAddNoteDialog dialog(n,this);
    try {
          dialog.exec();
          if (dialog.result()){
              dialog.getDocument()->addSubNote(n,n->getId());
              Editorspace::getInstance().addWidget(dialog.getDocument());
              updateNoteModel();
          }
      } catch (WorkspaceException& e){
          QMessageBox::information(this, "Erreur", e.getInfo());
      }
}

/**
 * @brief DocumentAddNoteDialog::DocumentAddNoteDialog
 * @param n
 * @param parent
 */

DocumentAddNoteDialog::DocumentAddNoteDialog(Note* n,QWidget *parent):QDialog(parent),correspondance(QMap<QListWidgetItem*,Document*>())
{
    setWindowTitle("Ajouter une note à un document");
    NoteManager::Iterator it;
    for(it = NoteManager::getInstance().begin(); it != NoteManager::getInstance().end(); ++it){
        QString type = QString::fromStdString(typeid(*(*it)).name());
        type.remove(0,1);
        if (type=="Document" && (*it)->getId()!=n->getId()){
            box.addItem((*it)->getTitle(), QVariant((*it)->getId()));
        }
    }
    QPushButton* ok = new QPushButton("Ajouter");
    QObject::connect(ok, SIGNAL(clicked()), this, SLOT(ok()));
    QPushButton* cancel = new QPushButton("Annuler");
    QObject::connect(cancel, SIGNAL(clicked()), this, SLOT(cancel()));
    QHBoxLayout* hLayout = new QHBoxLayout;
    hLayout->addWidget(ok);
    hLayout->addWidget(cancel);
    QVBoxLayout* vLayout = new QVBoxLayout;
    vLayout->addWidget(&box);
    vLayout->addLayout(hLayout);
    setLayout(vLayout);
}

/**
 * @brief DocumentAddNoteDialog::cancel
 */
void DocumentAddNoteDialog::cancel()
{
    done(0);
}

/**
 * @brief DocumentAddNoteDialog::ok
 */

void DocumentAddNoteDialog::ok(){
    unsigned int noteId = box.itemData(box.currentIndex()).toUInt();
    document=dynamic_cast<Document*>(NoteManager::getInstance().getNote(noteId));
    done(1);
}

/**
 * @brief Workspace::clearAll
 */

void Workspace::clearAll()
{
    xmlfile->clear();
    model->clear();
    model->clear();
    viewer->setModel(model);
    emit clearOthers();
}

/**
 * @brief Workspace::clear
 */

void Workspace::clear()
{
    clearAll();
}
