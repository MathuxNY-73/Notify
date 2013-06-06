//
//  NoteWidget.h
//  LO21_Projet
//


#ifndef NOTEWIDGET_H
#define NOTEWIDGET_H

#include <QWidget>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QApplication> //Toutes les lignes suivantes sont à décommenter sous Qt. Elles sont commentées parce que sinon sous XCode cela ne fonctionne pas.
#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include "note.h"

class NoteWidget : public QWidget
{
    //Macro
    Q_OBJECT

private:

protected:
    QLineEdit* title;
    QVBoxLayout* layout;

public:
    explicit NoteWidget(QWidget *parent=0);
    QVBoxLayout* getLayout() {return layout;}
    virtual Note* getNote()=0;

    //Slots
public slots:
    virtual void updateNote();

private slots:
    void titleChanged(QString q);

};

#endif // NOTEWIDGET_H