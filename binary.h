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
    Binary(const Binary& b);
    Binary& operator=(const Binary& b);
    
protected:
    QString desc;
    QString path;
    
public:
    Binary(unsigned int i,const QString& t, const QString& d, const QString& p);
    QString getDesc() const;
    void setDesc(const QString& d);
    QString getPath() const;
    void setPath(const QString& p);
};

class Video : public Binary {
private:
    Video(const Video& v);
    Video& operator=(const Video& v);
public:
    Video(unsigned int i,const QString& t, const QString& d, const QString& p):Binary(i,t,d,p){}
};

class Image : public Binary {
private:
    Image(const Image& i);
    Image& operator=(const Image& i);
public:
    Image(unsigned int i,const QString& t, const QString& d, const QString& p):Binary(i,t,d,p){}
};

class Audio : public Binary {
private:
    Audio(const Audio& a);
    Audio& operator=(const Audio& a);
public:
    Audio(unsigned int i,const QString& t, const QString& d, const QString& p):Binary(i,t,d,p){}
};
#endif // BINARY_H
