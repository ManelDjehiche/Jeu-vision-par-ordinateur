#pragma once
#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

class MyItem : public QGraphicsPixmapItem
{
public:
	MyItem(QImage img);//pour les obstacles: image idem
	~MyItem();

	QRectF boundingRect() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);


protected:
	void advance(int phase);

private:
	qreal angle;
	qreal speed;
	QImage image;
	void DoCollision();
};

