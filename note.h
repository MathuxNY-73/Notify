//
//  note.h
//  LO21_Projet
//
//  Created by Anthony WEIBEL and Antoine POUILLAUDE on 07/05/13.
//  Copyright (c) 2013 Antoine POUILLAUDE. All rights reserved.
//

#ifndef NOTE_H
#define NOTE_H

#include <iostream>
#include <QString>
#include <QTextStream>
#include <QStandardItem>


namespace Exports {
    class ExportStrategy;
}

class NoteWidget;

//Classe pour la gestion des exceptions

/**
 * \class NotesException
 * \brief La classe des exceptions des notes.
 */
class NotesException{
    
public:
    NotesException(const QString& message):info(message){}
    QString getInfo() const { return info; }
    
private:
    QString info;
};

//Definition de la classe Note

/**
 * \class Note {Abstract}
 * \brief La classe abstraite des notes.
 */
class Note {
    
private:
    //Attributs privés
    unsigned int id;

    //Construction
    Note(const Note& n);
    Note& operator=(const Note& n);
    
protected:
    //Attributs protégés
    QString title;
    QString path;
    bool loaded;
    bool modified;

    QStandardItem* item;

public:
    //Constructeurs
    Note(const QString& path);
    Note(unsigned int i, const QString& t);
    ~Note();
    
    //Methodes inlines

    /**
     * \fn unsigned int getId() const
     * \brief Récupérer l'ID de la note.
     * \return L'ID de la note en question.
     */
    unsigned int getId() const {return this->id;}

    /**
     * \fn QString getTitle() const
     * \brief Recupérer le titre de la note.
     * \return Le titre de la note.
     */
    QString getTitle() const {return this->title;}

    /**
     * \fn void setTitle(const QString& t)
     * \brief Fixer le titre de la note
     * \param Titre à donner à la note.
     */
    void setTitle(const QString& t)
    {
        modified=true;
        title=t;
    }

    /**
     * \fn QString getPath() const
     * \brief Recupérer le chemin de la note.
     * \return Le chemin vers le fichier de la note.
     */
    QString getPath() const {return this->path;}

    /**
     * \fn void setPath(const QString& p)
     * \brief Fixer un chemin
     * \param Chemin du fichier de la note.
     */
    void setPath(const QString& p) {
        modified=true;
        path=p;
    }

    /**
     * \fn bool isModify() const
     * \brief Modification
     * \return Retourne la valeur du booléen 'modified'
     */
    bool isModify() const {return modified;}

    /**
     * \fn void setModify(bool m)
     * \brief Modifier le booléen 'modified'
     * \param Valeur du booléen
     */
    void setModify(bool m){ modified=m;}
    
    //Methodes non-inlines
    void addSubNote(Note* n);
    void addSubNote(Note* n, unsigned int id);
    void removeSubNote(unsigned int id);
    Note* getSubNote(unsigned int id) const;
    
    
    //Methodes virtuelles pures ou pas

    /**
     * \fn virtual QString ExportNote(Exports::ExportStrategy* es) =0
     * \brief Exportation de Note
     * \param La strategie d'export que l'on souhaite utiliser
     * \return La chaine de caractère correspondant à l'exportation de la note.
     */
    virtual QString ExportNote(Exports::ExportStrategy* es) =0;

    /**
     * \fn virtual QString ExportAsPart(Exports::ExportStrategy* es, unsigned int tl) =0
     * \brief Exportation de Note en tant que partie d'un autre export.
     * \param La stratégie d'export que l'on souhaite utiliser.
     * \param Le niveau de titre dans l'export.
     * \return La chaine de caractère correspondant à l'export.
     */
    virtual QString ExportAsPart(Exports::ExportStrategy* es, unsigned int tl) =0;

    /**
     * \fn virtual Note& getCopy() =0
     * \brief Copier une note.
     * \return La note copiée.
     */
    virtual Note& getCopy() =0;

    /**
     * \fn virtual NoteWidget* getWidget()=0
     * \brief Récupérer le widget correspondant à la Note.
     * \return Le widget de la note.
     */
    virtual NoteWidget* getWidget()=0;

    QStandardItem* getItem();

};

#endif // NOTE_H
