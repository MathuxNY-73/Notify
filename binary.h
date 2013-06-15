//
//  binary.h
//  LO21_Projet
//
//  Created by Anthony WEIBEL and Antoine POUILLAUDE on 25/05/13.
//  Copyright (c) 2013 Antoine POUILLAUDE. All rights reserved.
//

#ifndef BINARY_H
#define BINARY_H

#include <QString>
#include <iostream>
#include "note.h"
#include "exports.h"
#include "binarywidget.h"

class BinaryException{
public:
    BinaryException(const QString& message):info(message){}
    QString getInfo() const { return info; }
private:
    QString info;
};

//Super-classe des fichiers binaires
class Binary : public Note{
    
private:
    //Methodes privées
    BinaryWidget* widget;
    unsigned int maxW;
    
    //Constructeurs de recopie
    Binary(const Binary& b);
    Binary& operator=(const Binary& b);
    
protected:
    //Attributs protégés
    QString desc;
    QString binPath;

public:
    //Constructeur
    Binary(unsigned int i,const QString& t, const QString& d, const QString& p);
    ~Binary();

    //Méthodes non-inlines
    QString getDesc() const;
    void setDesc(const QString& d);
    QString getBinPath() const;
    void setBinPath(const QString& p);


    //Ceci est un test afin de pouvoir afficher les notes contenues dans un document
    BinaryWidget* getWidget();
};


//Classe des binaires vidéo
class Video : public Binary {
    
private:
    VideoWidget* widget;
    unsigned int maxW;

    //Constructeurs de recopie
    Video(const Video& v);
    Video& operator=(const Video& v);


public:
    //Constructeurs
    Video(unsigned int i,const QString& t, const QString& d, const QString& p):Binary(i,t,d,p),maxW(0),widget(0){}
    ~Video();

    //Méthodes non inline
    QString ExportNote(Exports::ExportStrategy* es);
    QString ExportAsPart(Exports::ExportStrategy* es, unsigned int tl);
    
    QStandardItem* getItem();

    //Ceci est un test afin de pouvoir afficher les notes contenues dans un document
    VideoWidget* getWidget();
};


//Classe des binaires image
class Image : public Binary {
    
private:
    ImageWidget* widget;
    unsigned int maxW;

    //Constructeurs de recopie
    Image(const Image& i);
    Image& operator=(const Image& i);


public:
    //Constructeurs
    Image(unsigned int i,const QString& t, const QString& d, const QString& p):Binary(i,t,d,p),maxW(0),widget(0){}
    ~Image();

    //Méthodes non inline
    QString ExportNote(Exports::ExportStrategy* es);
    QString ExportAsPart(Exports::ExportStrategy* es, unsigned int tl);


    //Ceci est un test afin de pouvoir afficher les notes contenues dans un document
    ImageWidget* getWidget();

     QStandardItem* getItem();
};


//Classe des binaires audio
class Audio : public Binary {
    
private:
    AudioWidget* widget;
    unsigned int maxW;

    //Constructeurs de recopie
    Audio(const Audio& a);
    Audio& operator=(const Audio& a);

    
public:
    //Constructeurs
    Audio(unsigned int i,const QString& t, const QString& d, const QString& p):Binary(i,t,d,p),maxW(0),widget(0){}
    ~Audio();

    //Méthodes non inline
    QString ExportNote(Exports::ExportStrategy* es);
    QString ExportAsPart(Exports::ExportStrategy* es, unsigned int tl);


    //Ceci est un test afin de pouvoir afficher les notes contenues dans un document
    AudioWidget* getWidget();

    QStandardItem* getItem();
};
#endif // BINARY_H
