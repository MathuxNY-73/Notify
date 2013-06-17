//
//  main.cpp
//  LO21_Projet
//
//  Created by Anthony WEIBEL and Antoine POUILLAUDE on 07/05/13.
//  Copyright (c) 2013 Antoine POUILLAUDE. All rights reserved.
//

#include <iostream>
#include "note.h"
#include "article.h"
#include "document.h"
#include "binary.h"
#include "notemanager.h"
#include "notewidget.h"
#include "articlewidget.h"
#include "binarywidget.h"
#include "editorspace.h"
#include "mainwindow.h"
#include <QSet>
#include <QString>

/**
 * @fn  int main(int argc, char *argv[])
 * @brief Fonction main
 * @param argc
 * @param argv
 * @return
 */

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow m;
    m.show();

    return app.exec();
}
