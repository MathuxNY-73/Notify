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
#include "binary.h"

using namespace Exports;

ExportStrategy::ExportStrategy(){}


//Export en text
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

QString TextExport::exportNote(const Video& v, unsigned int tl){
    QString s,tab;
    for(unsigned int i=0 ; i<tl ; i++)
        tab+="    ";
    s=tab+v.getTitle()+"\n";     
    s=s+tab+"    "+"path : "+v.getPath()+"\n";
    s=s+tab+"    "+"description : "+v.getDesc()+"\n";
    return s;
}

QString TextExport::exportNote(const Image& i, unsigned int tl){
    QString s,tab;
    for(unsigned int j=0 ; j<tl ; j++)
        tab+="    ";
    s=tab+i.getTitle()+"\n";
    s=s+tab+"    "+"path : "+i.getPath()+"\n";
    s=s+tab+"    "+"description : "+i.getDesc()+"\n";
    return s;
}

QString TextExport::exportNote(const Audio& a, unsigned int tl){
    QString s,tab;
    for(unsigned int j=0 ; j<tl ; j++)
        tab+="    ";
    s=tab+a.getTitle()+"\n";
    s=s+tab+"    "+"path : "+a.getPath()+"\n";
    s=s+tab+"    "+"description : "+a.getDesc()+"\n";
    return s;
}

//Fonction qui permet de sortir les niveaux des parties
QString TeXExport::docStruct(unsigned int i) const{
    QString s;
    switch (i) {
        case 0:
            s="\\part{";
            break;
        case 1:
            s="\\section{";
            break;
        case 2:
            s="\\subsection{";
            break;
        case 3:
            s="\\subsubsection{";
            break;
        case 4:
            s="\\paragraph{";
            break;
        case 5:
            s="\\subparagraph{";
            break;
        default:
            s="\\subparagraph{";
    }
    return s;
}

//Export en LateX
QString TeXExport::header(const Note& n){
    QString s;
    //Definition du document en latex
    s="\\documentclass[a4paper, 12pt, leqno]{arcticle}";
    
    //Inclure les packages
    s=s+"\\usepackage[T1]{fontenc} \n"
    "\\usepackage[utf8x]{inputenc} \n"
    "\\usepackage[french]{babel} \n"
    "\\usepackage{graphicx} \n";
    
    //Crée le titre du document
    s=s+"\\title{\\textsc{\\textbf{"+n.getTitle()+"}}} \n"
        "\\date{"+n.getId()+"} \n";
    
    //On commence le document
    s=s+"\\begin{document} \n"
        "\\maketitle \n";
    return s;
}

QString TeXExport::footer(const Note& n){
    QString s;
    s="\\end{document} \n";
    return s;
}

QString TeXExport::exportNote(const Article& a, unsigned int tl){
    QString s;
    s=docStruct(tl)+a.getTitle()+"} \n";
    s=s+a.getText()+"\n";
    return s;
}

QString TeXExport::exportNote(const Document& d, unsigned int tl){
    QString s;
    s=docStruct(tl)+d.getTitle()+"} \n";
    Document::constIterator it;
    for(it=d.begin() ; it!=d.end() ; ++it)
        s=s+(*it)->ExportAsPart(this, tl+1);        //A voir avec damien le Dieu de LO21 qui a eu 2 fucking points en plus.
    return s;
}

QString TeXExport::exportNote(const Video& v, unsigned int tl){
    QString s;
    s=docStruct(tl)+v.getTitle()+"} \n";
    s=s+"path : "+v.getPath()+"\n";
    s=s+"description : "+v.getDesc()+"\n";
    return s;
}

QString TeXExport::exportNote(const Image& i, unsigned int tl){
    QString s;
    s="\\begin{figure} \n"
        "\\begin{center} \n";
    s=s+"\\includegraphics{"+i.getPath()+"} \n";
    s=s+"\\end{center} \n"
        "\\label{"+i.getTitle()+"} \n";
    s=s+"\\end{figure} \n";
    s=s+"\\textsc{\\textbf{Description}} :";
    s=s+i.getDesc()+"\n";
    return s;
}

QString TeXExport::exportNote(const Audio& a, unsigned int tl){
    QString s;
    s=docStruct(tl)+a.getTitle()+"} \n";
    s=s+"path : "+a.getPath()+"\n";
    s=s+"description : "+a.getDesc()+"\n";
    return s;
}


//TODO
//Export en HTML
//Export SaveText
