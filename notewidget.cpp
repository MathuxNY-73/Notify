//
//  NoteWidget.cpp
//  LO21_Projet
//

#include "notewidget.h"


NoteWidget::NoteWidget(QWidget *parent):QWidget(parent)
{
    title = new QLineEdit("titre",this);
    layout = new QVBoxLayout(this);
    glayout = new QGridLayout();
    root = new QPushButton("..",this);
    glayout->addWidget(root,0,0,1,1);
    glayout->addWidget(title,0,1,1,5);
    layout->addLayout(glayout);
    this->setLayout(layout);

    QObject::connect(title,SIGNAL(textChanged(QString)),this,SLOT(titleChanged(QString)));
    layout->addWidget(title);
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
    delete glayout;
    delete layout;
    delete root;
}
