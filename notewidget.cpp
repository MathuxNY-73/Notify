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
    directory = new QLabel("/",this);
    root = new QPushButton("..",this);
    tag= new QPushButton("Tag",this);
    hlayout->addWidget(root);
    hlayout->addWidget(directory);
    hlayout->addWidget(title);
    root->setMaximumWidth(80);
    layout->addLayout(hlayout);
    layout->addWidget(tag);
    tag->setMaximumWidth(85);
    tag->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
    this->setLayout(layout);


    QObject::connect(root,SIGNAL(clicked()),this,SLOT(choseDoc()));
    QObject::connect(title,SIGNAL(textChanged(QString)),this,SLOT(titleChanged(QString)));
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
