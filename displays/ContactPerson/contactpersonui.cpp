/**************************************************************************
**   File: contactpersonui.cpp
**   Created on: Thu Dec 18 20:39:34 EET 2014
**   Author: Michael Bishara
**   Copyright: SphinxSolutions.
**************************************************************************/

#include "contactpersonui.h"
#include "../Login/loginui.h"
#include "../MainWindow.h"

ContactPersonUI::ContactPersonUI(QWidget *parent) :ERPDisplay(parent)
{

contactperson = new ContactPerson();
flowLayout = new FlowLayout(formPanel);
flowLayout->setContentsMargins(0,0,0,0);

QIntValidator *intValidator = new QIntValidator ( 0, 1000000);
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
contact = new ERPComboBox();
contact->addItems(Contact::GetPairList());
block0Layout->addRow(QObject::tr("Contact"),contact);
name = new QLineEdit();
QStringList* list = new QStringList(ContactPerson::GetStringList());
QCompleter *completer = new QCompleter(*list);
completer->setCaseSensitivity(Qt::CaseInsensitive);
name->setCompleter(completer);
QObject::connect(name, SIGNAL(editingFinished()), this, SLOT(selectContactPerson()));
block0Layout->addRow(QObject::tr("Name"),name);
lastname = new QLineEdit();
block0Layout->addRow(QObject::tr("Last Name"),lastname);
position = new QLineEdit();
block0Layout->addRow(QObject::tr("Position"),position);
birthdate = new QDateEdit(QDate::currentDate());
birthdate->setCalendarPopup(true);
birthdate->setDisplayFormat("ddd dd/MM/yyyy");
block0Layout->addRow(QObject::tr("Birthdate"),birthdate);
number = new QLineEdit();
number->setValidator( intValidator );
block0Layout->addRow(QObject::tr("Number"),number);
flowLayout->addWidget(block0Layout);

block1Layout = new ERPFormBlock;
if(this->flowLayout && this->flowLayout->parent()->objectName() == "formPanel") 
 block1Layout->setMinimumWidth(330);
AddRemoveButtons* addremoveContactPersonTelephoneButtons = new AddRemoveButtons();
block1Layout->addRow("ContactPersonTelephones",addremoveContactPersonTelephoneButtons);
QObject::connect(addremoveContactPersonTelephoneButtons, SIGNAL(addPressed()), this, SLOT(addContactPersonTelephone()));

flowLayout->addWidget(block1Layout);

block2Layout = new ERPFormBlock;
if(this->flowLayout && this->flowLayout->parent()->objectName() == "formPanel") 
 block2Layout->setMinimumWidth(330);
AddRemoveButtons* addremoveContactPersonEmailButtons = new AddRemoveButtons();
block2Layout->addRow("ContactPersonEmails",addremoveContactPersonEmailButtons);
QObject::connect(addremoveContactPersonEmailButtons, SIGNAL(addPressed()), this, SLOT(addContactPersonEmail()));

flowLayout->addWidget(block2Layout);

}
ERPDisplay* ContactPersonUI::p_instance = 0;
void ContactPersonUI::ShowUI() { 
 if(ErpModel::GetInstance()->LoggedUser->UserID == 0) 
 LoginUI::ShowUI(); 
 else if(ErpModel::GetInstance()->UserAccessList.length() > 0){ 
 if( !ErpModel::GetInstance()->UserAccessList.at(0)->ContactPerson) 
 QMessageBox::warning(0, QObject::tr("Access Permission"),QObject::tr("You do not have Permission")); 
 else{	if (p_instance != 0) 
	p_instance->deleteLater(); 
	p_instance = new ContactPersonUI(mainwindow::GetMainDisplay()); 
  mainwindow::ShowDisplay(p_instance); 
} 
 }else	QMessageBox::warning(0, QObject::tr("Access Permission"),QObject::tr("You do not have a Permission List")); }
ContactPersonUI*ContactPersonUI::GetUI(){ 
 	if (p_instance == 0) { 
		p_instance = new ERPDisplay(mainwindow::GetMainDisplay()); 
	} 
	return (ContactPersonUI*) p_instance; 
}
void ContactPersonUI::addContactPersonTelephone(){ 
ContactPersonTelephoneUI* contactpersontelephoneui = new ContactPersonTelephoneUI();
contactpersontelephoneui->block0Layout->hideRow(contactpersontelephoneui->contactperson);
contactpersontelephoneui->controllers->setFixedHeight(0);
ContactPersonTelephones.append(contactpersontelephoneui);
RemovebtnWidgets* rmcontactpersontelephone = new RemovebtnWidgets(0,contactpersontelephoneui);
QObject::connect(rmcontactpersontelephone, SIGNAL(removePressed(QWidget*)), this, SLOT(removeContactPersonTelephone(QWidget*)));
block1Layout->addRow(QObject::tr("ContactPersonTelephone")+QString::number(ContactPersonTelephones.count()),rmcontactpersontelephone);
}
void ContactPersonUI::addContactPersonTelephone(ContactPersonTelephone* contactpersontelephone){ 
ContactPersonTelephoneUI* contactpersontelephoneui = new ContactPersonTelephoneUI();
contactpersontelephoneui->block0Layout->hideRow(contactpersontelephoneui->contactperson);
contactpersontelephoneui->controllers->setFixedHeight(0);
contactpersontelephoneui->fill(contactpersontelephone);
ContactPersonTelephones.append(contactpersontelephoneui);
RemovebtnWidgets* rmcontactpersontelephone = new RemovebtnWidgets(0,contactpersontelephoneui);
QObject::connect(rmcontactpersontelephone, SIGNAL(removePressed(QWidget*)), this, SLOT(removeContactPersonTelephone(QWidget*)));
block1Layout->addRow(QObject::tr("ContactPersonTelephone") +QString::number(ContactPersonTelephones.count()),rmcontactpersontelephone);
}
void ContactPersonUI::removeContactPersonTelephone(QWidget* widget){ 
if(ContactPersonTelephones.count()  > 0){
ContactPersonTelephoneUI* contactpersontelephoneui = (ContactPersonTelephoneUI*) widget;
ContactPersonTelephones.removeOne(contactpersontelephoneui);
RemovebtnWidgets* sender = (RemovebtnWidgets*) this->sender();
block1Layout->removeRow(sender);
}
}
void ContactPersonUI::addContactPersonEmail(){ 
ContactPersonEmailUI* contactpersonemailui = new ContactPersonEmailUI();
contactpersonemailui->block0Layout->hideRow(contactpersonemailui->contactperson);
contactpersonemailui->controllers->setFixedHeight(0);
ContactPersonEmails.append(contactpersonemailui);
RemovebtnWidgets* rmcontactpersonemail = new RemovebtnWidgets(0,contactpersonemailui);
QObject::connect(rmcontactpersonemail, SIGNAL(removePressed(QWidget*)), this, SLOT(removeContactPersonEmail(QWidget*)));
block2Layout->addRow(QObject::tr("ContactPersonEmail")+QString::number(ContactPersonEmails.count()),rmcontactpersonemail);
}
void ContactPersonUI::addContactPersonEmail(ContactPersonEmail* contactpersonemail){ 
ContactPersonEmailUI* contactpersonemailui = new ContactPersonEmailUI();
contactpersonemailui->block0Layout->hideRow(contactpersonemailui->contactperson);
contactpersonemailui->controllers->setFixedHeight(0);
contactpersonemailui->fill(contactpersonemail);
ContactPersonEmails.append(contactpersonemailui);
RemovebtnWidgets* rmcontactpersonemail = new RemovebtnWidgets(0,contactpersonemailui);
QObject::connect(rmcontactpersonemail, SIGNAL(removePressed(QWidget*)), this, SLOT(removeContactPersonEmail(QWidget*)));
block2Layout->addRow(QObject::tr("ContactPersonEmail") +QString::number(ContactPersonEmails.count()),rmcontactpersonemail);
}
void ContactPersonUI::removeContactPersonEmail(QWidget* widget){ 
if(ContactPersonEmails.count()  > 0){
ContactPersonEmailUI* contactpersonemailui = (ContactPersonEmailUI*) widget;
ContactPersonEmails.removeOne(contactpersonemailui);
RemovebtnWidgets* sender = (RemovebtnWidgets*) this->sender();
block2Layout->removeRow(sender);
}
}
void ContactPersonUI::fill(ContactPerson* contactperson){ 
clear();
this->contactperson = contactperson;
contact->setIndexByKey(contactperson->ContactID);
name->setText(contactperson->Name);
lastname->setText(contactperson->LastName);
position->setText(contactperson->Position);
birthdate->setDate(contactperson->Birthdate);
number->setText(QString::number(contactperson->Number));
foreach(ContactPersonTelephone* contactpersontelephone, contactperson->contactpersontelephones) {
addContactPersonTelephone(contactpersontelephone);
}
foreach(ContactPersonEmail* contactpersonemail, contactperson->contactpersonemails) {
addContactPersonEmail(contactpersonemail);
}
} 
void ContactPersonUI::clear(){ 
delete this->contactperson;
this->ContactPersonTelephones.clear();
this->ContactPersonEmails.clear();
lastname->setText("");
position->setText("");
birthdate->setDate(QDate::currentDate());
number->setText("");
QList<RemovebtnWidgets *> RWidgets = this->findChildren<RemovebtnWidgets *>();
foreach(RemovebtnWidgets * child, RWidgets)
{
if(child->parent()->parent()->parent() != 0)
((ERPFormBlock*)child->parent()->parent())->removeRow(child);
}
this->contactperson = new ContactPerson();
} 
void ContactPersonUI::selectContactPerson(){ 
if(ContactPerson::GetStringList().contains(QString::number(this->contactperson->ContactID)))
{
ContactPerson* con = ContactPerson::Get(QString::number(this->contactperson->ContactID));
if(this->contactperson->ContactPersonID != con->ContactPersonID){
fill(con);
}
}
else if(contactperson->ContactPersonID != 0)
clear();
}
bool ContactPersonUI::save(){ 
bool errors = false;
QString errorString =  "";
if(!contact->isHidden()) 
contactperson->ContactID = contact->getKey();
if(name->text().trimmed().isEmpty()){
errors = true;
errorString += QObject::tr("Name Can't be Empty! \n");
name->setObjectName("error");
name->style()->unpolish(name);
name->style()->polish(name);
name->update();
}
else { 
name->setObjectName("name");
name->style()->unpolish(name);
name->style()->polish(name);
name->update();
contactperson->Name = name->text().trimmed();
}
if(lastname->text().trimmed().isEmpty()){
errors = true;
errorString += QObject::tr("Last Name Can't be Empty! \n");
lastname->setObjectName("error");
lastname->style()->unpolish(lastname);
lastname->style()->polish(lastname);
lastname->update();
}
else { 
lastname->setObjectName("lastname");
lastname->style()->unpolish(lastname);
lastname->style()->polish(lastname);
lastname->update();
contactperson->LastName = lastname->text().trimmed();
}
if(position->text().trimmed().isEmpty()){
errors = true;
errorString += QObject::tr("Position Can't be Empty! \n");
position->setObjectName("error");
position->style()->unpolish(position);
position->style()->polish(position);
position->update();
}
else { 
position->setObjectName("position");
position->style()->unpolish(position);
position->style()->polish(position);
position->update();
contactperson->Position = position->text().trimmed();
}
if(birthdate->text().trimmed().isEmpty()){
errors = true;
errorString += QObject::tr("Birthdate Can't be Empty! \n");
birthdate->setObjectName("error");
birthdate->style()->unpolish(birthdate);
birthdate->style()->polish(birthdate);
birthdate->update();
}
else { 
birthdate->setObjectName("birthdate");
birthdate->style()->unpolish(birthdate);
birthdate->style()->polish(birthdate);
birthdate->update();
contactperson->Birthdate.setDate(birthdate->date().year(),birthdate->date().month(),birthdate->date().day());
}
if(number->text().trimmed().isEmpty()){
errors = true;
errorString += QObject::tr("Number Can't be Empty! \n");
number->setObjectName("error");
number->style()->unpolish(number);
number->style()->polish(number);
number->update();
}
else { 
number->setObjectName("number");
number->style()->unpolish(number);
number->style()->polish(number);
number->update();
contactperson->Number = number->text().trimmed().toInt();
}
for(int j = 0; j < ContactPersonTelephones.length(); j++){
ContactPersonTelephones.at(j)->description->setObjectName("description");
ContactPersonTelephones.at(j)->description->style()->unpolish(ContactPersonTelephones.at(j)->description);
ContactPersonTelephones.at(j)->description->style()->polish(ContactPersonTelephones.at(j)->description);
ContactPersonTelephones.at(j)->description->update();
for(int w = 0; w < ContactPersonTelephones.length(); w++){
if(ContactPersonTelephones.at(j) != ContactPersonTelephones.at(w))
if(ContactPersonTelephones.at(j)->description->text() == ContactPersonTelephones.at(w)->description->text()){
errors = true; 
 errorString += QObject::tr("ContactPersonTelephone has the same description \n");
ContactPersonTelephones.at(j)->description->setObjectName("error");
ContactPersonTelephones.at(j)->description->style()->unpolish(ContactPersonTelephones.at(j)->description);
ContactPersonTelephones.at(j)->description->style()->polish(ContactPersonTelephones.at(j)->description);
ContactPersonTelephones.at(j)->description->update();
}}}
for(int j = 0; j < ContactPersonEmails.length(); j++){
ContactPersonEmails.at(j)->description->setObjectName("description");
ContactPersonEmails.at(j)->description->style()->unpolish(ContactPersonEmails.at(j)->description);
ContactPersonEmails.at(j)->description->style()->polish(ContactPersonEmails.at(j)->description);
ContactPersonEmails.at(j)->description->update();
for(int w = 0; w < ContactPersonEmails.length(); w++){
if(ContactPersonEmails.at(j) != ContactPersonEmails.at(w))
if(ContactPersonEmails.at(j)->description->text() == ContactPersonEmails.at(w)->description->text()){
errors = true; 
 errorString += QObject::tr("ContactPersonEmail has the same description \n");
ContactPersonEmails.at(j)->description->setObjectName("error");
ContactPersonEmails.at(j)->description->style()->unpolish(ContactPersonEmails.at(j)->description);
ContactPersonEmails.at(j)->description->style()->polish(ContactPersonEmails.at(j)->description);
ContactPersonEmails.at(j)->description->update();
}}}
if(!errors) {
contactperson->save();
for(int i = 0; i < ContactPersonTelephones.length(); i++){
ContactPersonTelephones.at(i)->contactpersontelephone->ContactPersonID= contactperson->ContactPersonID;
if(!ContactPersonTelephones.at(i)->save()){ 
 errors = true; 
 break; } 
}
for(int i = 0; i < contactperson->contactpersontelephones.length(); i++){
bool flag = false;
for(int j = 0; j < ContactPersonTelephones.length(); j++){
if(contactperson->contactpersontelephones.at(i)->ContactPersonTelephoneID == ContactPersonTelephones.at(j)->contactpersontelephone->ContactPersonTelephoneID){
flag = true;}}
if(!flag){
contactperson->contactpersontelephones.at(i)->remove();}
}
for(int i = 0; i < ContactPersonEmails.length(); i++){
ContactPersonEmails.at(i)->contactpersonemail->ContactPersonID= contactperson->ContactPersonID;
if(!ContactPersonEmails.at(i)->save()){ 
 errors = true; 
 break; } 
}
for(int i = 0; i < contactperson->contactpersonemails.length(); i++){
bool flag = false;
for(int j = 0; j < ContactPersonEmails.length(); j++){
if(contactperson->contactpersonemails.at(i)->ContactPersonEmailID == ContactPersonEmails.at(j)->contactpersonemail->ContactPersonEmailID){
flag = true;}}
if(!flag){
contactperson->contactpersonemails.at(i)->remove();}
}
if(!errors){
ContactPersonIndexUI::ShowUI();
return true;}
else return false;
}
else{ QMessageBox::warning(this, QObject::tr("ContactPerson"),errorString.trimmed());
return false; 
 }
}
void ContactPersonUI::cancel(){ 
ContactPersonIndexUI::ShowUI();
}
bool ContactPersonUI::updateModel(){ 
bool errors = false;
QString errorString =  "";
if(contactperson->ContactID == 0) 
contactperson->ContactID = contact->getKey();
if(name->text().trimmed().isEmpty()){
errors = true;
errorString += QObject::tr("Name Can't be Empty! \n");
name->setObjectName("error");
name->style()->unpolish(name);
name->style()->polish(name);
name->update();
}
else { 
name->setObjectName("name");
name->style()->unpolish(name);
name->style()->polish(name);
name->update();
contactperson->Name = name->text().trimmed();
}
if(lastname->text().trimmed().isEmpty()){
errors = true;
errorString += QObject::tr("Last Name Can't be Empty! \n");
lastname->setObjectName("error");
lastname->style()->unpolish(lastname);
lastname->style()->polish(lastname);
lastname->update();
}
else { 
lastname->setObjectName("lastname");
lastname->style()->unpolish(lastname);
lastname->style()->polish(lastname);
lastname->update();
contactperson->LastName = lastname->text().trimmed();
}
if(position->text().trimmed().isEmpty()){
errors = true;
errorString += QObject::tr("Position Can't be Empty! \n");
position->setObjectName("error");
position->style()->unpolish(position);
position->style()->polish(position);
position->update();
}
else { 
position->setObjectName("position");
position->style()->unpolish(position);
position->style()->polish(position);
position->update();
contactperson->Position = position->text().trimmed();
}
if(birthdate->text().trimmed().isEmpty()){
errors = true;
errorString += QObject::tr("Birthdate Can't be Empty! \n");
birthdate->setObjectName("error");
birthdate->style()->unpolish(birthdate);
birthdate->style()->polish(birthdate);
birthdate->update();
}
else { 
birthdate->setObjectName("birthdate");
birthdate->style()->unpolish(birthdate);
birthdate->style()->polish(birthdate);
birthdate->update();
contactperson->Birthdate.fromString(birthdate->text().trimmed());
}
if(number->text().trimmed().isEmpty()){
errors = true;
errorString += QObject::tr("Number Can't be Empty! \n");
number->setObjectName("error");
number->style()->unpolish(number);
number->style()->polish(number);
number->update();
}
else { 
number->setObjectName("number");
number->style()->unpolish(number);
number->style()->polish(number);
number->update();
contactperson->Number = number->text().trimmed().toInt();
}
for(int j = 0; j < ContactPersonTelephones.length(); j++){
ContactPersonTelephones.at(j)->description->setObjectName("description");
ContactPersonTelephones.at(j)->description->style()->unpolish(ContactPersonTelephones.at(j)->description);
ContactPersonTelephones.at(j)->description->style()->polish(ContactPersonTelephones.at(j)->description);
ContactPersonTelephones.at(j)->description->update();
for(int w = 0; w < ContactPersonTelephones.length(); w++){
if(ContactPersonTelephones.at(j) != ContactPersonTelephones.at(w))
if(ContactPersonTelephones.at(j)->description->text() == ContactPersonTelephones.at(w)->description->text()){
errors = true; 
 errorString +=QObject::tr( "ContactPersonTelephone has the same description \n");
ContactPersonTelephones.at(j)->description->setObjectName("error");
ContactPersonTelephones.at(j)->description->style()->unpolish(ContactPersonTelephones.at(j)->description);
ContactPersonTelephones.at(j)->description->style()->polish(ContactPersonTelephones.at(j)->description);
ContactPersonTelephones.at(j)->description->update();
}}}
for(int j = 0; j < ContactPersonEmails.length(); j++){
ContactPersonEmails.at(j)->description->setObjectName("description");
ContactPersonEmails.at(j)->description->style()->unpolish(ContactPersonEmails.at(j)->description);
ContactPersonEmails.at(j)->description->style()->polish(ContactPersonEmails.at(j)->description);
ContactPersonEmails.at(j)->description->update();
for(int w = 0; w < ContactPersonEmails.length(); w++){
if(ContactPersonEmails.at(j) != ContactPersonEmails.at(w))
if(ContactPersonEmails.at(j)->description->text() == ContactPersonEmails.at(w)->description->text()){
errors = true; 
 errorString +=QObject::tr( "ContactPersonEmail has the same description \n");
ContactPersonEmails.at(j)->description->setObjectName("error");
ContactPersonEmails.at(j)->description->style()->unpolish(ContactPersonEmails.at(j)->description);
ContactPersonEmails.at(j)->description->style()->polish(ContactPersonEmails.at(j)->description);
ContactPersonEmails.at(j)->description->update();
}}}
for(int i = 0; i < ContactPersonTelephones.length(); i++){
ContactPersonTelephones.at(i)->contactpersontelephone->ContactPersonID= contactperson->ContactPersonID;
if(!ContactPersonTelephones.at(i)->updateModel()){ 
 errors = true; 
 break; } 
}
for(int i = 0; i < ContactPersonEmails.length(); i++){
ContactPersonEmails.at(i)->contactpersonemail->ContactPersonID= contactperson->ContactPersonID;
if(!ContactPersonEmails.at(i)->updateModel()){ 
 errors = true; 
 break; } 
}
if(!errors){
	return true;
}
else{ if(!errorString.trimmed().isEmpty()) QMessageBox::warning(this, QObject::tr("ContactPerson"),errorString.trimmed());
return false; 
 }
}
