#include "tagmanager.h"


using namespace Tags;

/**
 * \brief TagManager::Instance Pointeur sur l'unique instance de TagManager
 */
TagManager* TagManager::Instance=0;

/**
 * \fn TagManager& TagManager::getInstance(QWidget* parent)
 * \brief Design Pattern Singleton : créer une instance, si ce n'est déjà fait, de la classe TagManager
 * \param parent Widget parent de celui que l'on s'apprête à créer
 * \return TagManager& Retourne une référence sur l'instance ainsi créée
 */
TagManager& TagManager::getInstance(QWidget* parent)
{
    if(!Instance)
        Instance = new TagManager(parent);
    return *Instance;
}

/**
 * \fn  void TagManager::releaseInstance()
 * \brief Design Pattern Singleton : détruit l'instance existante de TagManager.
 */
void TagManager::releaseInstance()
{
    if(Instance)
        delete Instance;
    Instance=0;
}

/**
 * \fn TagManager::TagManager(QWidget* parent)
 * \brief Constructeur de la classe TagManager
 * \param parent Widget parent de celui que l'on s'apprête à créer
 */
TagManager::TagManager(QWidget* parent)
{
    tagChosing = new QListWidget(parent);
}

/**
 * \fn TagManager::~TagManager()
 * \brief Destructeur de la classe TagManager
 */
TagManager::~TagManager()
{
    delete tagChosing;
}

/**
 * \fn QListWidget* TagManager::getModel() const
 * \brief TagManager::getModel
 * \return tagChosing Retourne le modèle employé dans la classe TagManager.
 */
QListWidget* TagManager::getModel() const
{
    return tagChosing;
}

/**
 * \fn void TagManager::load()
 * \brief Fonction de chargement des tags dans le cardre d'un changement de workspace.
 * \bug Non définie
 */
void TagManager::load(){}

/**
 * \fn  void TagManager::clear()
 * \brief Fontion de suppression de tout les tags dans le cas d'un changement de workspace
 * \bug Non définie
 */
void TagManager::clear(){}

/**
 * \fn  void TagManager::addTag(const QString& name)
 * \brief Création d'un tag
 * \param name  Nom du tag à créer
 *
 * Fonction de création d'un tag. Elle vérifie si le nom donné par l'utilisateur n'existe pas déjà
 */
void TagManager::addTag(const QString& name){

    try
    {
        if(tagList.contains(name,Qt::CaseInsensitive))
            throw TagManagerException("Le tag que vous essayez d'jouter existe déjà");
        else
        {
            tagList<<name;
            QListWidgetItem* item= new QListWidgetItem(name,tagChosing);
            item->setFlags(Qt::ItemIsUserCheckable);
            item->setFlags(Qt::ItemIsEnabled);
            item->setSelected(0);
            item->setCheckState(Qt::Unchecked);
            tags.insert(name,QSet<Note*>());
            tagChosing->addItem(item);
            Workspace::getInstance().addTag(name);
        }
    }
    catch(TagManagerException& e)
    {
        QMessageBox::warning(&TagManagerWidget::getInstance(),"Warning",e.getInfo());
        return;
    }
}

/**
 * \fn  void TagManager::deleteTag(const QString& name)
 * \brief Supprime le tag précédement sélectionné par l'utilisateur
 * \param name Nom du tag à supprimer
 */
void TagManager::deleteTag(const QString& name){
    tagList.removeOne(name);
    tags.erase(tags.find(name));
    QList<QListWidgetItem*> listFound=tagChosing->findItems(name,Qt::MatchContains);
    if(!listFound.isEmpty())
        tagChosing->removeItemWidget(listFound.at(0));
}

/**
 * \fn void TagManager::addAssociation(const QString& name,Note* note)
 * \brief Créer une association entre un tag et une note fournie en paramètre
 * \param name Nom du tag auquel l'on souhaite associer la note
 * \param note Pointeur sur la note que l'on souhaite associer au tag 'name'
 */
void TagManager::addAssociation(const QString& name,Note* note)
{
    tags[name].insert(note);
}

/**
 * \fn  void TagManager::deleteAssociation(const QString& name, Note* note)
 * \brief Supprime une association de la table des associations entres tags et notes
 * \param name  Nom du tag associé à la note
 * \param note  Pointeur sur la note à retirer de la table
 */
void TagManager::deleteAssociation(const QString& name, Note* note)
{
    tags[name].remove(note);
}

/**
 * \brief TagManagerWidget::Instance Pointeur sur l'unique instance de TagManagerWidget
 */
TagManagerWidget* TagManagerWidget::Instance=0;

/**
 * \fn TagManagerWidget& TagManagerWidget::getInstance(QWidget* parent)
 * \brief Cette fonction sert à récupérer l'instance de TagManagerWidget
 * \param parent Widget parent du widgte que l'on s'apprête à créer
 * \return TagManagerWidget& Retourne l'instance de TagManagerWidget
 */
TagManagerWidget& TagManagerWidget::getInstance(QWidget* parent)
{
    if(!Instance)
        Instance = new TagManagerWidget(parent);
    return *Instance;
}

/**
 * \fn void TagManagerWidget::releaseInstance()
 * \brief Relacher le Widget Tag Manager.
 *Fonction implémentée dans le cadre du design pattern Signleton
 */
void TagManagerWidget::releaseInstance()
{
    if(Instance)
        delete Instance;
    Instance=0;
}

/**
 * \fn TagManagerWidget::TagManagerWidget(QWidget* parent):QWidget(parent),manager(&TagManager::getInstance())
 * \brief Constructeur de TagManagerWidget
 * \param parent Widget parent de TagManagerWidget
 */
TagManagerWidget::TagManagerWidget(QWidget* parent):QWidget(parent),manager(&TagManager::getInstance())
{
    //ALlocation des Widgets
    layout = new QVBoxLayout(this);
    QHBoxLayout* buttons = new QHBoxLayout();
    deleteTagBtn = new QPushButton("-",this);
    addTagBtn = new QPushButton("+",this);
    searchField = new QComboBox(this);

    buttons->addWidget(addTagBtn);
    buttons->addWidget(deleteTagBtn);

    layout->addWidget(searchField);
    layout->addWidget(manager->getModel());
    layout->addLayout(buttons);

    manager->getModel()->setSelectionMode(QAbstractItemView::ExtendedSelection);
    manager->getModel()->setMinimumSize(100,150);
    manager->getModel()->setMaximumSize(150,400);
    manager->getModel()->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);

    QObject::connect(addTagBtn,SIGNAL(clicked()),this,SLOT(addTags()));
    QObject::connect(deleteTagBtn,SIGNAL(clicked()),this,SLOT(deleteTags()));
    QObject::connect(manager->getModel(),SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(selectedTags(QListWidgetItem*)));
}

/**
 * \fn TagManagerWidget::~TagManagerWidget()
 * \brief Destructeur de TagManagerWidget
 */
TagManagerWidget::~TagManagerWidget()
{
    delete deleteTagBtn;
    delete addTagBtn;
    delete searchField;
    delete layout;
    manager->releaseInstance();
}

/**
 * \fn void TagManagerWidget::setAssociation(Note* n)
 * \brief Créer un association entre un tag et une note
 * \param n Prend en paramètre la note qui doit être associée au tag.
 */
void TagManagerWidget::setAssociation(Note* n){
    if(selectedItems.isEmpty())
    {
        QMessageBox::information(this,"Information","Aucun tag selectionné");
        return;
    }
    QList<QListWidgetItem*>::Iterator it;
    for(it=selectedItems.begin() ; it!=selectedItems.end() ; ++it)
        manager->addAssociation((*it)->text(),n);
    QMessageBox::information(&TagManagerWidget::getInstance(),"info","Association successfully added");
}

/**
 * \fn void TagManagerWidget::deleteAssociation(Note* n)
 * \brief Fonction widget qui permet de défaire les associations créées
 * \param n La note avec laquelle on va faire la recherche dans la Map.
 */
void TagManagerWidget::deleteAssociation(Note* n)
{
    DeleteAssociationDialog dialog(n,this);
    try {
          dialog.exec();
          if (dialog.result()){
              manager->deleteAssociation(dialog.getTag(),n);
          }
      } catch (WorkspaceException& e){
          QMessageBox::information(this, "Erreur", e.getInfo());
      }
}

/**
 * \fn void TagManagerWidget::addTags()
 * \brief Ajouter un tag.
 * Permet d'ajouter un tag au nom défini par l'utilisateur. On ne peut pas ajouter un tag dont le nom existe déjà
 */
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

/**
 * \fn  void TagManagerWidget::deleteTags()
 * \brief Supprimer un tag
 * Permet de supprimer un tag existant
 */
void TagManagerWidget::deleteTags()
{
    if(selectedItems.isEmpty())
    {
        QMessageBox::information(this,"Information","Aucun tag selectionné");
        return;
    }
    QString list="";
    QList<QListWidgetItem*>::Iterator it;
    for(it=selectedItems.begin() ; it!=selectedItems.end() ; ++it)
    {
        list+=(*it)->text()+"\n";
        manager->getModel()->removeItemWidget(*it);
        selectedItems.erase(it);
        manager->deleteTag((*it)->text());
    }
    QMessageBox::information(this,"Information","Les tags suivant ont été supprimé : \n"+list);
}

/**
 * \fn void TagManagerWidget::selectedTags(QListWidgetItem * tag)
 * \brief Slot pour cocher où décocher les tags.
 * \param Récupére le tag sur lequel l'utilisateur a agi
 * \bug Ne décoche pas les tags
 */
void TagManagerWidget::selectedTags(QListWidgetItem * tag)
{
    if(tag->checkState()==Qt::Checked);
    {
        tag->setSelected(0);
        tag->setCheckState(Qt::Unchecked);
        if(selectedItems.contains(tag))
            selectedItems.removeOne(tag);
    }
    if(tag->checkState()==Qt::Unchecked);
    {
        tag->setSelected(1);
        tag->setCheckState(Qt::Checked);
        if(!selectedItems.contains(tag))
            selectedItems<<tag;
    }

}

/**
 * \fn DeleteAssociationDialog::DeleteAssociationDialog(Note* n, QWidget* parent)
 * \brief Création d'une fenêtre de dialogue pour récupérer les tags existants sur la note
 * \param La note sur laquelle on va faire la recherche
 * \param Le widget parent
 */
DeleteAssociationDialog::DeleteAssociationDialog(Note* n, QWidget* parent):QDialog(parent)
{
    setWindowTitle("Supprimer un tag");
    TagManager::constAssocIterator it;
    for(it = TagManager::getInstance().associationBegin(); it != TagManager::getInstance().associationEnd() ; ++it){
        if((*it).contains(n))
        {
            box.addItem(it.key(),QVariant(it.key()));
        }
    }
    QPushButton* ok = new QPushButton("Supprimer");
    QObject::connect(ok, SIGNAL(clicked()), this, SLOT(ok()));
    QPushButton* cancel = new QPushButton("Annuler");
    QObject::connect(cancel, SIGNAL(clicked()), this, SLOT(cancel()));
    QHBoxLayout* hLayout = new QHBoxLayout;
    hLayout->addWidget(ok);
    hLayout->addWidget(cancel);
    QVBoxLayout* vLayout = new QVBoxLayout;
    vLayout->addWidget(&box);
    vLayout->addLayout(hLayout);
    setLayout(vLayout);
}

/**
 * \fn  void DeleteAssociationDialog::ok()
 * \brief Action effectuée lorsque l'on appuie sur ok
 */
void DeleteAssociationDialog::ok(){
    selectedTag = box.itemData(box.currentIndex()).toString();
    done(1);
}

/**
 * \fn void DeleteAssociationDialog::cancel()
 * \brief On sort de la fenêtre de dialogue
 */
void DeleteAssociationDialog::cancel()
{
    done(0);
}
