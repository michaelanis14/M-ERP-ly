﻿/*************************************
**   Created on:  10/8/2014
**   Author: michaelbishara
**   Copyright: Bishara©.
**************************************/

#ifndef ERPFORMBLOCK_H
#define ERPFORMBLOCK_H

#include <QWidget>
#include <QFormLayout>

class ERPFormBlock : public QWidget
{
	Q_OBJECT
public:
	explicit ERPFormBlock(QWidget *parent = 0);
	void addRow(const QString & labelText, QWidget * field );
private:
	QFormLayout *formLayout ;
signals:

public slots:

};

#endif // ERPFORMBLOCK_H