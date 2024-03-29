/**************************************************************************
**   File: invoicestateui.cpp
**   Created on: Fri Dec 19 21:09:57 EET 2014
**   Author: Michael Bishara
**   Copyright: SphinxSolutions.
**************************************************************************/

#include "invoicestateui.h"
#include "../Login/loginui.h"
#include "../MainWindow.h"

InvoiceStateUI::InvoiceStateUI(QWidget *parent) :ERPDisplay(parent)
{

invoicestate = new InvoiceState();
flowLayout = new FlowLayout(this);
flowLayout->setContentsMargins(0,0,0,0);

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
description = new QLineEdit();
block0Layout->addRow(QObject::tr("Description"),description);
flowLayout->addWidget(block0Layout);

}
ERPDisplay* InvoiceStateUI::p_instance = 0;
void InvoiceStateUI::ShowUI() { 
 if(ErpModel::GetInstance()->LoggedUser->UserID == 0) 
 LoginUI::ShowUI(); 
 else if(ErpModel::GetInstance()->UserAccessList.length() > 0){ 
 if( !ErpModel::GetInstance()->UserAccessList.at(0)->InvoiceState) 
 QMessageBox::warning(0, QObject::tr("Access Permission"),QObject::tr("You do not have Permission")); 
 else{	if (p_instance != 0) 
	p_instance->deleteLater(); 
	p_instance = new InvoiceStateUI(mainwindow::GetMainDisplay()); 
  mainwindow::ShowDisplay(p_instance); 
} 
 }else	QMessageBox::warning(0, QObject::tr("Access Permission"),QObject::tr("You do not have a Permission List")); }
InvoiceStateUI*InvoiceStateUI::GetUI(){ 
 	if (p_instance == 0) { 
		p_instance = new ERPDisplay(mainwindow::GetMainDisplay()); 
	} 
	return (InvoiceStateUI*) p_instance; 
}
void InvoiceStateUI::fill(InvoiceState* invoicestate){ 
clear();
this->invoicestate = invoicestate;
description->setText(invoicestate->Description);
} 
void InvoiceStateUI::clear(){ 
delete this->invoicestate;
description->setText("");
this->invoicestate = new InvoiceState();
} 
void InvoiceStateUI::selectInvoiceState(){ 
if(InvoiceState::GetStringList().contains(this->invoicestate->Description))
{
InvoiceState* con = InvoiceState::Get(this->invoicestate->Description);
if(this->invoicestate->InvoiceStateID != con->InvoiceStateID){
fill(con);
}
}
else if(invoicestate->InvoiceStateID != 0)
clear();
}
bool InvoiceStateUI::save(){ 
bool errors = false;
QString errorString =  "";
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
invoicestate->Description = description->text().trimmed();
}
if(!errors) {
invoicestate->save();
if(!errors){
InvoiceStateIndexUI::ShowUI();
return true;}
else return false;
}
else{ QMessageBox::warning(this, QObject::tr("InvoiceState"),errorString.trimmed());
return false; 
 }
}
void InvoiceStateUI::cancel(){ 
InvoiceStateIndexUI::ShowUI();
}
bool InvoiceStateUI::updateModel(){ 
bool errors = false;
QString errorString =  "";
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
invoicestate->Description = description->text().trimmed();
}
if(!errors){
	return true;
}
else{ if(!errorString.trimmed().isEmpty()) QMessageBox::warning(this, QObject::tr("InvoiceState"),errorString.trimmed());
return false; 
 }
}
