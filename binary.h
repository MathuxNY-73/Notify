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
#include <QString>

class Binary : public Note{
private:
    void load();
protected:
    QString desc;
    QString path;
public:
    Binary(const QString& t, const QString& d, const QString& p):Note(t),desc(d),path(p){}
    QString getDesc() const {return this->desc;}
    void setDesc(const QString& d) {desc=d;}
    QString getPath() const { return this->path;}
    void setPath(const QString& p) {path=p;}
};

class Video : public Binary {
private:
    Video(const Video& v){}
    Video& operator=(const Video& v){}
public:
    Video();
};

class Image : public Binary {
private:
    Image(const Image& v){}
    Image& operator=(const Image& v){}
public:
    Image();
};

class Audio : public Binary {
private:
    Audio(const Audio& v){}
    Audio& operator=(const Audio& v){}
public:
    Audio();
};
#endif // BINARY_H
