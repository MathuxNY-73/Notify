//
//  NoteWidget.cpp
//  LO21_Projet
//

#include "notewidget.h"


NoteWidget::NoteWidget(QWidget *parent):QWidget(parent)
{
    title = new QLineEdit("titre",this);
    layout = new QVBoxLayout(this);
    hlayout = new QHBoxLayout();
    directory = new QLabel("/",this);
    root = new QPushButton("..",this);
    hlayout->addWidget(root);
    hlayout->addWidget(directory);
    hlayout->addWidget(title);
    root->setMaximumWidth(80);
    layout->addLayout(hlayout);
    this->setLayout(layout);

    QObject::connect(title,SIGNAL(textChanged(QString)),this,SLOT(titleChanged(QString)));
}

void NoteWidget::titleChanged(QString q)
{
    getNote()->setTitle(q);
    emit changeTitle(q);
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
