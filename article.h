//
//  article.h
//  LO21_Projet
//
//  Created by Anthony WEIBEL and Antoine POUILLAUDE on 07/05/13.
//  Copyright (c) 2013 Antoine POUILLAUDE. All rights reserved.
//

#ifndef ARTICLE_H
#define ARTICLE_H

#include <iostream>
#include <QFile>
#include <QString>
#include <QTextStream>
//#include <QApplication> //Toutes les lignes suivantes sont à décommenter sous Qt. Elles sont commentées parce que sinon sous XCode cela ne fonctionne pas.
//#include <QWidget>
//#include <QLineEdit>
//#include <QTextEdit>
//#include <QPushButton>
//#include <QVBoxLayout>
//#include <QMessageBox>
#include "note.h"
#include "exports.h"

class Article : public Note {
    
private:
    //Attributs
    QString text;
    
    //Constructeurs de recopie
    Article(const Article&);
    Article& operator=(const Article&);
    //void load();
    
public:
    //Constructeurs
    Article(const QString& path):Note(path),text(""){}
    Article(unsigned int i, const QString& ti, const QString& te): Note(i,ti),text(te){}
    
    //Destructeur
    ~Article(){}
    
    //Methodes inlines
    const QString& getText() const { return text; }
    
    //Methodes non-inlines
    void setText(const QString& t);
    QString ExportAsPart(Exports::ExportStrategy* es, unsigned int tl) const;
    //QTextStream& operator<<(QTextStream& f, const Article& a);
};



/*Attention cette classe n'est pas dans la précédente
class ArticleEditeur : public QWidget {
    Q_OBJECT
    QLineEdit* titre;
    QTextEdit* text;
    QPushButton* save;
    QVBoxLayout* couche;
    Article* article;

public:
    explicit ArticleEditeur(Article* art, QWidget* parent = 0);
    Article& getArticle(){return *article;}

    //signals:
    private slots:
    void activerSlot(QString str);

    public slots:
    void saveArticle();
    void updateArticle();

};*/
#endif // ARTICLE_H
