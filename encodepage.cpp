#include "encodepage.h"
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QClipboard>
#include <QApplication>

EncodePage::EncodePage(QWidget *parent) : QWidget(parent)
{
    label1 = new QLabel(tr("raw data:"));
    label2 = new QLabel(tr("enc data:"));
	label3 = new QLabel(tr("key:"));

    /*rawData = new QLineEdit();
    encodeData = new QLineEdit();*/
    rawData = new QTextEdit();
    encodeData = new QTextEdit();
	keyData = new QLineEdit();

    encodeBtn = new QPushButton(tr("enco"));
    copyBtn = new QPushButton(tr("copy"));

    QGridLayout* UpLayout = new QGridLayout();
    QHBoxLayout* DownLayout = new QHBoxLayout();
    QVBoxLayout* MainLayout = new QVBoxLayout(this);

	UpLayout->addWidget(label1, 0, 0);
	UpLayout->addWidget(rawData, 0, 1);
	UpLayout->addWidget(label3, 1, 0);
	UpLayout->addWidget(keyData, 1, 1);
	UpLayout->addWidget(label2, 2, 0);
	UpLayout->addWidget(encodeData, 2, 1);
    UpLayout->setColumnStretch(0,1);
    UpLayout->setColumnStretch(1,3);

    DownLayout->addWidget(encodeBtn);
    DownLayout->addWidget(copyBtn);

    MainLayout->addLayout(UpLayout);
    MainLayout->addLayout(DownLayout);
    //MainLayout->setSizeConstraint(QLayout::SetFixedSize);

    des = new Des();

    connect(copyBtn,SIGNAL(clicked()),this,SLOT(copy_text()));
    connect(encodeBtn,SIGNAL(clicked()),this,SLOT(encode_text()));
	connect(keyData, SIGNAL(textChanged(const QString &)), this, SLOT(change_key(const QString &)));
}

void EncodePage::copy_text()
{
    QString source = encodeData->toPlainText();    //textedit是toPlainText()
    QClipboard* clipboard = QApplication::clipboard();  //获取系统截切板指针
    clipboard->setText(source);
    //QString originalText = clipboard->text();   //获取截切板信息
}

void EncodePage::change_key(const QString &)
{
	//qDebug("666");
	QString source = keyData->text();
	strcpy(key, source.toStdString().c_str());
}


void EncodePage::encode_text()
{
    QString raw_data = rawData->toPlainText();  //获取原始数据
    des->DES_E(raw_data.toStdString().c_str(),this->key); //进行加密
    encodeData->setText(QString((const char*)des->base->dst));    //将结果显示
}
