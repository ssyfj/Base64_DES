#ifndef CONTENT_H
#define CONTENT_H

#include <QFrame>
#include <QStackedWidget>
#include "decodepage.h"
#include "encodepage.h"

class Content : public QFrame
{
	Q_OBJECT
public:
	Content(QWidget *parent = 0);
	~Content();

	QStackedWidget* stack;

	DecodePage* dp;
	EncodePage* ep;
};

#endif // CONTENT_H
