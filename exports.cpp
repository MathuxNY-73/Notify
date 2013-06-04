//
//  exports.cpp
//  LO21_Projet
//
//  Created by Anthony WEIBEL and Antoine POUILLAUDE on 02/06/13.
//  Copyright (c) 2013 Antoine POUILLAUDE. All rights reserved.
//

#include "exports.h"
#include "note.h"
#include "article.h"
#include "document.h"

using namespace Exports;

ExportStrategy::ExportStrategy(){}

QString TextExport::header(const Note& n){
    QString s;
    s="";
    return s;
}

QString TextExport::footer(const Note& n){
    QString s;
    s="";
    return s;
}

QString TextExport::exportNote(const Article& a, unsigned int tl){
    QString s;
    for(unsigned int i=0 ; i<tl ; i++)
        s+="    ";
    s=s+a.getTitle()+"\n";
    for(unsigned int i=0 ; i<tl+1 ; i++)
        s+="    ";
    s=s+a.getText()+"\n";
    return s;
}

QString TextExport::exportNote(const Document& d, unsigned int tl){
    QString s;
    for(unsigned int i=0 ; i<tl ; i++)
        s+="    ";
    s=s+d.getTitle()+"\n";
    Document::constIterator it;
    for(unsigned int i=0 ; i<tl+1 ; i++)
        s+="    ";
    for(it=d.begin() ; it!=d.end() ; ++it)
        s=s+(*it)->ExportAsPart(this, tl+1);        //A voir avec damien le Dieu de LO21 qui a eu 2 fucking points en plus.
    return s;
}