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
<<<<<<< HEAD
#include "notefactory.h"
=======
#include "binarywidget.h"
#include "editorspace.h"
#include "mainwindow.h"
#include <QSet>
>>>>>>> Graphix
#include <QString>

/**
 * @fn  int main(int argc, char *argv[])
 * @brief Fonction main
 * @param argc
 * @param argv
 * @return
 */

int main(int argc, char *argv[])
{
<<<<<<< HEAD
    QMap<QString,NoteFactory*> map;
    Article a1(1,"Titre de l'article","Texte de l'article");
    Article a2(2,"Titre de l'article 2","Texte de l'article 2");
    Document d1(3,"Titre du document");
    d1.addSubNote(&a1);
    d1.addSubNote(&a2);

    map=NoteFactory::getFactories();
=======
    QApplication app(argc, argv);
    MainWindow m;
    m.show();
>>>>>>> Graphix

    Article* a3 = map["Article"]->buildNoteCopy(&a1);
    std::cout<<a3->getId()<<"   "<<a3->getText().toStdString()<<"    "<<a3->getText().toStdString()<<"\n";


    return 0;
}
