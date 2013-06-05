//
//  binary.h
//  LO21_Projet
//
//  Created by Anthony WEIBEL and Antoine POUILLAUDE on 25/05/13.
//  Copyright (c) 2013 Antoine POUILLAUDE. All rights reserved.
//

#ifndef BINARY_H
#define BINARY_H

#include "note.h"
#include "exports.h"
#include <QString>

class BinaryWidget;
class AudioWidget;
class ImageWidget;
class VideoWidget;

//Super-classe des fichiers binaires
class Binary : public Note{
    
private:
    //Methodes privées
    void load();
    
    //Constructeurs de recopie
    Binary(const Binary& b);
    Binary& operator=(const Binary& b);
    
protected:
    //Attributs protégés
    QString desc;
    QString path;
    
public:
    //Constructeur
    Binary(unsigned int i,const QString& t, const QString& d, const QString& p);
    
    //Méthodes non-inlines
    QString getDesc() const;
    void setDesc(const QString& d);
    QString getPath() const;
    void setPath(const QString& p);

    /*
    //Ceci est un test afin de pouvoir afficher les notes contenues dans un document
    BinaryWidget* getWidget();*/
};


//Classe des binaires vidéo
class Video : public Binary {
    
private:
    //Constructeurs de recopie
    Video(const Video& v);
    Video& operator=(const Video& v);
    
public:
    //Constructeurs
    Video(unsigned int i,const QString& t, const QString& d, const QString& p):Binary(i,t,d,p){}
    
    //Méthodes non inline
    QString ExportAsPart(Exports::ExportStrategy* es, unsigned int tl) const;
    
    /*
    //Ceci est un test afin de pouvoir afficher les notes contenues dans un document
    VideoWidget* getWidget();*/
};


//Classe des binaires image
class Image : public Binary {
    
private:
    //Constructeurs de recopie
    Image(const Image& i);
    Image& operator=(const Image& i);
    
public:
    //Constructeurs
    Image(unsigned int i,const QString& t, const QString& d, const QString& p):Binary(i,t,d,p){}
    
    //Méthodes non inline
    QString ExportAsPart(Exports::ExportStrategy* es, unsigned int tl) const;

    /*
    //Ceci est un test afin de pouvoir afficher les notes contenues dans un document
    ImageWidget* getWidget();*/
};


//Classe des binaires audio
class Audio : public Binary {
    
private:
    //Constructeurs de recopie
    Audio(const Audio& a);
    Audio& operator=(const Audio& a);
    
public:
    //Constructeurs
    Audio(unsigned int i,const QString& t, const QString& d, const QString& p):Binary(i,t,d,p){}
    
    //Méthodes non inline
    QString ExportAsPart(Exports::ExportStrategy* es, unsigned int tl) const;

    /*
    //Ceci est un test afin de pouvoir afficher les notes contenues dans un document
    AudioWidget* getWidget();*/
};
#endif // BINARY_H
