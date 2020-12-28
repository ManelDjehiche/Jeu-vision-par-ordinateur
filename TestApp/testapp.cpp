/*
	PROJET VISION : CREATION D'UN JEU
*/

#include <QLabel>
#include <QWidget>
#include "testapp.h"
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <QTimer>
#include <QTime>
#include <QGraphicsScene>
#include "MyItem.h"

using namespace cv;
using namespace std;

//pour vérifier que le personnage a atteint tout les buts (selon le num de niveau)
int gagner[5];

TestApp::TestApp(QWidget *parent) :
		QMainWindow(parent)
{
	ui.setupUi(this);
	
	//les images des labels sont mises dans ressources
	// on les donne dans l'attribut pix en sélectionnant direct depuis l'outil les ressources adéquates
	//redimentionner les images exactement comme voulu dans l'interface
	ui.labelPerso->setScaledContents(true);
	ui.label_but1->setScaledContents(true);
	ui.label_but2->setScaledContents(true);
	ui.label_but3->setScaledContents(true);
	ui.label_but4->setScaledContents(true);
	ui.label_but5->setScaledContents(true);

	//mettre la bordure du terrain de jeu
	ui.frameTerrain->setStyleSheet("#frameTerrain { border: 5px solid purple; }");

	//pour juste afficher la position du perso, pour se la jouer xD
	//ui.labelNiveau->setText(QString::number(ui.labelPerso->x()) + "," + QString::number(ui.labelPerso->y()));

	//pour que rien ne change de pc à un autre!!!
	ui.frameTerrain->setGeometry(QRect(9, 9, 731, 561));
	ui.line_bas->setGeometry(QRect(0,550,731,16));
	ui.line_droite->setGeometry(QRect(720, 0,20 ,561 ));
	ui.line_gauche->setGeometry(QRect(-10, 0, 20, 561));
	ui.line_haut->setGeometry(QRect(10, 0, 731, 16));


	//les spinBoxes
	//niveau de 1 à 5
	ui.spinBox_niveau->setMinimum(1);
	ui.spinBox_niveau->setMaximum(5);

	//vitesse de 10 à 60
	ui.spinBox_vitesse->setMinimum(10);
	ui.spinBox_vitesse->setMaximum(60);

	//ne pas laisser voir les autres buts, un peu de suspense xD
	//astuce : mettre image transparente fera disparaitre le label ! super !
	QPixmap pix(":/TestApp/Resources/images/transparent.png");
	int w = ui.label_but2->width();
	int h = ui.label_but2->height();
	ui.label_but2->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));

	QPixmap pix3(":/TestApp/Resources/images/transparent.png");
	int w3 = ui.label_but3->width();
	int h3 = ui.label_but3->height();
	ui.label_but3->setPixmap(pix3.scaled(w3, h3, Qt::KeepAspectRatio));

	QPixmap pix4(":/TestApp/Resources/images/transparent.png");
	int w4 = ui.label_but4->width();
	int h4 = ui.label_but4->height();
	ui.label_but4->setPixmap(pix4.scaled(w4, h4, Qt::KeepAspectRatio));

	QPixmap pix5(":/TestApp/Resources/images/transparent.png");
	int w5 = ui.label_but5->width();
	int h5 = ui.label_but5->height();
	ui.label_but5->setPixmap(pix5.scaled(w5, h5, Qt::KeepAspectRatio));

	//épaisseur de la bordure de la frame (utile?)
	//ui.labelNiveau->setText(QString::number(ui.frameTerrain->frameWidth()) + "px");

	//connections des boutons
	connect(ui.buttonLancer, SIGNAL(clicked()), this, SLOT(on_Lancer_clicked()));
	connect(ui.bouton_infos, SIGNAL(clicked()), this, SLOT(on_Infos_clicked()));
}

TestApp::~TestApp()
{

}


//empty folder images_capture, pour qu'on se retrouve pas avec des erreurs entre chaque partie !!!!
//images_capture contient toutes les images (de frame normale à flèche détectée sans bruits)
//et cela d'une seule partie à la fois, quand y a une nouvelle partie, on vide le dossier
void empty_folder()
{
	std::string command = "del /Q ";
	std::string path = ".\\images_capture\\*.png";
	system(command.append(path).c_str());
}


//détection de collision
// prendre rectangle du perso et ceux des 4 murs et vérifier une intersection
// (quelques points suffisent pour dire qu'ils se sont touchés)
int coll(Ui::TestAppClass ui)
{
	QRect persona = QRect(ui.labelPerso->x(), ui.labelPerso->y(), ui.labelPerso->width(), ui.labelPerso->height());
	QRect bas = QRect(ui.line_bas->x(), ui.line_bas->y(), ui.line_bas->width(), ui.line_bas->height());
	QRect haut = QRect(ui.line_haut->x(), ui.line_haut->y(), ui.line_haut->width(), ui.line_haut->height());
	QRect droite = QRect(ui.line_droite->x(), ui.line_droite->y(), ui.line_droite->width(), ui.line_droite->height());
	QRect gauche = QRect(ui.line_gauche->x(), ui.line_gauche->y(), ui.line_gauche->width(), ui.line_gauche->height());


	if (persona.intersects(bas) || persona.intersects(haut) || persona.intersects(droite) || persona.intersects(gauche))
	{
		return 1;
	}

	return 0;
}


//idem que la collision, on détecte si le perso a touché l'un des buts, on le fait disparaitre et on le prend en compte
//tout dépend du niveau, quand tout les buts auront été atteint, la fonction retourne 1
int atteindre_but(Ui::TestAppClass ui, int nb_buts) //c'est ici qu'on va vérifier le array
{
	QRect persona = QRect(ui.labelPerso->x(), ui.labelPerso->y(), ui.labelPerso->width(), ui.labelPerso->height());
	QRect but1 = QRect(ui.label_but1->x(), ui.label_but1->y(), ui.label_but1->width(), ui.label_but1->height());
	QRect but2 = QRect(ui.label_but2->x(), ui.label_but2->y(), ui.label_but2->width(), ui.label_but2->height());
	QRect but3 = QRect(ui.label_but3->x(), ui.label_but3->y(), ui.label_but3->width(), ui.label_but3->height());
	QRect but4 = QRect(ui.label_but4->x(), ui.label_but4->y(), ui.label_but4->width(), ui.label_but4->height());
	QRect but5 = QRect(ui.label_but5->x(), ui.label_but5->y(), ui.label_but5->width(), ui.label_but5->height());


	//case = numéro de niveau
	// pour savoir combien de buts à vérifier
	switch (nb_buts)
	{
		case 1:
		{
			if (persona.intersects(but1))
			{
				QPixmap pix(":/TestApp/Resources/images/transparent.png");
				int w = ui.label_but1->width();
				int h = ui.label_but1->height();
				ui.label_but1->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));
				return 1;
			}
			else
			{
				return 0;
			}
			break;
		}
		case 2:
		{
			if (persona.intersects(but1))
			{
				gagner[0] = 1;
				QPixmap pix(":/TestApp/Resources/images/transparent.png");
				int w = ui.label_but1->width();
				int h = ui.label_but1->height();
				ui.label_but1->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));

			}
			if (persona.intersects(but2))
			{
				gagner[1] = 1;
				QPixmap pix2(":/TestApp/Resources/images/transparent.png");
				int w2 = ui.label_but2->width();
				int h2 = ui.label_but2->height();
				ui.label_but2->setPixmap(pix2.scaled(w2, h2, Qt::KeepAspectRatio));
			}

			if (gagner[0] == 1 && gagner[1] == 1)
			{
				return 1;
			}
			else
			{
				return 0;
			}

			break;
		}
		case 3:
		{
			if (persona.intersects(but1)) 
			{
				gagner[0] = 1;
				QPixmap pix(":/TestApp/Resources/images/transparent.png");
				int w = ui.label_but1->width();
				int h = ui.label_but1->height();
				ui.label_but1->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));
			}
			if (persona.intersects(but2))
			{
				gagner[1] = 1;
				QPixmap pix2(":/TestApp/Resources/images/transparent.png");
				int w2 = ui.label_but2->width();
				int h2 = ui.label_but2->height();
				ui.label_but2->setPixmap(pix2.scaled(w2, h2, Qt::KeepAspectRatio));
			}
			if (persona.intersects(but3))
			{
				gagner[2] = 1;
				QPixmap pix3(":/TestApp/Resources/images/transparent.png");
				int w3 = ui.label_but3->width();
				int h3 = ui.label_but3->height();
				ui.label_but3->setPixmap(pix3.scaled(w3, h3, Qt::KeepAspectRatio));

			}

			if (gagner[0] == 1 && gagner[1] == 1 && gagner[2] == 1)
			{
				return 1;
			}
			else
			{
				return 0;
			}
			break;
		}
		case 4:
		{
			if (persona.intersects(but1))
			{
				gagner[0] = 1;
				QPixmap pix(":/TestApp/Resources/images/transparent.png");
				int w = ui.label_but1->width();
				int h = ui.label_but1->height();
				ui.label_but1->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));
			}
			if (persona.intersects(but2))
			{
				gagner[1] = 1;
				QPixmap pix2(":/TestApp/Resources/images/transparent.png");
				int w2 = ui.label_but2->width();
				int h2 = ui.label_but2->height();
				ui.label_but2->setPixmap(pix2.scaled(w2, h2, Qt::KeepAspectRatio));
			}
			if (persona.intersects(but3))
			{
				gagner[2] = 1;
				QPixmap pix3(":/TestApp/Resources/images/transparent.png");
				int w3 = ui.label_but3->width();
				int h3 = ui.label_but3->height();
				ui.label_but3->setPixmap(pix3.scaled(w3, h3, Qt::KeepAspectRatio));

			}
			if (persona.intersects(but4))
			{
				gagner[3] = 1;
				QPixmap pix4(":/TestApp/Resources/images/transparent.png");
				int w4 = ui.label_but4->width();
				int h4 = ui.label_but4->height();
				ui.label_but4->setPixmap(pix4.scaled(w4, h4, Qt::KeepAspectRatio));
			}
			if (gagner[0] == 1 && gagner[1] == 1 && gagner[2] == 1 && gagner[3] == 1)
			{
				return 1;
			}
			else
			{
				return 0;
			}
			break;
		}
		case 5:
		{
			if (persona.intersects(but1))
			{
				gagner[0] = 1;
				QPixmap pix(":/TestApp/Resources/images/transparent.png");
				int w = ui.label_but1->width();
				int h = ui.label_but1->height();
				ui.label_but1->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));
			}
			if (persona.intersects(but2))
			{
				gagner[1] = 1;
				QPixmap pix2(":/TestApp/Resources/images/transparent.png");
				int w2 = ui.label_but2->width();
				int h2 = ui.label_but2->height();
				ui.label_but2->setPixmap(pix2.scaled(w2, h2, Qt::KeepAspectRatio));
			}
			if (persona.intersects(but3))
			{
				gagner[2] = 1;
				QPixmap pix3(":/TestApp/Resources/images/transparent.png");
				int w3 = ui.label_but3->width();
				int h3 = ui.label_but3->height();
				ui.label_but3->setPixmap(pix3.scaled(w3, h3, Qt::KeepAspectRatio));

			}
			if (persona.intersects(but4))
			{
				gagner[3] = 1;
				QPixmap pix4(":/TestApp/Resources/images/transparent.png");
				int w4 = ui.label_but4->width();
				int h4 = ui.label_but4->height();
				ui.label_but4->setPixmap(pix4.scaled(w4, h4, Qt::KeepAspectRatio));
			}
			if (persona.intersects(but5))
			{
				gagner[4] = 1;
				QPixmap pix5(":/TestApp/Resources/images/transparent.png");
				int w5 = ui.label_but5->width();
				int h5 = ui.label_but5->height();
				ui.label_but5->setPixmap(pix5.scaled(w5, h5, Qt::KeepAspectRatio));
			}

			if (gagner[0] == 1 && gagner[1] == 1 && gagner[2] == 1 && gagner[3] == 1 && gagner[4] == 1)
			{
				return 1;
			}
			else
			{
				return 0;
			}
			break;
		}
	default:
		break;
	}

	if (persona.intersects(but1))
	{
		return 1;
	}

	return 0;
}


//lancement de la capture vidéo
//prend en compte la vitesse choisie et le niveau
//niveau à donner à la fonction d'atteinte de buts
int lire_frame2(Ui::TestAppClass ui, int speed, int niveau)
{
	empty_folder();
	// la capture video ici un fichier
	//VideoCapture cap("webcam.avi");
	//la capture vidéo ici une webcam
	VideoCapture cap;
	//if (!cap.isOpened())
	if (!cap.open(0))
		return 0;
	namedWindow("TAPEZ ECHAP SUR CETTE FENETRE POUR ARRETER", WINDOW_AUTOSIZE);



	//////////////////////////////////////////////////////////////////////////////////////////////////////////


	int i = 0;
	for (;;)
	{
		

		Mat frame;

		cap >> frame; //Pour récupérer la frame et la convertir en Mat (et la décompresser)

		if (frame.empty()) break; // end of video stream

		if (i <= 5)
		{//ATTENDRE UN PEU PSK LA CAMERA ELLE A PAS OUVERT CES YEUX !!!! S'IL LE FAUT ATTENDRE BCP!!!
			i++;
			continue;
		}

		// fliper ^^
		flip(frame, frame, 1);

		//ça sert à rien d'enregistrer? non! xD on va direct montrer ça dans l'appli u_u
		String chemin = ".\\images_capture\\img" + std::to_string(i) + ".png";
		imwrite(chemin, frame);

		//hsv
		Mat hsv;
		cvtColor(frame, hsv, COLOR_BGR2HSV);

		/*
		Mat mask1;
		inRange(hsv, Scalar(0, 120, 70), Scalar(10, 255, 255), mask1);

		
		//---------------------------------------------------------------------
		//Mat kernel = Mat::ones(3, 3, CV_32F);
		//morphologyEx(mask1, mask1, cv::MORPH_OPEN, kernel);
		//morphologyEx(mask1, mask1, cv::MORPH_DILATE, kernel);

		Mat res1;

		// segmentation avec le masque
		bitwise_and(frame, frame, res1, mask1);


		//hsv
		Mat hsv2;
		cvtColor(frame, hsv2, COLOR_BGR2HSV);
		Mat mask3;

		//blue
		inRange(hsv2, Scalar(78, 158, 124), Scalar(138, 255, 255), mask3);
		Mat res3;
		bitwise_and(frame, frame, res3, mask3);


		int erode_type = 2;
		int erode_size = 12;

		Mat element1 = getStructuringElement(erode_type, Size(2 * erode_size + 1, 2 * erode_size + 1));
		//-------------------------------------------------------
		Mat erode_rouge; //frame sans bruits
		erode(res1, erode_rouge, element1);
		//-------------------------------------------------------
		Mat erode_bleu; //frame sans bruits
		erode(res3, erode_bleu, element1);
		//-------------------------------------------------------

		//imshow("bleu", erode_bleu);
		//imshow("rouge", erode_rouge);


		Mat mask2, res2;

		//blue
		inRange(hsv, Scalar(78, 158, 124), Scalar(138, 255, 255), mask2);
		// les deux pour l'afficher ^^
		mask1 = mask1 + mask2;
		bitwise_and(frame, frame, res2, mask1);

		//imshow("les deux", res2);
		//c'est cette Mat qu'on va utiliser


		//ça sert à rien d'enregistrer? non! xD on va direct montrer ça dans l'appli u_u
		String chemin2 = ".\\images_capture\\color" + std::to_string(i) + ".png";
		imwrite(chemin2, res2);

		Mat dst;
		erode(res2, dst, element1);
		//imshow("erode", dst); // à useeeeer

		//ça sert à rien d'enregistrer? non! xD on va direct montrer ça dans l'appli u_u
		String chemin3 = ".\\images_capture\\color_sans_bruit" + std::to_string(i) + ".png";
		imwrite(chemin3, dst);

		//mettre la version HSV pour détecter les couleurs
		QPixmap pix(".\\images_capture\\color_sans_bruit" + QString::number(i) + ".png");
		int w = ui.labelNumNiveau->width();
		int h = ui.labelNumNiveau->height();
		ui.labelNumNiveau->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		Mat gray;

		// conversion au grayscale
		cvtColor(erode_bleu, gray, COLOR_BGR2GRAY);
		blur(gray, gray, Size(3, 3));


		Mat canny_output;
		vector<vector<Point> > contours;
		vector<Vec4i> hierarchy;

		int thresh = 100;
		RNG rng(12345);

		//détection des bords
		Canny(gray, canny_output, thresh, thresh * 2, 3);
		//les contours
		findContours(canny_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

		Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);
		for (int i = 0; i< contours.size(); i++)
		{
			Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
			drawContours(drawing, contours, i, color, 2, 8, hierarchy, 0, Point());
		}

		//namedWindow("Contours", WINDOW_AUTOSIZE);
		//imshow("Contours", drawing);

		//---------------------------------------------------------------
		// moments
		vector<Moments> mu(contours.size());
		for (int i = 0; i < contours.size(); i++)
		{
			mu[i] = moments(contours[i], false);
		}

		//centres
		vector<Point2f> mc(contours.size());
		for (int i = 0; i < contours.size(); i++)
		{
			if (mu[i].m00 != 0 && mu[i].m01!=0 && mu[i].m10!=0) //sinon y a erreur !!
			{
				mc[i] = Point2f(mu[i].m10 / mu[i].m00, mu[i].m01 / mu[i].m00);
			}
			else
			{
				mc[i] = Point2f(200.f, 200.f);
			}
			
		}
		//------------------------------------------------------------------


		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		Mat gray2;

		// gray
		cvtColor(erode_rouge, gray2, COLOR_BGR2GRAY);
		blur(gray2, gray2, Size(3, 3));


		Mat canny_output2;
		vector<vector<Point> > contours2;
		vector<Vec4i> hierarchy2;

		int thresh2 = 100;
		RNG rng2(12345);

		Canny(gray2, canny_output2, thresh2, thresh2 * 2, 3);
		findContours(canny_output2, contours2, hierarchy2, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

		// dessiner les contours
		Mat drawing2 = Mat::zeros(canny_output2.size(), CV_8UC3);
		for (int i = 0; i< contours2.size(); i++)
		{
			Scalar color2 = Scalar(rng2.uniform(0, 255), rng2.uniform(0, 255), rng2.uniform(0, 255));
			drawContours(drawing2, contours2, i, color2, 2, 8, hierarchy2, 0, Point());
		}

		//namedWindow("Contours2", WINDOW_AUTOSIZE);
		//imshow("Contours2", drawing2);

		//---------------------------------------------------------------
		// recup les moments
		vector<Moments> mu2(contours2.size());
		for (int i = 0; i < contours2.size(); i++)
		{
			mu2[i] = moments(contours2[i], false);
		}

		// recup des centroids
		vector<Point2f> mc2(contours2.size());
		for (int i = 0; i < contours2.size(); i++)
		{
			
			if (mu2[i].m00 != 0 && mu2[i].m01 != 0 && mu2[i].m10 != 0)
			{
				mc2[i] = Point2f(mu2[i].m10 / mu2[i].m00, mu2[i].m01 / mu2[i].m00); //diviser sur m00
			}
			else
			{
				mc2[i] = Point2f(200.f, 200.f); //erreur de division
			}

			
		}

		if (mc.size() >= 1 && mc2.size() >= 1)
		{
		mettre les calculs de la fleche
		}
		*/

		//l'érosion se fait avant pour ne pas fausser les calculs
		int erode_type = 2;
		int erode_size = 12;

		Mat element1 = getStructuringElement(erode_type, Size(2 * erode_size + 1, 2 * erode_size + 1));
		//-------------------------------------------------------
		erode(hsv, hsv, element1);

			vector<int> vect_xrouge;
			vector<int> vect_yrouge;
			vector<int> vect_xbleu;
			vector<int> vect_ybleu;

			for (int l = 0; l < hsv.rows; l++)
			{
				for (int j = 0; j < hsv.cols; j++)
				{
					Vec3b intensity = hsv.at<Vec3b>(l, j);
					uchar blue = intensity.val[0];
					uchar green = intensity.val[1];
					uchar red = intensity.val[2];

					//red
					if (blue >= 0 && blue <= 10 && green >= 120 && green <= 255 && red >= 70 && red <= 255)
					{
						//PRENDRE ICI OUI!!!
						//je l'ai appliqué à src_r juste pour voir ^^
						//hsv.at<Vec3b>(i, j) = Vec3b(0, 100, 100);
						vect_xrouge.push_back(l);
						vect_yrouge.push_back(j);
					}
					else
					{
						////blue inRange(hsv2, Scalar(78, 158, 124), Scalar(138, 255, 255), mask3);
						if (blue >= 78 && blue <= 138 && green >= 158 && green <= 255 && red >= 124 && red <= 255)
						{
							//PRENDRE ICI OUI!!!
							//hsv.at<Vec3b>(i, j) = Vec3b(240, 100, 100);
							vect_xbleu.push_back(l);
							vect_ybleu.push_back(j);
						}
						else
						{
							//ignorer
							hsv.at<Vec3b>(l, j) = Vec3b(0, 0, 0);
							frame.at<Vec3b>(l, j) = Vec3b(0, 0, 0);
						}
					}

				}
			}


			int sommeXR = 0;
			int sommeYR = 0;
			int sommeXB = 0;
			int sommeYB = 0;

			for (int l : vect_xrouge)
			{
				sommeXR = sommeXR + l;
			}

			for (int j : vect_yrouge)
			{
				sommeYR = sommeYR + j;
			}

			for (int l : vect_xbleu)
			{
				sommeXB = sommeXB + l;
			}

			for (int j : vect_ybleu)
			{
				sommeYB = sommeYB + j;
			}

			if (vect_xrouge.size() >0 && vect_yrouge.size() > 0 && vect_xbleu.size()>0 && vect_ybleu.size()>0)
			{
				float centre_rx = sommeXR / vect_xrouge.size();
				float centre_ry = sommeYR / vect_yrouge.size();
				float centre_bx = sommeXB / vect_xbleu.size();
				float centre_by = sommeYB / vect_ybleu.size();

				//rouge
				hsv.at<Vec3b>(centre_rx, centre_ry) = Vec3b(255, 255, 255);
				frame.at<Vec3b>(centre_rx, centre_ry) = Vec3b(255, 255, 255);
				for (int rx = centre_rx - 5; rx < centre_rx + 5; rx++)
				{
					for (int ry = centre_ry -5; ry < centre_ry+ 5; ry++)
					{
						hsv.at<Vec3b>(rx, ry) = Vec3b(255, 255, 255);
						frame.at<Vec3b>(rx, ry) = Vec3b(255, 255, 255);
					}
				}

				//bleu
				hsv.at<Vec3b>(centre_bx, centre_by) = Vec3b(255, 255, 255);
				frame.at<Vec3b>(centre_bx, centre_by) = Vec3b(255, 255, 255);
				for (int bx = centre_bx - 5; bx < centre_bx + 5; bx++)
				{
					for (int by = centre_by - 5; by < centre_by + 5; by++)
					{
						hsv.at<Vec3b>(bx, by) = Vec3b(255, 255, 255);
						frame.at<Vec3b>(bx, by) = Vec3b(255, 255, 255);
					}
				}

				//enregister
				String chemin3 = ".\\images_capture\\sans_bruit" + std::to_string(i) + ".png";
				imwrite(chemin3, frame);

				//mettre la version HSV pour détecter les couleurs
				QPixmap pix(".\\images_capture\\sans_bruit" + QString::number(i) + ".png");
				int w = ui.labelNumNiveau->width();
				int h = ui.labelNumNiveau->height();
				ui.labelNumNiveau->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));


				float dx = centre_rx - centre_bx;
				float dy = centre_ry - centre_by;

				
				float length = sqrtf(dx*dx + dy*dy);

				dx /= length;
				dy /= length;

				// vitesse
				dx *= speed;
				dy *= speed;
				

				//bouger !!
				ui.labelPerso->move(ui.labelPerso->x() + dy, ui.labelPerso->y() + dx);

				//faire un switch case et niv 1 ne vérifier qu'un seul sinon deux sinon 3 etc
				//faire un array de bool (int) de la taille du niveau, si toutes les cases = vrai (1) alors gagner!!

				if (atteindre_but(ui, niveau) == 1)
				{
					ui.label_fin->setText("BRAVO !");
					break;
				}



				//vérifier si y a une collision avec la frame
				if (coll(ui))
				{
					ui.label_fin->setText("DOMMAGE...");
					break;
				}
				
			}
			else
			{
				//ne pas bouger
				ui.labelPerso->move(ui.labelPerso->x(), ui.labelPerso->y());
			}


			/*
			//vitesse de la souris
			//int speed = 50;

			//determiner l'orientation de la souris selon des deux points start et end
			//float dx = mc2[0].x - mc[0].x;
			//float dy = mc2[0].y - mc[0].y;

				float length = sqrtf(dx*dx + dy*dy);

				dx /= length;
				dy /= length;

				// vitesse
				dx *= speed;
				dy *= speed;

				//bouger !!
				ui.labelPerso->move(ui.labelPerso->x() + dx, ui.labelPerso->y() + dy);

				//faire un switch case et niv 1 ne vérifier qu'un seul sinon deux sinon 3 etc
				//faire un array de bool (int) de la taille du niveau, si toutes les cases = vrai (1) alors gagner!!
			
				if (atteindre_but(ui, niveau) == 1)
				{
					ui.label_fin->setText("BRAVO !");
					break;
				}



				//vérifier si y a une collision avec la frame
				if (coll(ui))
				{
					ui.label_fin->setText("DOMMAGE...");
					break;
				}

		
		
		*/

		if (waitKey(10) == 27) break; // stop capturing by pressing ESC
	}
	cap.release();//Pour relacher la capture on utilize ça

	ui.buttonLancer->setEnabled(true);
	ui.spinBox_niveau->setEnabled(true);
	ui.spinBox_vitesse->setEnabled(true);
	return 0;
}

//génération aléatoire pour les labels du perso et buts selon les bordures du terrain de jeu
QRect place_aleatoire()
{
	int x = qrand() % ((680 + 1) - (-5)) + (-5);
	int y = qrand() % ((505 + 1) - 5) + 5;

	QRect alea = QRect(x, y, 71, 71);
	return alea;
}




void TestApp::on_Lancer_clicked()
{
	/* TESTER SI LA GENERATION EST FAUSSE : CERTAINS BUTS SONT DANS LA MEME PLACE */
	//utiliser l'astuce du rectangle ! ^^
	
	// PAS SUR LE PERSONNAGE !!!
	QRect persona = QRect(ui.labelPerso->x(), ui.labelPerso->y(), ui.labelPerso->width(), ui.labelPerso->height());

	//les buts aléatoirement
	//il faut pas qu'ils soient dans la même place

	//but1
	ui.label_but1->setGeometry(place_aleatoire());
	QRect but1 = QRect(ui.label_but1->x(), ui.label_but1->y(), ui.label_but1->width(), ui.label_but1->height());
	if (but1.intersects(persona))
	{
		ui.label_but1->setGeometry(place_aleatoire());
		QRect but1 = QRect(ui.label_but1->x(), ui.label_but1->y(), ui.label_but1->width(), ui.label_but1->height());
	}

	
	//but2
	ui.label_but2->setGeometry(place_aleatoire());
	QRect but2 = QRect(ui.label_but2->x(), ui.label_but2->y(), ui.label_but2->width(), ui.label_but2->height());
	if (but2.intersects(but1) || but2.intersects(persona))
	{
		ui.label_but2->setGeometry(place_aleatoire());
		QRect but2 = QRect(ui.label_but2->x(), ui.label_but2->y(), ui.label_but2->width(), ui.label_but2->height());
	}

	//but3
	ui.label_but3->setGeometry(place_aleatoire());
	QRect but3 = QRect(ui.label_but3->x(), ui.label_but3->y(), ui.label_but3->width(), ui.label_but3->height());
	if (but3.intersects(but1) || but3.intersects(but2) || but3.intersects(persona))
	{
		ui.label_but3->setGeometry(place_aleatoire());
		QRect but3 = QRect(ui.label_but3->x(), ui.label_but3->y(), ui.label_but3->width(), ui.label_but3->height());
	}
	
	//but4
	ui.label_but4->setGeometry(place_aleatoire());
	QRect but4 = QRect(ui.label_but4->x(), ui.label_but4->y(), ui.label_but4->width(), ui.label_but4->height());
	if (but4.intersects(but1) || but4.intersects(but2) && but4.intersects(but3) || but4.intersects(persona))
	{
		ui.label_but4->setGeometry(place_aleatoire());
		QRect but4 = QRect(ui.label_but4->x(), ui.label_but4->y(), ui.label_but4->width(), ui.label_but4->height());
	}

	//but5
	ui.label_but5->setGeometry(place_aleatoire());
	QRect but5 = QRect(ui.label_but5->x(), ui.label_but5->y(), ui.label_but5->width(), ui.label_but5->height());
	if (but5.intersects(but1) || but5.intersects(but2) || but5.intersects(but3) || but5.intersects(but4) || but5.intersects(persona))
	{
		ui.label_but5->setGeometry(place_aleatoire());
		QRect but5 = QRect(ui.label_but5->x(), ui.label_but5->y(), ui.label_but5->width(), ui.label_but5->height());
	}
	

	//vider le message de fin de partie
	ui.label_fin->setText("");

	//remettre le perso à sa place
	ui.labelPerso->setGeometry(QRect(320, 430, 61, 61));

	//remettre tout à faux
	for (int i = 0; i < 4; i++)
	{
		gagner[i] = 0;
	}

	//désactiver les boutons
	ui.buttonLancer->setEnabled(false);
	ui.spinBox_niveau->setEnabled(false);
	ui.spinBox_vitesse->setEnabled(false);

	//prendre la vitesse
	int speed = ui.spinBox_vitesse->value();

	//prendre le niveau
	int niveau = ui.spinBox_niveau->value();

	//selon le niveau, faire apparaitre ou disparaitre des buts
	//disparaitre --> mettre image transparente + il sera pas pris en compte dans la fonction atteinte de but
	switch (niveau)
	{
		case 1:
		{
			//à faire passer aussi pour les tests
			//int gagner[1];
			gagner[0] = 0;

			//vider les 4 autres buts
			QPixmap pix1(":/TestApp/Resources/images/but_marshmallow.png");
			int w1 = ui.label_but1->width();
			int h1 = ui.label_but1->height();
			ui.label_but1->setPixmap(pix1.scaled(w1, h1, Qt::KeepAspectRatio));
			
			
			QPixmap pix(":/TestApp/Resources/images/transparent.png");
			int w = ui.label_but2->width();
			int h = ui.label_but2->height();
			ui.label_but2->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));

			QPixmap pix3(":/TestApp/Resources/images/transparent.png");
			int w3 = ui.label_but3->width();
			int h3 = ui.label_but3->height();
			ui.label_but3->setPixmap(pix3.scaled(w3, h3, Qt::KeepAspectRatio));

			QPixmap pix4(":/TestApp/Resources/images/transparent.png");
			int w4 = ui.label_but4->width();
			int h4 = ui.label_but4->height();
			ui.label_but4->setPixmap(pix4.scaled(w4, h4, Qt::KeepAspectRatio));

			QPixmap pix5(":/TestApp/Resources/images/transparent.png");
			int w5 = ui.label_but5->width();
			int h5 = ui.label_but5->height();
			ui.label_but5->setPixmap(pix5.scaled(w5, h5, Qt::KeepAspectRatio));


			break;
		}
		case 2:
		{
			//int gagner[2];
			gagner[0] = 0;
			gagner[1] = 0;

			//vider les 3 autres et remettre le deuxième (premier jamais il part!) c'est ça xD
			QPixmap pix1(":/TestApp/Resources/images/but_marshmallow.png");
			int w1 = ui.label_but1->width();
			int h1 = ui.label_but1->height();
			ui.label_but1->setPixmap(pix1.scaled(w1, h1, Qt::KeepAspectRatio));

			QPixmap pix(":/TestApp/Resources/images/but_23.png");
			int w = ui.label_but2->width();
			int h = ui.label_but2->height();
			ui.label_but2->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));

			QPixmap pix3(":/TestApp/Resources/images/transparent.png");
			int w3 = ui.label_but3->width();
			int h3 = ui.label_but3->height();
			ui.label_but3->setPixmap(pix3.scaled(w3, h3, Qt::KeepAspectRatio));

			QPixmap pix4(":/TestApp/Resources/images/transparent.png");
			int w4 = ui.label_but4->width();
			int h4 = ui.label_but4->height();
			ui.label_but4->setPixmap(pix4.scaled(w4, h4, Qt::KeepAspectRatio));

			QPixmap pix5(":/TestApp/Resources/images/transparent.png");
			int w5 = ui.label_but5->width();
			int h5 = ui.label_but5->height();
			ui.label_but5->setPixmap(pix5.scaled(w5, h5, Qt::KeepAspectRatio));
			break;
		}
		case 3:
		{
			//int gagner[3];
			gagner[0] = 0;
			gagner[1] = 0;
			gagner[2] = 0;

			//vider les 2 autres et remettre le deuxième et le 3eme (premier jamais il part!)
			QPixmap pix1(":/TestApp/Resources/images/but_marshmallow.png");
			int w1 = ui.label_but1->width();
			int h1 = ui.label_but1->height();
			ui.label_but1->setPixmap(pix1.scaled(w1, h1, Qt::KeepAspectRatio));

			QPixmap pix(":/TestApp/Resources/images/but_23.png");
			int w = ui.label_but2->width();
			int h = ui.label_but2->height();
			ui.label_but2->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));

			QPixmap pix3(":/TestApp/Resources/images/but_palette.png");
			int w3 = ui.label_but3->width();
			int h3 = ui.label_but3->height();
			ui.label_but3->setPixmap(pix3.scaled(w3, h3, Qt::KeepAspectRatio));

			QPixmap pix4(":/TestApp/Resources/images/transparent.png");
			int w4 = ui.label_but4->width();
			int h4 = ui.label_but4->height();
			ui.label_but4->setPixmap(pix4.scaled(w4, h4, Qt::KeepAspectRatio));

			QPixmap pix5(":/TestApp/Resources/images/transparent.png");
			int w5 = ui.label_but5->width();
			int h5 = ui.label_but5->height();
			ui.label_but5->setPixmap(pix5.scaled(w5, h5, Qt::KeepAspectRatio));

			break;
		}
		case 4:
		{
			//int gagner[4];
			gagner[0] = 0;
			gagner[1] = 0;
			gagner[2] = 0;
			gagner[3] = 0;

			//vider les 1 autres et remettre le deuxième, 3eme et 4eme (premier jamais il part!)
			QPixmap pix1(":/TestApp/Resources/images/but_marshmallow.png");
			int w1 = ui.label_but1->width();
			int h1 = ui.label_but1->height();
			ui.label_but1->setPixmap(pix1.scaled(w1, h1, Qt::KeepAspectRatio));

			QPixmap pix(":/TestApp/Resources/images/but_23.png");
			int w = ui.label_but2->width();
			int h = ui.label_but2->height();
			ui.label_but2->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));

			QPixmap pix3(":/TestApp/Resources/images/but_palette.png");
			int w3 = ui.label_but3->width();
			int h3 = ui.label_but3->height();
			ui.label_but3->setPixmap(pix3.scaled(w3, h3, Qt::KeepAspectRatio));

			QPixmap pix4(":/TestApp/Resources/images/but_bbibbi.png");
			int w4 = ui.label_but4->width();
			int h4 = ui.label_but4->height();
			ui.label_but4->setPixmap(pix4.scaled(w4, h4, Qt::KeepAspectRatio));

			QPixmap pix5(":/TestApp/Resources/images/transparent.png");
			int w5 = ui.label_but5->width();
			int h5 = ui.label_but5->height();
			ui.label_but5->setPixmap(pix5.scaled(w5, h5, Qt::KeepAspectRatio));
			break;
		}
		case 5:
		{
			//int gagner[5];
			gagner[0] = 0;
			gagner[1] = 0;
			gagner[2] = 0;
			gagner[3] = 0;
			gagner[4] = 0;

			//mettre tout (premier jamais il part!)
			QPixmap pix1(":/TestApp/Resources/images/but_marshmallow.png");
			int w1 = ui.label_but1->width();
			int h1 = ui.label_but1->height();
			ui.label_but1->setPixmap(pix1.scaled(w1, h1, Qt::KeepAspectRatio));

			QPixmap pix(":/TestApp/Resources/images/but_23.png");
			int w = ui.label_but2->width();
			int h = ui.label_but2->height();
			ui.label_but2->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));

			QPixmap pix3(":/TestApp/Resources/images/but_palette.png");
			int w3 = ui.label_but3->width();
			int h3 = ui.label_but3->height();
			ui.label_but3->setPixmap(pix3.scaled(w3, h3, Qt::KeepAspectRatio));

			QPixmap pix4(":/TestApp/Resources/images/but_bbibbi.png");
			int w4 = ui.label_but4->width();
			int h4 = ui.label_but4->height();
			ui.label_but4->setPixmap(pix4.scaled(w4, h4, Qt::KeepAspectRatio));

			QPixmap pix5(":/TestApp/Resources/images/but_blueming.png");
			int w5 = ui.label_but5->width();
			int h5 = ui.label_but5->height();
			ui.label_but5->setPixmap(pix5.scaled(w5, h5, Qt::KeepAspectRatio));
			break;
		}

	default:
		break;
	}

	//niveau sera aussi le size de l'array à passer (gagner)
	lire_frame2(ui,speed,niveau);
}


//les infos du jeu
void TestApp::on_Infos_clicked()
{
	QString l1 = "COMMENT JOUER ?\n";
	QString l2 = "1 - Choisissez une vitesse et un niveau de jeu\n";
	QString l3 = "2 - Cliquez sur jouer et attendez que la webcam s'allume\n";
	QString l4 = "3 - Deplacez vous personnage a l'aide de la feuille de jeu\n";
	QString lbonus = "4 - Si vous ne filmez pas la feuille le lapin ne bougera pas\n";
	QString l5 = "---------------------------------------------------\n";
	QString l6 = "Vous gagnez : si le lapin atteint tout les buts\n";
	QString l7 = "Vous perdez : si le lapin se heurte a un mur\n";
	QString l8 = "---------------------------------------------------\n";
	QString l9 = "L'HISTOIRE DU PETIT LAPIN\n";
	QString l10 = "Tokki est un petit lapin qui recherche ses affaires.\n";
	QString l11 = "Il va donc avancer jusqu'a atteindre son objectif:\n";
	QString l12 = "les recuperer toutes !\n";
	
	QString message = l1 + l2 + l3 + l4 + lbonus + l5 + l6+ l7 + l8 + l9 + l10 + l11 + l12;
		 
	QMessageBox::information(this, "Information sur le jeu",message);
}