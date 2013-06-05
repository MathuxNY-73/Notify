//
//  binarywidget.h
//  LO21_Projet
//
//  Created by Anthony WEIBEL and Antoine POUILLAUDE on 05/06/13.
//  Copyright (c) 2013 Antoine POUILLAUDE. All rights reserved.
//

#ifndef BINARYWIDGET_H
#define BINARYWIDGET_H

#include "notewidget.h"
#include "note.h"
#include "binary.h"

class BinaryWidget : public NoteWidget
{
public:
    BinaryWidget(QWidget* parent);
};

class AudioWidget : public BinaryWidget
{
public:
    AudioWidget(QWidget* parent);
};

class VideoWidget : public BinaryWidget
{
public:
    VideoWidget(QWidget* parent);
};

class ImageWidget : public BinaryWidget
{
public:
    ImageWidget(QWidget* parent);
};

#endif // BINARYWIDGET_H
