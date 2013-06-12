#include "tagmanager.h"


using namespace Tags;


TagManager* TagManager::Instance=0;
TagManagerWidget* TagManagerWidget::Instance=0;

TagManager& TagManager::getInstance()
{
    if(!Instance)
        Instance = new TagManager();
    return *Instance;
}

void TagManager::releaseInstance()
{
    if(Instance)
        delete Instance;
    Instance=0;
}

TagManager::TagManager()
{
}

TagManager::~TagManager()
{
    delete tagModel;
}

void TagManager::load(){}


TagManagerWidget& TagManagerWidget::getInstance(QWidget* parent)
{
    if(!Instance)
        Instance = new TagManagerWidget(parent);
    return *Instance;
}

void TagManagerWidget::releaseInstance()
{
    if(Instance)
        delete Instance;
    Instance=0;
}

TagManagerWidget::TagManagerWidget(QWidget* parent):QWidget(parent)
{
    //ALlocation des Widgets
    layout = new QVBoxLayout(this);
    QHBoxLayout* buttons = new QHBoxLayout();
    deleteTag = new QPushButton(this);
    addTag = new QPushButton(this);
    tagging = new QGroupBox(this);
    searchField = new QComboBox(this);

    deleteTag->setEnabled(false); //Empêche de supprimer un tag sans en avoir sélectionné un.

    buttons->addWidget(addTag);
    buttons->addWidget(deleteTag);

    layout->addWidget(searchField);
    layout->addWidget(tagging);
    layout->addLayout(buttons);



}

TagManagerWidget::~TagManagerWidget()
{
    delete deleteTag;
    delete addTag;
    delete tagging;
    delete searchField;
    delete layout;
}

