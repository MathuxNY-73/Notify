//
//  NoteWidget.cpp
//  LO21_Projet
//

#include "notewidget.h"
#include "workspace.h"

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

void NoteWidget::titleChanged(QString q)
{
    getNote()->setTitle(q);
    getNote()->getItem()->setText(q);
}

void NoteWidget::updateNote()
{
    getNote()->setTitle(title->text());
}

NoteWidget::~NoteWidget()
{
    delete title;
    delete root;
    delete directory;
    delete hlayout;
    delete layout;
}

void NoteWidget::choseDoc(){
    Workspace::getInstance().rootChange(note);
}

void NoteWidget::tagAssociation()
{
    Tags::TagManagerWidget::getInstance().setAssociation(note);
}

void NoteWidget::unTagAssociation()
{
    Tags::TagManagerWidget::getInstance().deleteAssociation(note);
}
