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
    tagModel = new QStandardItemModel();
}

TagManager::~TagManager()
{
    delete tagModel;
}

void TagManager::load(){}

void TagManager::clear(){}
void TagManager::addTag(const QString& name){
    QStandardItem* item = new QStandardItem(name);
    tags.insert(item,QSet<Note*>());
    tagModel->appendRow(item);
}

void TagManager::deleteTag(int row){
    QStandardItem* item = tagModel->item(row+1);
    tags.remove(item);
    tagModel->removeRow(row+1);
}

void TagManager::addAssociation(int row, Note* note)
{
    tags[tagModel->item(row)].insert(note);
}
void TagManager::deleteAssociation(int row, Note* note)
{
    tags[tagModel->item(row)].remove(note);
}

QStandardItemModel* TagManager::getModel() const
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
    bool ok=false;
    QString name = QInputDialog::getText(this,"New Tag","Set the name of your new tag :", QLineEdit::Normal, QString() , &ok);
    if(ok && !name.isEmpty())
        manager->addTag(name);
    else
        return;
}

void TagManagerWidget::deleteTags()
{
    QItemSelectionModel *selection = viewer->selectionModel();
    QModelIndexList listeSelections = selection->selectedIndexes();
    for (int i = 0 ; i < listeSelections.size() ; i++)
    {
        QVariant elementSelectionne = manager->getModel()->data(listeSelections[i], Qt::DisplayRole);
        manager->deleteTag(elementSelectionne.toModelIndex().row());
    }
}

void TagManagerWidget::setAssociation(){

}

void TagManagerWidget::deleteAssociation()
{

}
