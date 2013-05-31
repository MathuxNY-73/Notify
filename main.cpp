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
#include <QString>

int main(int argc, char *argv[])
{
    //Ici les tests
    Article a1(1,"Ceci est un titre","Ceci est du texte");
    std::cout<<(a1.getTitle()).toStdString();
    return 0;

}
