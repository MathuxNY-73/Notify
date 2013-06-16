#ifndef FACTORIES_H
#define FACTORIES_H

#include "note.h"
#include "time.h"
#include "article.h"
#include "document.h"
#include "binary.h"


//definition des Factories
class NoteFactory{

protected:
    unsigned int getNewId();

public:
    NoteFactory(){}
    virtual Note* buildNote(unsigned int id,const QString& title) =0; //méthode qui sera utilisée par NoteManager quand le programme se lancera. Ajoute une note déja existante physiquement au Qset de NoteManager (cette méthode sera utilisé par la méthode load (ou qqchose du genre) de notemanager)
    virtual Note* buildNewNote(const QString& title) =0; //crée une Note à partir de rien
    virtual Note* buildNoteCopy() =0;
    QMap<QString, NoteFactory*> static getFactories();
};


class ArticleFactory{

public:
    ArticleFactory(){}
    Article* buildNewNote(const QString& title);
    Article* buildNote(unsigned int id,const QString& title);
    Article* buildNoteCopy();
};

class DocumentFactory{
public:
    DocumentFactory(){}
    Document* buildNewNote(const QString& title);
    Document* buildNote(unsigned int id,const QString& title);
    Document* buildNoteCopy();
};

class AudioFactory{

public:
    AudioFactory(){}
    Audio* buildNewNote(const QString& title);
    Audio* buildNote(unsigned int id,const QString& title);
    Audio* buildNoteCopy();
};

class ImageFactory{

public:
    ImageFactory(){}
    Image* buildNewNote(const QString& title);
    Image* buildNote(unsigned int id,const QString& title);
    Image* buildNoteCopy();
};

class VideoFactory{

public:
    VideoFactory(){}
    Video* buildNewNote(const QString& title);
    Video* buildNote(unsigned int id,const QString& title);
    Video* buildNoteCopy();
};


#endif // FACTORIES_H
