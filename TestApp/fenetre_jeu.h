#ifndef FENETRE_JEU_H
#define FENETRE_JEU_H

#include <QMainWindow>
#include <QtWidgets/QMainWindow>

namespace Ui {
class fenetre_jeu;
}

class fenetre_jeu : public QMainWindow
{
    Q_OBJECT

public:
    explicit fenetre_jeu(QWidget *parent = 0);
    ~fenetre_jeu();

private:
    Ui::fenetre_jeu *ui;
};

#endif // FENETRE_JEU_H
