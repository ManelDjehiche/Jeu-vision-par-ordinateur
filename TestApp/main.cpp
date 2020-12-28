/*
PROJET VISION : CREATION D'UN JEU
*/

#include "ui_testapp.h"
#include "testapp.h"
#include <QtWidgets/QApplication>


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	TestApp w;

	w.setFixedSize(984, 766); //fixer la taille de la fenêtre

	w.show();
	return a.exec();
}

