//
//  binarywidget.cpp
//  LO21_Projet
//
//  Created by Anthony WEIBEL and Antoine POUILLAUDE on 05/06/13.
//  Copyright (c) 2013 Antoine POUILLAUDE. All rights reserved.
//

#include "binarywidget.h"
#include "binary.h"
#include "notewidget.h"

//Methodes de Binary Widgets

/**
 * \fn BinaryWidget::BinaryWidget(Binary* b,QWidget* parent)
 * \brief Constructeur de la classe Binary
 * \param Pointeur sur l'objet Binary associé au widget.
 * \param Widget parent. Par defaut 'NULL'.
 */
BinaryWidget::BinaryWidget(Binary* b,QWidget* parent):NoteWidget(b,parent),binary(b)
{

    //Allocation des Widgets
    hlayout = new QHBoxLayout();
    bwse = new QPushButton("Browse",this);
    path = new QLabel("Path : ",this);
    pathEdit = new QLabel(this);
    descpt = new QTextEdit("Description",this);
    //save = new QPushButton("Save",this);
    //save->setEnabled(false);
    bwse->setMaximumWidth(150);
    //bwse->setStyle();
    QObject::connect(descpt,SIGNAL(textChanged()),this,SLOT(enableSave()));
    QObject::connect(title,SIGNAL(textChanged(QString)),this,SLOT(enableSave()));
    QObject::connect(bwse,SIGNAL(clicked()),this,SLOT(getPath()));

    //Layout
    hlayout->addWidget(path);
    hlayout->addWidget(pathEdit);
    hlayout->addWidget(bwse);
    layout->addLayout(hlayout);
    layout->addWidget(descpt);


    pathEdit->setText(binary->getBinPath());
    path->setMaximumWidth(35);
    path->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);

    title->setText(binary->getTitle());
    descpt->setText(binary->getDesc());
}

/**
 * \fn BinaryWidget::~BinaryWidget()
 * \brief Destructeur de la classe BinaryWidget
 */
BinaryWidget::~BinaryWidget()
{
    delete descpt;
    delete path;
    delete bwse;
    delete hlayout;
}

/**
 * \fn Note* BinaryWidget::getNote()
 * \brief Récupérer la partie Note.
 * \return Un pointeur sur la partie note du binaire associé au Widget
 */
Note* BinaryWidget::getNote()
{
    return dynamic_cast<Note*>(binary);
}

/**
 * \fn void BinaryWidget::updateNote()
 * \brief Mise à jour du binaire associée
 */
void BinaryWidget::updateNote()
{
    binary->setTitle(title->text());
    binary->setDesc(descpt->toPlainText());
    binary->setBinPath(pathEdit->text());
    binary->setModify(false);
}

/**
 * \fn void BinaryWidget::modification()
 * \brief Slots de modification.
 * Cette fonction est appelée si les divers champs du widget sont modifiés
 */
void BinaryWidget::modification()
{
    binary->setModify(true);
    emit mod();
}

/**
 * \fn void BinaryWidget::getPath()
 * \brief Récupération du chemin vers le fichier binaire.
 * Ce slot ouvre une fenêtre de dialogue pour selectionner le fichier à associer au binaire.
 */
void BinaryWidget::getPath()
{
    QString fichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "*.*");
    binary->setBinPath(fichier);
    pathEdit->setText(binary->getBinPath());
}

//Méthodes de AudioWidget

/**
 * \fn AudioWidget::AudioWidget(Audio* a, QWidget* parent)
 * \brief Constructeur de l'objet AudioWidget
 * \param Pointeur sur l'audio associé au widget.
 * \param Widget parent.
 */
AudioWidget::AudioWidget(Audio* a, QWidget* parent):BinaryWidget(a,parent),audio(a)
{
    //Allocations des widgets et connection
    play = new QPushButton("Play",this);
    play->setMaximumWidth(100);
    play->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    QObject::connect(play,SIGNAL(clicked()),this,SLOT(lire()));

    stop = new QPushButton("Stop", this);
    stop->setMaximumWidth(100);
    stop->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    QObject::connect(stop,SIGNAL(clicked()),this,SLOT(arreter()));

    hlayout = new QHBoxLayout();
    QWidget* spacer= new QWidget(this);
    spacer->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);

    //Configuration  des widgets
    play->setToolTip("Push to play");
    stop->setToolTip("Push to stop");
    stop->setEnabled(false);

    //Mise en layout des widgets
    hlayout->addWidget(spacer);
    hlayout->addWidget(play);
    hlayout->addWidget(stop);
    layout->addLayout(hlayout);

}

/**
 * \fn AudioWidget::~AudioWidget()
 * \brief Destructeur de l'objet Widget Audio
 */
AudioWidget::~AudioWidget(){}

/**
 * \fn void AudioWidget::lire()
 * \brief Slot de lecture du fichier audio.
 * \bug Non définie.
 */
void AudioWidget::lire()
{
    stop->setEnabled(true);
    //Je ne sais pas ce qu'il faut mettre ici
}

/**
 * \fn void AudioWidget::arreter()
 * \brief Slot pour arrêter la lecture du fichier audio
 * \bug Non définie
 */
void AudioWidget::arreter()
{
    stop->setEnabled(false);
    //Je ne sais pas ce qu'il faut mettre ici non plus
}

/**
 * \fn Note* AudioWidget::getNote()
 * \brief Récupérer la partie note.
 * \return Pointeur sur la partie Note de l'Audio.
 */
Note* AudioWidget::getNote()
{
    return dynamic_cast<Note*>(audio);
}

//Methodes de Image Widget

/**
 * \fn ImageWidget::ImageWidget(Image* i,QWidget* parent)
 * \brief Constructeur de l'objet ImageWidget
 * \param Pointeur sur l'image à associer au widget
 * \param Widget parent
 * \bug Je ne peux pas afficher l'image car l'application crash.
 */
ImageWidget::ImageWidget(Image* i,QWidget* parent):BinaryWidget(i,parent),image(i)
{
    /*img = new QPixmap(image->getPath());
    label->setPixmap((const QPixmap&) img);
    //label->adjustSize();
    layout->addWidget(label);*/
}

/**
 * \fn ImageWidget::~ImageWidget()
 * \brief Destructeur du widget
 */
ImageWidget::~ImageWidget(){}

/**
 * \fn Note* ImageWidget::getNote()
 * \brief Récupérer la partie note
 * \return Pointeur sur la partie Note de l'Image
 */
Note* ImageWidget::getNote()
{
    return dynamic_cast<Note*>(image);
}

//Méthodes de Video Widget

/**
 * \fn VideoWidget::VideoWidget(Video* v,QWidget* parent)
 * \brief Constructeur de l'objet Video Widget
 * \param Pointeur sur l'objet video à associer au widget
 * \param Widget parent
 */
VideoWidget::VideoWidget(Video* v,QWidget* parent):BinaryWidget(v,parent),video(v)
{

    //Allocations des widgets et connection
    play = new QPushButton("Play",this);
    play->setMaximumWidth(100);
    play->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    QObject::connect(play,SIGNAL(clicked()),this,SLOT(lire()));

    pause = new QPushButton("Pause",this);
    pause->setMaximumWidth(100);
    pause->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    QObject::connect(pause,SIGNAL(clicked()),this,SLOT(setPause()));

    stop = new QPushButton("Stop", this);
    stop->setMaximumWidth(100);
    stop->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    QObject::connect(stop,SIGNAL(clicked()),this,SLOT(arreter()));

    hlayout = new QHBoxLayout();

    QWidget* spacer= new QWidget(this);
    spacer->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);

    //Configuration  des widgets
    play->setToolTip("Push to play");
    pause->setToolTip("Push to pause");
    stop->setToolTip("Push to stop");
    pause->setEnabled(false);
    stop->setEnabled(false);

    //Mise en layout des widgets
    hlayout->addWidget(spacer);
    hlayout->addWidget(play);
    hlayout->addWidget(pause);
    hlayout->addWidget(stop);
    layout->addLayout(hlayout);
}

/**
 * \fn VideoWidget::~VideoWidget()
 * \brief Destructeur de l'objet VideoWidget
 */
VideoWidget::~VideoWidget(){}

/**
 * \fn void VideoWidget::lire()
 * \brief Slot de lecture du fichier Video
 */
void VideoWidget::lire()
{
    play->setText("Play");
    stop->setEnabled(true);
    pause->setEnabled(true);
    //Je ne sais pas ce qu'il faut mettre ici
}

/**
 * \fn void VideoWidget::setPause()
 * \brief Slot de mise en pause de la video
 */
void VideoWidget::setPause()
{
    play->setText("Resume");
    pause->setEnabled(false);
    //Je ne sais pas ce qu'il faut mettre ici
}

/**
 * \fn void VideoWidget::arreter()
 * \brief Slot d'arrêt de lecture de la video
 */
void VideoWidget::arreter()
{
    stop->setEnabled(false);
    pause->setEnabled(false);
    //Je ne sais pas ce qu'il faut mettre ici
}

/**
 * \fn Note* VideoWidget::getNote()
 * \brief Récupérer la partie note de l'objet video associé
 * \return Pointeur sur la partie note en question.
 */
Note* VideoWidget::getNote()
{
    return dynamic_cast<Note*>(video);
}
