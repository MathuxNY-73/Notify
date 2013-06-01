//
//  binary.cpp
//  LO21_Projet
//
//  Created by Anthony WEIBEL and Antoine POUILLAUDE on 25/05/13.
//  Copyright (c) 2013 Antoine POUILLAUDE. All rights reserved.
//

#include "binary.h"
#include "note.h"

//Methodes de Binary

Binary::Binary(unsigned int i,const QString& t, const QString& d, const QString& p):Note(i,t),desc(d),path(p){}

QString Binary::getDesc() const {
    return this->desc;
}

void Binary::setDesc(const QString& d) {
    desc=d;
}

QString Binary::getPath() const {
    return this->path;
}

void Binary::setPath(const QString& p) {
    path=p;
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