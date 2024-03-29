/**************************************************************************
**   File: projectindexui.h
**   Created on: Thu Dec 18 12:57:59 EET 2014
**   Author: Michael Bishara
**   Copyright: SphinxSolutions.
**************************************************************************/

#ifndef PROJECTINDEXUI_H
#define PROJECTINDEXUI_H
#include "../../erpdisplay.h"
#include "../CommonUI/erpformblock.h"
#include "../CommonUI/erpcombobox.h"
#include "../CommonUI/erptableview.h"
#include "../../Model/project.h"
#include "../../Model/projectstatus.h"
#include "../../Model/contact.h"

#include "../ProjectSales/projectsalesui.h"
#include "../Task/taskui.h"
#include "../ProjectContactPerson/projectcontactpersonui.h"
#include "../ProjectService/projectserviceui.h"
#include "../ProjectFile/projectfileui.h"

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QtSql>
#include <QSqlRelationalDelegate>
#include <QSqlRelationalTableModel>
class ProjectIndexUI : public ERPDisplay
{
	Q_OBJECT
public:
	explicit ProjectIndexUI(QWidget *parent = 0);
	static void ShowUI();
	static ProjectIndexUI* GetUI();
ERPTableView *tabel; 
 Project *model; 
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
