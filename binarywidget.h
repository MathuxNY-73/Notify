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
#include <QHBoxLayout>
#include <QLabel>
#include <QGridLayout>
#include <QPixmap>


class BinaryWidget : public NoteWidget
{

private:

protected:
    QHBoxLayout* hlayout;
    QPushButton* bwse;
    QLabel* path;
    QTextEdit* descpt;
    Binary* binary;

public:
    BinaryWidget(Binary* b,QWidget* parent);
};

class AudioWidget : public BinaryWidget
{
    Audio* audio;

public:
    AudioWidget(Audio* a,QWidget* parent);
};

class VideoWidget : public BinaryWidget
{

private:
    Video* video;

public:
    VideoWidget(Video* v,QWidget* parent);
};

class ImageWidget : public BinaryWidget
{

private:
    QGridLayout* glayout;
    QPixmap* img;
    Image* image;

public:
    ImageWidget(Image* i,QWidget* parent);
};

#endif // BINARYWIDGET_H
