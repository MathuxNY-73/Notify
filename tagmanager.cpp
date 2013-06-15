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
    tagModel = new QStringListModel(tagList,this);
}

TagManager::~TagManager()
{
    delete tagModel;
}

void TagManager::load(){}

void TagManager::clear(){}

void TagManager::addTag(const QString& name){

    try
    {
        if(tagList.contains(name,Qt::CaseInsensitive))
            throw TagManagerException("Le tag que vous essayez d'jouter existe déjà");
        else
        {
            tagList<<name;
            tags.insert(name,QSet<Note*>());
            tagModel->setStringList(tagList);
        }
    }
    catch(TagManagerException& e)
    {
        QMessageBox::warning(&TagManagerWidget::getInstance(),"Warning",e.getInfo());
        return;
    }
}

void TagManager::deleteTag(const QString& name){
    tagList.removeOne(name);
    tags.erase(tags.find(name));
    tagModel->setStringList(tagList);
}

void TagManager::addAssociation(const QString& name,const QSet<Note*>& note)
{
    tags[name]= tags[name].unite(note);
    QMessageBox::information(&TagManagerWidget::getInstance(),"info","Association successfully added");
}
void TagManager::deleteAssociation(const QString& name, Note* note)
{
    tags[name].remove(note);
}

QStringListModel* TagManager::getModel() const
{
    return tagModel;
}



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

TagManagerWidget::TagManagerWidget(QWidget* parent):QWidget(parent),manager(&TagManager::getInstance())
{
    //ALlocation des Widgets
    layout = new QVBoxLayout(this);
    QHBoxLayout* buttons = new QHBoxLayout();
    deleteTagBtn = new QPushButton("-",this);
    addTagBtn = new QPushButton("+",this);
    //tagging = new QGroupBox(this);
    searchField = new QComboBox(this);
    viewer = new QListView(this);

    viewer->setModel(manager->getModel());
    viewer->setSelectionMode(QAbstractItemView::ExtendedSelection);

    deleteTagBtn->setEnabled(true); //Empêche de supprimer un tag sans en avoir sélectionné un.

    buttons->addWidget(addTagBtn);
    buttons->addWidget(deleteTagBtn);

    layout->addWidget(searchField);
    layout->addWidget(viewer);
    layout->addLayout(buttons);

    viewer->setMinimumSize(100,150);
    viewer->setMaximumSize(150,400);
    viewer->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);

    QObject::connect(addTagBtn,SIGNAL(clicked()),this,SLOT(addTags()));
    QObject::connect(deleteTagBtn,SIGNAL(clicked()),this,SLOT(deleteTags()));
}

TagManagerWidget::~TagManagerWidget()
{
    delete deleteTagBtn;
    delete addTagBtn;
    //delete tagging;
    delete searchField;
    delete layout;
    manager->releaseInstance();
}

void TagManagerWidget::addTags()
{
    try{
        bool ok=false;
        QString name = QInputDialog::getText(this,"New Tag","Set the name of your new tag :", QLineEdit::Normal, QString() , &ok);
        if(ok && !name.isEmpty())
            Workspace::getInstance().addTag(name);
            manager->addTag(name);
    }catch(TagManagerException& e){
        QMessageBox::warning(this,"Alert",e.getInfo());
        return;
    }
}

void TagManagerWidget::deleteTags()
{
    QItemSelectionModel *selection = viewer->selectionModel();
    QModelIndexList listeSelections = selection->selectedIndexes();
    for (int i = 0 ; i < listeSelections.size() ; i++)
    {
        QVariant elementSelectionne = manager->getModel()->data(listeSelections[i], Qt::DisplayRole);
        manager->deleteTag(elementSelectionne.toString());
    }
}

void TagManagerWidget::setAssociation(){
    /*QSet<Note*> select = Workspace::getInstance().getSelectedNote();
    if (select.isEmpty())
        return;
    QItemSelectionModel *selection = viewer->selectionModel();
    QModelIndexList listeSelections = selection->selectedIndexes();
    for (int i = 0 ; i < listeSelections.size() ; i++)
    {
        QVariant elementSelectionne = manager->getModel()->data(listeSelections[i], Qt::DisplayRole);
        manager->addAssociation(elementSelectionne.toString(),select);
    }*/
}

void TagManagerWidget::deleteAssociation()
{
    return;
}
