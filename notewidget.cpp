//
//  NoteWidget.cpp
//  LO21_Projet
//

#include "notewidget.h"
#include "workspace.h"

/**
 * \fn  NoteWidget::NoteWidget(Note* n,QWidget *parent)
 * \brief Constructeur d'un widget associé à une note
 * \param Note associée au Widget
 * \param Widget parent de celui créé.'NULL' par défaut.
 */
NoteWidget::NoteWidget(Note* n,QWidget *parent):QWidget(parent),note(n)
{
    title = new QLineEdit("titre",this);
    layout = new QVBoxLayout(this);
    hlayout = new QHBoxLayout();
    hlayoutTag=new QHBoxLayout();
    directory = new QLabel("/",this);
    root = new QPushButton("..",this);
    tag= new QPushButton("Tag",this);
    untag= new QPushButton("Untag",this);
    hlayout->addWidget(root);
    hlayout->addWidget(directory);
    hlayout->addWidget(title);
    root->setMaximumWidth(80);
    layout->addLayout(hlayout);

    hlayoutTag->addWidget(tag);
    hlayoutTag->addWidget(untag);

    layout->addLayout(hlayoutTag);
    untag->setMaximumWidth(85);
    untag->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
    tag->setMaximumWidth(85);
    tag->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
    this->setLayout(layout);


    QObject::connect(root,SIGNAL(clicked()),this,SLOT(choseDoc()));
    QObject::connect(title,SIGNAL(textChanged(QString)),this,SLOT(titleChanged(QString)));
    QObject::connect(tag,SIGNAL(clicked()),this,SLOT(tagAssociation()));
    QObject::connect(untag,SIGNAL(clicked()),this,SLOT(unTagAssociation()));
}

/**
 * \fn NoteWidget::~NoteWidget()
 * \brief Destructeur du widget de note
 */
NoteWidget::~NoteWidget()
{
    delete title;
    delete root;
    delete directory;
    delete hlayout;
    delete layout;
}

/**
 * \fn void NoteWidget::updateNote()
 * \brief Slot qui permet de mettre la note à jour.
 */
void NoteWidget::updateNote()
{
    getNote()->setTitle(title->text());
}

/**
 * \fn void NoteWidget::tagAssociation()
 * \brief Créer une association
 *Slot appelé lorsque l'utilisateur appuie sur le bouton 'tag'. Il permet de faire appelle à la fonction que permettra de tagger la note.
 */
void NoteWidget::tagAssociation()
{
    Tags::TagManagerWidget::getInstance().setAssociation(note);
}

/**
 * \fn  void NoteWidget::unTagAssociation()
 * \brief Defaire une association
 *  Slot qui permet de faire appelle à la fonction qui supprimera l'association entre les tags et la note.
 */
void NoteWidget::unTagAssociation()
{
    Tags::TagManagerWidget::getInstance().deleteAssociation(note);
}

/**
 * \fn void NoteWidget::titleChanged(QString q)
 * \brief Slot qui met à jour le titre de la note associée au widget.
 * \param Titre modifié.
 */
void NoteWidget::titleChanged(QString q)
{
    getNote()->setTitle(q);
    getNote()->getItem()->setText(q);
}

/**
 * \fn void NoteWidget::choseDoc()
 * \brief Choisir document racine
 *Ce slot est appelé lorsque l'utilisateur clique sur le bouton '..'. Elle permet de faire appelle à la fonction qui permet de
 *choisir le document auquel on souhaite associer la note.
 */
void NoteWidget::choseDoc(){
    Workspace::getInstance().rootChange(note);
}
