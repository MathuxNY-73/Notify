//
//  binarywidget.cpp
//  LO21_Projet
//
//  Created by Anthony WEIBEL and Antoine POUILLAUDE on 05/06/13.
//  Copyright (c) 2013 Antoine POUILLAUDE. All rights reserved.
//

#include "binarywidget.h"
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

AudioWidget::AudioWidget(Audio* a, QWidget* parent):BinaryWidget(a,parent),audio(a)
{


}

ImageWidget::ImageWidget(Image* i,QWidget* parent):BinaryWidget(i,parent),image(i)
{
    img = new QPixmap(i->getPath());
    label->setPixmap((const QPixmap&) img);
    //label->adjustSize();
    layout->addWidget(label);
}

VideoWidget::VideoWidget(Video* v,QWidget* parent):BinaryWidget(v,parent),video(v)
{

}
