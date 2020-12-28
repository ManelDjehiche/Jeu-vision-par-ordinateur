#include "MyItem.h"


MyItem::MyItem(QImage img)
{
	//POUR QU'IL SOIENT PAS DANS LE MEME ENDROIT + UN PEU DE VARIETE DANS LE JEU
	//random start rotation
	angle = (qrand() % 360);
	setRotation(angle);

	//set the speed !!!!!
	speed = 5; //5 pixels chaque Timer


	//random start position
	int StartX = 0;
	int StartY = 0;

	if (qrand() % 1) //pour avoir plus de randomiter xD
	{
		StartX = (qrand() % 200); //NE PAS DEPASSER TAILLE DE LA SCENE LES METTRE BIEN LOINS POUR QUE CEUX QUI BOUGENT PAS NE TOUCHENT PAS
		StartY = (qrand() % 200); //NE PAS DEPASSER TAILLE DE LA SCENE
	}
	else
	{
		StartX = (qrand() % -100); //NE PAS DEPASSER TAILLE DE LA SCENE
		StartY = (qrand() % -100); //NE PAS DEPASSER TAILLE DE LA SCENE
	}

	setPos(mapToParent(StartX, StartY)); //vérifier qu'il n'est pas en collision avec d'autres
}


MyItem::~MyItem()
{
}

QRectF MyItem::boundingRect() const
{
	//va retourner le QRect de la résolution de l'image de this
	QRect bordures = QRect(0, 0, image.width(), image.height());
	return bordures;
}

void MyItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

	//basic collision detection

	if (scene()->collidingItems(this).isEmpty())
	{
		//no collision...
		//ne rien faire
	}
	else
	{
		//COLLISION !!!
		for (int j = 0; j<image.height(); j++)
		{
			for (int i = 0; i<image.width(); i++)
			{
				int index = image.pixelIndex(i, j);
				image.setColor(index, qRgb(0, 255, 255));
					
			}
		}

		//set the new position
		DoCollision();
	}
	
}

void MyItem::advance(int phase)
{
	if (!phase) return; //l'objet ne bouge pas

	QPointF location = this->pos(); //récupérer sa position

	setPos(mapToParent(0,-(speed))); //CHANGER ICI IL SUFFIT DE PASSER ARGUMENT A CE ADVANCE UN X ET Y QUOI

}


void MyItem::DoCollision()
{
	//get a new position

	//change the angle with a little randomness xD

	if ((qrand() % 1))
	{
		setRotation(rotation() + (180 + qrand() % 10));
	}
	else
	{
		setRotation(rotation() + (180 + qrand() % -10)); //move it to the opposite direction
	}

	//vérifier que la new position est dans la scene et ne sort pas
	QPointF newpoint = mapToParent(-(boundingRect().width()), -(boundingRect().width() + 2));

	if (!scene()->sceneRect().contains((newpoint)))
	{
		//le remettre à l'intérieur u_u
		newpoint = mapToParent(0, 0);

	}
	else
	{
		//on peut user la new position newpoint !
		setPos(newpoint);
	}
}