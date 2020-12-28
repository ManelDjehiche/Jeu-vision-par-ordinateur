#include "fenetre_jeu.h"


fenetre_jeu::fenetre_jeu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::fenetre_jeu)
{
    ui->setupUi(this);
}

fenetre_jeu::~fenetre_jeu()
{
    delete ui;
}
