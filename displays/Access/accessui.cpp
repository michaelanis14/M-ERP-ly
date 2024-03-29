/**************************************************************************
**   File: accessui.cpp
**   Created on: Thu Dec 18 12:57:59 EET 2014
**   Author: Michael Bishara
**   Copyright: SphinxSolutions.
**************************************************************************/

#include "accessui.h"
#include "../Login/loginui.h"
#include "../MainWindow.h"

AccessUI::AccessUI(QWidget *parent) :ERPDisplay(parent)
{

access = new Access();
flowLayout = new FlowLayout(formPanel);
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
title = new QLineEdit();
block0Layout->addRow(QObject::tr("Title"),title);
admin = new QCheckBox();
block0Layout->addRow(QObject::tr("Admin"),admin);
deliveryorderserial = new QCheckBox();
block0Layout->addRow(QObject::tr("Delivery Order Serial"),deliveryorderserial);
deliveryorder = new QCheckBox();
block0Layout->addRow(QObject::tr("Delivery Order"),deliveryorder);
company = new QCheckBox();
block0Layout->addRow(QObject::tr("Company"),company);
tax = new QCheckBox();
block0Layout->addRow(QObject::tr("Tax"),tax);
contact = new QCheckBox();
block0Layout->addRow(QObject::tr("Contact"),contact);
contacttelephone = new QCheckBox();
block0Layout->addRow(QObject::tr("Contact Telephone"),contacttelephone);
contactemail = new QCheckBox();
block0Layout->addRow(QObject::tr("Contact Email"),contactemail);
bankaccount = new QCheckBox();
block0Layout->addRow(QObject::tr("Bank Account"),bankaccount);
contactclass = new QCheckBox();
block0Layout->addRow(QObject::tr("Contact Class"),contactclass);
contacttype = new QCheckBox();
block0Layout->addRow(QObject::tr("Contact Type"),contacttype);
country = new QCheckBox();
block0Layout->addRow(QObject::tr("Country"),country);
currency = new QCheckBox();
block0Layout->addRow(QObject::tr("Currency"),currency);
contactstatus = new QCheckBox();
block0Layout->addRow(QObject::tr("Contact Status"),contactstatus);
fieldtype = new QCheckBox();
block0Layout->addRow(QObject::tr("Field Type"),fieldtype);
contactfield = new QCheckBox();
block0Layout->addRow(QObject::tr("Contact Field"),contactfield);
contactfielddata = new QCheckBox();
block0Layout->addRow(QObject::tr("Contact Field Data"),contactfielddata);
contactpersonfield = new QCheckBox();
block0Layout->addRow(QObject::tr("Contact Person Field"),contactpersonfield);
contactpersonfielddata = new QCheckBox();
block0Layout->addRow(QObject::tr("Contact Person Field Data"),contactpersonfielddata);
contactperson = new QCheckBox();
block0Layout->addRow(QObject::tr("Contact Person"),contactperson);
contactpersontelephone = new QCheckBox();
block0Layout->addRow(QObject::tr("Contact Person Telephone"),contactpersontelephone);
contactpersonemail = new QCheckBox();
block0Layout->addRow(QObject::tr("Contact Person Email"),contactpersonemail);
projectstatus = new QCheckBox();
block0Layout->addRow(QObject::tr("Project Status"),projectstatus);
project = new QCheckBox();
block0Layout->addRow(QObject::tr("Project"),project);
projectfile = new QCheckBox();
block0Layout->addRow(QObject::tr("Project File"),projectfile);
projectcontactperson = new QCheckBox();
block0Layout->addRow(QObject::tr("Project Contact Person"),projectcontactperson);
projectservice = new QCheckBox();
block0Layout->addRow(QObject::tr("Project Service"),projectservice);
projectsales = new QCheckBox();
block0Layout->addRow(QObject::tr("Project Sales"),projectsales);
unit = new QCheckBox();
block0Layout->addRow(QObject::tr("Unit"),unit);
productcategory = new QCheckBox();
block0Layout->addRow(QObject::tr("Product Category"),productcategory);
productimage = new QCheckBox();
block0Layout->addRow(QObject::tr("Product Image"),productimage);
product = new QCheckBox();
block0Layout->addRow(QObject::tr("Product"),product);
productfield = new QCheckBox();
block0Layout->addRow(QObject::tr("Product Field"),productfield);
productfielddata = new QCheckBox();
block0Layout->addRow(QObject::tr("Product Field Data"),productfielddata);
service = new QCheckBox();
block0Layout->addRow(QObject::tr("Service"),service);
store = new QCheckBox();
block0Layout->addRow(QObject::tr("Store"),store);
purchasestatus = new QCheckBox();
block0Layout->addRow(QObject::tr("Purchase Status"),purchasestatus);
purchaseserial = new QCheckBox();
block0Layout->addRow(QObject::tr("Purchase Serial"),purchaseserial);
purchase = new QCheckBox();
block0Layout->addRow(QObject::tr("Purchase"),purchase);
purchasestoreproduct = new QCheckBox();
block0Layout->addRow(QObject::tr("Purchase Store Product"),purchasestoreproduct);
purchasefreeline = new QCheckBox();
block0Layout->addRow(QObject::tr("Purchase Free Line"),purchasefreeline);
returnpurchase = new QCheckBox();
block0Layout->addRow(QObject::tr("Return Purchase"),returnpurchase);
returnpurchasestoreproduct = new QCheckBox();
block0Layout->addRow(QObject::tr("Return Purchase Store Product"),returnpurchasestoreproduct);
returnpurchasefreeline = new QCheckBox();
block0Layout->addRow(QObject::tr("Return Purchase Free Line"),returnpurchasefreeline);
deliveryorderstatus = new QCheckBox();
block0Layout->addRow(QObject::tr("Delivery Order Status"),deliveryorderstatus);
deliveryorderstoreproduct = new QCheckBox();
block0Layout->addRow(QObject::tr("Delivery Order Store Product"),deliveryorderstoreproduct);
deliveryorderservice = new QCheckBox();
block0Layout->addRow(QObject::tr("Delivery Order Service"),deliveryorderservice);
deliveryorderfreeline = new QCheckBox();
block0Layout->addRow(QObject::tr("Delivery Order Freeline"),deliveryorderfreeline);
returndeliveryorder = new QCheckBox();
block0Layout->addRow(QObject::tr("Return Delivery Order"),returndeliveryorder);
returndeliveryorderstoreproduct = new QCheckBox();
block0Layout->addRow(QObject::tr("Return Delivery Order Store Product"),returndeliveryorderstoreproduct);
returndeliveryorderservice = new QCheckBox();
block0Layout->addRow(QObject::tr("Return Delivery Order Service"),returndeliveryorderservice);
returndeliveryorderfreeline = new QCheckBox();
block0Layout->addRow(QObject::tr("Return Delivery Order Freeline"),returndeliveryorderfreeline);
invoiceperiod = new QCheckBox();
block0Layout->addRow(QObject::tr("Invoice Period"),invoiceperiod);
invoiceyear = new QCheckBox();
block0Layout->addRow(QObject::tr("Invoice Year"),invoiceyear);
invoicestate = new QCheckBox();
block0Layout->addRow(QObject::tr("Invoice State"),invoicestate);
invoiceserial = new QCheckBox();
block0Layout->addRow(QObject::tr("Invoice Serial"),invoiceserial);
invoice = new QCheckBox();
block0Layout->addRow(QObject::tr("Invoice"),invoice);
invoicestatedate = new QCheckBox();
block0Layout->addRow(QObject::tr("Invoice State Date"),invoicestatedate);
invoicefreeline = new QCheckBox();
block0Layout->addRow(QObject::tr("Invoice Freeline"),invoicefreeline);
paymenttype = new QCheckBox();
block0Layout->addRow(QObject::tr("Payment Type"),paymenttype);
payment = new QCheckBox();
block0Layout->addRow(QObject::tr("Payment"),payment);
task = new QCheckBox();
block0Layout->addRow(QObject::tr("Task"),task);
language = new QCheckBox();
block0Layout->addRow(QObject::tr("Language"),language);
timebooking = new QCheckBox();
block0Layout->addRow(QObject::tr("Time Booking"),timebooking);
login = new QCheckBox();
block0Layout->addRow(QObject::tr("Login"),login);
hashkey = new QLineEdit();
block0Layout->addRow(QObject::tr("hashKey"),hashkey);
user = new ERPComboBox();
user->addItems(User::GetPairList());
block0Layout->addRow(QObject::tr("User"),user);
flowLayout->addWidget(block0Layout);

}
ERPDisplay* AccessUI::p_instance = 0;
void AccessUI::ShowUI() { 
 if(ErpModel::GetInstance()->LoggedUser->UserID == 0) 
 LoginUI::ShowUI(); 
 else if(ErpModel::GetInstance()->UserAccessList.length() > 0){ 
 if( !ErpModel::GetInstance()->UserAccessList.at(0)->Admin) 
 QMessageBox::warning(0, QObject::tr("Access Permission"),QObject::tr("You do not have Permission")); 
 else{	if (p_instance != 0) 
	p_instance->deleteLater(); 
	p_instance = new AccessUI(mainwindow::GetMainDisplay()); 
  mainwindow::ShowDisplay(p_instance); 
} 
 }else	QMessageBox::warning(0, QObject::tr("Access Permission"),QObject::tr("You do not have a Permission List")); }
AccessUI*AccessUI::GetUI(){ 
 	if (p_instance == 0) { 
		p_instance = new ERPDisplay(mainwindow::GetMainDisplay()); 
	} 
	return (AccessUI*) p_instance; 
}
void AccessUI::fill(Access* access){ 
clear();
this->access = access;
title->setText(access->Title);
admin->setChecked(access->Admin);
deliveryorderserial->setChecked(access->DeliveryOrderSerial);
deliveryorder->setChecked(access->DeliveryOrder);
company->setChecked(access->Company);
tax->setChecked(access->Tax);
contact->setChecked(access->Contact);
contacttelephone->setChecked(access->ContactTelephone);
contactemail->setChecked(access->ContactEmail);
bankaccount->setChecked(access->BankAccount);
contactclass->setChecked(access->ContactClass);
contacttype->setChecked(access->ContactType);
country->setChecked(access->Country);
currency->setChecked(access->Currency);
contactstatus->setChecked(access->ContactStatus);
fieldtype->setChecked(access->FieldType);
contactfield->setChecked(access->ContactField);
contactfielddata->setChecked(access->ContactFieldData);
contactpersonfield->setChecked(access->ContactPersonField);
contactpersonfielddata->setChecked(access->ContactPersonFieldData);
contactperson->setChecked(access->ContactPerson);
contactpersontelephone->setChecked(access->ContactPersonTelephone);
contactpersonemail->setChecked(access->ContactPersonEmail);
projectstatus->setChecked(access->ProjectStatus);
project->setChecked(access->Project);
projectfile->setChecked(access->ProjectFile);
projectcontactperson->setChecked(access->ProjectContactPerson);
projectservice->setChecked(access->ProjectService);
projectsales->setChecked(access->ProjectSales);
unit->setChecked(access->Unit);
productcategory->setChecked(access->ProductCategory);
productimage->setChecked(access->ProductImage);
product->setChecked(access->Product);
productfield->setChecked(access->ProductField);
productfielddata->setChecked(access->ProductFieldData);
service->setChecked(access->Service);
store->setChecked(access->Store);
purchasestatus->setChecked(access->PurchaseStatus);
purchaseserial->setChecked(access->PurchaseSerial);
purchase->setChecked(access->Purchase);
purchasestoreproduct->setChecked(access->PurchaseStoreProduct);
purchasefreeline->setChecked(access->PurchaseFreeLine);
returnpurchase->setChecked(access->ReturnPurchase);
returnpurchasestoreproduct->setChecked(access->ReturnPurchaseStoreProduct);
returnpurchasefreeline->setChecked(access->ReturnPurchaseFreeLine);
deliveryorderstatus->setChecked(access->DeliveryOrderStatus);
deliveryorderstoreproduct->setChecked(access->DeliveryOrderStoreProduct);
deliveryorderservice->setChecked(access->DeliveryOrderService);
deliveryorderfreeline->setChecked(access->DeliveryOrderFreeline);
returndeliveryorder->setChecked(access->ReturnDeliveryOrder);
returndeliveryorderstoreproduct->setChecked(access->ReturnDeliveryOrderStoreProduct);
returndeliveryorderservice->setChecked(access->ReturnDeliveryOrderService);
returndeliveryorderfreeline->setChecked(access->ReturnDeliveryOrderFreeline);
invoiceperiod->setChecked(access->InvoicePeriod);
invoiceyear->setChecked(access->InvoiceYear);
invoicestate->setChecked(access->InvoiceState);
invoiceserial->setChecked(access->InvoiceSerial);
invoice->setChecked(access->Invoice);
invoicestatedate->setChecked(access->InvoiceStateDate);
invoicefreeline->setChecked(access->InvoiceFreeline);
paymenttype->setChecked(access->PaymentType);
payment->setChecked(access->Payment);
task->setChecked(access->Task);
language->setChecked(access->Language);
timebooking->setChecked(access->TimeBooking);
login->setChecked(access->Login);
hashkey->setText(access->hashKey);
user->setIndexByKey(access->UserID);
} 
void AccessUI::clear(){ 
delete this->access;
title->setText("");
admin->setChecked(false);
deliveryorderserial->setChecked(false);
deliveryorder->setChecked(false);
company->setChecked(false);
tax->setChecked(false);
contact->setChecked(false);
contacttelephone->setChecked(false);
contactemail->setChecked(false);
bankaccount->setChecked(false);
contactclass->setChecked(false);
contacttype->setChecked(false);
country->setChecked(false);
currency->setChecked(false);
contactstatus->setChecked(false);
fieldtype->setChecked(false);
contactfield->setChecked(false);
contactfielddata->setChecked(false);
contactpersonfield->setChecked(false);
contactpersonfielddata->setChecked(false);
contactperson->setChecked(false);
contactpersontelephone->setChecked(false);
contactpersonemail->setChecked(false);
projectstatus->setChecked(false);
project->setChecked(false);
projectfile->setChecked(false);
projectcontactperson->setChecked(false);
projectservice->setChecked(false);
projectsales->setChecked(false);
unit->setChecked(false);
productcategory->setChecked(false);
productimage->setChecked(false);
product->setChecked(false);
productfield->setChecked(false);
productfielddata->setChecked(false);
service->setChecked(false);
store->setChecked(false);
purchasestatus->setChecked(false);
purchaseserial->setChecked(false);
purchase->setChecked(false);
purchasestoreproduct->setChecked(false);
purchasefreeline->setChecked(false);
returnpurchase->setChecked(false);
returnpurchasestoreproduct->setChecked(false);
returnpurchasefreeline->setChecked(false);
deliveryorderstatus->setChecked(false);
deliveryorderstoreproduct->setChecked(false);
deliveryorderservice->setChecked(false);
deliveryorderfreeline->setChecked(false);
returndeliveryorder->setChecked(false);
returndeliveryorderstoreproduct->setChecked(false);
returndeliveryorderservice->setChecked(false);
returndeliveryorderfreeline->setChecked(false);
invoiceperiod->setChecked(false);
invoiceyear->setChecked(false);
invoicestate->setChecked(false);
invoiceserial->setChecked(false);
invoice->setChecked(false);
invoicestatedate->setChecked(false);
invoicefreeline->setChecked(false);
paymenttype->setChecked(false);
payment->setChecked(false);
task->setChecked(false);
language->setChecked(false);
timebooking->setChecked(false);
login->setChecked(false);
hashkey->setText("");
this->access = new Access();
} 
void AccessUI::selectAccess(){ 
if(Access::GetStringList().contains(this->access->Title))
{
Access* con = Access::Get(this->access->Title);
if(this->access->AccessID != con->AccessID){
fill(con);
}
}
else if(access->AccessID != 0)
clear();
}
bool AccessUI::save(){ 
bool errors = false;
QString errorString =  "";
if(title->text().trimmed().isEmpty()){
errors = true;
errorString += QObject::tr("Title Can't be Empty! \n");
title->setObjectName("error");
title->style()->unpolish(title);
title->style()->polish(title);
title->update();
}
else { 
title->setObjectName("title");
title->style()->unpolish(title);
title->style()->polish(title);
title->update();
access->Title = title->text().trimmed();
}
access->Admin = admin->text().trimmed().toInt();
access->DeliveryOrderSerial = deliveryorderserial->text().trimmed().toInt();
access->DeliveryOrder = deliveryorder->text().trimmed().toInt();
access->Company = company->text().trimmed().toInt();
access->Tax = tax->text().trimmed().toInt();
access->Contact = contact->text().trimmed().toInt();
access->ContactTelephone = contacttelephone->text().trimmed().toInt();
access->ContactEmail = contactemail->text().trimmed().toInt();
access->BankAccount = bankaccount->text().trimmed().toInt();
access->ContactClass = contactclass->text().trimmed().toInt();
access->ContactType = contacttype->text().trimmed().toInt();
access->Country = country->text().trimmed().toInt();
access->Currency = currency->text().trimmed().toInt();
access->ContactStatus = contactstatus->text().trimmed().toInt();
access->FieldType = fieldtype->text().trimmed().toInt();
access->ContactField = contactfield->text().trimmed().toInt();
access->ContactFieldData = contactfielddata->text().trimmed().toInt();
access->ContactPersonField = contactpersonfield->text().trimmed().toInt();
access->ContactPersonFieldData = contactpersonfielddata->text().trimmed().toInt();
access->ContactPerson = contactperson->text().trimmed().toInt();
access->ContactPersonTelephone = contactpersontelephone->text().trimmed().toInt();
access->ContactPersonEmail = contactpersonemail->text().trimmed().toInt();
access->ProjectStatus = projectstatus->text().trimmed().toInt();
access->Project = project->text().trimmed().toInt();
access->ProjectFile = projectfile->text().trimmed().toInt();
access->ProjectContactPerson = projectcontactperson->text().trimmed().toInt();
access->ProjectService = projectservice->text().trimmed().toInt();
access->ProjectSales = projectsales->text().trimmed().toInt();
access->Unit = unit->text().trimmed().toInt();
access->ProductCategory = productcategory->text().trimmed().toInt();
access->ProductImage = productimage->text().trimmed().toInt();
access->Product = product->text().trimmed().toInt();
access->ProductField = productfield->text().trimmed().toInt();
access->ProductFieldData = productfielddata->text().trimmed().toInt();
access->Service = service->text().trimmed().toInt();
access->Store = store->text().trimmed().toInt();
access->PurchaseStatus = purchasestatus->text().trimmed().toInt();
access->PurchaseSerial = purchaseserial->text().trimmed().toInt();
access->Purchase = purchase->text().trimmed().toInt();
access->PurchaseStoreProduct = purchasestoreproduct->text().trimmed().toInt();
access->PurchaseFreeLine = purchasefreeline->text().trimmed().toInt();
access->ReturnPurchase = returnpurchase->text().trimmed().toInt();
access->ReturnPurchaseStoreProduct = returnpurchasestoreproduct->text().trimmed().toInt();
access->ReturnPurchaseFreeLine = returnpurchasefreeline->text().trimmed().toInt();
access->DeliveryOrderStatus = deliveryorderstatus->text().trimmed().toInt();
access->DeliveryOrderStoreProduct = deliveryorderstoreproduct->text().trimmed().toInt();
access->DeliveryOrderService = deliveryorderservice->text().trimmed().toInt();
access->DeliveryOrderFreeline = deliveryorderfreeline->text().trimmed().toInt();
access->ReturnDeliveryOrder = returndeliveryorder->text().trimmed().toInt();
access->ReturnDeliveryOrderStoreProduct = returndeliveryorderstoreproduct->text().trimmed().toInt();
access->ReturnDeliveryOrderService = returndeliveryorderservice->text().trimmed().toInt();
access->ReturnDeliveryOrderFreeline = returndeliveryorderfreeline->text().trimmed().toInt();
access->InvoicePeriod = invoiceperiod->text().trimmed().toInt();
access->InvoiceYear = invoiceyear->text().trimmed().toInt();
access->InvoiceState = invoicestate->text().trimmed().toInt();
access->InvoiceSerial = invoiceserial->text().trimmed().toInt();
access->Invoice = invoice->text().trimmed().toInt();
access->InvoiceStateDate = invoicestatedate->text().trimmed().toInt();
access->InvoiceFreeline = invoicefreeline->text().trimmed().toInt();
access->PaymentType = paymenttype->text().trimmed().toInt();
access->Payment = payment->text().trimmed().toInt();
access->Task = task->text().trimmed().toInt();
access->Language = language->text().trimmed().toInt();
access->TimeBooking = timebooking->text().trimmed().toInt();
access->Login = login->text().trimmed().toInt();
if(hashkey->text().trimmed().isEmpty()){
errors = true;
errorString += QObject::tr("hashKey Can't be Empty! \n");
hashkey->setObjectName("error");
hashkey->style()->unpolish(hashkey);
hashkey->style()->polish(hashkey);
hashkey->update();
}
else { 
hashkey->setObjectName("hashkey");
hashkey->style()->unpolish(hashkey);
hashkey->style()->polish(hashkey);
hashkey->update();
access->hashKey = hashkey->text().trimmed();
}
if(!user->isHidden()) 
access->UserID = user->getKey();
if(!errors) {
access->save();
if(!errors){
AccessIndexUI::ShowUI();
return true;}
else return false;
}
else{ QMessageBox::warning(this, QObject::tr("Access"),errorString.trimmed());
return false; 
 }
}
void AccessUI::cancel(){ 
AccessIndexUI::ShowUI();
}
bool AccessUI::updateModel(){ 
bool errors = false;
QString errorString =  "";
if(title->text().trimmed().isEmpty()){
errors = true;
errorString += QObject::tr("Title Can't be Empty! \n");
title->setObjectName("error");
title->style()->unpolish(title);
title->style()->polish(title);
title->update();
}
else { 
title->setObjectName("title");
title->style()->unpolish(title);
title->style()->polish(title);
title->update();
access->Title = title->text().trimmed();
}
access->Admin = admin->text().trimmed().toInt();
access->DeliveryOrderSerial = deliveryorderserial->text().trimmed().toInt();
access->DeliveryOrder = deliveryorder->text().trimmed().toInt();
access->Company = company->text().trimmed().toInt();
access->Tax = tax->text().trimmed().toInt();
access->Contact = contact->text().trimmed().toInt();
access->ContactTelephone = contacttelephone->text().trimmed().toInt();
access->ContactEmail = contactemail->text().trimmed().toInt();
access->BankAccount = bankaccount->text().trimmed().toInt();
access->ContactClass = contactclass->text().trimmed().toInt();
access->ContactType = contacttype->text().trimmed().toInt();
access->Country = country->text().trimmed().toInt();
access->Currency = currency->text().trimmed().toInt();
access->ContactStatus = contactstatus->text().trimmed().toInt();
access->FieldType = fieldtype->text().trimmed().toInt();
access->ContactField = contactfield->text().trimmed().toInt();
access->ContactFieldData = contactfielddata->text().trimmed().toInt();
access->ContactPersonField = contactpersonfield->text().trimmed().toInt();
access->ContactPersonFieldData = contactpersonfielddata->text().trimmed().toInt();
access->ContactPerson = contactperson->text().trimmed().toInt();
access->ContactPersonTelephone = contactpersontelephone->text().trimmed().toInt();
access->ContactPersonEmail = contactpersonemail->text().trimmed().toInt();
access->ProjectStatus = projectstatus->text().trimmed().toInt();
access->Project = project->text().trimmed().toInt();
access->ProjectFile = projectfile->text().trimmed().toInt();
access->ProjectContactPerson = projectcontactperson->text().trimmed().toInt();
access->ProjectService = projectservice->text().trimmed().toInt();
access->ProjectSales = projectsales->text().trimmed().toInt();
access->Unit = unit->text().trimmed().toInt();
access->ProductCategory = productcategory->text().trimmed().toInt();
access->ProductImage = productimage->text().trimmed().toInt();
access->Product = product->text().trimmed().toInt();
access->ProductField = productfield->text().trimmed().toInt();
access->ProductFieldData = productfielddata->text().trimmed().toInt();
access->Service = service->text().trimmed().toInt();
access->Store = store->text().trimmed().toInt();
access->PurchaseStatus = purchasestatus->text().trimmed().toInt();
access->PurchaseSerial = purchaseserial->text().trimmed().toInt();
access->Purchase = purchase->text().trimmed().toInt();
access->PurchaseStoreProduct = purchasestoreproduct->text().trimmed().toInt();
access->PurchaseFreeLine = purchasefreeline->text().trimmed().toInt();
access->ReturnPurchase = returnpurchase->text().trimmed().toInt();
access->ReturnPurchaseStoreProduct = returnpurchasestoreproduct->text().trimmed().toInt();
access->ReturnPurchaseFreeLine = returnpurchasefreeline->text().trimmed().toInt();
access->DeliveryOrderStatus = deliveryorderstatus->text().trimmed().toInt();
access->DeliveryOrderStoreProduct = deliveryorderstoreproduct->text().trimmed().toInt();
access->DeliveryOrderService = deliveryorderservice->text().trimmed().toInt();
access->DeliveryOrderFreeline = deliveryorderfreeline->text().trimmed().toInt();
access->ReturnDeliveryOrder = returndeliveryorder->text().trimmed().toInt();
access->ReturnDeliveryOrderStoreProduct = returndeliveryorderstoreproduct->text().trimmed().toInt();
access->ReturnDeliveryOrderService = returndeliveryorderservice->text().trimmed().toInt();
access->ReturnDeliveryOrderFreeline = returndeliveryorderfreeline->text().trimmed().toInt();
access->InvoicePeriod = invoiceperiod->text().trimmed().toInt();
access->InvoiceYear = invoiceyear->text().trimmed().toInt();
access->InvoiceState = invoicestate->text().trimmed().toInt();
access->InvoiceSerial = invoiceserial->text().trimmed().toInt();
access->Invoice = invoice->text().trimmed().toInt();
access->InvoiceStateDate = invoicestatedate->text().trimmed().toInt();
access->InvoiceFreeline = invoicefreeline->text().trimmed().toInt();
access->PaymentType = paymenttype->text().trimmed().toInt();
access->Payment = payment->text().trimmed().toInt();
access->Task = task->text().trimmed().toInt();
access->Language = language->text().trimmed().toInt();
access->TimeBooking = timebooking->text().trimmed().toInt();
access->Login = login->text().trimmed().toInt();
if(hashkey->text().trimmed().isEmpty()){
errors = true;
errorString += QObject::tr("hashKey Can't be Empty! \n");
hashkey->setObjectName("error");
hashkey->style()->unpolish(hashkey);
hashkey->style()->polish(hashkey);
hashkey->update();
}
else { 
hashkey->setObjectName("hashkey");
hashkey->style()->unpolish(hashkey);
hashkey->style()->polish(hashkey);
hashkey->update();
access->hashKey = hashkey->text().trimmed();
}
if(access->UserID == 0) 
access->UserID = user->getKey();
if(!errors){
	return true;
}
else{ if(!errorString.trimmed().isEmpty()) QMessageBox::warning(this, QObject::tr("Access"),errorString.trimmed());
return false; 
 }
}
