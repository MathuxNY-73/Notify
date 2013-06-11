//
//  notes.cpp
//  LO21_Projet
//
//  Created by Anthony WEIBEL and Antoine POUILLAUDE on 07/05/13.
//  Copyright (c) 2013 Antoine POUILLAUDE. All rights reserved.
//

#include "note.h"
#include "article.h"
#include <fstream>
#include <QFile>

Note::Note(const QString& p):title(""), path(p), modified(false){}
Note::Note(unsigned int i, const QString& t):id(i),title(t),path(""),loaded(false),modified(false),item(0){}
Note::~Note()
{
    delete item;
}
