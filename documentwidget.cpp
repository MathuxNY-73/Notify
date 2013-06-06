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
    Document::Iterator it;
    for(it=d->begin() ; it!=d->end() ; ++it)
        layout->addWidget((*it)->getWidget());
}
