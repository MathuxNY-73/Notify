#ifndef TAGMANAGER_H
#define TAGMANAGER_H

#include "note.h"
#include "notemanager.h"
#include "workspace.h"
#include <QObject>
#include <QComboBox>
#include <QGroupBox>

namespace Tags
{

class TagManager : public QObject
{
    Q_OBJECT

private:
    typedef QMap<QString,QSet<Note*> > Association;
    QList<Note*> filteredNote;
    QList<QString> filteredTags;

    //On le met en singleton
    TagManager();
    ~TagManager();
    TagManager(const TagManager& t);
    TagManager& operator=(const TagManager& t);

    static TagManager* Instance;
    QStandardItemModel* tagModel;

public:

    //Singleton
    static TagManager& getInstance();
    static void releaseInstance();

    //Methodes
    void load();
    void clear();
    void addTag(const QString& name);
    void deleteTag(const QString& name);
    void addAssociation(const QString& tag, const Note* note);
    void deleteAssociation(const QString& tagName, const Note* note);
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
    QPushButton* deleteTag, *addTag;

public:
    static TagManagerWidget& getInstance(QWidget* parent=0);
    static void releaseInstance();


};

}
#endif // TAGMANAGER_H
