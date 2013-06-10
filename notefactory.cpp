#include "notefactory.h"
#include <typeinfo>

/* a-t-on vraiment besoin de définir le constructeur?
NoteFactory::NoteFactory()
{
}
*/

QMap<QString, NoteFactory*> NoteFactory::getFactories(){
    QMap<QString, NoteFactory*> map;
    map["Article"]=new ArticleFactory();       //J'ai une erreur ici qui me dit que je ne peut pas allouer de l'espace sur des classe abstraites et je pense que cela est dû à l'erreur ennoncé précédement dans l'exports.h
    map["Document"]=new DocumentFactory();
    //map["html"]=new HTMLExport();
    return map;
}

unsigned int NoteFactory::getNewId(){
    time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );
    return now->tm_mon*100000000 + now->tm_mday*1000000 + now->tm_hour*10000 + now->tm_min*100 + now->tm_sec; //valable que pour une période de 1 an. Après un an on peut avoir deux ID pareils (mais probabilité faible)
}


Article* ArticleFactory::buildNewNote(const QString& title){
    Article* a = new Article(getNewId(), title, "");
    return a;
}

Article* ArticleFactory::buildNote(unsigned int id){
    //à définir selon l'architecture du projet choisie
}

Article* ArticleFactory::buildNoteCopy(const Article* n){
    Article* a = new Article(getNewId(), (*n).getTitle(), (*n).getText());
    return a;
}
/*
Document* DocumentFactory::buildNewNote(const QString& title){
    Document* a = new Document(getNewId(), title);
    return a;
}

Document* DocumentFactory::buildNote(unsigned int id){
    //à définir selon l'architecture du projet choisie
}

Document* DocumentFactory::buildNoteCopy(const Note* n){//En cours de développement
    QList<Note*> list;
    Document::constIterator i;
    for (i=n->begin(); i!=n->end() ; ++i){
        if(typeid(*(*i)).name()=="Article")
            list<<ArticleFactory::buildNoteCopy(*i);
        else if(typeid(*(*i)).name()=="Document")
            list<<DocumentFactory::buildNoteCopy(*i);
        else if(typeid(*(*i)).name()=="Image")
            list<<ImageFactory::buildNoteCopy(*i);
        else if(typeid(*(*i)).name()=="Video")
            list<<VideoFactory::buildNoteCopy(*i);
        else if(typeid(*(*i)).name()=="Audio")
            list<<ArticleFactory::buildNoteCopy(*i);

    }
    Document* d= new Document(getNewId(),n->getTitle(),list);
    return d;
}

Audio* AudioFactory::buildNewNote(const QString& title){
    Audio* a = new Audio(getNewId(), title, "", "");
    return a;
}

Audio* AudioFactory::buildNote(unsigned int id){
    //à définir selon l'architecture du projet choisie
}

Video* VideoFactory::buildNewNote(const QString& title){
    Video* a = new Video(getNewId(), title, "", "");
    return a;
}

Video* VideoFactory::buildNote(unsigned int id){
    //à définir selon l'architecture du projet choisie
}

Image* ImageFactory::buildNewNote(const QString& title){
    Image* a = new Image(getNewId(), title, "", "");
    return a;
}

Image* ImageFactory::buildNote(unsigned int id){
    //à définir selon l'architecture du projet choisie
}*/
