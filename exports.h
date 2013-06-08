//
//  exports.h
//  LO21_Projet
//
//  Created by Anthony WEIBEL and Antoine POUILLAUDE on 02/06/13.
//  Copyright (c) 2013 Antoine POUILLAUDE. All rights reserved.
//

#ifndef EXPORTS_H
#define EXPORTS_H

#include <QString>
#include <QTextStream>
#include "note.h"

//#include "notewidget.h"

class Article;
class Document;
class Binary;
class Video;
class Image;
class Audio;


namespace Exports{

    
    //Mise en place du design pattern strategy et template methods
    class ExportStrategy{
        
    private:
        
    public:
        //Constructeurs
        ExportStrategy();
        
        //Methodes inlines
        
        //Méthodes non-inlines
        static QMap<QString, ExportStrategy*> getExport();
        
        //Méthode virtuelles
        virtual QString header(Note* n) =0;
        virtual QString footer(Note* n) =0;
        virtual QString exportNote(Article* n, unsigned int tl=0) =0;
        virtual QString exportNote(Document* n, unsigned int tl=0) =0;
        virtual QString exportNote(Audio* n, unsigned int tl=0) =0;
        virtual QString exportNote(Video* n, unsigned int tl=0) =0;
        virtual QString exportNote(Image* n, unsigned int tl=0) =0;
    };
    
    //Exporter en txt
    class TextExport : public ExportStrategy {
        
    private:
      
    public:
        //Constructeurs
        TextExport(){}
        
        //Methodes inlines
        
        //Methodes non-inlines
        QString header(Note* n);
        QString footer(Note* n);
        QString exportNote(Article* a, unsigned int tl=0);        //Ces fonctions n'implémentent, apparement, pas la fonction virtuelle de l'ExportStrategy je ne sais pas pourquoi.
        QString exportNote(Document* d, unsigned int tl=0);
        QString exportNote(Image* i, unsigned int tl=0);
        QString exportNote(Audio* a, unsigned int tl=0);
        QString exportNote(Video* v, unsigned int tl=0);
        //using ExportStrategy::exportNote;


    };

    class TeXExport : public ExportStrategy{
    
    private:
        
    public:
        //Constructeurs
        TeXExport(){}
        
        //Methodes inlines
        
        //Methodes non-inlines
        QString header(Note* n);
        QString footer(Note* n);
        QString exportNote(Article* a, unsigned int tl=0);
        QString exportNote(Document* d, unsigned int tl=0);
        QString exportNote(Image* i, unsigned int tl=0);
        QString exportNote(Audio* a, unsigned int tl=0);
        QString exportNote(Video* v, unsigned int tl=0);
        //using ExportStrategy::exportNote;
        QString docStruct(unsigned int i) const;
        
    };

    class HTMLExport : public ExportStrategy {
    
    private:
    
    public:
        //Constructeurs
        HTMLExport(){}
        
        //Methodes inlines
        
        //Methodes non-inlines
        QString header(Note* n);
        QString footer(Note* n);
        QString exportNote(Article* a, unsigned int tl=0);
        QString exportNote(Document* d, unsigned int tl=0);
        QString exportNote(Image* i, unsigned int tl=0);
        QString exportNote(Audio* a, unsigned int tl=0);
        QString exportNote(Video* v, unsigned int tl=0);
        //using ExportStrategy::exportNote;
    };

    class SaveTextExport : public ExportStrategy{
    
    private:
    
    public:
        //Constructeurs
        SaveTextExport(){}
        
        //Methodes inlines
        
        //Methodes non-inlines
        QString header(Note* n);
        QString footer(Note* n);
        QString exportNote(Article* a, unsigned int tl=0);
        QString exportNote(Document* d, unsigned int tl=0);
        QString exportNote(Image* i, unsigned int tl=0);
        QString exportNote(Audio* a, unsigned int tl=0);
        QString exportNote(Video* v, unsigned int tl=0);
        //using ExportStrategy::exportNote;
    
    };

}


#endif // EXPORTS_H
