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

BinaryWidget::BinaryWidget(Binary* b,QWidget* parent):NoteWidget(parent),binary(b)
{
    //Allocation des Widgets
    hlayout = new QHBoxLayout();
    bwse = new QPushButton("Browse",this);
    path = new QLabel("Path : ",this);
    descpt = new QTextEdit("Description",this);
    save = new QPushButton("Save",this);
    save->setEnabled(false);
    QObject::connect(descpt,SIGNAL(textChanged()),this,SLOT(enableSave()));
    QObject::connect(title,SIGNAL(clicked()),this,SLOT(enableSave()));

    //Layout
    hlayout->addWidget(path);
    hlayout->addWidget(bwse);
    layout->addLayout(hlayout);
    layout->addWidget(descpt);
    layout->addWidget(save);

     //Je pense que cette est à écrire plutôt dans les classes filles.
    path->setText("Path : "+binary->getPath());
    title->setText(binary->getTitle());
    descpt->setText(binary->getDesc());
}
void BinaryWidget::enableSave()
{
    save->setEnabled(true);
}

void BinaryWidget::updateNote()
{
    binary->setTitle(title->text());
    binary->setDesc(descpt->toPlainText());
    binary->setPath(path->text());
    binary->setModify(false);
}
void BinaryWidget::modification()
{
    binary->setModify(true);
    emit isModified();
}

//Méthodes de AudioWidget

AudioWidget::AudioWidget(Audio* a, QWidget* parent):BinaryWidget(a,parent),audio(a)
{
    //Allocations des widgets et connection
    play = new QPushButton("Play",this);
    QObject::connect(play,SIGNAL(clicked()),this,SLOT(QSound::play()));

    stop = new QPushButton("Stop", this);
    QObject::connect(stop,SIGNAL(clicked()),this,SLOT(QSound::stop()));

    glayout = new QGridLayout();

    //Configuration  des widgets
    play->setToolTip("Push to play");
    stop->setToolTip("Push to stop");
    stop->setEnabled(false);

    //Mise en layout des widgets
    glayout->addWidget(play,0,5,1,1);
    glayout->addWidget(stop,0,6,1,1);
    layout->addLayout(glayout);

}

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

//Methodes de Image Widget

ImageWidget::ImageWidget(Image* i,QWidget* parent):BinaryWidget(i,parent),image(i)
{
    //Chez moi ces lignes font planter l'application. Essaye de compiler chez toi.
    img = new QPixmap(image->getPath());
    label->setPixmap((const QPixmap&) img);
    //label->adjustSize();
    layout->addWidget(label);
}

//Méthodes de Video Widget

VideoWidget::VideoWidget(Video* v,QWidget* parent):BinaryWidget(v,parent),video(v)
{

    //Allocations des widgets et connection
    play = new QPushButton("Play",this);
    QObject::connect(play,SIGNAL(clicked()),this,SLOT(lire()));

    pause = new QPushButton("Pause",this);
    QObject::connect(pause,SIGNAL(clicked()),this,SLOT(setPause()));

    stop = new QPushButton("Stop", this);
    QObject::connect(stop,SIGNAL(clicked()),this,SLOT(arreter()));

    glayout = new QGridLayout();

    //Configuration  des widgets
    play->setToolTip("Push to play");
    pause->setToolTip("Push to pause");
    stop->setToolTip("Push to stop");
    pause->setEnabled(false);
    stop->setEnabled(false);

    //Mise en layout des widgets
    glayout->addWidget(play,0,5,1,1);
    glayout->addWidget(pause,0,6,1,1);
    glayout->addWidget(stop,0,7,1,1);
    layout->addLayout(glayout);
}

void VideoWidget::lire()
{
    stop->setEnabled(true);
    pause->setEnabled(true);
    //Je ne sais pas ce qu'il faut mettre ici
}

void VideoWidget::setPause()
{
    //Je ne sais pas ce qu'il faut mettre ici
}

void VideoWidget::arreter()
{
    stop->setEnabled(false);
    //Je ne sais pas ce qu'il faut mettre ici
}
