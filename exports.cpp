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
#include <typeinfo>


using namespace Exports;

ExportStrategy::ExportStrategy(){}

QMap<QString, ExportStrategy*> ExportStrategy::getExport(){
    QMap<QString, ExportStrategy*> map;
    map["text"]=new TextExport();
    map["TeX"]=new TeXExport();
    map["html"]=new HTMLExport();
    map["save"]=new SaveTextExport();
    return map;
}

//Export en text
QString TextExport::header(Note* n){
    QString s;
    s="Header ID : {"+QString::number(n->getId())+"} \n "
            "Title : {"+n->getTitle()+"} \n"
            "======================================== \n";
    return s;
}

QString TextExport::footer(Note* n){

    QString s;
    s="======================================== \n"
            "Footer \n"
            ""+QString::number(n->getId())+n->getTitle()+"\n\n\n";
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

QString TextExport::exportNote(Document* d, unsigned int tl){
    QString s;
    for(unsigned int i=0 ; i<tl ; i++)
        s+="    ";
    s=s+d->getTitle()+"\n";
    Document::Iterator it;
    for(unsigned int i=0 ; i<tl+1 ; i++)
        s+="    ";
    for(it=d->begin() ; it!=d->end() ; ++it)
        s=s+(*it)->ExportAsPart(this, tl+1);        
    return s;
}

QString TextExport::exportNote(Video* v, unsigned int tl){
    QString s,tab;
    for(unsigned int i=0 ; i<tl ; i++)
        tab+="    ";
    s=tab+v->getTitle()+"\n";
    s=s+tab+"    "+"path : "+v->getPath()+"\n";
    s=s+tab+"    "+"description : "+v->getDesc()+"\n";
    return s;
}

QString TextExport::exportNote(Image* i, unsigned int tl){
    QString s,tab;
    for(unsigned int j=0 ; j<tl ; j++)
        tab+="    ";
    s=tab+i->getTitle()+"\n";
    s=s+tab+"    "+"path : "+i->getPath()+"\n";
    s=s+tab+"    "+"description : "+i->getDesc()+"\n";
    return s;
}

QString TextExport::exportNote(Audio* a, unsigned int tl){
    QString s,tab;
    for(unsigned int j=0 ; j<tl ; j++)
        tab+="    ";
    s=tab+a->getTitle()+"\n";
    s=s+tab+"    "+"path : "+a->getPath()+"\n";
    s=s+tab+"    "+"description : "+a->getDesc()+"\n";
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
QString TeXExport::header(Note* n){
    QString s;
    //Definition du document en latex
    s="\\documentclass[a4paper, 12pt]{article} \n \n";
    
    //Inclure les packages
    s=s+"\\usepackage[T1]{fontenc} \n"
    "\\usepackage[utf8x]{inputenc} \n"
    "\\usepackage[french]{babel} \n"
    "\\usepackage{graphicx} \n";
    
    //Crée le titre du document
    s=s+"\\title{\\textsc{\\textbf{"+n->getTitle()+"}}} \n"
        "\\date{"+QString::number(n->getId())+"} \n \n";
    
    //On commence le document
    s=s+"\\begin{document} \n"
        "\\maketitle \n";
    return s;
}

QString TeXExport::footer(Note* n){
    QString s;
    s=" \n \\end{document} \n";
    return s;
}

QString TeXExport::exportNote(Article* a, unsigned int tl){
    QString s;
    s=docStruct(tl)+a->getTitle()+"} \n";
    s=s+a->getText()+"\n";
    return s;
}

QString TeXExport::exportNote(Document* d, unsigned int tl){
    QString s;
    s=docStruct(tl)+d->getTitle()+"} \n";
    Document::Iterator it;
    for(it=d->begin() ; it!=d->end() ; ++it)
        s=s+(*it)->ExportAsPart(this, tl+1);        
    return s;
}

QString TeXExport::exportNote(Video* v, unsigned int tl){
    QString s;
    s=docStruct(tl)+v->getTitle()+"} \n";
    s=s+"path : "+v->getPath()+"\n";
    s=s+"description : "+v->getDesc()+"\n";
    return s;
}

QString TeXExport::exportNote(Image* i, unsigned int tl){
    QString s;
    s="\\begin{figure} \n"
        "\\begin{center} \n";
    s=s+"\\includegraphics{"+i->getPath()+"} \n";
    s=s+"\\end{center} \n"
        "\\label{"+i->getTitle()+"} \n";
    s=s+"\\end{figure} \n";
    s=s+"\\textsc{\\textbf{Description}} :";
    s=s+i->getDesc()+"\n";
    return s;
}

QString TeXExport::exportNote(Audio* a, unsigned int tl){
    QString s;
    s=docStruct(tl)+a->getTitle()+"} \n";
    s=s+a->getPath()+"\n";
    s=s+"description : "+a->getDesc()+"\n";
    return s;
}


//TODO
//Export en HTML
QString HTMLExport::header(Note* n){
    QString s;
    //Definition du document en HTML
    s="<!DOCTYPE html> \n"
        "<html lang='fr'>";
    s=s+"<head> \n"
        "<meta charset='utf-8'> \n"
        "<title>"+n->getTitle()+"</title> \n";
    
    //Debut du corps
    s=s+"</head> \n"
        "<body> \n";

    return s;
}

QString HTMLExport::footer(Note* n){
    QString s;
    s="</body> \n"
        "</html> \n";
    return s;
}

QString HTMLExport::exportNote(Article* a, unsigned int tl){
    QString s,indent="";
    for(unsigned int i=0 ; i<tl ; i++)
        indent+="    ";
    if(tl>=6)
        tl=6;
    s=indent+"<h"+(QString)tl+">"+a->getTitle()+"</h"+(QString)tl+"> \n";
    s=s+indent+"<p>\n    "+a->getText()+"\n</p>";
    return s;
}

QString HTMLExport::exportNote(Document* d, unsigned int tl){
    QString s,indent="";
    for(unsigned int i=0 ; i<tl ; i++)
        indent+="    ";
    if(tl>=6)
        tl=6;
    s=indent+"<h"+(QString)tl+">"+d->getTitle()+"</h"+(QString)tl+"> \n";
    Document::Iterator it;
    for(it=d->begin() ; it!=d->end() ; ++it)
        s=s+(*it)->ExportAsPart(this, tl+1);        
    return s;
}

QString HTMLExport::exportNote(Video* v, unsigned int tl){
    QString s,indent="";
    for(unsigned int i=0 ; i<tl ; i++)
        indent+="    ";
    s=indent+"<p> \n";
    s=s+indent+"<a href=file://"+v->getPath()+">"+v->getTitle()+"</a> \n";
    s=s+indent+" \n Description : \n"+v->getDesc()+"\n </p> \n";
    return s;
}

QString HTMLExport::exportNote(Image* i, unsigned int tl){
    QString s,indent="";
    for(unsigned int i=0 ; i<tl ; i++)
        indent+="    ";
    if(tl>=6)
        tl=6;
    s=indent+"<h"+(QString)tl+">"+i->getTitle()+"</h"+(QString)tl+"> \n";
    s=s+indent+"<p> \n";
    s=s+indent+"    "+"<img src=file://"+i->getPath()+"> \n";
    s=s+indent+"Description : \n"+i->getDesc()+"\n </p> \n";
    return s;
}

QString HTMLExport::exportNote(Audio* a, unsigned int tl){
    QString s,indent="";
    for(unsigned int i=0 ; i<tl ; i++)
        indent+="    ";
    s=indent+"<p> /n";
    s=s+indent+"<a href=file://"+a->getPath()+">"+a->getTitle()+"</a> \n";
    s=s+indent+"Description : \n"+a->getDesc()+"\n </p> \n";
    return s;
}

//Export SaveText

QString SaveTextExport::header(Note* n){
    QString s;
    s=""+QString::fromStdString(typeid(*n).name())+"\n"
            ">"+QString::number(n->getId())+"\n"
            ">"+n->getTitle()+"\n"
            ">>>>>>>>>>>>BEGIN";
    return s;
}

QString SaveTextExport::footer(Note* n){

    QString s;
    s=">>>>>>>>>>>>END \n"
            ">"+QString::number(n->getId())+"\n";
    return s;
}

QString SaveTextExport::exportNote(Article* a, unsigned int tl){
    QString s,indent="";
    for(unsigned int i=0 ; i<tl ; i++)
        indent+=">>>>";
    s=s+indent+a->getText()+"\n";
    return s;
}

QString SaveTextExport::exportNote(Document* d, unsigned int tl){
    QString s,indent="";
    for(unsigned int i=0 ; i<tl+1 ; i++)
        indent+=">>>>";
    Document::Iterator it;
    for(it=d->begin() ; it!=d->end() ; ++it)
        s=s+indent+QString::number((*it)->getId())+"\n";
    return s;
}

QString SaveTextExport::exportNote(Video* v, unsigned int tl){
    QString s,tab;
    for(unsigned int i=0 ; i<tl ; i++)
        tab+=">>>>";
    s=s+tab+v->getPath()+"\n";
    s=s+tab+v->getDesc()+"\n";
    return s;
}

QString SaveTextExport::exportNote(Image* i, unsigned int tl){
    QString s,tab;
    for(unsigned int j=0 ; j<tl ; j++)
        tab+=">>>>";
    s=s+tab+i->getPath()+"\n";
    s=s+tab+i->getDesc()+"\n";
    return s;
}

QString SaveTextExport::exportNote(Audio* a, unsigned int tl){
    QString s,tab;
    for(unsigned int j=0 ; j<tl ; j++)
        tab+=">>>>";
    s=s+tab+a->getPath()+"\n";
    s=s+tab+a->getDesc()+"\n";
    return s;
}
