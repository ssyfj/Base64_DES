#ifndef DECODEPAGE_H
#define DECODEPAGE_H

#include <QWidget>
#include <QLabel>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include "des.h"

class DecodePage : public QWidget
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
    void decode_text();
	void change_key(const QString &);
public:
    explicit DecodePage(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // DECODEPAGE_H
