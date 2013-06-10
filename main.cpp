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
#include "binarywidget.h"
#include "editorspace.h"
#include "mainwindow.h"
#include <QSet>
#include <QString>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow m;
    m.show();
    /*QSet<Note*> set;
    QApplication app(argc, argv);
    // QWidget fenetre;
    //QVBoxLayout la(&fenetre);
    NoteManager* nm;
    nm = NoteManager::getInstance();
    Article a2(3,"Titre article 2", "Contenu article 2");
    Article a1(1,"Titre article","Contenu article");
    Article a3(4,"Titre article 3", "Contenu article 3");
    Article a4(5,"Titre article 4","Contenu article 4");
    Audio ad1(6,"Titre du fichier audio", "Ce fichier contient une chanson","~/Audio/chattons.wav");
    Image i1(7,"Titre de l'image", "Ce fichier est une image","./Icons/Qt_logo.png");
    Video v1(8,"Titre de la video","Ce fichier est une video","~/Movies/The Dark Knight.avi");
    Document d1(2,"Titre du document");
    d1.addSubNote(&a1);
    d1.addSubNote(&a2);
    d1.addSubNote(&a3);
    d1.addSubNote(&v1);
    d1.addSubNote(&a4);
    d1.addSubNote(&ad1);
    //d1.addSubNote(&i1);
    nm->addNote(&a1);
    nm->addNote(&a2);
    nm->addNote(&a3);
    nm->addNote(&v1);
    nm->addNote(&a4);
    nm->addNote(&ad1);
    nm->addNote(&i1);
    nm->addNote(&d1);

    Editorspace ws;
    ws.setWorkspace(nm);
    //ArticleWidget aw(&a1);
    //ImageWidget iw(&i1);
    //DocumentWidget dw(&d1);
    //AudioWidget aw(&ad1);
    //VideoWidget vw(&v1);


    ws.show();*/

    return app.exec();
}
