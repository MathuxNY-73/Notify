#include "mainwindow.h"
#include "ui_mainwindow.h"


/**
 * \fn MainWindow::MainWindow(QWidget *parent)
 * \brief Construction de la MainWindow
 * \param Widget parent de MainWindow. 'NULL' par defaut.
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    id = 0;

    NoteManager::getInstance();

    //Configuration

    QWidget* spacer= new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);


    //Action
    ui->actionArticle->setIcon(QIcon("/Users/Antoine/Documents/ProjetInfo/Github/Notify_Github/Icons/articleIcon48.png"));
    ui->actionDocument->setIcon(QIcon("/Users/Antoine/Documents/ProjetInfo/Github/Notify_Github/Icons/document1Icon48.png"));
    ui->actionImage_2->setIcon(QIcon("/Users/Antoine/Documents/ProjetInfo/Github/Notify_Github/Icons/imageIcon48.png"));
    ui->actionAudio->setIcon(QIcon("/Users/Antoine/Documents/ProjetInfo/Github/Notify_Github/Icons/audioIcon48.png"));
    ui->actionVideo->setIcon(QIcon("/Users/Antoine/Documents/ProjetInfo/Github/Notify_Github/Icons/videoIcon48.png"));
    ui->actionQuit->setIcon(QIcon("/Users/Antoine/Documents/ProjetInfo/Github/Notify_Github/Icons/stop_2_48.png"));

    //Toolbar
    ui->toolBar->addAction(ui->actionArticle);
    ui->toolBar->addAction(ui->actionDocument);
    ui->toolBar->addAction(ui->actionImage_2);
    ui->toolBar->addAction(ui->actionAudio);
    ui->toolBar->addAction(ui->actionVideo);
    ui->toolBar->addWidget(spacer);
    ui->toolBar->addAction(ui->actionQuit);

    //Connection
    QObject::connect(ui->actionQuit,SIGNAL(triggered()),qApp,SLOT(quit()));
    QObject::connect(ui->actionWorkspace,SIGNAL(triggered()),this,SLOT(newWorkspace()));
    QObject::connect(ui->actionArticle,SIGNAL(triggered()),this,SLOT(newArticle()));
    QObject::connect(ui->actionDocument,SIGNAL(triggered()),this,SLOT(newDocument()));
    QObject::connect(ui->actionVideo,SIGNAL(triggered()),this,SLOT(newVideo()));
    QObject::connect(ui->actionImage_2,SIGNAL(triggered()),this,SLOT(newImage()));
    QObject::connect(ui->actionAudio,SIGNAL(triggered()),this,SLOT(newAudio()));
    QObject::connect(ui->actionSave,SIGNAL(triggered()),this,SLOT(saveWorkspace()));
    QObject::connect(ui->actionSave_As,SIGNAL(triggered()),this,SLOT(saveWorkspaceAs()));

    QObject::connect(this,SIGNAL(clear()),&Workspace::getInstance(),SLOT(clear()));

    //Zone de travail

    gridLayout = new QGridLayout(ui->centralwidget);
    ui->centralwidget->setLayout(gridLayout);

    work = &Workspace::getInstance(ui->centralwidget);
    editor = &Editorspace::getInstance(ui->centralwidget);

    gridLayout->addWidget(work,0,0,1,1);
    gridLayout->addWidget(editor,0,1,2,1);
    gridLayout->addWidget(&Tags::TagManagerWidget::getInstance(ui->centralwidget),1,0,1,1);
}

/**
 * \fn MainWindow::~MainWindow()
 * \brief Destructeur de MainWindow
 */
MainWindow::~MainWindow()
{
    delete ui;
    delete gridLayout;
    Tags::TagManagerWidget::releaseInstance();
    Workspace::releaseInstance();
    Editorspace::releaseInstance();
}

/**
 * \fn QString MainWindow::getPath() const
 * \brief Récupérer un chemin défini par l'utilisateur.
 * \return Retourne le chemin choisi.
 * Methode servant à recupérer le chemin de sauvegarde des fichiers par l'intermédiaire d'une boîte de dialogue.
 */
QString MainWindow::getPath() const
{
    QString dossier = QFileDialog::getSaveFileName(ui->centralwidget, "Save a workspace", QString(), "*.*");
    if(dossier=="")
        return "";
    QDir workFolder(dossier);
    if(!workFolder.mkpath(dossier))
         throw MyException("An error occured while creating the workspace directory");
    else
    {
        return QString(dossier);
     }
}

/**
 * \fn void MainWindow::newArticle()
 * \brief Slot permmettant de créer un nouvel article.
 */
void MainWindow::newArticle()
{
    if(NoteManager::exist())
    {
        Article* a =dynamic_cast<Article*>(NoteManager::getInstance().getFactory()["Article"]->buildNewNote("Titre de l'article"));
        try{
            work->addNote(a);
        }catch(MyException& e){
            QMessageBox::warning(ui->centralwidget,"Error",e.getInfo());
            delete a;
            return;
        }
        id++;
    }

}

/**
 * \fn void MainWindow::newDocument()
 * \brief Slot permmettant de créer un nouveau document.
 */
void MainWindow::newDocument()
{
    if(NoteManager::exist())
    {
        Document* d =dynamic_cast<Document*>(NoteManager::getInstance().getFactory()["Document"]->buildNewNote("Titre du document"));
        try{
            work->addNote(d);
        }catch(MyException& e){
            QMessageBox::warning(ui->centralwidget,"Error",e.getInfo());
            delete d;
            return;
        }
        id++;
    }

}

/**
 * \fn void MainWindow::newAudio()
 * \brief Slot permmettant de créer un nouvel audio.
 */
void MainWindow::newAudio()
{
    if(NoteManager::exist())
    {
        Audio* a = dynamic_cast<Audio*>(NoteManager::getInstance().getFactory()["Audio"]->buildNewNote("Titre de l'audio"));
        try{
            work->addNote(a);
        }catch(MyException& e){
            QMessageBox::warning(ui->centralwidget,"Error",e.getInfo());
            delete a;
            return;
        }
        id++;
    }

}

/**
 * \fn void MainWindow::newVideo()
 * \brief Slot permmettant de créer une nouvelle video.
 */
void MainWindow::newVideo()
{
    if(NoteManager::exist())
    {
        Video* v = dynamic_cast<Video*>(NoteManager::getInstance().getFactory()["Video"]->buildNewNote("Titre de la video"));
        try{
            work->addNote(v);
        }catch(MyException& e){
            QMessageBox::warning(ui->centralwidget,"Error",e.getInfo());
            delete v;
            return;
        }
        id++;
    }

}

/**
 * \fn void MainWindow::newImage()
 * \brief Slot permmettant de créer une nouvelle image.
 */
void MainWindow::newImage()
{
    if(NoteManager::exist())
    {
        Image* i = dynamic_cast<Image*>(NoteManager::getInstance().getFactory()["Image"]->buildNewNote("Titre de l'image"));
        try{
            work->addNote(i);
        }catch(MyException& e){
            QMessageBox::warning(ui->centralwidget,"Error",e.getInfo());
            delete i;
            return;
        }
        id++;
    }

}

/**
 * \fn void MainWindow::newWorkspace()
 * \brief Nouveau Workspace
 * Slot permettant de changer de workspace en proposant la sauvegarde à l'utilisateur.
 */
void MainWindow::newWorkspace()
{
    if(NoteManager::exist())
    {
        QMessageBox message(this);
        message.setText("An instance of workspace already exists.");
        message.setInformativeText("Do you want to save your changes ?");
        message.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        message.setDefaultButton(QMessageBox::Save);
        message.setIcon(QMessageBox::Warning);
        int ret = message.exec();
        switch(ret){
        case QMessageBox::Save:
            try{
                saveWorkspace();
                NoteManager::releaseInstance();
                NoteManager::getInstance();
        }catch(MyException& e)
            {
                QMessageBox::critical(ui->centralwidget,"Alert",e.getInfo());
            }
            break;
        case QMessageBox::Discard:
            NoteManager::releaseInstance();
            emit clear();
            NoteManager::getInstance();
            return;
        case QMessageBox::Cancel:
            return;
        default:
            return;
        }
    }
}

/**
 * \fn void MainWindow::saveWorkspace()
 * \brief Fonction de sauvegarde (Save)
 * Slot permettant de faire appelle à la fonction de sauvegarde du workspace.
 */
void MainWindow::saveWorkspace()
{
    if(NoteManager::getInstance().getPath()=="")
    {
        saveWorkspaceAs();
        return;
    }
    Workspace::getInstance().saveInFile();
}

/**
 * \fn void MainWindow::saveWorkspaceAs()
 * \brief Fontion de sauvegarde (Save As..)
 * Slot faisant appelle à la fonction de sauvegarde du Workspace en passant en argument le chemin de sauvegarde choisi par l'utilisateur.
 */
void MainWindow::saveWorkspaceAs()
{
    QString dossier = QFileDialog::getSaveFileName(ui->centralwidget, "Save workspace as...", QString(), "*.*");
    QDir workFolder(dossier);
    if(!workFolder.mkpath(dossier))
         throw MyException("An error occured while creating the workspace directory");
    else
    {
        NoteManager::getInstance().setPath(QString(dossier)+"/");
        QMessageBox::information(ui->centralwidget,"Information","Le chemin est :"+NoteManager::getInstance().getPath());
        Workspace::getInstance().saveInFile();
     }
}
