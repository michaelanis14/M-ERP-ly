/**************************************************************************
**   File: deliveryorderfreelineui.cpp
**   Created on: Thu Dec 18 12:57:59 EET 2014
**   Author: Michael Bishara
**   Copyright: SphinxSolutions.
**************************************************************************/

#include "deliveryorderfreelineui.h"
#include "../Login/loginui.h"
#include "../MainWindow.h"

DeliveryOrderFreelineUI::DeliveryOrderFreelineUI(QWidget *parent) :ERPDisplay(parent)
{

deliveryorderfreeline = new DeliveryOrderFreeline();
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
deliveryorder = new ERPComboBox();
deliveryorder->addItems(DeliveryOrder::GetPairList());
block0Layout->addRow(QObject::tr("Delivery Order"),deliveryorder);
description = new QLineEdit();
block0Layout->addRow(QObject::tr("Description"),description);
amount = new QLineEdit();
amount->setValidator( doubleValidator );
block0Layout->addRow(QObject::tr("Amount"),amount);
price = new QLineEdit();
price->setValidator( doubleValidator );
block0Layout->addRow(QObject::tr("Price"),price);
flowLayout->addWidget(block0Layout);

}
ERPDisplay* DeliveryOrderFreelineUI::p_instance = 0;
void DeliveryOrderFreelineUI::ShowUI() { 
 if(ErpModel::GetInstance()->LoggedUser->UserID == 0) 
 LoginUI::ShowUI(); 
 else if(ErpModel::GetInstance()->UserAccessList.length() > 0){ 
 if( !ErpModel::GetInstance()->UserAccessList.at(0)->DeliveryOrderFreeline) 
 QMessageBox::warning(0, QObject::tr("Access Permission"),QObject::tr("You do not have Permission")); 
 else{	if (p_instance != 0) 
	p_instance->deleteLater(); 
	p_instance = new DeliveryOrderFreelineUI(mainwindow::GetMainDisplay()); 
  mainwindow::ShowDisplay(p_instance); 
} 
 }else	QMessageBox::warning(0, QObject::tr("Access Permission"),QObject::tr("You do not have a Permission List")); }
DeliveryOrderFreelineUI*DeliveryOrderFreelineUI::GetUI(){ 
 	if (p_instance == 0) { 
		p_instance = new ERPDisplay(mainwindow::GetMainDisplay()); 
	} 
	return (DeliveryOrderFreelineUI*) p_instance; 
}
void DeliveryOrderFreelineUI::fill(DeliveryOrderFreeline* deliveryorderfreeline){ 
clear();
this->deliveryorderfreeline = deliveryorderfreeline;
deliveryorder->setIndexByKey(deliveryorderfreeline->DeliveryOrderID);
description->setText(deliveryorderfreeline->Description);
amount->setText(QString::number(deliveryorderfreeline->Amount));
price->setText(QString::number(deliveryorderfreeline->Price));
} 
void DeliveryOrderFreelineUI::clear(){ 
delete this->deliveryorderfreeline;
description->setText("");
amount->setText("");
price->setText("");
this->deliveryorderfreeline = new DeliveryOrderFreeline();
} 
void DeliveryOrderFreelineUI::selectDeliveryOrderFreeline(){ 
if(DeliveryOrderFreeline::GetStringList().contains(QString::number(this->deliveryorderfreeline->DeliveryOrderID)))
{
DeliveryOrderFreeline* con = DeliveryOrderFreeline::Get(QString::number(this->deliveryorderfreeline->DeliveryOrderID));
if(this->deliveryorderfreeline->DeliveryOrderFreelineID != con->DeliveryOrderFreelineID){
fill(con);
}
}
else if(deliveryorderfreeline->DeliveryOrderFreelineID != 0)
clear();
}
bool DeliveryOrderFreelineUI::save(){ 
bool errors = false;
QString errorString =  "";
if(!deliveryorder->isHidden()) 
deliveryorderfreeline->DeliveryOrderID = deliveryorder->getKey();
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
deliveryorderfreeline->Description = description->text().trimmed();
}
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
deliveryorderfreeline->Amount = amount->text().trimmed().toDouble();
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
deliveryorderfreeline->Price = price->text().trimmed().toDouble();
}
if(!errors) {
deliveryorderfreeline->save();
if(!errors){
DeliveryOrderFreelineIndexUI::ShowUI();
return true;}
else return false;
}
else{ QMessageBox::warning(this, QObject::tr("DeliveryOrderFreeline"),errorString.trimmed());
return false; 
 }
}
void DeliveryOrderFreelineUI::cancel(){ 
DeliveryOrderFreelineIndexUI::ShowUI();
}
bool DeliveryOrderFreelineUI::updateModel(){ 
bool errors = false;
QString errorString =  "";
if(deliveryorderfreeline->DeliveryOrderID == 0) 
deliveryorderfreeline->DeliveryOrderID = deliveryorder->getKey();
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
deliveryorderfreeline->Description = description->text().trimmed();
}
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
deliveryorderfreeline->Amount = amount->text().trimmed().toDouble();
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
deliveryorderfreeline->Price = price->text().trimmed().toDouble();
}
if(!errors){
	return true;
}
else{ if(!errorString.trimmed().isEmpty()) QMessageBox::warning(this, QObject::tr("DeliveryOrderFreeline"),errorString.trimmed());
return false; 
 }
}
