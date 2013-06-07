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

    //Layout
    hlayout->addWidget(path);
    hlayout->addWidget(bwse);
    layout->addLayout(hlayout);
    layout->addWidget(descpt);

     //Je pense que cette est à écrire plutôt dans les classes filles.
    path->setText("Path : "+binary->getPath());
    title->setText(binary->getTitle());
    descpt->setText(binary->getDesc());
}

//Méthodes de AudioWidget

AudioWidget::AudioWidget(Audio* a, QWidget* parent):BinaryWidget(a,parent),audio(a)
{
    //Allocations des widgets
    pl = new QPushButton("Play",this);
    stop = new QPushButton("Stop", this);
    glayout = new QGridLayout();
    cursor = new QSlider(Qt::Horizontal,this);

    //Configuration  des widgets
    pl->setToolTip("Push to play");
    stop->setToolTip("Push to stop");

    //Mise en layout des widgets
    glayout->addWidget(cursor,0,0,1,5);
    glayout->addWidget(pl,0,5,1,1);
    glayout->addWidget(stop,0,6,1,1);
    layout->addLayout(glayout);
}

void AudioWidget::setPlay()
{

}

void AudioWidget::setStop()
{

}

ImageWidget::ImageWidget(Image* i,QWidget* parent):BinaryWidget(i,parent),image(i)
{
    //Chez moi ces lignes font planter l'application. Essaye de compiler chez toi.
    img = new QPixmap(image->getPath());
    label->setPixmap((const QPixmap&) img);
    //label->adjustSize();
    layout->addWidget(label);
}

VideoWidget::VideoWidget(Video* v,QWidget* parent):BinaryWidget(v,parent),video(v)
{

}
