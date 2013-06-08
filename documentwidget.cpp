//
//  documentwidget.cpp
//  LO21_Projet
//
//  Created by Anthony WEIBEL and Antoine POUILLAUDE on 07/05/13.
//  Copyright (c) 2013 Antoine POUILLAUDE. All rights reserved.
//

#include "documentwidget.h"
#include "document.h"
#include "notewidget.h"

DocumentWidget::DocumentWidget(Document* d, QWidget* parent):NoteWidget(parent),document(d)
{
    save = new QPushButton("Sauvegarder",this);
    try{
        if(d!=NULL)
        {
            title->setText(d->getTitle());
        }
        else
            throw DocumentException("L'article n'existe pas");
    } catch(DocumentException& e){
        std::cout<<"Fatal Error:"<<e.getInfo().toStdString()<<"\n";
    }

    save->setEnabled(false);

    Document::Iterator it;
    for(it=d->begin() ; it!=d->end() ; ++it)
    {
        layout->addWidget((*it)->getWidget());
        QObject::connect((*it)->getWidget(),SIGNAL(isModified()),this,SLOT(modification()));
    }
    QObject::connect(title,SIGNAL(textChanged(QString)),this,SLOT(modification()));
    layout->addWidget(save);
    QObject::connect(save,SIGNAL(clicked()),this,SLOT(updateNote()));
}

void DocumentWidget::updateNote()
{
    QMessageBox::information(this, "Sauvegarde", "Votre document a bien été sauvegardé...");
    save->setEnabled(false);
}

void DocumentWidget::modification()
{
    save->setEnabled(true);
    document->setModify(true);
    emit isModified();
}

