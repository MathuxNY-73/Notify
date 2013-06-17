#include "articlewidget.h"
#include "article.h"

/**
 * \fn ArticleWidget::ArticleWidget(Article* a,QWidget* parent)
 * \brief Constructeur des widgets d'articles
 * \param Pointeur vers l'article associé au Widget
 * \param Widget parent
 */
ArticleWidget::ArticleWidget(Article* a,QWidget* parent):NoteWidget(a,parent),article(a)
{   
    //Allocation des différents widgets
    text= new QTextEdit("Contenu",this);
    //save = new QPushButton("Sauvegarder",this); //Je l'enlève

    //Definition
    //save->setEnabled(false);
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
    //layout->addWidget(save);

    //Connection
    QObject::connect(text,SIGNAL(textEdited()),this,SLOT(modification()));
    QObject::connect(title,SIGNAL(textEdited(QString)),this,SLOT(modification()));

}

/**
 * \fn void ArticleWidget::modification()
 * \brief Modification de l'article.
 */
void ArticleWidget::modification()
{
    article->setModify(true);
    emit mod();
}

/**
 * \fn Note* ArticleWidget::getNote()
 * \brief Récupérer la partie Note.
 * \return Un pointeur sur la partie note de l'article associé au Widget
 */
Note* ArticleWidget::getNote()
{
    return dynamic_cast<Note*>(article);
}

/**
 * \fn void ArticleWidget::updateNote()
 * \brief Mise à jour des propriétés de l'objet article associé à partir des champs du widget
 */
void ArticleWidget::updateNote()
{
     article->setTitle(title->text());
     article->setText(text->toPlainText());
}
