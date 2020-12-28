#ifndef TESTAPP_H
#define TESTAPP_H

#include <QtWidgets/QMainWindow>
#include <QtCore>
/*
PROJET VISION : CREATION D'UN JEU
*/

#include <QtGui>
#include<QMessageBox>
#include "ui_testapp.h"

class TestApp : public QMainWindow
{
	Q_OBJECT

public:
	TestApp(QWidget *parent = 0);
	~TestApp();

private:
	Ui::TestAppClass ui;

private slots:
	void on_Lancer_clicked();
	void on_Infos_clicked();
};

#endif // TESTAPP_H
