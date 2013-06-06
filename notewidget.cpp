//
//  NoteWidget.cpp
//  LO21_Projet
//

#include "notewidget.h"

NoteWidget::NoteWidget(QWidget *parent):QWidget(parent)
{
    title = new QLineEdit("titre",this);
    layout = new QVBoxLayout(this);
    layout->addWidget(title);
    this->setLayout(layout);
    QObject::connect(title,SIGNAL(textChanged(QString)),this,SLOT(titleChanged(QString)));


}

void NoteWidget::titleChanged(QString q)
{}

void NoteWidget::updateNote()
{
    getNote()->setTitle(title->text());
}