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

QString TextExport::header(Note* n){
    QString s;
    s="Voici le header";
    return s;
}

QString TextExport::footer(Note* n){
    QString s;
    s="Voici le footer";
    return s;
}

QString TextExport::exportNote(Article* a, unsigned int tl){
    QString s;
    for(unsigned int i=0 ; i<tl ; i++)
        s+="    ";
    s=s+a->getTitle()+"\n";
    for(unsigned int i=0 ; i<tl+1 ; i++)
        s+="    ";
    s=s+a->getText()+"\n";
    return s;
}

/*QString TextExport::exportNote(Document* d, unsigned int tl){     Je ne voie pas comment l'implémenter.
    QList<Note*>::const_iterator it;
    for(it=d->notes.begin() ; it!=d->notes.end() ; ++it)
        
}*/