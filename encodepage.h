#ifndef ENCODEPAGE_H
#define ENCODEPAGE_H

#include <QWidget>
#include <QLabel>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include "des.h"

class EncodePage : public QWidget
{
    Q_OBJECT
private:
    QLabel* label1;
	QLabel* label2;
	QLabel* label3;

    /*QLineEdit* rawData;
    QLineEdit* encodeData;*/
    QTextEdit* rawData;
	QLineEdit* keyData;
    QTextEdit* encodeData;

    QPushButton* encodeBtn;
    QPushButton* copyBtn;

    Des* des;
	char key[10];
private slots:
    void copy_text();
    void encode_text();
	void change_key(const QString &);
public:
    explicit EncodePage(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // ENCODEPAGE_H
