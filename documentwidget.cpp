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
#include "exports.h"
#include <iostream>

DocumentWidget::DocumentWidget(Document* d, QWidget* parent):NoteWidget(parent),document(d)
{
    save = new QPushButton("Sauvegarder",this);
    exp = new QPushButton("Exporter",this);
    //fen = new QTextEdit(this);
    file = new QFile(this);
    file->setFileName("/Users/Antoine/Documents/ProjetInfo/Github/Notify_Github/test.txt");
    try
    {
        if(!file->open(QIODevice::WriteOnly))
            throw DocumentException("Ne parvient pas ouvrir le fichier");
    }
    catch(DocumentException& e)
    {
        QMessageBox::information(this,"Fatal Error",e.getInfo());
    }
    out = new QTextStream(file);
    try{
        if(d!=NULL)
        {
            title->setText(d->getTitle());
        }
        else
            throw DocumentException("L'article n'existe pas");
    } catch(DocumentException& e){
        QMessageBox::information(this,"Fatal Error",e.getInfo());
    }

    save->setEnabled(false);

    Document::Iterator it;
    for(it=d->begin() ; it!=d->end() ; ++it)
    {
        layout->addWidget((*it)->getWidget());
        QObject::connect((*it)->getWidget(),SIGNAL(mod()),this,SLOT(modification()));
    }
    QObject::connect(title,SIGNAL(textChanged(QString)),this,SLOT(modification()));
    //layout->addWidget(fen);
    layout->addWidget(save);
    layout->addWidget(exp);
    QObject::connect(save,SIGNAL(clicked()),this,SLOT(updateNote()));
    QObject::connect(exp,SIGNAL(clicked()),this,SLOT(giveExport()));
}

void DocumentWidget::updateNote()
{
    document->setTitle(title->text());
    Document::Iterator it;
    for(it=document->begin() ; it!=document->end() ; ++it)
        (*it)->getWidget()->updateNote();
    document->setModify(false);
}

void DocumentWidget::modification()
{
    document->setModify(true);
    emit mod();
}

void DocumentWidget::giveExport()
{
    QString h,f,c;
    Exports::SaveTextExport ste;

    h=ste.header(document);
    f=ste.footer(document);
    c=ste.exportNote(document,0);
    (*out)<<(const QString&)(h+c+f);
}
