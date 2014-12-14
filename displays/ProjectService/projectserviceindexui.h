/**************************************************************************
**   File: projectserviceindexui.h
**   Created on: Sun Dec 14 22:39:12 EET 2014
**   Author: Michael Bishara
**   Copyright: SphinxSolutions.
**************************************************************************/

#ifndef PROJECTSERVICEINDEXUI_H
#define PROJECTSERVICEINDEXUI_H
#include "../../erpdisplay.h"
#include "../CommonUI/erpformblock.h"
#include "../CommonUI/erpcombobox.h"
#include "../CommonUI/erptableview.h"
#include "../../Model/projectservice.h"
#include "../../Model/project.h"
#include "../../Model/service.h"


#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QtSql>
#include <QSqlRelationalDelegate>
#include <QSqlRelationalTableModel>
class ProjectServiceIndexUI : public ERPDisplay
{
	Q_OBJECT
public:
	explicit ProjectServiceIndexUI(QWidget *parent = 0);
	static void ShowUI();
	static ProjectServiceIndexUI* GetUI();
ERPTableView *tabel; 
 ProjectService *model; 
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