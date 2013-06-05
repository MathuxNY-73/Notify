//
//  main.cpp
//  LO21_Projet
//
//  Created by Anthony WEIBEL and Antoine POUILLAUDE on 07/05/13.
//  Copyright (c) 2013 Antoine POUILLAUDE. All rights reserved.
//

#include <iostream>
#include "note.h"
#include "article.h"
#include "document.h"
#include "binary.h"
#include "notemanager.h"
#include "notewidget.h"
#include "articlewidget.h"
#include <QString>

int main(int argc, char *argv[])
{
    //Ici les tests
    Article a1(1,"Ceci est un titre","Ceci est du texte");
    std::cout<<(a1.getTitle()).toStdString()<<"\n";
    Document d1(2,"Titre du document");
    d1.removeSubNote(2);
    /*try{
        std::cout<<((d1.Document::getSubNote(5))->getTitle()).toStdString()<<"\n"; Provoque une erreur, il faudrait trouver une meilleure solution pour gérer l'erreur car l'erreur vient en effet du fait (alliteration en "f") que l'on renvoie le pointeur NULL. 
    }
    catch (NotesException& n){
        
    }*/
    
    std::cout<<(d1.getTitle()).toStdString()<<"\n";
    d1.addSubNote(&a1);
    std::cout<<((d1.Document::getSubNote(1))->getTitle()).toStdString()<<"\n";
    //std::cout<<((d1.Document::getSubNote(3))->getTitle()).toStdString()<<"\n";
    d1.addSubNote(&d1,2);
    d1.addSubNote(&d1);
    d1.removeSubNote(3);
    d1.removeSubNote(2);
    d1.removeSubNote(1);
    Video v1(3,"Ceci est une video","Video de chats","/home/video/video de chatons.avi");
    d1.addSubNote(&v1);
    std::cout<<((d1.Document::getSubNote(3))->getTitle()).toStdString()<<"\n";  //Remarque : à partir d'un document il nous est impossible de récupérer "desc" et "path" car getSubNote renvoie Note*.
    Image i1(4,"Ceci est une image","Image d'avion","/home/images/airbusa380.avi");
    d1.addSubNote(&i1,4);
    NoteManager* nm1;
    nm1 = NoteManager::getInstance();
    nm1->addNote(&d1);
    nm1->addNote(&a1);
    nm1->deleteNote(&d1);
    std::cout<<(nm1->getFilename(2)).toStdString()<<"\n";
    std::cout<<(nm1->getFilename(1)).toStdString()<<"\n";
    try{
        NoteManager* nm2;
        nm2=NoteManager::getInstance();
        if(nm2==nm1)
        {
            nm2->releaseInstance();
            throw NoteManagerException("An instance of NoteManager already exists");
        }
    }
    catch ( NoteManagerException &e){
        std::cout<<"Fatal Error:"<<e.getInfo().toStdString()<<"\n";
    }
    nm1->releaseInstance();
    std::cout<<(a1.getTitle()).toStdString()<<"\n";

    QApplication app(argc, argv);
    ArticleWidget aw(&a1);
    aw.show();

    return app.exec();
}
