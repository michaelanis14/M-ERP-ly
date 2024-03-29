﻿/*************************************
**   Created on:  10/4/2014
**   Author: michaelbishara
**   Copyright: Bishara©.
**************************************/

#ifndef ERPCOMBOBOX_H
#define ERPCOMBOBOX_H

#include <QWidget>
#include <QComboBox>

class ERPComboBox : public QComboBox
{
	Q_OBJECT
public:
	explicit ERPComboBox(QWidget *parent = 0);
	void addItems(QList<QPair< int,QString > >);
	int getKey();
	void setIndexByKey(int key);
	bool addedItems;
private:
	QList<QPair<int, QString> >  items;
signals:
	void refreshModel();

public slots:

protected slots:
	void focusOutEvent(QFocusEvent *e);


};

#endif // ERPCOMBOBOX_H
