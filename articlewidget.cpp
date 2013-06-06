#include "articlewidget.h"
#include "article.h"

ArticleWidget::ArticleWidget(Article* a,QWidget* parent):NoteWidget(parent),article(a)
{
    //Allocation des différents widgets
    text= new QTextEdit("Contenu",this);
    save = new QPushButton("Sauvegarder",this);

    //Definition
    save->setEnabled(false);
    try{
        if(a!=NULL)
        {
            text->setText(article->getText());
            title->setText(article->getTitle());
        }
        else
            throw ArticleException("L'article n'existe pas");
    } catch(ArticleException& e){
        std::cout<<"Fatal Error:"<<e.getInfo().toStdString()<<"\n";
    }


    //Layout
    layout->addWidget(text);
    layout->addWidget(save);

    //Connection
    QObject::connect(text,SIGNAL(textChanged()),this,SLOT(enableSave()));
    QObject::connect(title,SIGNAL(textEdited(QString)),this,SLOT(enableSave()));
    QObject::connect(save,SIGNAL(clicked()),this,SLOT(updateNote()));
}

void ArticleWidget::enableSave()
{
    save->setEnabled(true);
}

void ArticleWidget::updateNote()
{
     article->setTitle(title->text());
     article->setText(text->toPlainText());
     save->setEnabled(false);
     QMessageBox::information(this, "Sauvegarde", "Votre article a bien été sauvegardé...");
}
