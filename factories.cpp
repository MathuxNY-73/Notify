//
//  exports.cpp
//  LO21_Projet
//
//  Created by Anthony WEIBEL and Antoine POUILLAUDE on 02/06/13.
//  Copyright (c) 2013 Antoine POUILLAUDE. All rights reserved.
//

#include "factories.h"
#include <typeinfo>

unsigned int NoteFactory::getNewId(){

    time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );
    return now->tm_mon*100000000 + now->tm_mday*1000000 + now->tm_hour*10000 + now->tm_min*100 + now->tm_sec; //valable que pour une période de 1 an. Après un an on peut avoir deux ID pareils (mais probabilité faible)
}

QMap<QString, NoteFactory*> NoteFactory::getFactories(){
    QMap<QString, NoteFactory*> map;
    map["Article"]=new ArticleFactory();
    map["Document"]=new DocumentFactory();
    map["Image"]=new ImageFactory();
    map["Audio"]=new AudioFactory();
    map["Video"]=new VideoFactory();
    return map;
}

Article* ArticleFactory::buildNewNote(const QString& title){
    Article* a = new Article(getNewId(), title, "");
    return a;
}

Article* ArticleFactory::buildNote(unsigned int id,const QString& title){
    Article* a= new Article(id,title,"");
    return a;
}

Article* ArticleFactory::buildNoteCopy(){
    Article* a = new Article(getNewId(), "","");
    return a;
}

Document* DocumentFactory::buildNewNote(const QString& title){
    Document* a = new Document(getNewId(), title);
    return a;
}

Document* DocumentFactory::buildNote(unsigned int id,const QString& title){
    Document* d = new Document(id,title);
    return d;
}

Document* DocumentFactory::buildNoteCopy(){
    Document*d = new Document(getNewId(),"");
    return d;
}

Audio* AudioFactory::buildNewNote(const QString& title){
    Audio* a = new Audio(getNewId(), title, "", "");
    return a;
}

Audio* AudioFactory::buildNote(unsigned int id,const QString& title){
    Audio* a = new Audio(id,title);
    return a;
}

Audio* AudioFactory::buildNoteCopy(){
    Audio* a = new Audio(getNewId(),"");
    return a;
}

Video* VideoFactory::buildNewNote(const QString& title){
    Video* a = new Video(getNewId(), title);
    return a;
}

Video* VideoFactory::buildNote(unsigned int id,const QString& title){
    Video* a = new Video(id,title);
    return a;
}

Video* VideoFactory::buildNoteCopy(){
    Video* a = new Video(getNewId(),"");
    return a;
}

Image* ImageFactory::buildNewNote(const QString& title){
    Image* a = new Image(getNewId(),title);
    return a;
}

Image* ImageFactory::buildNoteCopy(){
    Image* a = new Image(getNewId(),"");
    return a;
}

Image* ImageFactory::buildNote(unsigned int id,const QString& title){
    Image* a = new Image(id,title);
    return a;
}
