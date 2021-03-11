#include "content.h"
#include <QtWidgets/QApplication>
#include <QApplication>
#include <QSplitter>
#include <QListWidget>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QFont font("ZYSong18030", 12);
	a.setFont(font);

	QSplitter* splitterMain = new QSplitter(Qt::Horizontal, 0);
	splitterMain->setOpaqueResize(true);

	QListWidget* list = new QListWidget(splitterMain);
	list->insertItem(0, QObject::tr("encrypt"));
	list->insertItem(1, QObject::tr("decrypt"));
	list->setFixedWidth(80);


	Content* content = new Content(splitterMain);

	QObject::connect(list, SIGNAL(currentRowChanged(int)), content->stack, SLOT(setCurrentIndex(int)));


	splitterMain->setWindowTitle(QObject::tr("197XXXX:ld"));
	splitterMain->setFixedSize(550, 350);
	splitterMain->show();

	return a.exec();
}

