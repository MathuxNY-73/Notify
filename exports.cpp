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

QMap<QString, ExportStrategy*> ExportStrategy::getExport(){
    QMap<QString, ExportStrategy*> map;
    map["text"]=new TextExport();       //J'ai une erreur ici qui me dit que je ne peut pas allouer de l'espace sur des classe abstraites et je pense que cela est dû à l'erreur ennoncé précédement dans l'exports.h
    map["TeX"]=new TeXExport();
    //map["html"]=new HTMLExport();
    return map;
}

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
        s=s+(*it)->ExportAsPart(this, tl+1);        
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
    s="\\documentclass[a4paper, 12pt]{arcticle}";
    
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
        s=s+(*it)->ExportAsPart(this, tl+1);        
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
QString HTMLExport::header(const Note& n){
    QString s;
    //Definition du document en HTML
    s="<!DOCTYPE html> \n"
        "<html lang='fr'>";
    s=s+"<head> \n"
        "<meta charset='utf-8'> \n"
        "<title>"+n.getTitle()+"</title>";
    
    //Debut du corps
    s=s+"</head> \n"
        "<body> \n";
    
    //Crée le titre du document
    s=s+"\\title{\\textsc{\\textbf{"+n.getTitle()+"}}} \n"
    "\\date{"+n.getId()+"} \n";
    
    //On commence le document
    s=s+"\\begin{document} \n"
    "\\maketitle \n";
    return s;
}

QString HTMLExport::footer(const Note& n){
    QString s;
    s="</body> \n"
        "</html> \n";
    return s;
}

QString HTMLExport::exportNote(const Article& a, unsigned int tl){
    QString s,indent="";
    for(unsigned int i=0 ; i<tl ; i++)
        indent+="    ";
    if(tl>=6)
        tl=6;
    s=indent+"<h"+(QString)tl+">"+a.getTitle()+"</h"+(QString)tl+">";
    s=s+indent+"    <p>"+a.getText()+"</p> \n";
    return s;
}

QString HTMLExport::exportNote(const Document& d, unsigned int tl){
    QString s,indent="";
    for(unsigned int i=0 ; i<tl ; i++)
        indent+="    ";
    if(tl>=6)
        tl=6;
    s=indent+"<h"+(QString)tl+">"+d.getTitle()+"</h"+(QString)tl+">";
    Document::constIterator it;
    for(it=d.begin() ; it!=d.end() ; ++it)
        s=s+(*it)->ExportAsPart(this, tl+1);        
    return s;
}

/*QString HTMLExport::exportNote(const Video& v, unsigned int tl){
    QString s;
    s=docStruct(tl)+v.getTitle()+"} \n";
    s=s+"path : "+v.getPath()+"\n";
    s=s+"description : "+v.getDesc()+"\n";
    return s;
}*/

QString HTMLExport::exportNote(const Image& i, unsigned int tl){
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

/*QString HTMLExport::exportNote(const Audio& a, unsigned int tl){
    QString s;
    s=docStruct(tl)+a.getTitle()+"} \n";
    s=s+"path : "+a.getPath()+"\n";
    s=s+"description : "+a.getDesc()+"\n";
    return s;
}*/
//Export SaveText
