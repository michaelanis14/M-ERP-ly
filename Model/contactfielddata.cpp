/**************************************************************************
**   File: contactfielddata.cpp
**   Created on: Thu Dec 18 12:57:58 EET 2014
**   Author: Michael Bishara
**   Copyright: SphinxSolutions.
**************************************************************************/
#include "contactfielddata.h"
#include "erpmodel.h"

ContactFieldData::ContactFieldData()
 : QSqlRelationalTableModel(){

this->ContactFieldDataID = 0 ;
this->ContactID = 0 ;
this->ContactFieldID = 0 ;
this->Value = "";
this->CreatedOn = "";
this->EditedOn = "";
this->setTable("ContactFieldData");
this->setEditStrategy(QSqlTableModel::OnManualSubmit);
this->setRelation(1, QSqlRelation("Contact", "ContactID", "Name"));
this->setRelation(2, QSqlRelation("ContactField", "ContactFieldID", "Description"));
}
ContactFieldData::ContactFieldData(int ContactFieldDataID,int ContactID,int ContactFieldID,QString Value,QString CreatedOn,QString EditedOn) : QSqlRelationalTableModel(){
this->ContactFieldDataID = ContactFieldDataID ;
this->ContactID = ContactID ;
this->ContactFieldID = ContactFieldID ;
this->Value = Value ;
this->CreatedOn = CreatedOn ;
this->EditedOn = EditedOn ;
}

ContactFieldData::ContactFieldData(int ContactID,int ContactFieldID,QString Value,QString CreatedOn,QString EditedOn) : QSqlRelationalTableModel(){
this->ContactFieldDataID = 0 ;
this->ContactID = ContactID ;
this->ContactFieldID = ContactFieldID ;
this->Value = Value ;
this->CreatedOn = CreatedOn ;
this->EditedOn = EditedOn ;
}

bool ContactFieldData::Init()
{

QString table = "ContactFieldData";
QString query =
"(ContactFieldDataID INT NOT NULL AUTO_INCREMENT, "
"PRIMARY KEY (ContactFieldDataID),"
"ContactID INT NOT NULL, "
" KEY(ContactID),"
"FOREIGN KEY (ContactID) REFERENCES Contact(ContactID)  ON DELETE CASCADE,"
"ContactFieldID INT NOT NULL, "
"FOREIGN KEY (ContactFieldID) REFERENCES ContactField(ContactFieldID)  ON DELETE CASCADE,"
"Value VARCHAR(40) NOT NULL, "
"CreatedOn VARCHAR(40) NOT NULL, "
"EditedOn VARCHAR(40) NOT NULL, KEY(EditedOn) )" ;

QList<QPair<QString,QString> >variables;
variables.append(qMakePair(QString(" INT"),QString("ContactFieldDataID")));variables.append(qMakePair(QString(" INT"),QString("ContactID")));variables.append(qMakePair(QString(" INT"),QString("ContactFieldID")));variables.append(qMakePair(QString(" VARCHAR(40)"),QString("Value")));variables.append(qMakePair(QString(" VARCHAR(40)"),QString("CreatedOn")));variables.append(qMakePair(QString(" VARCHAR(40)"),QString("EditedOn")));ErpModel::GetInstance()->createTable(table,query,variables);
return true;
}
ContactFieldData* ContactFieldData::p_instance = 0;
ContactFieldData* ContactFieldData::GetInstance() {
	if (p_instance == 0) {
		p_instance = new ContactFieldData();
		ContactFieldData::GetAll();
	}
return p_instance;
}
bool ContactFieldData::save() {
this->EditedOn = QDate::currentDate().toString();
if(ContactFieldDataID== 0) {
this->CreatedOn = QDate::currentDate().toString();
ErpModel::GetInstance()->qeryExec("INSERT INTO ContactFieldData (ContactID,ContactFieldID,Value,CreatedOn,EditedOn)"
"VALUES ('" +QString::number(this->ContactID)+"','"+QString::number(this->ContactFieldID)+"','"+QString(this->Value)+"','"+QString(this->CreatedOn)+"','"+QString(this->EditedOn)+"')");
}else {
ErpModel::GetInstance()->qeryExec("UPDATE ContactFieldData SET "	"ContactID = '"+QString::number(this->ContactID)+"',"+"ContactFieldID = '"+QString::number(this->ContactFieldID)+"',"+"Value = '"+QString(this->Value)+"',"+"CreatedOn = '"+QString(this->CreatedOn)+"',"+"EditedOn = '"+QString(this->EditedOn)+"' WHERE ContactFieldDataID ='"+QString::number(this->ContactFieldDataID)+"'");
 }QSqlQuery query = ErpModel::GetInstance()->qeryExec("SELECT  ContactFieldDataID FROM ContactFieldData WHERE ContactID = "+QString::number(ContactID)+" AND EditedOn = '"+this->EditedOn+"'"  );
while (query.next()) { 
 if(query.value(0).toInt() != 0){ 
 this->ContactFieldDataID = query.value(0).toInt();	
 } 
 }
return true;
}
bool ContactFieldData::save(QSqlRecord &record) {
	if(ErpModel::GetInstance()->db.open()) 
 if(this->insertRowIntoTable(record)) 
 return true; 
 return false;
}

bool ContactFieldData::remove() {
if(ContactFieldDataID!= 0) {
(ErpModel::GetInstance()->qeryExec("DELETE FROM ContactFieldData WHERE ContactFieldDataID ="+QString::number(this->ContactFieldDataID)+""));
return true;
 }
return false;
}

ContactFieldData* ContactFieldData::get() {
if(ContactFieldDataID!= 0) {
QSqlQuery query = (ErpModel::GetInstance()->qeryExec("SELECT * FROM ContactFieldData"
"WHERE ContactFieldDataID ='"+QString::number(this->ContactFieldDataID)+"'"));
while (query.next()) {
return new ContactFieldData(query.value(0).toInt(),query.value(1).toInt(),query.value(2).toInt(),query.value(3).toString(),query.value(4).toString(),query.value(5).toString());
 }

}
return new ContactFieldData();
 }

QList<ContactFieldData*> ContactFieldData::GetAll() {
	QList<ContactFieldData*> contactfielddatas =   QList<ContactFieldData*>();
	QSqlQuery query = (ErpModel::GetInstance()->qeryExec("SELECT *  FROM ContactFieldData ORDER BY ContactFieldDataID ASC"));
	while (query.next()) {
contactfielddatas.append(new ContactFieldData(query.value(0).toInt(),query.value(1).toInt(),query.value(2).toInt(),query.value(3).toString(),query.value(4).toString(),query.value(5).toString()));
	}
	return contactfielddatas;
}

ContactFieldData* ContactFieldData::Get(int id) {
ContactFieldData* contactfielddata = new ContactFieldData();
if(id != 0) {
QSqlQuery query = (ErpModel::GetInstance()->qeryExec("SELECT * FROM ContactFieldData WHERE ContactFieldDataID = '"+QString::number(id)+"' ORDER BY ContactFieldDataID ASC "));
while (query.next()) {
contactfielddata = new ContactFieldData(query.value(0).toInt(),query.value(1).toInt(),query.value(2).toInt(),query.value(3).toString(),query.value(4).toString(),query.value(5).toString());
 }

}
return contactfielddata;
}

ContactFieldData* ContactFieldData::get(const QModelIndex &index) {
QModelIndex primaryKeyIndex = QSqlRelationalTableModel::index(index.row(), 0); 
 if(data(primaryKeyIndex).toInt() != 0) 
 return Get(data(primaryKeyIndex).toInt());
else return new ContactFieldData();
}

ContactFieldData* ContactFieldData::Get(QString name) {
ContactFieldData* contactfielddata = new ContactFieldData();
if(name != NULL) {
QSqlQuery query = (ErpModel::GetInstance()->qeryExec("SELECT *  FROM ContactFieldData WHERE ContactID = QString::number("+name+")"));
while (query.next()) {
contactfielddata = new ContactFieldData(query.value(0).toInt(),query.value(1).toInt(),query.value(2).toInt(),query.value(3).toString(),query.value(4).toString(),query.value(5).toString());

 }

}
return contactfielddata;
 }

QList<ContactFieldData*> ContactFieldData::Search(QString keyword) {
QList<ContactFieldData*>list;
if(keyword != NULL) {
QSqlQuery query = (ErpModel::GetInstance()->qeryExec("SELECT *  FROM ContactFieldData"
"WHERE" 
"Value LIKE '%"+keyword+"%'"
"OR CreatedOn LIKE '%"+keyword+"%'"
"OR EditedOn LIKE '%"+keyword+"%'"
));
while (query.next()) {
list.append(new ContactFieldData(query.value(0).toInt(),query.value(1).toInt(),query.value(2).toInt(),query.value(3).toString(),query.value(4).toString(),query.value(5).toString()));
 }

}
return list;
 }

QList<QString> ContactFieldData::GetStringList() {
	QList<QString> list;
	QList<ContactFieldData*> contactfielddatas =   QList<ContactFieldData*>();
contactfielddatas = GetAll();
	for(int i = 0; i <contactfielddatas.count(); i++){
		list.append(contactfielddatas[i]->Value);
	}
	return list;
}

QList<QPair< int,QString > > ContactFieldData::GetPairList() {
	QList<QPair<int,QString > > list;
	QList<ContactFieldData*> contactfielddatas =   QList<ContactFieldData*>();
contactfielddatas = GetAll();
	for(int i = 0; i <contactfielddatas.count(); i++){
		list.append(qMakePair(contactfielddatas[i]->ContactFieldDataID,QString::number(contactfielddatas[i]->ContactID)));
	}
	return list;
}

QList<QPair< int,QString > > ContactFieldData::GetPairList(QList<ContactFieldData*> contactfielddatas) {
	QList<QPair<int,QString > > list;
	for(int i = 0; i <contactfielddatas.count(); i++){
		list.append(qMakePair(contactfielddatas[i]->ContactFieldDataID,QString::number(contactfielddatas[i]->ContactID)));
	}
	return list;
}

int ContactFieldData::GetIndex(QString name) {
	QList<ContactFieldData*> contactfielddatas =   QList<ContactFieldData*>();
contactfielddatas = GetAll();
	for(int i = 0; i <contactfielddatas.count(); i++){
		if(contactfielddatas[i]->ContactID == name.toInt()){
			return i;
		}
	}
	return 0;
}

QList<ContactFieldData*> ContactFieldData::QuerySelect(QString select) {
QList<ContactFieldData*>list;
if(select != NULL) {
QSqlQuery query = (ErpModel::GetInstance()->qeryExec("SELECT *  FROM ContactFieldData WHERE "+select+"" ));
while (query.next()) {
list.append(new ContactFieldData(query.value(0).toInt(),query.value(1).toInt(),query.value(2).toInt(),query.value(3).toString(),query.value(4).toString(),query.value(5).toString()));
 }

}
return list;
 }

Qt::ItemFlags ContactFieldData::flags(const QModelIndex &index) const {
Qt::ItemFlags flags = QSqlRelationalTableModel::flags(index);
flags ^= Qt::ItemIsEditable;
if (
index.column() == 1 || index.column() == 2 || index.column() == 3 || index.column() == 4 || index.column() == 5)
flags |= Qt::ItemIsEditable;
return flags;
}

bool ContactFieldData::setData(const QModelIndex &index, const QVariant &value, int /* role */) {
	if (index.column() < 1)
		return false;
QModelIndex primaryKeyIndex = QSqlRelationalTableModel::index(index.row(), 0);
int id = data(primaryKeyIndex).toInt();
bool ok = true;
if((data(QSqlRelationalTableModel::index(index.row(), index.column())).toString() != value.toString().toLower())){
if (index.column() == 1)
ok = setContactID(id, value.toString());
else if (index.column() == 2)
ok = setContactFieldID(id, value.toString());
else if (index.column() == 3)
ok = setValue(id, value.toString());
else if (index.column() == 4)
ok = setCreatedOn(id, value.toString());
else if (index.column() == 5)
ok = setEditedOn(id, value.toString());
refresh();
}
return ok;
}

bool ContactFieldData::remove(const QModelIndex &index) {
QModelIndex primaryKeyIndex = QSqlRelationalTableModel::index(index.row(), 0);
bool ok = true;
this->ContactFieldDataID = data(primaryKeyIndex).toInt();
ok = this->remove();
refresh();
return ok;
}

void ContactFieldData::refresh() {
if(!ErpModel::GetInstance()->db.isOpen()&&!ErpModel::GetInstance()->db.open())
qDebug() <<"Couldn't open DataBase at Refresh() ContactFieldData!";
this->setHeaderData(1, Qt::Horizontal, QObject::tr("Contact"));
this->setHeaderData(2, Qt::Horizontal, QObject::tr("Contact Field"));
this->setHeaderData(3, Qt::Horizontal, QObject::tr("Value"));
this->setHeaderData(4, Qt::Horizontal, QObject::tr("Created On"));
this->setHeaderData(5, Qt::Horizontal, QObject::tr("Edited On"));
	this->select();
//	if(ErpModel::GetInstance()->db.isOpen())
//		ErpModel::GetInstance()->db.close();
}
bool ContactFieldData::setContactID(int ContactFieldDataID, const QString &ContactID) {
QSqlQuery query;
query.prepare("update ContactFieldData set ContactID = ? where ContactFieldDataID = ?");
query.addBindValue(ContactID);
query.addBindValue(ContactFieldDataID);
if( !query.exec() )
qDebug() << query.lastError().text();
return true;
}
bool ContactFieldData::setContactFieldID(int ContactFieldDataID, const QString &ContactFieldID) {
QSqlQuery query;
query.prepare("update ContactFieldData set ContactFieldID = ? where ContactFieldDataID = ?");
query.addBindValue(ContactFieldID);
query.addBindValue(ContactFieldDataID);
if( !query.exec() )
qDebug() << query.lastError().text();
return true;
}
bool ContactFieldData::setValue(int ContactFieldDataID, const QString &Value) {
QSqlQuery query;
query.prepare("update ContactFieldData set Value = ? where ContactFieldDataID = ?");
query.addBindValue(Value);
query.addBindValue(ContactFieldDataID);
if( !query.exec() )
qDebug() << query.lastError().text();
return true;
}
bool ContactFieldData::setCreatedOn(int ContactFieldDataID, const QString &CreatedOn) {
QSqlQuery query;
query.prepare("update ContactFieldData set CreatedOn = ? where ContactFieldDataID = ?");
query.addBindValue(CreatedOn);
query.addBindValue(ContactFieldDataID);
if( !query.exec() )
qDebug() << query.lastError().text();
return true;
}
bool ContactFieldData::setEditedOn(int ContactFieldDataID, const QString &EditedOn) {
QSqlQuery query;
query.prepare("update ContactFieldData set EditedOn = ? where ContactFieldDataID = ?");
query.addBindValue(EditedOn);
query.addBindValue(ContactFieldDataID);
if( !query.exec() )
qDebug() << query.lastError().text();
return true;
}

