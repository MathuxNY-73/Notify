//
//  binarywidget.cpp
//  LO21_Projet
//
//  Created by Anthony WEIBEL and Antoine POUILLAUDE on 05/06/13.
//  Copyright (c) 2013 Antoine POUILLAUDE. All rights reserved.
//

#include "binarywidget.h"

BinaryWidget::BinaryWidget(Binary* b,QWidget* parent):NoteWidget(parent),binary(b)
{
    //Allocation des Widgets
    hlayout = new QHBoxLayout(this);
    bwse = new QPushButton("Browse",this);
    path = new QLabel("Path : ",this);
    descpt = new QTextEdit("Description",this);

    //Layout
    hlayout->addWidget(path);
    hlayout->addWidget(bwse);

    //layout->addLayout(hlayout);  Je pense que cette est à écrire plutôt dans les classes filles.
    path->setText("Path : "+binary->getPath());
    descpt->setText(binary->getDesc());

}

AudioWidget::AudioWidget(Audio* a, QWidget* parent):BinaryWidget(a,parent),audio(a)
{


}

ImageWidget::ImageWidget(Image* i,QWidget* parent):BinaryWidget(i,parent),image(i)
{
    glayout = new QGridLayout(this);
    img = new QPixmap();
}

VideoWidget::VideoWidget(Video* v,QWidget* parent):BinaryWidget(v,parent),video(v)
{

}
