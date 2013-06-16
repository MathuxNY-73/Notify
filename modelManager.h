#ifndef MODELMANAGER_H
#define MODELMANAGER_H

#include <QStandardItem>
#include "note.h"

class NoteItem : public QStandardItem
{
private:
    Note* note;
public:
    NoteItem(const QString& title, Note* n):QStandardItem(title),note(n){}
    ~NoteItem(){}
    Note* getNote() const{ return note;}
    void update() {setText(note->getTitle());}
};


#endif // MODELMANAGER_H
