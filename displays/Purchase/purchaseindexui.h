/**************************************************************************
**   File: purchaseindexui.h
**   Created on: Thu Dec 18 23:40:35 EET 2014
**   Author: Michael Bishara
**   Copyright: SphinxSolutions.
**************************************************************************/

#ifndef PURCHASEINDEXUI_H
#define PURCHASEINDEXUI_H
#include "../../erpdisplay.h"
#include "../CommonUI/erpformblock.h"
#include "../CommonUI/erpcombobox.h"
#include "../CommonUI/erptableview.h"
#include "../../Model/purchase.h"
#include "../../Model/purchaseserial.h"

#include "../PurchaseStoreProduct/purchasestoreproductui.h"
#include "../PurchaseFreeLine/purchasefreelineui.h"

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QtSql>
#include <QSqlRelationalDelegate>
#include <QSqlRelationalTableModel>
class PurchaseIndexUI : public ERPDisplay
{
	Q_OBJECT
public:
	explicit PurchaseIndexUI(QWidget *parent = 0);
	static void ShowUI();
	static PurchaseIndexUI* GetUI();
ERPTableView *tabel; 
 Purchase *model; 
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
