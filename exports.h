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
        virtual QString header(const Note& n) =0;
        virtual QString footer(const Note& n) =0;
        virtual QString exportNote(const Note& n, unsigned int tl=0) =0;
    };
    
    //Exporter en txt
    class TextExport : public ExportStrategy {
        
    private:
      
    public:
        //Constructeurs
        TextExport(){}
        
        //Methodes inlines
        
        //Methodes non-inlines
        QString header(const Note& n);
        QString footer(const Note& n);
        QString exportNote(const Article& a, unsigned int tl=0);
        QString exportNote(const Document& d, unsigned int tl=0);
        QString exportNote(const Image& i, unsigned int tl=0);
        QString exportNote(const Audio& a, unsigned int tl=0);
        QString exportNote(const Video& v, unsigned int tl=0);

    };

    class TeXExport : public ExportStrategy{
    
    private:
        
    public:
        //Constructeurs
        TeXExport(){}
        
        //Methodes inlines
        
        //Methodes non-inlines
        QString header(const Note& n);
        QString footer(const Note& n);
        QString exportNote(const Article& a, unsigned int tl=0);
        QString exportNote(const Document& d, unsigned int tl=0);
        QString exportNote(const Image& i, unsigned int tl=0);
        QString exportNote(const Audio& a, unsigned int tl=0);
        QString exportNote(const Video& v, unsigned int tl=0);
        QString docStruct(unsigned int i) const;
        
    };

    class HTMLExport : public ExportStrategy {
    
    private:
    
    public:
        //Constructeurs
        HTMLExport(){}
        
        //Methodes inlines
        
        //Methodes non-inlines
        QString header(const Note& n);
        QString footer(const Note& n);
        QString exportNote(const Article& a, unsigned int tl=0);
        QString exportNote(const Document& d, unsigned int tl=0);
        QString exportNote(const Image& i, unsigned int tl=0);
        QString exportNote(const Audio& a, unsigned int tl=0);
        QString exportNote(const Video& v, unsigned int tl=0);
    
    };

    class SaveTextExport : public ExportStrategy{
    
    private:
    
    public:
        //Constructeurs
        SaveTextExport(){}
        
        //Methodes inlines
        
        //Methodes non-inlines
        QString header(const Note& n);
        QString footer(const Note& n);
        QString exportNote(const Article& a, unsigned int tl=0);
        QString exportNote(const Document& d, unsigned int tl=0);
        QString exportNote(const Image& i, unsigned int tl=0);
        QString exportNote(const Audio& a, unsigned int tl=0);
        QString exportNote(const Video& v, unsigned int tl=0);
    
    };

}

#endif // EXPORTS_H
