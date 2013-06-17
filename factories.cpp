//
//  exports.cpp
//  LO21_Projet
//
//  Created by Anthony WEIBEL and Antoine POUILLAUDE on 02/06/13.
//  Copyright (c) 2013 Antoine POUILLAUDE. All rights reserved.
//

#include "factories.h"
#include <typeinfo>

/**
 * \fn  unsigned int NoteFactory::getNewId()
 * \brief Methode servant à créer les ids à partir de l'horloge systéme
 * \return Identifiant de note.
 */
unsigned int NoteFactory::getNewId(){

    time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );
    return now->tm_mon*100000000 + now->tm_mday*1000000 + now->tm_hour*10000 + now->tm_min*100 + now->tm_sec; //valable que pour une période de 1 an. Après un an on peut avoir deux ID pareils (mais probabilité faible)
}

/**
 * \fn QMap<QString, NoteFactory*> NoteFactory::getFactories()
 * \brief Fonction qui renvoit une map contenant les pointeurs vers les factories
 * \return Map de correspondance entre type de note et factory
 */
QMap<QString, NoteFactory*> NoteFactory::getFactories(){
    QMap<QString, NoteFactory*> map;
    map["Article"]=new ArticleFactory();
    map["Document"]=new DocumentFactory();
    map["Image"]=new ImageFactory();
    map["Audio"]=new AudioFactory();
    map["Video"]=new VideoFactory();
    return map;
}

/**
 * \fn Article* ArticleFactory::buildNewNote(const QString& title)
 * \brief Fontion de création des notes.
 * \param Titre de l'article à créer.
 * \return Pointeur sur l'article créé
 */
Article* ArticleFactory::buildNewNote(const QString& title){
    Article* a = new Article(getNewId(), title, "");
    return a;
}

/**
 * \fn Article* ArticleFactory::buildNote(unsigned int id,const QString& title)
 * \brief Fonction servant à reconstruire un article.
 * \param Id de l'article à reconstruire.
 * \param Titre de l'article.
 * \return Pointeur sur l'article reconstruit
 */
Article* ArticleFactory::buildNote(unsigned int id,const QString& title){
    Article* a= new Article(id,title,"");
    return a;
}

/**
 * \fn Article* ArticleFactory::buildNoteCopy()
 * \brief Fonction servant à créer un nouvel id pour copier un article.
 * \return Pointeur sur le nouvel Article
 */
Article* ArticleFactory::buildNoteCopy(){
    unsigned int newId = getNewId();
    Article* a = new Article(newId, "Titre de l'article " + QString::number(newId),"");
    return a;
}

/**
 * \fn Document* DocumentFactory::buildNewNote(const QString& title)
 * \brief Fonction de construction d'un nouveau Document.
 * \param Titre du document à créer
 * \return Pointeur sur le nouveau Document
 */
Document* DocumentFactory::buildNewNote(const QString& title){
    Document* a = new Document(getNewId(), title);
    return a;
}

/**
 * \fn Document* DocumentFactory::buildNote(unsigned int id,const QString& title)
 * \brief Fonction servant à reconstruire un document.
 * \param Id du document à reconstruire.
 * \param Titre du document.
 * \return Pointeur sur le document reconstruit.
 */
Document* DocumentFactory::buildNote(unsigned int id,const QString& title){
    Document* d = new Document(id,title);
    return d;
}

/**
 * \fn Document* DocumentFactory::buildNoteCopy()
 * \brief Fonction servant à créer un nouvel id pour copier un document.
 * \return Pointeur sur le nouveau Document
 */
Document* DocumentFactory::buildNoteCopy(){
    unsigned int newId = getNewId();
    Document*d = new Document(newId,"Titre du document " + QString::number(newId));
    return d;
}

/**
 * \fn Audio* AudioFactory::buildNewNote(const QString& title)
 * \brief Fontion de création d'un audio.
 * \param Titre de l'Audio à créer.
 * \return Pointeur sur l'audio créé
 */
Audio* AudioFactory::buildNewNote(const QString& title){
    Audio* a = new Audio(getNewId(), title, "", "");
    return a;
}

/**
 * \fn Audio* AudioFactory::buildNote(unsigned int id,const QString& title)
 * \brief Fonction servant à reconstruire un audio.
 * \param Id de l'audio à reconstruire.
 * \param Titre de l'audio.
 * \return Pointeur sur l'audio reconstruit
 */
Audio* AudioFactory::buildNote(unsigned int id,const QString& title){
    Audio* a = new Audio(id,title);
    return a;
}

/**
 * \fn Audio* AudioFactory::buildNoteCopy()
 * \brief Fonction servant à créer un nouvel id pour copier un audio.
 * \return Pointeur sur le nouvel Audio
 */
Audio* AudioFactory::buildNoteCopy(){
    unsigned int newId = getNewId();
    Audio* a = new Audio(newId,"Titre de l'audio " + QString::number(newId));
    return a;
}

/**
 * \fn Video* VideoFactory::buildNewNote(const QString& title)
 * \brief Fontion de création d'une video.
 * \param Titre de la video à créer.
 * \return Pointeur sur la video créée
 */
Video* VideoFactory::buildNewNote(const QString& title){
    Video* a = new Video(getNewId(), title);
    return a;
}

/**
 * \fn Video* VideoFactory::buildNote(unsigned int id,const QString& title)
 * \brief Fonction servant à reconstruire une video.
 * \param Id de la video à reconstruire.
 * \param Titre de la video
 * \return Pointeur sur la video reconstruite
 */
Video* VideoFactory::buildNote(unsigned int id,const QString& title){
    Video* a = new Video(id,title);
    return a;
}

/**
 * \fn Video* VideoFactory::buildNoteCopy()
 * \brief Fonction servant à créer un nouvel id pour copier une video.
 * \return Pointeur sur la nouvelle video
 */
Video* VideoFactory::buildNoteCopy(){
    unsigned int newId = getNewId();
    Video* a = new Video(newId,"Titre de la video " + QString::number(newId));
    return a;
}

/**
 * \fn Image* ImageFactory::buildNewNote(const QString& title)
 * \brief Fontion de création d'une image.
 * \param Titre de l'image à créer.
 * \return Pointeur sur la nouvelle image
 */
Image* ImageFactory::buildNewNote(const QString& title){
    unsigned int newId = getNewId();
    Image* a = new Image(getNewId(),title);
    return a;
}

/**
 * \fn Image* ImageFactory::buildNoteCopy()
 * \brief Fonction servant à créer un nouvel id pour copier une image
 * \return Pointeur sur la nouvelle image
 */
Image* ImageFactory::buildNoteCopy(){
    unsigned int newId = getNewId();
    Image* a = new Image(newId,"Titre de l'image " + QString::number(newId));
    return a;
}

/**
 * \fn Image* ImageFactory::buildNote(unsigned int id,const QString& title)
 * \brief Fonction servant à reconstruire une image.
 * \param Id de l'image à reconstruire.
 * \param Titre de l'image
 * \return Pointeur sur l'image reconstruite
 */
Image* ImageFactory::buildNote(unsigned int id,const QString& title){
    Image* a = new Image(id,title);
    return a;
}
