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
#include <QHBoxLayout>
#include <QLabel>
#include <QGridLayout>
#include <QPixmap>
#include <QImage>
#include <QObject>
#include <QSlider>

class Binary;
class Audio;
class Video;
class Image;
class BinaryException;

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
    BinaryWidget(Binary* b,QWidget* parent=0);
    Note* getNote(){}
};

class AudioWidget : public BinaryWidget
{

private:
    Audio* audio;
    QPushButton* pl;
    QPushButton* stop;
    QGridLayout* glayout;
    QSlider* cursor;

public:
    AudioWidget(Audio* a,QWidget* parent=0);
};

class VideoWidget : public BinaryWidget
{

private:
    Video* video;

public:
    VideoWidget(Video* v,QWidget* parent=0);
};

class ImageWidget : public BinaryWidget
{

private:
    //QGridLayout* glayout;
    QPixmap* img;
    Image* image;
    QLabel* label;

public:
    ImageWidget(Image* i,QWidget* parent=0);
};

#endif // BINARYWIDGET_H
