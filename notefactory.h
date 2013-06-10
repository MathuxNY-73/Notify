#ifndef NOTEFACTORY_H
#define NOTEFACTORY_H

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
    //NotesFactory(); //on ne peut pas laisser le constructeur par défaut?
    virtual Note* buildNote(unsigned int id) =0; //méthode qui sera utilisée par NoteManager quand le programme se lancera. Ajoute une note déja existante physiquement au Qset de NoteManager (cette méthode sera utilisé par la méthode load (ou qqchose du genre) de notemanager)
    virtual Note* buildNewNote(const QString& title) =0; //crée une Note à partir de rien
    QMap<QString, NoteFactory*> static getFactories();
};


class ArticleFactory : public NoteFactory{
public:
    Article* buildNewNote(const QString& title);
    Article* buildNote(unsigned int id);
};

class DocumentFactory  : public NoteFactory{
    Document* buildNewNote(const QString& title);
    Document* buildNote(unsigned int id);
};

class AudioFactory : public NoteFactory{
    Audio* buildNewNote(const QString& title);
    Audio* buildNote(unsigned int id);
};

class ImageFactory : public NoteFactory{
    Image* buildNewNote(const QString& title);
    Image* buildNote(unsigned int id);
};

class VideoFactory : public NoteFactory{
    Video* buildNewNote(const QString& title);
    Video* buildNote(unsigned int id);
};




#endif // NOTEFACTORY_H
