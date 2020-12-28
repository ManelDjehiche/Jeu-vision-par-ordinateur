/********************************************************************************
** Form generated from reading UI file 'testapp.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TESTAPP_H
#define UI_TESTAPP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TestAppClass
{
public:
    QAction *actionChanger_de_niveau;
    QAction *actionAide;
    QWidget *centralWidget;
    QFrame *frameTerrain;
    QLabel *labelPerso;
    QLabel *label_but1;
    QFrame *line_bas;
    QFrame *line_droite;
    QFrame *line_gauche;
    QLabel *label_but2;
    QLabel *label_but3;
    QLabel *label_but4;
    QLabel *label_but5;
    QLabel *labelNiveau;
    QLabel *labelNumNiveau;
    QPushButton *buttonLancer;
    QLabel *label;
    QLabel *label_2;
    QFrame *line_haut;
    QSpinBox *spinBox_vitesse;
    QLabel *label_3;
    QSpinBox *spinBox_niveau;
    QLabel *label_4;
    QLabel *label_fin;
    QPushButton *bouton_infos;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *TestAppClass)
    {
        if (TestAppClass->objectName().isEmpty())
            TestAppClass->setObjectName(QStringLiteral("TestAppClass"));
        TestAppClass->resize(984, 766);
        actionChanger_de_niveau = new QAction(TestAppClass);
        actionChanger_de_niveau->setObjectName(QStringLiteral("actionChanger_de_niveau"));
        actionAide = new QAction(TestAppClass);
        actionAide->setObjectName(QStringLiteral("actionAide"));
        centralWidget = new QWidget(TestAppClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        frameTerrain = new QFrame(centralWidget);
        frameTerrain->setObjectName(QStringLiteral("frameTerrain"));
        frameTerrain->setGeometry(QRect(9, 9, 731, 561));
        frameTerrain->setFrameShape(QFrame::StyledPanel);
        frameTerrain->setFrameShadow(QFrame::Raised);
        labelPerso = new QLabel(frameTerrain);
        labelPerso->setObjectName(QStringLiteral("labelPerso"));
        labelPerso->setGeometry(QRect(320, 430, 61, 61));
        labelPerso->setPixmap(QPixmap(QString::fromUtf8(":/TestApp/Resources/images/perso_iu.png")));
        label_but1 = new QLabel(frameTerrain);
        label_but1->setObjectName(QStringLiteral("label_but1"));
        label_but1->setGeometry(QRect(350, 150, 71, 71));
        label_but1->setPixmap(QPixmap(QString::fromUtf8(":/TestApp/Resources/images/but_marshmallow.png")));
        line_bas = new QFrame(frameTerrain);
        line_bas->setObjectName(QStringLiteral("line_bas"));
        line_bas->setGeometry(QRect(0, 550, 731, 16));
        line_bas->setFrameShape(QFrame::HLine);
        line_bas->setFrameShadow(QFrame::Sunken);
        line_droite = new QFrame(frameTerrain);
        line_droite->setObjectName(QStringLiteral("line_droite"));
        line_droite->setGeometry(QRect(720, 0, 20, 561));
        line_droite->setFrameShape(QFrame::VLine);
        line_droite->setFrameShadow(QFrame::Sunken);
        line_gauche = new QFrame(frameTerrain);
        line_gauche->setObjectName(QStringLiteral("line_gauche"));
        line_gauche->setGeometry(QRect(-10, 0, 20, 561));
        line_gauche->setFrameShape(QFrame::VLine);
        line_gauche->setFrameShadow(QFrame::Sunken);
        label_but2 = new QLabel(frameTerrain);
        label_but2->setObjectName(QStringLiteral("label_but2"));
        label_but2->setGeometry(QRect(110, 120, 71, 71));
        label_but2->setPixmap(QPixmap(QString::fromUtf8(":/TestApp/Resources/images/but_23.png")));
        label_but3 = new QLabel(frameTerrain);
        label_but3->setObjectName(QStringLiteral("label_but3"));
        label_but3->setGeometry(QRect(630, 40, 71, 71));
        label_but3->setPixmap(QPixmap(QString::fromUtf8(":/TestApp/Resources/images/but_palette.png")));
        label_but4 = new QLabel(frameTerrain);
        label_but4->setObjectName(QStringLiteral("label_but4"));
        label_but4->setGeometry(QRect(620, 450, 71, 71));
        label_but4->setPixmap(QPixmap(QString::fromUtf8(":/TestApp/Resources/images/but_bbibbi.png")));
        label_but5 = new QLabel(frameTerrain);
        label_but5->setObjectName(QStringLiteral("label_but5"));
        label_but5->setGeometry(QRect(300, 10, 71, 71));
        label_but5->setPixmap(QPixmap(QString::fromUtf8(":/TestApp/Resources/images/but_blueming.png")));
        label_but1->raise();
        labelPerso->raise();
        line_bas->raise();
        line_droite->raise();
        line_gauche->raise();
        label_but2->raise();
        label_but3->raise();
        label_but4->raise();
        label_but5->raise();
        labelNiveau = new QLabel(centralWidget);
        labelNiveau->setObjectName(QStringLiteral("labelNiveau"));
        labelNiveau->setGeometry(QRect(300, 660, 491, 41));
        QFont font;
        font.setPointSize(8);
        font.setBold(true);
        font.setUnderline(true);
        font.setWeight(75);
        labelNiveau->setFont(font);
        labelNumNiveau = new QLabel(centralWidget);
        labelNumNiveau->setObjectName(QStringLiteral("labelNumNiveau"));
        labelNumNiveau->setGeometry(QRect(760, 40, 201, 131));
        QFont font1;
        font1.setItalic(true);
        labelNumNiveau->setFont(font1);
        buttonLancer = new QPushButton(centralWidget);
        buttonLancer->setObjectName(QStringLiteral("buttonLancer"));
        buttonLancer->setGeometry(QRect(790, 210, 151, 41));
        buttonLancer->setAutoDefault(false);
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(390, 600, 341, 31));
        QFont font2;
        font2.setBold(true);
        font2.setWeight(75);
        label->setFont(font2);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(430, 630, 301, 31));
        label_2->setFont(font2);
        line_haut = new QFrame(centralWidget);
        line_haut->setObjectName(QStringLiteral("line_haut"));
        line_haut->setGeometry(QRect(10, 0, 731, 16));
        line_haut->setFrameShape(QFrame::HLine);
        line_haut->setFrameShadow(QFrame::Sunken);
        spinBox_vitesse = new QSpinBox(centralWidget);
        spinBox_vitesse->setObjectName(QStringLiteral("spinBox_vitesse"));
        spinBox_vitesse->setGeometry(QRect(160, 600, 71, 41));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(80, 610, 71, 21));
        QFont font3;
        font3.setPointSize(9);
        label_3->setFont(font3);
        spinBox_niveau = new QSpinBox(centralWidget);
        spinBox_niveau->setObjectName(QStringLiteral("spinBox_niveau"));
        spinBox_niveau->setGeometry(QRect(160, 660, 71, 41));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(80, 670, 71, 21));
        label_4->setFont(font3);
        label_fin = new QLabel(centralWidget);
        label_fin->setObjectName(QStringLiteral("label_fin"));
        label_fin->setGeometry(QRect(790, 280, 151, 61));
        QFont font4;
        font4.setPointSize(10);
        font4.setBold(true);
        font4.setWeight(75);
        label_fin->setFont(font4);
        bouton_infos = new QPushButton(centralWidget);
        bouton_infos->setObjectName(QStringLiteral("bouton_infos"));
        bouton_infos->setGeometry(QRect(790, 390, 151, 41));
        TestAppClass->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(TestAppClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        TestAppClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(TestAppClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        TestAppClass->setStatusBar(statusBar);

        retranslateUi(TestAppClass);

        QMetaObject::connectSlotsByName(TestAppClass);
    } // setupUi

    void retranslateUi(QMainWindow *TestAppClass)
    {
        TestAppClass->setWindowTitle(QApplication::translate("TestAppClass", "Jeu du lapin", Q_NULLPTR));
        actionChanger_de_niveau->setText(QApplication::translate("TestAppClass", "Changer de niveau", Q_NULLPTR));
        actionAide->setText(QApplication::translate("TestAppClass", "Aide", Q_NULLPTR));
        labelPerso->setText(QString());
        label_but1->setText(QString());
        label_but2->setText(QString());
        label_but3->setText(QString());
        label_but4->setText(QString());
        label_but5->setText(QString());
        labelNiveau->setText(QApplication::translate("TestAppClass", "Pour REJOUER : Tapez ECHAP et fermez la fenetre grise", Q_NULLPTR));
        labelNumNiveau->setText(QApplication::translate("TestAppClass", "          Directions", Q_NULLPTR));
        buttonLancer->setText(QApplication::translate("TestAppClass", "JOUER", Q_NULLPTR));
        label->setText(QApplication::translate("TestAppClass", "ATTENTION ! Plus la vitesse augmente,", Q_NULLPTR));
        label_2->setText(QApplication::translate("TestAppClass", "plus il sera difficile de jouer !", Q_NULLPTR));
        label_3->setText(QApplication::translate("TestAppClass", "Vitesse", Q_NULLPTR));
        label_4->setText(QApplication::translate("TestAppClass", "Niveau", Q_NULLPTR));
        label_fin->setText(QString());
        bouton_infos->setText(QApplication::translate("TestAppClass", "Informations", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class TestAppClass: public Ui_TestAppClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TESTAPP_H
