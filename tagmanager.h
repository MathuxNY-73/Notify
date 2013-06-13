#ifndef TAGMANAGER_H
#define TAGMANAGER_H

#include "note.h"
#include "notemanager.h"
#include "workspace.h"
#include <QRadioButton>
#include <QObject>
#include <QComboBox>
#include <QGroupBox>
#include <QInputDialog>
#include <QListView>

namespace Tags
{

class TagManagerWidget;

class TagManager : public QObject
{
    Q_OBJECT

    friend class TagManagerWidget;

private:
    typedef QMap<QStandardItem*,QSet<Note*> > Association;
    Association tags;
    QList<Note*> filteredNote;
    QList<QStandardItem*> filteredTags;

    //On le met en singleton
    TagManager();
    ~TagManager();
    TagManager(const TagManager& t);
    TagManager& operator=(const TagManager& t);

    static TagManager* Instance;
    QStandardItemModel* tagModel;

    QStandardItemModel* getModel() const;

public:

    //Singleton
    static TagManager& getInstance();
    static void releaseInstance();

    //Methodes
    void load();
    void clear();
    void addTag(const QString& name);
    void deleteTag(int row);
    void addAssociation(int row, Note* note);
    void deleteAssociation(int row, Note* note);


    typedef Association::const_iterator constAssocIterator;
    typedef Association::Iterator assocIterator;
    constAssocIterator associationBegin() const { return tags.cbegin();}
    assocIterator associationBegin() { return tags.begin();}
    constAssocIterator associationEnd() const {return tags.cend();}
    assocIterator associationEnd() {return tags.end();}

    typedef QList<Note*>::const_iterator constFNIterator;
    typedef QList<Note*>::Iterator FNIterator;
    constFNIterator fniBegin() const { return filteredNote.cbegin();}
    FNIterator fniNoteBegin() { return filteredNote.begin();}
    constFNIterator fniEnd() const {return filteredNote.cend();}
    FNIterator fniEnd() {return filteredNote.end();}

    typedef QList<QStandardItem*>::const_iterator constFTIterator;
    typedef QList<QStandardItem*>::Iterator FTIterator;
    constFTIterator ftiBegin() const { return filteredTags.cbegin();}
    FTIterator ftiBegin() { return filteredTags.begin();}
    constFTIterator ftiEnd() const {return filteredTags.cend();}
    FTIterator ftiEnd() {return filteredTags.end();}
};

class TagManagerWidget : public QWidget
{
    Q_OBJECT

private:
    Tags::TagManager* manager;

    //singleton
    TagManagerWidget(QWidget* parent=0);
    ~TagManagerWidget();
    TagManagerWidget(const TagManagerWidget& t);
    TagManagerWidget& operator=(const TagManagerWidget& t);
    static TagManagerWidget* Instance;

    QComboBox* searchField;
    QVBoxLayout* layout;
    QGroupBox* tagging;
    QListView* viewer;
    QPushButton* deleteTagBtn, *addTagBtn;

public:
    static TagManagerWidget& getInstance(QWidget* parent=0);
    static void releaseInstance();

public slots :
    void addTags();
    void deleteTags();
    void setAssociation();
    void deleteAssociation();

};

}
#endif // TAGMANAGER_H
