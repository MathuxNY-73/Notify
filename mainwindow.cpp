#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    id = 0;

    NoteManager::getInstance();

    //Configuration
    //ui->actionWorkspace->setEnabled(false);

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


    //Zone de travail

    gridLayout = new QGridLayout(ui->centralwidget);
    ui->centralwidget->setLayout(gridLayout);

    work = &Workspace::getInstance(ui->centralwidget);
    editor = &Editorspace::getInstance(ui->centralwidget);

    gridLayout->addWidget(work,0,0,1,1);
    gridLayout->addWidget(editor,0,1,2,1);
    gridLayout->addWidget(&Tags::TagManagerWidget::getInstance(ui->centralwidget),1,0,1,1);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete gridLayout;
    Tags::TagManagerWidget::releaseInstance();
    Workspace::releaseInstance();
    Editorspace::releaseInstance();
}

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
            saveInFile();
            try{
                QString path = getPath();
                if (path!="")
                {
                    Workspace::getInstance().getFile("");
                    NoteManager::releaseInstance();
                    NoteManager::getInstance().setPath(path);
                }
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

QString MainWindow::getPath() const
{
    QString dossier = QFileDialog::getSaveFileName(ui->centralwidget, "Save a workspace", QString(), "*.*");
    QDir workFolder(dossier);
    //bool ok=false;
    //QString name = QInputDialog::getText(ui->centralwidget,"New Workspace","Set the name of your new Workspace:", QLineEdit::Normal, QString() , &ok);
        if(!workFolder.mkpath(dossier))
            throw MyException("An error occured while creating the workspace directory");
        else
        {
            //workPath=""+dossier+"/"+name;
            QMessageBox::information(ui->centralwidget,"Information","Le chemin est :"+dossier);
            return QString(dossier);
        }
}

void MainWindow::newArticle()
{
    if(NoteManager::exist())
    {
        Article* a = new Article(id,"Titre de l'article","Texte de l'article");
        work->addNote(a);
        id++;
    }

}

void MainWindow::newDocument()
{
    if(NoteManager::exist())
    {
        Document* d = new Document(id,"Titre du document");
        work->addNote(d);
        id++;
    }

}

void MainWindow::newImage()
{
    if(NoteManager::exist())
    {
        Image* i = new Image(id,"Titre de l'image","Description de l'image","/Users/Antoine/Pictures/avion.jpg");
        work->addNote(i);
        id++;
    }

}

void MainWindow::newVideo()
{
    if(NoteManager::exist())
    {
        Video* v = new Video(id,"Titre de la video","Description de la video","/Users/Antoine/Movies/themask.avi");
        work->addNote(v);
        id++;
    }

}

void MainWindow::newAudio()
{
    if(NoteManager::exist())
    {
        Audio* a = new Audio(id,"Titre du fichier audio","Description du fichier audio","/Users/Antoine/Music/chattons.wav");
        work->addNote(a);
        id++;
    }

}

void MainWindow::saveInFile() const{
    return;
}

