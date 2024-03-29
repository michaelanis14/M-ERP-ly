﻿/**************************************************************************
**   File: purchaseui.h
**   Created on: Thu Dec 18 23:40:35 EET 2014
**   Author: Michael Bishara
**   Copyright: SphinxSolutions.
**************************************************************************/

#ifndef PURCHASEUI_H
#define PURCHASEUI_H
#include "../../erpdisplay.h"
#include "purchaseindexui.h"
#include "../CommonUI/erpformblock.h"
#include "../CommonUI/erpcombobox.h"
#include "../CommonUI/addremovebuttons.h"
#include "../CommonUI/RemovebtnWidgets.h"
#include "../../Model/purchase.h"
#include "../../Model/erpmodel.h"
#include "../../Model/purchase.h"
#include "../../Model/purchaseserial.h"

#include "../PurchaseStoreProduct/purchasestoreproductui.h"
#include "../PurchaseFreeLine/purchasefreelineui.h"

#include <QWidget>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QCompleter>
#include <QMessageBox>
#include <QDateEdit>
class PurchaseUI : public ERPDisplay
{
	Q_OBJECT
public:
	explicit PurchaseUI(QWidget *parent = 0);
	static void ShowUI();
	static PurchaseUI* GetUI();
	ERPFormBlock* block0Layout;
	ERPFormBlock* block1Layout;
	ERPFormBlock* block2Layout;
	QList<PurchaseStoreProductUI*> PurchaseStoreProducts;
	QList<PurchaseFreeLineUI*> PurchaseFreeLines;
	QLineEdit*serial;
	ERPComboBox*purchaseserial;
	QDateEdit*creationdate;
	QDateEdit*deliverydate;
	void fill(Purchase* purchase);
Purchase* purchase;
private:
	static ERPDisplay* p_instance;
private slots:
	void addPurchaseStoreProduct();
	void addPurchaseStoreProduct(PurchaseStoreProduct* PurchaseStoreProduct);
	void removePurchaseStoreProduct(QWidget* widget);
	void addPurchaseFreeLine();
	void addPurchaseFreeLine(PurchaseFreeLine* PurchaseFreeLine);
	void removePurchaseFreeLine(QWidget* widget);
	void selectPurchase();
	void cancel();
	void clear();
public slots:
	bool save();
	bool updateModel();
	void selectionChanged(QString);
};
#endif
