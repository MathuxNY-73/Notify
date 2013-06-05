//
//  binarywidget.cpp
//  LO21_Projet
//
//  Created by Anthony WEIBEL and Antoine POUILLAUDE on 05/06/13.
//  Copyright (c) 2013 Antoine POUILLAUDE. All rights reserved.
//

#include "binarywidget.h"

BinaryWidget::BinaryWidget(QWidget* parent):NoteWidget(parent)
{

}

AudioWidget::AudioWidget(QWidget* parent):BinaryWidget(parent)
{

}

ImageWidget::ImageWidget(QWidget* parent):BinaryWidget(parent)
{

}

VideoWidget::VideoWidget(QWidget* parent):BinaryWidget(parent)
{

}
