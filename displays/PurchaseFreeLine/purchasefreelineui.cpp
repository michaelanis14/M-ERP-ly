﻿/**************************************************************************
**   File: purchasefreelineui.cpp
**   Created on: Thu Dec 18 12:57:59 EET 2014
**   Author: Michael Bishara
**   Copyright: SphinxSolutions.
**************************************************************************/

#include "purchasefreelineui.h"
#include "../Login/loginui.h"
#include "../MainWindow.h"

PurchaseFreeLineUI::PurchaseFreeLineUI(QWidget *parent) :ERPDisplay(parent)
{

	purchasefreeline = new PurchaseFreeLine();
	flowLayout = new FlowLayout(this);
	flowLayout->setContentsMargins(0,0,0,0);

	QDoubleValidator* doubleValidator = new QDoubleValidator(0,99.0, 2);
	QPushButton* save = new QPushButton("Save");
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
	purchase = new ERPComboBox();
	purchase->addItems(Purchase::GetPairList());
	block0Layout->addRow(QObject::tr("Purchase"),purchase);
	description = new QLineEdit();
	block0Layout->addRow(QObject::tr("Description"),description);
	contact = new ERPComboBox();
	contact->addItems(Contact::GetPairList((Contact::QuerySelect("ContactTypeID = 2"))));
	block0Layout->addRow(QObject::tr("Contact"),contact);
	amount = new QLineEdit();
	amount->setValidator( doubleValidator );
	connect(amount, SIGNAL(textChanged(QString)), this, SLOT(updateTotal(QString)));

	block0Layout->addRow(QObject::tr("Amount"),amount);
	price = new QLineEdit();
	price->setValidator( doubleValidator );
	connect(price, SIGNAL(textChanged(QString)), this, SLOT(updateTotal(QString)));

	block0Layout->addRow(QObject::tr("Price Per Item"),price);
	total = new QLineEdit();
	total->setEnabled(false);
	total->setValidator( doubleValidator );

	updateTotal("QString");
	block0Layout->addRow(QObject::tr("Total"),total);


	flowLayout->addWidget(block0Layout);

}
ERPDisplay* PurchaseFreeLineUI::p_instance = 0;
void PurchaseFreeLineUI::ShowUI() {
	if(ErpModel::GetInstance()->LoggedUser->UserID == 0)
		LoginUI::ShowUI();
	else if(ErpModel::GetInstance()->UserAccessList.length() > 0){
		if( !ErpModel::GetInstance()->UserAccessList.at(0)->PurchaseFreeLine)
			QMessageBox::warning(0, QObject::tr("Access Permission"),QObject::tr("You do not have Permission"));
		else{	if (p_instance != 0)
				p_instance->deleteLater();
			p_instance = new PurchaseFreeLineUI(mainwindow::GetMainDisplay());
			mainwindow::ShowDisplay(p_instance);
		}
	}else	QMessageBox::warning(0, QObject::tr("Access Permission"),QObject::tr("You do not have a Permission List")); }
PurchaseFreeLineUI*PurchaseFreeLineUI::GetUI(){
	if (p_instance == 0) {
		p_instance = new ERPDisplay(mainwindow::GetMainDisplay());
	}
	return (PurchaseFreeLineUI*) p_instance;
}
void PurchaseFreeLineUI::fill(PurchaseFreeLine* purchasefreeline){
	clear();
	this->purchasefreeline = purchasefreeline;
	purchase->setIndexByKey(purchasefreeline->PurchaseID);
	description->setText(purchasefreeline->Description);
	contact->setIndexByKey(purchasefreeline->ContactID);
	amount->setText(QString::number(purchasefreeline->Amount));
	price->setText(QString::number(purchasefreeline->Price));
}
void PurchaseFreeLineUI::clear(){
	delete this->purchasefreeline;
	description->setText("");
	amount->setText("");
	price->setText("");
	this->purchasefreeline = new PurchaseFreeLine();
}
void PurchaseFreeLineUI::selectPurchaseFreeLine(){
	if(PurchaseFreeLine::GetStringList().contains(QString::number(this->purchasefreeline->PurchaseID)))
	{
		PurchaseFreeLine* con = PurchaseFreeLine::Get(QString::number(this->purchasefreeline->PurchaseID));
		if(this->purchasefreeline->PurchaseFreeLineID != con->PurchaseFreeLineID){
			fill(con);
		}
	}
	else if(purchasefreeline->PurchaseFreeLineID != 0)
		clear();
}
bool PurchaseFreeLineUI::save(){
	bool errors = false;
	QString errorString =  "";
	if(!purchase->isHidden())
		purchasefreeline->PurchaseID = purchase->getKey();
	if(description->text().trimmed().isEmpty()){
		errors = true;
		errorString += QObject::tr("Description Can't be Empty! \n");
		description->setObjectName("error");
		description->style()->unpolish(description);
		description->style()->polish(description);
		description->update();
	}
	else {
		description->setObjectName("description");
		description->style()->unpolish(description);
		description->style()->polish(description);
		description->update();
		purchasefreeline->Description = description->text().trimmed();
	}
	if(!contact->isHidden())
		purchasefreeline->ContactID = contact->getKey();
	if(amount->text().trimmed().isEmpty()){
		errors = true;
		errorString += QObject::tr("Amount Can't be Empty! \n");
		amount->setObjectName("error");
		amount->style()->unpolish(amount);
		amount->style()->polish(amount);
		amount->update();
	}
	else {
		amount->setObjectName("amount");
		amount->style()->unpolish(amount);
		amount->style()->polish(amount);
		amount->update();
		purchasefreeline->Amount = amount->text().trimmed().toDouble();
	}
	if(price->text().trimmed().isEmpty()){
		errors = true;
		errorString += QObject::tr("Price Can't be Empty! \n");
		price->setObjectName("error");
		price->style()->unpolish(price);
		price->style()->polish(price);
		price->update();
	}
	else {
		price->setObjectName("price");
		price->style()->unpolish(price);
		price->style()->polish(price);
		price->update();
		purchasefreeline->Price = price->text().trimmed().toDouble();
	}
	if(!errors) {
		purchasefreeline->save();
		if(!errors){
			PurchaseFreeLineIndexUI::ShowUI();
			return true;}
		else return false;
	}
	else{ QMessageBox::warning(this, QObject::tr("PurchaseFreeLine"),errorString.trimmed());
		return false;
	}
}
void PurchaseFreeLineUI::cancel(){
	PurchaseFreeLineIndexUI::ShowUI();
}
bool PurchaseFreeLineUI::updateModel(){
	bool errors = false;
	QString errorString =  "";
	if(purchasefreeline->PurchaseID == 0)
		purchasefreeline->PurchaseID = purchase->getKey();
	if(description->text().trimmed().isEmpty()){
		errors = true;
		errorString += QObject::tr("Description Can't be Empty! \n");
		description->setObjectName("error");
		description->style()->unpolish(description);
		description->style()->polish(description);
		description->update();
	}
	else {
		description->setObjectName("description");
		description->style()->unpolish(description);
		description->style()->polish(description);
		description->update();
		purchasefreeline->Description = description->text().trimmed();
	}
	if(purchasefreeline->ContactID == 0)
		purchasefreeline->ContactID = contact->getKey();
	if(amount->text().trimmed().isEmpty()){
		errors = true;
		errorString += QObject::tr("Amount Can't be Empty! \n");
		amount->setObjectName("error");
		amount->style()->unpolish(amount);
		amount->style()->polish(amount);
		amount->update();
	}
	else {
		amount->setObjectName("amount");
		amount->style()->unpolish(amount);
		amount->style()->polish(amount);
		amount->update();
		purchasefreeline->Amount = amount->text().trimmed().toDouble();
	}
	if(price->text().trimmed().isEmpty()){
		errors = true;
		errorString += QObject::tr("Price Can't be Empty! \n");
		price->setObjectName("error");
		price->style()->unpolish(price);
		price->style()->polish(price);
		price->update();
	}
	else {
		price->setObjectName("price");
		price->style()->unpolish(price);
		price->style()->polish(price);
		price->update();
		purchasefreeline->Price = price->text().trimmed().toDouble();
	}
	if(!errors){
		return true;
	}
	else{ if(!errorString.trimmed().isEmpty()) QMessageBox::warning(this, QObject::tr("PurchaseFreeLine"),errorString.trimmed());
		return false;
	}
}

void PurchaseFreeLineUI::updateTotal(QString){

	double tot = ((amount->text().toDouble()) * (price->text().toDouble()));
	total->setText(QString::number(tot,'f',2));
}
