//
//  article.cpp
//  LO21_Projet
//
//  Created by Anthony WEIBEL and Antoine POUILLAUDE on 07/05/13.
//  Copyright (c) 2013 Antoine POUILLAUDE. All rights reserved.
//

#include "article.h"
#include <fstream>
#include <QFile>
//#include "notefactory.h"


void Article::setText(const QString& t) {
    modified=true; text=t;
}

QString Article::ExportAsPart(Exports::ExportStrategy* es, unsigned int tl) const
{
    return es->exportNote(*this,tl);
}


