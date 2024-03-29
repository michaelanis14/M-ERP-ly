/**************************************************************************
**   File: productcategoryui.cpp
**   Created on: Thu Dec 18 12:57:58 EET 2014
**   Author: Michael Bishara
**   Copyright: SphinxSolutions.
**************************************************************************/

#include "productcategoryui.h"
#include "../Login/loginui.h"
#include "../MainWindow.h"

ProductCategoryUI::ProductCategoryUI(QWidget *parent) :ERPDisplay(parent)
{

productcategory = new ProductCategory();
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
ERPDisplay* ProductCategoryUI::p_instance = 0;
void ProductCategoryUI::ShowUI() { 
 if(ErpModel::GetInstance()->LoggedUser->UserID == 0) 
 LoginUI::ShowUI(); 
 else if(ErpModel::GetInstance()->UserAccessList.length() > 0){ 
 if( !ErpModel::GetInstance()->UserAccessList.at(0)->ProductCategory) 
 QMessageBox::warning(0, QObject::tr("Access Permission"),QObject::tr("You do not have Permission")); 
 else{	if (p_instance != 0) 
	p_instance->deleteLater(); 
	p_instance = new ProductCategoryUI(mainwindow::GetMainDisplay()); 
  mainwindow::ShowDisplay(p_instance); 
} 
 }else	QMessageBox::warning(0, QObject::tr("Access Permission"),QObject::tr("You do not have a Permission List")); }
ProductCategoryUI*ProductCategoryUI::GetUI(){ 
 	if (p_instance == 0) { 
		p_instance = new ERPDisplay(mainwindow::GetMainDisplay()); 
	} 
	return (ProductCategoryUI*) p_instance; 
}
void ProductCategoryUI::fill(ProductCategory* productcategory){ 
clear();
this->productcategory = productcategory;
description->setText(productcategory->Description);
} 
void ProductCategoryUI::clear(){ 
delete this->productcategory;
description->setText("");
this->productcategory = new ProductCategory();
} 
void ProductCategoryUI::selectProductCategory(){ 
if(ProductCategory::GetStringList().contains(this->productcategory->Description))
{
ProductCategory* con = ProductCategory::Get(this->productcategory->Description);
if(this->productcategory->ProductCategoryID != con->ProductCategoryID){
fill(con);
}
}
else if(productcategory->ProductCategoryID != 0)
clear();
}
bool ProductCategoryUI::save(){ 
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
productcategory->Description = description->text().trimmed();
}
if(!errors) {
productcategory->save();
if(!errors){
ProductCategoryIndexUI::ShowUI();
return true;}
else return false;
}
else{ QMessageBox::warning(this, QObject::tr("ProductCategory"),errorString.trimmed());
return false; 
 }
}
void ProductCategoryUI::cancel(){ 
ProductCategoryIndexUI::ShowUI();
}
bool ProductCategoryUI::updateModel(){ 
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
productcategory->Description = description->text().trimmed();
}
if(!errors){
	return true;
}
else{ if(!errorString.trimmed().isEmpty()) QMessageBox::warning(this, QObject::tr("ProductCategory"),errorString.trimmed());
return false; 
 }
}
