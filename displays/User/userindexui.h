/**************************************************************************
**   File: userindexui.h
**   Created on: Sun Nov 16 16:19:26 EET 2014
**   Author: Michael Bishara
**   Copyright: SphinxSolutions.
**************************************************************************/

#ifndef USERINDEXUI_H
#define USERINDEXUI_H
#include "../../erpdisplay.h"
#include "../CommonUI/erpformblock.h"
#include "../CommonUI/erpcombobox.h"
#include "../../Model/user.h"
#include "../../Model/user.h"
#include "../../Model/employee.h"


#include <QWidget>
#include <QLineEdit>
#include <QTableView>
#include <QPushButton>
#include <QtSql>
#include <QSqlRelationalDelegate>
#include <QSqlRelationalTableModel>
class UserIndexUI : public ERPDisplay
{
	Q_OBJECT
public:
	explicit UserIndexUI(QWidget *parent = 0);
	static void ShowUI();
	static UserIndexUI* GetUI();
QTableView *tabel; 
 User *model; 
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
};
#endif