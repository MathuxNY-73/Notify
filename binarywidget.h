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
#include <QSlider>


class Binary;
class Audio;
class Video;
class Image;
class BinaryException;

/**
 * \class BinaryWidget : public NoteWidget
 * \brief Classe des widgets des fichiers binaires
 */
class BinaryWidget : public NoteWidget
{
    //Macro
    Q_OBJECT
private:

protected:
    QHBoxLayout* hlayout;
    QPushButton* bwse;
    QLabel* path,*pathEdit;
    QTextEdit* descpt;
    Binary* binary;


public:
    explicit BinaryWidget(Binary* b,QWidget* parent=0);
    ~BinaryWidget();
    Note* getNote();

    //slots
public slots:
    void updateNote();
    void modification();
    void getPath();
};

/**
 * \class AudioWidget : public BinaryWidget
 * \brief Classe des widgets audio
 */
class AudioWidget : public BinaryWidget
{
    //Macro
    Q_OBJECT

private:
    Audio* audio;
    QPushButton* play, *stop;
    QHBoxLayout* hlayout;

public:
    explicit AudioWidget(Audio* a,QWidget* parent=0);
    ~AudioWidget();
    Note* getNote();

//Slots
public slots:
    void lire();
    void arreter();

};

/**
 * \class VideoWidget : public BinaryWidget
 * \brief Classe des widgets video
 */
class VideoWidget : public BinaryWidget
{
    Q_OBJECT
private:
    Video* video;
    QPushButton* play, *pause, *stop;
    QSlider* cursor;
    QHBoxLayout* hlayout;

public:
    explicit VideoWidget(Video* v,QWidget* parent=0);
    ~VideoWidget();
    Note* getNote();
//slots
public slots:
    void lire();
    void setPause();
    void arreter();

};

/**
 * \class ImageWidget : public BinaryWidget
 * \brief Classe des widgets image
 */
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
    ~ImageWidget();
    Note* getNote();

};

#endif // BINARYWIDGET_H
