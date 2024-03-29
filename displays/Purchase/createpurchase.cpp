﻿/*************************************
**   Created on:  12/7/2014
**   Author: michaelbishara
**   Copyright: Bishara©.
**************************************/

#include "createpurchase.h"
#include "../PurchaseStoreProduct/purchasestoreproductindexui.h"
#include "../MainWindow.h"

#include <QItemSelectionModel>

CreatePurchase::CreatePurchase(QWidget *parent) :
	ERPDisplay(parent)
{
	this->setObjectName("Index");
	purchase = new Purchase();
	flowLayout = new FlowLayout(formPanel);
	flowLayout->setContentsMargins(0,0,0,0);

	QPushButton* save = new QPushButton("SSSave");
	QObject::connect(save, SIGNAL(clicked()), this, SLOT(save()));
	save->setObjectName("save");
	QPushButton* cancel = new QPushButton("Cancel");
	cancel->setObjectName("cancel");
	QObject::connect(cancel, SIGNAL(clicked()), this, SLOT(cancel()));
	QPushButton* clear = new QPushButton("Clear");
	QObject::connect(clear, SIGNAL(clicked()), this, SLOT(clear()));
	clear->setObjectName("clear");
	this->controllers->addControllerButton(save);
	this->controllers->addControllerButton(clear);
	this->controllers->addControllerButton(cancel);
	block0Layout = new ERPFormBlock;
	if(this->flowLayout && this->flowLayout->parent()->objectName() == "formPanel")
		block0Layout->setMinimumWidth(330);
	creationdate = new QDateEdit(QDate::currentDate());
	creationdate->setCalendarPopup(true);
	creationdate->setDisplayFormat("ddd dd/MM/yyyy");
	block0Layout->addRow("Creation Date",creationdate);
	deliverydate = new QDateEdit(QDate::currentDate());
	deliverydate->setCalendarPopup(true);
	deliverydate->setDisplayFormat("ddd dd/MM/yyyy");
	block0Layout->addRow("Delivery Date",deliverydate);


	purchasestoreproductui = new PurchaseStoreProductUI();
	purchasestoreproductui->block0Layout->hideRow(purchasestoreproductui->purchase);
	purchasestoreproductui->controllers->setFixedHeight(0);
	block0Layout->addRow("Product"+QString::number(PurchaseStoreProducts.count()),purchasestoreproductui);

	addremovePurchaseStoreProductButtons = new AddRemoveButtons();
	QObject::connect(addremovePurchaseStoreProductButtons, SIGNAL(addPressed()), this, SLOT(addPurchaseStoreProduct()));


	block0Layout->addRow("",addremovePurchaseStoreProductButtons);

	flowLayout->addWidget(block0Layout);

	block1Layout = new ERPFormBlock;

	tabel = new ERPTableView();
	model = new QStandardItemModel(PurchaseStoreProducts.count(),5,0);
	model->setHeaderData(0, Qt::Horizontal, QObject::tr("Number"));
	model->setHeaderData(1, Qt::Horizontal, QObject::tr("Store"));
	model->setHeaderData(2, Qt::Horizontal, QObject::tr("Supplier"));
	model->setHeaderData(3, Qt::Horizontal, QObject::tr("Product"));
	model->setHeaderData(4, Qt::Horizontal, QObject::tr("Amount"));
	tabel->tabel->setModel(model);
	block1Layout->addRow("",tabel);

	QWidget *tabelControls =  new QWidget();
	QHBoxLayout *layout = new QHBoxLayout(tabelControls);
	layout->setContentsMargins(0,0,0,0);
	remove = new QPushButton("Remove");

	QObject::connect(remove, SIGNAL(clicked()), this, SLOT(removeRow()));
	QObject::connect(tabel->tabel->selectionModel(), &QItemSelectionModel::selectionChanged, this, &CreatePurchase::onSelectionChanged);

	remove->setObjectName("remove");
	remove->setEnabled(false);
	layout->addWidget(remove,0,Qt::AlignCenter);

	block1Layout->addRow("",tabelControls);
	flowLayout->addWidget(block1Layout);

}
ERPDisplay* CreatePurchase::p_instance = 0;
void CreatePurchase::ShowUI() {
	if (p_instance != 0)
		p_instance->deleteLater();
	p_instance = new CreatePurchase(mainwindow::GetMainDisplay());
	mainwindow::ShowDisplay(p_instance);
}
CreatePurchase*CreatePurchase::GetUI(){
	if (p_instance == 0) {
		p_instance = new ERPDisplay(mainwindow::GetMainDisplay());
	}
	return (CreatePurchase*) p_instance;
}
void CreatePurchase::onSelectionChanged(){
	int e = tabel->tabel->selectionModel()->selectedRows().count();
	remove->setEnabled(e);
}
void CreatePurchase::removeRow(){
	PurchaseStoreProducts.takeAt(tabel->tabel->selectionModel()->selectedRows().at(0).row())->deleteLater();
	refreshTabel();
}
void CreatePurchase::refreshTabel(){
	model = new QStandardItemModel(PurchaseStoreProducts.count(),5,0);
	int row = 0; //row

	foreach(PurchaseStoreProductUI* p,PurchaseStoreProducts){

		model->setItem(row,0,new QStandardItem(QString::number(row+1)));
		model->setItem(row,1,new QStandardItem(p->store->currentText()));
		model->setItem(row,2,new QStandardItem(p->contact->currentText()));
		model->setItem(row,3,new QStandardItem(p->product->currentText()));
		model->setItem(row,4,new QStandardItem(QString::number(p->purchasestoreproduct->Amount)));
		row++;
	}
	model->setHeaderData(0, Qt::Horizontal, QObject::tr("Number"));
	model->setHeaderData(1, Qt::Horizontal, QObject::tr("Store"));
	model->setHeaderData(2, Qt::Horizontal, QObject::tr("Supplier"));
	model->setHeaderData(3, Qt::Horizontal, QObject::tr("Product"));
	model->setHeaderData(4, Qt::Horizontal, QObject::tr("Amount"));
	tabel->tabel->setModel(model);
	QObject::connect(tabel->tabel->selectionModel(), &QItemSelectionModel::selectionChanged, this, &CreatePurchase::onSelectionChanged);

	//tabel->tabel->sortByColumn(0,Qt::AscendingOrder);
	tabel->repaint();
}

void CreatePurchase::addPurchaseStoreProduct(){

	PurchaseStoreProducts.append(purchasestoreproductui);
	if(!this->updateModel())
		PurchaseStoreProducts.removeOne(purchasestoreproductui);
	else{
	block0Layout->hideRow(purchasestoreproductui);
	block0Layout->removeRow(addremovePurchaseStoreProductButtons);
	refreshTabel();
	purchasestoreproductui = new PurchaseStoreProductUI();
	purchasestoreproductui->controllers->setFixedHeight(0);
	block0Layout->addRow("",purchasestoreproductui);

	addremovePurchaseStoreProductButtons = new AddRemoveButtons();
	QObject::connect(addremovePurchaseStoreProductButtons, SIGNAL(addPressed()), this, SLOT(addPurchaseStoreProduct()));
	block0Layout->addRow("",addremovePurchaseStoreProductButtons);
	}
}
void CreatePurchase::addPurchaseStoreProduct(PurchaseStoreProduct* PurchaseStoreProduct){
	PurchaseStoreProductUI*purchasestoreproductui = new PurchaseStoreProductUI();
	PurchaseStoreProducts.append(purchasestoreproductui);
	purchasestoreproductui->block0Layout->removeRow(purchasestoreproductui->purchase);
	purchasestoreproductui->controllers->setFixedHeight(0);
	purchasestoreproductui->fill(PurchaseStoreProduct);
	refreshTabel();
}
void CreatePurchase::removePurchaseStoreProduct(QWidget* widget){
	if(PurchaseStoreProducts.count()  > 0){
		PurchaseStoreProductUI* purchasestoreproductui = (PurchaseStoreProductUI*) widget;
		PurchaseStoreProducts.removeOne(purchasestoreproductui);
		RemovebtnWidgets* sender = (RemovebtnWidgets*) this->sender();
		block0Layout->removeRow(sender);
	}
}
void CreatePurchase::fill(Purchase* purchase){
	clear();
	this->purchase = purchase;
	creationdate->setDate(purchase->CreationDate);
	deliverydate->setDate(purchase->DeliveryDate);
	foreach(PurchaseStoreProduct* purchasestoreproduct, purchase->purchasestoreproducts) {
		addPurchaseStoreProduct(purchasestoreproduct);
	}
}
void CreatePurchase::clear(){
	delete this->purchase;
	this->PurchaseStoreProducts.clear();
	creationdate->setDate(QDate::currentDate());
	deliverydate->setDate(QDate::currentDate());
	this->purchase = new Purchase();
}
void CreatePurchase::selectPurchase(){
	if(Purchase::GetStringList().contains(QString::number(this->purchase->PurchaseSerialID)))
	{
	Purchase* con = Purchase::Get(QString::number(this->purchase->PurchaseSerialID));
	if(this->purchase->PurchaseID != con->PurchaseID){
	fill(con);
	}
	}
	else if(purchase->PurchaseID != 0)
	clear();
}
bool CreatePurchase::save(){
	bool errors = false;
	QString errorString =  "";
	if(creationdate->text().trimmed().isEmpty()){
		errors = true;
		errorString += "Creation Date Can't be Empty! \n";
		creationdate->setObjectName("error");
		creationdate->style()->unpolish(creationdate);
		creationdate->style()->polish(creationdate);
		creationdate->update();
	}
	else {
		creationdate->setObjectName("creationdate");
		creationdate->style()->unpolish(creationdate);
		creationdate->style()->polish(creationdate);
		creationdate->update();
		purchase->CreationDate.fromString(creationdate->text().trimmed());
	}
	if(deliverydate->text().trimmed().isEmpty()){
		errors = true;
		errorString += "Delivery Date Can't be Empty! \n";
		deliverydate->setObjectName("error");
		deliverydate->style()->unpolish(deliverydate);
		deliverydate->style()->polish(deliverydate);
		deliverydate->update();
	}
	else {
		deliverydate->setObjectName("deliverydate");
		deliverydate->style()->unpolish(deliverydate);
		deliverydate->style()->polish(deliverydate);
		deliverydate->update();
		purchase->DeliveryDate.fromString(deliverydate->text());
	}
	if(!errors) {
		purchase->save();
		for(int i = 0; i < PurchaseStoreProducts.length(); i++){
			PurchaseStoreProducts.at(i)->purchasestoreproduct->PurchaseID= purchase->PurchaseID;
			if(!PurchaseStoreProducts.at(i)->save()){
				errors = true;
				break; }
		}
		for(int i = 0; i < purchase->purchasestoreproducts.length(); i++){
			bool flag = false;
			for(int j = 0; j < PurchaseStoreProducts.length(); j++){
				if(purchase->purchasestoreproducts.at(i)->PurchaseStoreProductID == PurchaseStoreProducts.at(j)->purchasestoreproduct->PurchaseStoreProductID){
					flag = true;}}
			if(!flag){
				purchase->purchasestoreproducts.at(i)->remove();}
		}
		if(!errors){
			PurchaseIndexUI::ShowUI();
			return true;}
		else return false;
	}
	else{ QMessageBox::warning(this, "Purchase",errorString.trimmed());
		return false;
	}
}
void CreatePurchase::cancel(){
	PurchaseIndexUI::ShowUI();
}
bool CreatePurchase::updateModel(){
	bool errors = false;
	QString errorString =  "";
	if(creationdate->text().trimmed().isEmpty()){
		errors = true;
		errorString += "Creation Date Can't be Empty! \n";
		creationdate->setObjectName("error");
		creationdate->style()->unpolish(creationdate);
		creationdate->style()->polish(creationdate);
		creationdate->update();
	}
	else {
		creationdate->setObjectName("creationdate");
		creationdate->style()->unpolish(creationdate);
		creationdate->style()->polish(creationdate);
		creationdate->update();
		purchase->CreationDate.fromString(creationdate->text());
	}
	if(deliverydate->text().trimmed().isEmpty()){
		errors = true;
		errorString += "Delivery Date Can't be Empty! \n";
		deliverydate->setObjectName("error");
		deliverydate->style()->unpolish(deliverydate);
		deliverydate->style()->polish(deliverydate);
		deliverydate->update();
	}
	else {
		deliverydate->setObjectName("deliverydate");
		deliverydate->style()->unpolish(deliverydate);
		deliverydate->style()->polish(deliverydate);
		deliverydate->update();
		purchase->DeliveryDate.fromString(deliverydate->text().trimmed());
	}
	for(int i = 0; i < PurchaseStoreProducts.length(); i++){
		if(!PurchaseStoreProducts.at(i)->updateModel()){
			errors = true;
			break; }
	}
	if(!errors){
		return true;
	}
	else{ if(!errorString.trimmed().isEmpty())
		QMessageBox::warning(this, "Purchase",errorString.trimmed());
		return false;
	}
}
void CreatePurchase::showEvent(QShowEvent * event){
	if(this->parent() != 0){
		tabel->setFixedWidth(mainwindow::GetMainDisplay()->width() - mainwindow::GetMainDisplay()->navigation->width() - 420);
		tabel->setFixedHeight(mainwindow::GetMainDisplay()->height() - mainwindow::GetMainDisplay()->inNavPurchase->height() - 150);
	}
	event->accept();
}
