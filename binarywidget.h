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
//#include <QObject>
#include <QSlider>
//#include <Phonon>


class Binary;
class Audio;
class Video;
class Image;
class BinaryException;

class BinaryWidget : public NoteWidget
{
    //Macro
    Q_OBJECT
private:

protected:
    QHBoxLayout* hlayout;
    QPushButton* bwse;
    QLabel* path;
    QTextEdit* descpt;
    Binary* binary;
    //QPushButton* save;


public:
    explicit BinaryWidget(Binary* b,QWidget* parent=0);
    Note* getNote(){}

    //slots
public slots:
    void updateNote();
    void modification();
private slots:
    void enableSave();
};

class AudioWidget : public BinaryWidget
{
    //Macro
    Q_OBJECT

private:
    Audio* audio;
    QPushButton* play, *stop;
    QGridLayout* glayout;

public:
    explicit AudioWidget(Audio* a,QWidget* parent=0);

//Slots
public slots:
    void lire();
    void arreter();

};

class VideoWidget : public BinaryWidget
{
    Q_OBJECT
private:
    Video* video;
    //Phonon::VideoPlayer* player;
    QPushButton* play, *pause, *stop;
    QSlider* cursor;
    QGridLayout* glayout;

public:
    explicit VideoWidget(Video* v,QWidget* parent=0);

//slots
public slots:
    void lire();
    void setPause();
    void arreter();

};

class ImageWidget : public BinaryWidget
{
    Q_OBJECT
private:
    //QGridLayout* glayout;
    QPixmap* img;
    Image* image;
    QLabel* label;

public:
    explicit ImageWidget(Image* i,QWidget* parent=0);
};

#endif // BINARYWIDGET_H
