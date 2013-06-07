//
//  binary.cpp
//  LO21_Projet
//
//  Created by Anthony WEIBEL and Antoine POUILLAUDE on 25/05/13.
//  Copyright (c) 2013 Antoine POUILLAUDE. All rights reserved.
//

#include "binary.h"


//Methodes de Binary

Binary::Binary(unsigned int i,const QString& t, const QString& d, const QString& p):Note(i,t),desc(d),path(p){}

QString Binary::getDesc() const {
    return desc;
}

void Binary::setDesc(const QString& d) {
    desc=d;
}

QString Binary::getPath() const {
    return path;
}

void Binary::setPath(const QString& p) {
    path=p;
}

//Methodes de Audio

QString Audio::ExportAsPart(Exports::ExportStrategy* es, unsigned int tl) const{
    return es->exportNote(*this,tl);
}

//Methodes de Image

QString Image::ExportAsPart(Exports::ExportStrategy* es, unsigned int tl) const{
    return es->exportNote(*this,tl);
}

//Methodes de Video

QString Video::ExportAsPart(Exports::ExportStrategy* es, unsigned int tl) const{
    return es->exportNote(*this,tl);
}


BinaryWidget* Binary::getWidget()
{
    BinaryWidget* dw = new BinaryWidget(this);
    return dw;
}

VideoWidget* Video::getWidget()
{
    VideoWidget* dw = new VideoWidget(this);
    return dw;
}

ImageWidget* Image::getWidget()
{
    ImageWidget* dw = new ImageWidget(this);
    return dw;
}

AudioWidget* Audio::getWidget()
{
    AudioWidget* dw = new AudioWidget(this);
    return dw;
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
