#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "editorspace.h"
#include "workspace.h"
#include "tagmanager.h"
#include <QMainWindow>
#include <QWidget>
#include <QSizePolicy>
#include <QException>
#include <QIcon>
#include <QAction>
#include <QMenuBar>

namespace Ui {
class MainWindow;
class MyException;
}

class MyException
{
    QString info;

public:
    MyException(const QString& message):info(message){}
    QString getInfo() const { return info; }
};

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    unsigned int id;

    QWidget* central;
    Tags::TagManagerWidget* tags;
    Editorspace* editor;
    Workspace* work;

    QGridLayout* gridLayout;

    //slots
private slots:
public slots:
    void newArticle();
    void newDocument();
    void newAudio();
    void newVideo();
    void newImage();

    void newWorkspace();
};

#endif // MAINWINDOW_H
