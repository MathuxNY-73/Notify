//
//  workspace.cpp
//  LO21_Projet
//
//  Created by Anthony WEIBEL and Antoine POUILLAUDE on 09/06/13.
//  Copyright (c) 2013 Antoine POUILLAUDE. All rights reserved.
//

#include "editorspace.h"
#include "exports.h"
#include <iostream>

/*Editorspace::Editorspace(QWidget* parent):QWidget(parent)
{
    onglets = new QTabWidget(this);
    layout = new QVBoxLayout(this);
    editor= new QSet<Note*>();

    //Editeurs
    HEdit = new QTextEdit(this);
    TXEdit = new QTextEdit(this);
    TxtEdit = new QTextEdit(this);

    //Layout
    layout_HTML= new QVBoxLayout(onglets);
    layout_TeX= new QVBoxLayout(onglets);
    layout_Text= new QVBoxLayout(onglets);
    /*layout_HTML->setSizeConstraint(QLayout::SetFixedSize);
    layout_TeX->setSizeConstraint(QLayout::SetFixedSize);
    layout_Text->setSizeConstraint(QLayout::SetFixedSize);


    //Ajout des editeurs aux layouts
    layout_HTML->addWidget(HEdit);
    layout_TeX->addWidget(TXEdit);
    layout_Text->addWidget(TxtEdit);

    //Déclaration de scrolling
    scroll_HTML= new QScrollArea(this);
    scroll_TeX= new QScrollArea(this);
    scroll_Text= new QScrollArea(this);
    scroll_Editor= new QScrollArea(this);

    //Configuration des scrolls
    scroll_HTML->setWidgetResizable(true);
    scroll_TeX->setWidgetResizable(true);
    scroll_Text->setWidgetResizable(true);
    scroll_Editor->setWidgetResizable(true);

    //Ajout des Widgets aux scrollAera
    scroll_HTML->setWidget(HEdit);
    scroll_TeX->setWidget(TXEdit);
    scroll_Text->setWidget(TxtEdit);

    //Mise en conteneur
    onglets->addTab(scroll_Editor,"Editor");
    onglets->addTab(scroll_HTML,"HTML");
    onglets->addTab(scroll_TeX,"TeX");
    onglets->addTab(scroll_Text,"Text");

    layout->addWidget(onglets);
}*/

Editorspace::Editorspace(NoteManager* nm,QWidget* parent):QWidget(parent),noteM(nm)
{
    onglets = new QTabWidget(this);
    layout = new QVBoxLayout(this);
    container = new QFrame();

    //Editeurs
    HEdit = new QTextEdit(this);
    TXEdit = new QTextEdit(this);
    TxtEdit = new QTextEdit(this);
    HEdit->setReadOnly(true);
    TXEdit->setReadOnly(true);
    TxtEdit->setReadOnly(true);

    //Layout
    layout_HTML= new QVBoxLayout(onglets);
    layout_TeX= new QVBoxLayout(onglets);
    layout_Text= new QVBoxLayout(onglets);
    layout_Editor= new QVBoxLayout(container);
    /*layout_HTML->setSizeConstraint(QLayout::SetFixedSize);
    layout_TeX->setSizeConstraint(QLayout::SetFixedSize);
    layout_Text->setSizeConstraint(QLayout::SetFixedSize);
    */

    //Ajout des editeurs aux layouts
    layout_HTML->addWidget(HEdit);
    layout_TeX->addWidget(TXEdit);
    layout_Text->addWidget(TxtEdit);

    //Déclaration de scrolling
    scroll_HTML= new QScrollArea(this);
    scroll_TeX= new QScrollArea(this);
    scroll_Text= new QScrollArea(this);
    scroll_Editor= new QScrollArea(this);

    //Configuration des scrolls
    scroll_HTML->setWidgetResizable(true);
    scroll_TeX->setWidgetResizable(true);
    scroll_Text->setWidgetResizable(true);
    scroll_Editor->setWidgetResizable(true);

    //Ajout des Widgets aux scrollAera
    scroll_HTML->setWidget(HEdit);
    scroll_TeX->setWidget(TXEdit);
    scroll_Text->setWidget(TxtEdit);
    scroll_Editor->setWidget(container);

    //Mise en conteneur
    onglets->addTab(scroll_Editor,"Editor");
    onglets->addTab(scroll_HTML,"HTML");
    onglets->addTab(scroll_TeX,"TeX");
    onglets->addTab(scroll_Text,"Text");

    layout->addWidget(onglets);

    //Ajout des widgets dans l'editeur
    NoteManager::Iterator it;
    for(it=noteM->begin();it!=noteM->end() ; ++it)
        layout_Editor->addWidget((*it)->getWidget());

    //Création des connexions
    QObject::connect(onglets,SIGNAL(currentChanged(int)),this,SLOT(changementOnglet(int)));
}

void Editorspace::changementOnglet(int i)
{
    NoteManager::Iterator it;
    for(it=noteM->begin();it!=noteM->end() ; ++it)
        (*it)->getWidget()->updateNote();
    QString s="";
    Exports::ExportStrategy* es;
    switch(i)
    {
    case 1:
        es=noteM->getStrategy("html");
        if(es==0)
        {
            HEdit->setText("Cet export n'existe pas");
            break;
        }
        for(it=noteM->begin();it!=noteM->end() ; ++it)
            s+=(*it)->ExportNote(es);
        HEdit->setText(s);
        break;
    case 2:
        es=noteM->getStrategy("TeX");
        if(es==0)
        {
            TXEdit->setText("Cet export n'existe pas");
            break;
        }
        for(it=noteM->begin();it!=noteM->end() ; ++it)
            s+=(*it)->ExportNote(es);
            TXEdit->setText(s);
        break;
    case 3:
        es=noteM->getStrategy("text");
        if(es==0)
        {
            TxtEdit->setText("Cet export n'existe pas");
            break;
        }
        for(it=noteM->begin();it!=noteM->end() ; ++it)
            s+=(*it)->ExportNote(es);
            TxtEdit->setText(s);
        break;
    }
}
