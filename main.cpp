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
#include <QString>

int main(int argc, char *argv[])
{
    //Ici les tests
    Article a1(1,"Ceci est un titre","Ceci est du texte");
    std::cout<<(a1.getTitle()).toStdString()<<"\n";
    Document d1(2,"Titre du document");
    std::cout<<(d1.getTitle()).toStdString()<<"\n";
    d1.addSubNote(&a1);
    std::cout<<((d1.Document::getSubNote(1))->getTitle()).toStdString()<<"\n";
    d1.addSubNote(&d1,2);
    d1.addSubNote(&d1);
    d1.removeSubNote(3);
    d1.removeSubNote(2);
    d1.removeSubNote(1);
    return 0;

}
