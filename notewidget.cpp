//
//  NoteWidget.cpp
//  LO21_Projet
//
//  Created by Anthony WEIBEL and Antoine POUILLAUDE on 07/05/13.
//  Copyright (c) 2013 Antoine POUILLAUDE. All rights reserved.
//

#include "notewidget.h"

NoteWidget::NoteWidget(QWidget *parent)
{
    title = new QLineEdit("titre",parent);
    layout = new QVBoxLayout(parent);
    layout->addWidget(title);
    parent->setLayout(layout);

    //setWindowTitle("Éditeur de notes");
    /*QMenu *mFichier = menuBar()->addMenu("&Fichier");
    QMenu *mEdition = menuBar()->addMenu("&Edition");
    QMenu *mNouveau = mFichier->addMenu("&Ouvrir");
    QAction *actionNewArticle = mNouveau->addMenu("Article");
    QAction *actionNewImage = mNouveau->addMenu("Image");
    QAction *actionNewAudio = mNouveau->addMenu("Audio");
    QAction *actionNewDocument = mNouveau->addMenu("Document");
    mFichier->addSeparator();
    QAction *actionQuitter = mFichier->addAction("&Quitter");*/

    //Connection
    //QObject::connect(title,SIGNAL(textChanged(QString)),this,SLOT());

    /*QObject::connect(actionNewArcticle,SIGNAL(triggered()),this,SLOT(openArticle()));
    QObject::connect(actionNewImage,SIGNAL(triggered()),this,SLOT(openImage()));
    QObject::connect(actionNewAudio,SIGNAL(triggered()),this,SLOT(openAudio()));
    QObject::connect(actionNewVideo,SIGNAL(triggered()),this,SLOT(openVideo()));
    QObject::connect(actionNewDocument,SIGNAL(triggered()),this,SLOT(openDocument()));
    QObject::connect(actionQuitter,SIGNAL(triggered()),app,SLOT(quit()));*/

    //Q3
    /*actionQuitter->setIcon(QIcon("../icons/quitter.png"));
    actionNewImage->setIcon(QIcon("../icons/image.png"));
    actionNewAudio->setIcon(QIcon("../icons/audio.png"));
    actionNewVideo->setIcon(QIcon("../icons/video.png"));
    actionNewDocument->setIcon(QIcon("../icons/document.png"));
    actionNewArcticle->setIcon(QIcon("../icons/acticle.png"));

    QToolBar *toolBarOpen = addToolBar("Open");
    toolBarOpen->addAction(actionNewArcticle);
    toolBarOpen->addAction(actionNewDocument);
    toolBarOpen->addAction(actionNewAudio);
    toolBarOpen->addAction(actionNewImage);
    toolBarOpen->addAction(actionNewVideo);

    onglets=new QTabWidget(this);
    setCentralWidget(onglets);
    visualisateurText=0;
    editeur=0;*/
}
