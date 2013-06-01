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
    Video v1(3,"Ceci est une video","Video de chat","/home/video/chaton.avi");
    d1.addSubNote(&v1);
    std::cout<<((d1.Document::getSubNote(3))->getTitle()).toStdString()<<"\n";  //Remarque : à partir d'un document il nous est impossible de récupérer "desc" et "path" car getSubNote renvoie Note*.
    return 0;

}
