/**************************************************************************
**   File: deliveryorderserialindexui.cpp
**   Created on: Fri Dec 19 13:01:03 EET 2014
**   Author: Michael Bishara
**   Copyright: SphinxSolutions.
**************************************************************************/

#include "deliveryorderserialindexui.h"
#include "deliveryorderserialui.h"
#include "../Login/loginui.h"
#include "../MainWindow.h"
#include "../../Model/erpmodel.h"

DeliveryOrderSerialIndexUI::DeliveryOrderSerialIndexUI(QWidget *parent) :ERPDisplay(parent)
{

this->setObjectName("DeliveryOrderSerialIndexUI");
flowLayout = new FlowLayout(formPanel);
flowLayout->setContentsMargins(0,0,0,0);
model = new DeliveryOrderSerial(); 
	model->refresh(); 
	if(!ErpModel::GetInstance()->db.open()) 
	qDebug() <<"Couldn't open databaseee!";
ERPFormBlock* block0Layout = new ERPFormBlock; 
 tabel = new ERPTableView(); 
 tabel->tabel->setModel(model); 
 block0Layout->addRow("",tabel); 
 flowLayout->addWidget(block0Layout); 
  add = new QPushButton("Add"); 
 QObject::connect(add, SIGNAL(clicked()), this, SLOT(addRow())); 
 add->setObjectName("add"); 
 remove = new QPushButton(QObject::tr("Remove")); 
 remove->setObjectName("remove"); 
 QObject::connect(remove, SIGNAL(clicked()), this, SLOT(removeRow())); 
 edit = new QPushButton(QObject::tr("Edit")); 
 QObject::connect(edit, SIGNAL(clicked()), this, SLOT(editRow())); 
 edit->setObjectName("edit"); 
 edit->setEnabled(false); 
 remove->setEnabled(false); 
 QObject::connect(tabel->tabel->selectionModel(), &QItemSelectionModel::selectionChanged, this, &DeliveryOrderSerialIndexUI::onSelectionChanged);
this->controllers->addControllerButton(add); 
 this->controllers->addControllerButton(edit);  
 this->controllers->addControllerButton(remove);
}
ERPDisplay* DeliveryOrderSerialIndexUI::p_instance = 0;
void DeliveryOrderSerialIndexUI::ShowUI() { 
 if(ErpModel::GetInstance()->LoggedUser->UserID == 0) 
 LoginUI::ShowUI(); 
 else if(ErpModel::GetInstance()->UserAccessList.length() > 0){ 
 if( !ErpModel::GetInstance()->UserAccessList.at(0)->DeliveryOrderSerial) 
 QMessageBox::warning(0, QObject::tr("Access Permission"),QObject::tr("You do not have Permission")); 
 else{	if (p_instance != 0) 
	p_instance->deleteLater(); 
	p_instance = new DeliveryOrderSerialIndexUI(mainwindow::GetMainDisplay()); 
  mainwindow::ShowDisplay(p_instance); 
} 
 }else	QMessageBox::warning(0, QObject::tr("Access Permission"),QObject::tr("You do not have a Permission List")); }
DeliveryOrderSerialIndexUI*DeliveryOrderSerialIndexUI::GetUI(){ 
 	if (p_instance == 0) { 
		p_instance = new ERPDisplay(mainwindow::GetMainDisplay()); 
	} 
	return (DeliveryOrderSerialIndexUI*) p_instance; 
}
void DeliveryOrderSerialIndexUI::addRow(){ 
 DeliveryOrderSerialUI::ShowUI();}
void DeliveryOrderSerialIndexUI::editRow(){ 
 DeliveryOrderSerialUI::ShowUI(); 
 DeliveryOrderSerialUI::GetUI()->fill(model->get(tabel->tabel->selectionModel()->selectedRows().last())); 
 }
void DeliveryOrderSerialIndexUI::removeRow(){ 
 model->remove(tabel->tabel->selectionModel()->selectedRows().last()); 
 }
void DeliveryOrderSerialIndexUI::onSelectionChanged(){ 
 int e = tabel->tabel->selectionModel()->selectedRows().count(); 
 remove->setEnabled(e); 
 edit->setEnabled(e); 
 }
void DeliveryOrderSerialIndexUI::showEvent(QShowEvent * event){ 
 	if(this->parent() != 0){ 
 tabel->setMinimumWidth(mainwindow::GetMainDisplay()->width() - mainwindow::GetMainDisplay()->navigation->width() - 50); 
 tabel->setMinimumHeight(mainwindow::GetMainDisplay()->height() - mainwindow::GetMainDisplay()->inNavContacts->height() - 100); 
	} 
 event->accept(); 
 }

