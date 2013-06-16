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

BinaryWidget::~BinaryWidget()
{
    delete descpt;
    delete path;
    delete bwse;
    delete hlayout;
}

void BinaryWidget::enableSave()
{
    //save->setEnabled(true);
}

void BinaryWidget::updateNote()
{
    binary->setTitle(title->text());
    binary->setDesc(descpt->toPlainText());
    binary->setBinPath(pathEdit->text());
    binary->setModify(false);
}
void BinaryWidget::modification()
{
    binary->setModify(true);
    emit mod();
}

Note* BinaryWidget::getNote()
{
    return dynamic_cast<Note*>(binary);
}

void BinaryWidget::getPath()
{
    QString fichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "*.*");
    binary->setBinPath(fichier);
    pathEdit->setText(binary->getBinPath());
}

//Méthodes de AudioWidget

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

AudioWidget::~AudioWidget(){}

void AudioWidget::lire()
{
    stop->setEnabled(true);
    //Je ne sais pas ce qu'il faut mettre ici
}

void AudioWidget::arreter()
{
    stop->setEnabled(false);
    //Je ne sais pas ce qu'il faut mettre ici non plus
}

Note* AudioWidget::getNote()
{
    return dynamic_cast<Note*>(audio);
}

//Methodes de Image Widget

ImageWidget::ImageWidget(Image* i,QWidget* parent):BinaryWidget(i,parent),image(i)
{
    //Chez moi ces lignes font planter l'application. Essaye de compiler chez toi.
    /*img = new QPixmap(image->getPath());
    label->setPixmap((const QPixmap&) img);
    //label->adjustSize();
    layout->addWidget(label);*/
}
ImageWidget::~ImageWidget(){}

Note* ImageWidget::getNote()
{
    return dynamic_cast<Note*>(image);
}

//Méthodes de Video Widget

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

VideoWidget::~VideoWidget(){}

void VideoWidget::lire()
{
    play->setText("Play");
    stop->setEnabled(true);
    pause->setEnabled(true);
    //Je ne sais pas ce qu'il faut mettre ici
}

void VideoWidget::setPause()
{
    play->setText("Resume");
    pause->setEnabled(false);
    //Je ne sais pas ce qu'il faut mettre ici
}

void VideoWidget::arreter()
{
    stop->setEnabled(false);
    pause->setEnabled(false);
    //Je ne sais pas ce qu'il faut mettre ici
}

Note* VideoWidget::getNote()
{
    return dynamic_cast<Note*>(video);
}
