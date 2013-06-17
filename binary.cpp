//
//  binary.cpp
//  LO21_Projet
//
//  Created by Anthony WEIBEL and Antoine POUILLAUDE on 25/05/13.
//  Copyright (c) 2013 Antoine POUILLAUDE. All rights reserved.
//

#include "binary.h"
#include "notemanager.h"

//Methodes de Binary

/**
 * \fn Binary::Binary(unsigned int i,const QString& t, const QString& d, const QString& p)
 * \brief Constructeur des objets binaires
 * \param Identifiant de la note à construire
 * \param Titre de la note à construire
 * \param Description de l'objet binaire
 * \param Chemin vers le fichier binaire associé à l'objet
 */
Binary::Binary(unsigned int i,const QString& t, const QString& d, const QString& p):Note(i,t),widget(0),maxW(0),desc(d),binPath(p){}

/**
 * \fn Binary::Binary(const QString& p)
 * \brief Constructeur d'un objet binaire à partir d'un chemin
 * \param Chemin vers le fichier note
 */
Binary::Binary(const QString& p):Note(p),widget(0),maxW(0){}

/**
 * \fn Binary::Binary(unsigned int i, const QString& path)
 * @brief Constructeur d'un objet binaire à partir de l'Id et du chemin
 * @param Identifiant de la note
 * @param Chemin vers le fichier note
 */
Binary::Binary(unsigned int i, const QString& path):Note(i,path),widget(0),maxW(0),desc(""),binPath(""){}

/**
 * \fn Binary::~Binary()
 * \brief Destructeur de l'objet binaire
 */
Binary::~Binary()
{
    if(widget)
        delete widget;
}

/**
 * \fn QString Binary::getDesc() const
 * \brief Récupérer la description du fichier binaire associé à l'objet
 * \return Chaine de caractères contenant la description du fichier binaire
 */
QString Binary::getDesc() const {
    return desc;
}

/**
 * \fn void Binary::setDesc(const QString& d)
 * \brief Fixer la description du fichier binaire
 * \param Description
 */
void Binary::setDesc(const QString& d) {
    modified=true;
    desc=d;
}

/**
 * \fn QString Binary::getBinPath() const
 * \brief Récupérer le chemin du fichier binaire
 * \return Chemin vers le fichier sur le disque
 */
QString Binary::getBinPath() const {
    return binPath;
}

/**
 * \fn void Binary::setBinPath(const QString& p)
 * \brief Fixer le chemin vers le fichier binaire
 * \param Chemin vers le fichier sur le disque
 */
void Binary::setBinPath(const QString& p) {
    modified=true;
    binPath=p;
}

/**
 * \fn BinaryWidget* Binary::getWidget()
 * \brief Récupérer le widget associé
 * \return Pointeur sur le widget associé à l'objet
 */
BinaryWidget* Binary::getWidget()
{
    if(maxW==0)
    {
        widget = new BinaryWidget(this);
        maxW++;
    }
    return widget;
}

//Methodes de Audio
QString Audio::ExportNote(Exports::ExportStrategy* es)
{
    return es->header(this)+es->exportNote(this)+es->footer(this);
}

QString Audio::ExportAsPart(Exports::ExportStrategy* es, unsigned int tl) {
    return es->exportNote(this,tl);
}


AudioWidget* Audio::getWidget()
{
    if(maxW==0)
    {
        widget = new AudioWidget(this);
        maxW++;
    }
    return widget;
}

Audio::~Audio(){
    if(widget)
        delete widget;
}

Audio& Audio::getCopy()
{
    Audio* a=dynamic_cast<Audio*>(NoteManager::getInstance().getFactory()["Audio"]->buildNoteCopy());
    a->setDesc(desc);
    a->setBinPath(binPath);
    return *a;
}


//Methodes de Image
QString Image::ExportNote(Exports::ExportStrategy* es)
{
    return es->header(this)+es->exportNote(this)+es->footer(this);
}

QString Image::ExportAsPart(Exports::ExportStrategy* es, unsigned int tl) {
    return es->exportNote(this,tl);
}

ImageWidget* Image::getWidget()
{
    if(maxW==0)
    {
        widget = new ImageWidget(this);
        maxW++;
    }
    return widget;
}


Image::~Image()
{
    if(widget)
        delete widget;
}

Image& Image::getCopy()
{
    Image* i=dynamic_cast<Image*>(NoteManager::getInstance().getFactory()["Image"]->buildNoteCopy());
    i->setDesc(desc);
    i->setBinPath(binPath);
    return *i;
}


//Methodes de Video
QString Video::ExportNote(Exports::ExportStrategy* es)
{
    return es->header(this)+es->exportNote(this)+es->footer(this);
}

QString Video::ExportAsPart(Exports::ExportStrategy* es, unsigned int tl) {
    return es->exportNote(this,tl);
}

VideoWidget* Video::getWidget()
{
    if(maxW==0)
    {
        widget = new VideoWidget(this);
        maxW++;
    }
    return widget;
}


Video::~Video(){
    if(widget)
        delete widget;
}

Video& Video::getCopy()
{
    Video* v=dynamic_cast<Video*>(NoteManager::getInstance().getFactory()["Video"]->buildNoteCopy());
    v->setDesc(desc);
    v->setBinPath(binPath);
    return *v;
}

