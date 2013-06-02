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
#include "note.h"

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
        virtual QString exportNote(Note* n, unsigned int tl) =0;
    };
    
    //Exporter en txt
    class TextExport{
        
    private:
      
    public:
        //Constructeurs
        TextExport(){}
        
        //Methodes inlines
        
        //Methodes non-inlines
        QString header(Note* n);
        QString footer(Note* n);
        QString exportNote(Article* a, unsigned int tl);
        QString exportNote(Document* d, unsigned int tl);
        QString exportNote(Image* i, unsigned int tl);
        QString exportNote(Audio* a, unsigned int tl);
        QString exportNote(Video* v, unsigned int tl);

    };

    class TexExport{
    
    private:
        
    public:
        //Constructeurs
        TexExport(){}
        
        //Methodes inlines
        
        //Methodes non-inlines
        QString header(Note* n);
        QString footer(Note* n);
        QString exportNote(Article* a, unsigned int tl);
        QString exportNote(Document* d, unsigned int tl);
        QString exportNote(Image* i, unsigned int tl);
        QString exportNote(Audio* a, unsigned int tl);
        QString exportNote(Video* v, unsigned int tl);
        
    };

    class HTMLExport{
    
    private:
    
    public:
        //Constructeurs
        HTMLExport(){}
        
        //Methodes inlines
        
        //Methodes non-inlines
        QString header(Note* n);
        QString footer(Note* n);
        QString exportNote(Article* a, unsigned int tl);
        QString exportNote(Document* d, unsigned int tl);
        QString exportNote(Image* i, unsigned int tl);
        QString exportNote(Audio* a, unsigned int tl);
        QString exportNote(Video* v, unsigned int tl);
    
    };

    class SaveTextExport{
    
    private:
    
    public:
        //Constructeurs
        SaveTextExport(){}
        
        //Methodes inlines
        
        //Methodes non-inlines
        QString header(Note* n);
        QString footer(Note* n);
        QString exportNote(Article* a, unsigned int tl);
        QString exportNote(Document* d, unsigned int tl);
        QString exportNote(Image* i, unsigned int tl);
        QString exportNote(Audio* a, unsigned int tl);
        QString exportNote(Video* v, unsigned int tl);
    
    };
}


#endif // EXPORTS_H
