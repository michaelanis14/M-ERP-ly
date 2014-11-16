/**************************************************************************
**   File: contactclass.cpp
**   Created on: Sun Nov 16 16:19:26 EET 2014
**   Author: Michael Bishara
**   Copyright: SphinxSolutions.
**************************************************************************/
#include "contactclass.h"
#include "erpmodel.h"

ContactClass::ContactClass()
 : QSqlRelationalTableModel(){

this->ContactClassID = 0 ;
this->Description = " ";
this->CreatedOn = " ";
this->EditedOn = " ";
this->setTable("ContactClass");
this->setEditStrategy(QSqlTableModel::OnManualSubmit);
}
ContactClass::ContactClass(int ContactClassID,QString Description,QString CreatedOn,QString EditedOn) : QSqlRelationalTableModel(){
this->ContactClassID = ContactClassID ;
this->Description = Description ;
this->CreatedOn = CreatedOn ;
this->EditedOn = EditedOn ;
}

ContactClass::ContactClass(QString Description,QString CreatedOn,QString EditedOn) : QSqlRelationalTableModel(){
this->ContactClassID = 0 ;
this->Description = Description ;
this->CreatedOn = CreatedOn ;
this->EditedOn = EditedOn ;
}

bool ContactClass::Init()
{

QString table = "ContactClass";
QString query =
"(ContactClassID INT NOT NULL AUTO_INCREMENT, "
"PRIMARY KEY (ContactClassID),"
"Description VARCHAR(40) NOT NULL, "
"CreatedOn VARCHAR(40) NOT NULL, "
"EditedOn VARCHAR(40) NOT NULL )" ;

ErpModel::GetInstance()->createTable(table,query);
return true;
}
ContactClass* ContactClass::p_instance = 0;
ContactClass* ContactClass::GetInstance() {
	if (p_instance == 0) {
		p_instance = new ContactClass();
		ContactClass::GetAll();
	}
return p_instance;
}
bool ContactClass::save() {
if(ContactClassID== 0) {
this->CreatedOn = QDateTime::currentDateTime().toString(); 
	this->EditedOn = QDateTime::currentDateTime().toString();
ErpModel::GetInstance()->qeryExec("INSERT INTO ContactClass (Description,CreatedOn,EditedOn)"
"VALUES ('" +QString(this->Description)+"','"+QString(this->CreatedOn)+"','"+QString(this->EditedOn)+"')");
}else {
ErpModel::GetInstance()->qeryExec("UPDATE ContactClass SET ""Description = '"+QString(this->Description)+"','"+"CreatedOn = '"+QString(this->CreatedOn)+"','"+"EditedOn = '"+QString(this->EditedOn)+"' WHERE ContactClassID ='"+QString::number(this->ContactClassID)+"'");
 }QSqlQuery query = ErpModel::GetInstance()->qeryExec("SELECT  ContactClassID FROM ContactClass WHERE Description = '"+Description+"' AND EditedOn = '"+this->EditedOn+"'"  );
while (query.next()) { 
 if(query.value(0).toInt() != 0){ 
 this->ContactClassID = query.value(0).toInt();	
 } 
 }
return true;
}

bool ContactClass::remove() {
if(ContactClassID!= 0) {
(ErpModel::GetInstance()->qeryExec("DELETE FROM ContactClass WHERE ContactClassID ="+QString::number(this->ContactClassID)+""));
return true;
 }
return false;
}

ContactClass* ContactClass::get() {
if(ContactClassID!= 0) {
QSqlQuery query = (ErpModel::GetInstance()->qeryExec("SELECT * FROM ContactClass"
"WHERE ContactClassID ='"+QString::number(this->ContactClassID)+"'"));
while (query.next()) {
return new ContactClass(query.value(0).toInt(),query.value(1).toString(),query.value(2).toString(),query.value(3).toString());
 }

}
return new ContactClass();
 }

QList<ContactClass*> ContactClass::GetAll() {
	ContactClass::GetInstance()->contactclasss.clear();
	QSqlQuery query = (ErpModel::GetInstance()->qeryExec("SELECT *  FROM ContactClass"));
	while (query.next()) {
		ContactClass::GetInstance()->contactclasss.append(new ContactClass(query.value(0).toInt(),query.value(1).toString(),query.value(2).toString(),query.value(3).toString()));
	}
	return ContactClass::GetInstance()->contactclasss;
}

ContactClass* ContactClass::Get(int id) {
ContactClass* contactclass = new ContactClass();
if(id != 0) {
QSqlQuery query = (ErpModel::GetInstance()->qeryExec("SELECT * FROM ContactClass WHERE ContactClassID = '"+QString::number(id)+"'"));
while (query.next()) {
contactclass = new ContactClass(query.value(0).toInt(),query.value(1).toString(),query.value(2).toString(),query.value(3).toString());
 }

}
return contactclass;
}

ContactClass* ContactClass::get(const QModelIndex &index) {
QModelIndex primaryKeyIndex = QSqlRelationalTableModel::index(index.row(), 0); 
 if(data(primaryKeyIndex).toInt() != 0) 
 return Get(data(primaryKeyIndex).toInt());
else return new ContactClass();
}

ContactClass* ContactClass::Get(QString name) {
ContactClass* contactclass = new ContactClass();
if(name != NULL) {
QSqlQuery query = (ErpModel::GetInstance()->qeryExec("SELECT *  FROM ContactClass WHERE Description = '"+name+"'"));
while (query.next()) {
contactclass = new ContactClass(query.value(0).toInt(),query.value(1).toString(),query.value(2).toString(),query.value(3).toString());

 }

}
return contactclass;
 }

QList<ContactClass*> ContactClass::Search(QString keyword) {
QList<ContactClass*>list;
if(keyword != NULL) {
QSqlQuery query = (ErpModel::GetInstance()->qeryExec("SELECT *  FROM ContactClass"
"WHERE" 
"Description LIKE '%"+keyword+"%'"
"OR CreatedOn LIKE '%"+keyword+"%'"
"OR EditedOn LIKE '%"+keyword+"%'"
));
while (query.next()) {
list.append(new ContactClass(query.value(0).toInt(),query.value(1).toString(),query.value(2).toString(),query.value(3).toString()));
 }

}
return list;
 }

QList<QString> ContactClass::GetStringList() {
	QList<QString> list;
	int count =ContactClass::GetInstance()->contactclasss.count();
	if( count < 2){
		ContactClass::GetAll();
	}
	for(int i = 0; i < count; i++){
		list.append(ContactClass::GetInstance()->contactclasss[i]->Description);
	}
	return list;
}

QHash<int,QString> ContactClass::GetHashList() {
	QHash<int,QString> list;
	int count =ContactClass::GetInstance()->contactclasss.count();
	if( count < 2){
		ContactClass::GetAll();
	}
	for(int i = 0; i < count; i++){
		list.insert(ContactClass::GetInstance()->contactclasss[i]->ContactClassID,ContactClass::GetInstance()->contactclasss[i]->Description);
	}
	return list;
}

int ContactClass::GetIndex(QString name) {
	int count =ContactClass::GetInstance()->contactclasss.count();
	if( count < 2){
		ContactClass::GetAll();
	}
	for(int i = 0; i < count; i++){
		if(ContactClass::GetInstance()->contactclasss[i]->Description == name){
			return i;
		}
	}
	return 0;
}

QList<ContactClass*> ContactClass::QuerySelect(QString select) {
QList<ContactClass*>list;
if(select != NULL) {
QSqlQuery query = (ErpModel::GetInstance()->qeryExec("SELECT *  FROM ContactClass WHERE "+select+"" ));
while (query.next()) {
list.append(new ContactClass(query.value(0).toInt(),query.value(1).toString(),query.value(2).toString(),query.value(3).toString()));
 }

}
return list;
 }

Qt::ItemFlags ContactClass::flags(const QModelIndex &index) const {
Qt::ItemFlags flags = QSqlRelationalTableModel::flags(index);
flags ^= Qt::ItemIsEditable;
if (
index.column() == 1 || index.column() == 2 || index.column() == 3)
flags |= Qt::ItemIsEditable;
return flags;
}

bool ContactClass::setData(const QModelIndex &index, const QVariant &value, int /* role */) {
	if (index.column() < 1)
		return false;
QModelIndex primaryKeyIndex = QSqlRelationalTableModel::index(index.row(), 0);
int id = data(primaryKeyIndex).toInt();
bool ok = true;
if((data(QSqlRelationalTableModel::index(index.row(), index.column())).toString() != value.toString().toLower())){
if (index.column() == 1)
ok = setDescription(id, value.toString());
else if (index.column() == 2)
ok = setCreatedOn(id, value.toString());
else if (index.column() == 3)
ok = setEditedOn(id, value.toString());
refresh();
}
return ok;
}

bool ContactClass::remove(const QModelIndex &index) {
QModelIndex primaryKeyIndex = QSqlRelationalTableModel::index(index.row(), 0);
bool ok = true;
this->ContactClassID = data(primaryKeyIndex).toInt();
ok = this->remove();
refresh();
return ok;
}

void ContactClass::refresh() {
if(!ErpModel::GetInstance()->db.isOpen()&&!ErpModel::GetInstance()->db.open())
qDebug() <<"Couldn't open DataBase at Refresh() ContactClass!";
this->setHeaderData(1, Qt::Horizontal, QObject::tr("Description"));
this->setHeaderData(2, Qt::Horizontal, QObject::tr("Created On"));
this->setHeaderData(3, Qt::Horizontal, QObject::tr("Edited On"));
	this->select();
//	if(ErpModel::GetInstance()->db.isOpen())
//		ErpModel::GetInstance()->db.close();
}
bool ContactClass::setDescription(int ContactClassID, const QString &Description) {
QSqlQuery query;
query.prepare("update ContactClass set Description = ? where ContactClassID = ?");
query.addBindValue(Description);
query.addBindValue(ContactClassID);
if( !query.exec() )
qDebug() << query.lastError().text();
return true;
}
bool ContactClass::setCreatedOn(int ContactClassID, const QString &CreatedOn) {
QSqlQuery query;
query.prepare("update ContactClass set CreatedOn = ? where ContactClassID = ?");
query.addBindValue(CreatedOn);
query.addBindValue(ContactClassID);
if( !query.exec() )
qDebug() << query.lastError().text();
return true;
}
bool ContactClass::setEditedOn(int ContactClassID, const QString &EditedOn) {
QSqlQuery query;
query.prepare("update ContactClass set EditedOn = ? where ContactClassID = ?");
query.addBindValue(EditedOn);
query.addBindValue(ContactClassID);
if( !query.exec() )
qDebug() << query.lastError().text();
return true;
}

