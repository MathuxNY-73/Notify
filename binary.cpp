//
//  binary.cpp
//  LO21_Projet
//
//  Created by Anthony WEIBEL and Antoine POUILLAUDE on 25/05/13.
//  Copyright (c) 2013 Antoine POUILLAUDE. All rights reserved.
//

#include "binary.h"


//Methodes de Binary

Binary::Binary(unsigned int i,const QString& t, const QString& d, const QString& p):Note(i,t),desc(d),path(p),maxW(0){}

QString Binary::getDesc() const {
    return desc;
}

void Binary::setDesc(const QString& d) {
    modified=true;
    desc=d;
}

QString Binary::getPath() const {
    return path;
}

void Binary::setPath(const QString& p) {
    modified=true;
    path=p;
}

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

QStandardItem* Audio::load() const
{
    QStandardItem* i = new QStandardItem(title);
    return i;
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

QStandardItem* Image::load() const
{
    QStandardItem* i = new QStandardItem(title);
    return i;
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

QStandardItem* Video::load() const
{
    QStandardItem* i = new QStandardItem(title);
    return i;
}


//Constructeurs de recopie
/*
//Video
Video::Video(const Video& v){}
Video::operator=(const Video &v){}

//Image
Image::Image(const Image& i){}
Image::operator=(const Image &i){}

//Audio
Audio::Audio(const Audio& a){}
Audio::operator=(const Audio &a){}
*/

//Je ne les implémente pas tout de suite car à mon avis pour la recopie on aura besoin des factories.
