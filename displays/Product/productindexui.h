﻿/**************************************************************************
**   File: productindexui.h
**   Created on: Thu Dec 18 12:57:59 EET 2014
**   Author: Michael Bishara
**   Copyright: SphinxSolutions.
**************************************************************************/

#ifndef PRODUCTINDEXUI_H
#define PRODUCTINDEXUI_H
#include "../../erpdisplay.h"
#include "../CommonUI/erpformblock.h"
#include "../CommonUI/erpcombobox.h"
#include "../CommonUI/erptableview.h"
#include "../../Model/product.h"
#include "../../Model/unit.h"
#include "../../Model/tax.h"
#include "../../Model/productcategory.h"

#include "../ProductImage/productimageui.h"

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QtSql>

#include <QSqlRelationalTableModel>
class ProductIndexUI : public ERPDisplay
{
	Q_OBJECT
public:
	explicit ProductIndexUI(QWidget *parent = 0);
	static void ShowUI();
	static ProductIndexUI* GetUI();
ERPTableView *tabel;
 Product *model;
 QPushButton* add;
 QPushButton* remove;
 QPushButton* edit;
private:
	static ERPDisplay* p_instance;
private slots:
	void addRow();
 void removeRow();
 void editRow();
 void onSelectionChanged();
protected:
void showEvent(QShowEvent * event);
};
#endif
