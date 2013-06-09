#include "notefactory.h"
#include <typeinfo>

/* a-t-on vraiment besoin de définir le constructeur?
NoteFactory::NoteFactory()
{
}
*/

unsigned int getNewId(){
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

Article* ArticleFactory::buildNoteCopy(const Article& n){
    Article* a = new Article(getNewId(), n.getTitle(), n.getText());
    return a;
}

Document* DocumentFactory::buildNewNote(const QString& title){
    Document* a = new Document(getNewId(), title);
    return a;
}

Document* DocumentFactory::buildNote(unsigned int id){
    //à définir selon l'architecture du projet choisie
}

Document* DocumentFactory::buildNoteCopy(const Document& n){//En cours de développement
    Document* a = new Document(getNewId(), n.getTitle());
    Document::constIterator i;
    for (i=n.begin(); i!=n.end() ; ++i){
        buildNoteCopy((*i)); //il faudra faire une méthode getFactory() dans les classes et sous classes de Note (voir tes exports)

    }

    return a;
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
}
