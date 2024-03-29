/**************************************************************************
**   File: productcategoryui.h
**   Created on: Thu Dec 18 12:57:58 EET 2014
**   Author: Michael Bishara
**   Copyright: SphinxSolutions.
**************************************************************************/

#ifndef PRODUCTCATEGORYUI_H
#define PRODUCTCATEGORYUI_H
#include "../../erpdisplay.h"
#include "productcategoryindexui.h"
#include "../CommonUI/erpformblock.h"
#include "../CommonUI/erpcombobox.h"
#include "../CommonUI/addremovebuttons.h"
#include "../CommonUI/RemovebtnWidgets.h"
#include "../../Model/productcategory.h"
#include "../../Model/erpmodel.h"
#include "../../Model/productcategory.h"


#include <QWidget>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QCompleter>
#include <QMessageBox>
#include <QDateEdit>
class ProductCategoryUI : public ERPDisplay
{
	Q_OBJECT
public:
	explicit ProductCategoryUI(QWidget *parent = 0);
	static void ShowUI();
	static ProductCategoryUI* GetUI();
	ERPFormBlock* block0Layout;
	QLineEdit*description;
	void fill(ProductCategory* productcategory);
ProductCategory* productcategory;
private:
	static ERPDisplay* p_instance;
private slots:
	void selectProductCategory();
	void cancel();
	void clear();
public slots:
	bool save();
	bool updateModel();
};
#endif
