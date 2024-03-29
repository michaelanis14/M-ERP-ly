/**************************************************************************
**   File: paymenttype.cpp
**   Created on: Sat Dec 20 02:32:00 EET 2014
**   Author: Michael Bishara
**   Copyright: SphinxSolutions.
**************************************************************************/
#include "paymenttype.h"
#include "erpmodel.h"

PaymentType::PaymentType()
 : QSqlRelationalTableModel(){

this->PaymentTypeID = 0 ;
this->Description = "";
this->CreatedOn = "";
this->EditedOn = "";
this->setTable("PaymentType");
this->setEditStrategy(QSqlTableModel::OnManualSubmit);
}
PaymentType::PaymentType(int PaymentTypeID,QString Description,QString CreatedOn,QString EditedOn) : QSqlRelationalTableModel(){
this->PaymentTypeID = PaymentTypeID ;
this->Description = Description ;
this->CreatedOn = CreatedOn ;
this->EditedOn = EditedOn ;
}

PaymentType::PaymentType(QString Description,QString CreatedOn,QString EditedOn) : QSqlRelationalTableModel(){
this->PaymentTypeID = 0 ;
this->Description = Description ;
this->CreatedOn = CreatedOn ;
this->EditedOn = EditedOn ;
}

bool PaymentType::Init()
{

QString table = "PaymentType";
QString query =
"(PaymentTypeID INT NOT NULL AUTO_INCREMENT, "
"PRIMARY KEY (PaymentTypeID),"
"Description VARCHAR(40) NOT NULL, "
" KEY(Description),"
"CreatedOn VARCHAR(40) NOT NULL, "
"EditedOn VARCHAR(40) NOT NULL, KEY(EditedOn) )" ;

QList<QPair<QString,QString> >variables;
variables.append(qMakePair(QString(" INT"),QString("PaymentTypeID")));variables.append(qMakePair(QString(" VARCHAR(40)"),QString("Description")));variables.append(qMakePair(QString(" VARCHAR(40)"),QString("CreatedOn")));variables.append(qMakePair(QString(" VARCHAR(40)"),QString("EditedOn")));ErpModel::GetInstance()->createTable(table,query,variables);
return true;
}
PaymentType* PaymentType::p_instance = 0;
PaymentType* PaymentType::GetInstance() {
	if (p_instance == 0) {
		p_instance = new PaymentType();
		PaymentType::GetAll();
	}
return p_instance;
}
bool PaymentType::save() {
this->EditedOn = QDate::currentDate().toString();
if(PaymentTypeID== 0) {
this->CreatedOn = QDate::currentDate().toString();
ErpModel::GetInstance()->qeryExec("INSERT INTO PaymentType (Description,CreatedOn,EditedOn)"
"VALUES ('" +QString(this->Description)+"','"+QString(this->CreatedOn)+"','"+QString(this->EditedOn)+"')");
}else {
ErpModel::GetInstance()->qeryExec("UPDATE PaymentType SET "	"Description = '"+QString(this->Description)+"',"+"CreatedOn = '"+QString(this->CreatedOn)+"',"+"EditedOn = '"+QString(this->EditedOn)+"' WHERE PaymentTypeID ='"+QString::number(this->PaymentTypeID)+"'");
 }QSqlQuery query = ErpModel::GetInstance()->qeryExec("SELECT  PaymentTypeID FROM PaymentType WHERE Description = '"+Description+"' AND EditedOn = '"+this->EditedOn+"'"  );
while (query.next()) { 
 if(query.value(0).toInt() != 0){ 
 this->PaymentTypeID = query.value(0).toInt();	
 } 
 }
return true;
}
bool PaymentType::save(QSqlRecord &record) {
	if(ErpModel::GetInstance()->db.open()) 
 if(this->insertRowIntoTable(record)) 
 return true; 
 return false;
}

bool PaymentType::remove() {
if(PaymentTypeID!= 0) {
(ErpModel::GetInstance()->qeryExec("DELETE FROM PaymentType WHERE PaymentTypeID ="+QString::number(this->PaymentTypeID)+""));
return true;
 }
return false;
}

PaymentType* PaymentType::get() {
if(PaymentTypeID!= 0) {
QSqlQuery query = (ErpModel::GetInstance()->qeryExec("SELECT * FROM PaymentType"
"WHERE PaymentTypeID ='"+QString::number(this->PaymentTypeID)+"'"));
while (query.next()) {
return new PaymentType(query.value(0).toInt(),query.value(1).toString(),query.value(2).toString(),query.value(3).toString());
 }

}
return new PaymentType();
 }

QList<PaymentType*> PaymentType::GetAll() {
	QList<PaymentType*> paymenttypes =   QList<PaymentType*>();
	QSqlQuery query = (ErpModel::GetInstance()->qeryExec("SELECT *  FROM PaymentType ORDER BY PaymentTypeID ASC"));
	while (query.next()) {
paymenttypes.append(new PaymentType(query.value(0).toInt(),query.value(1).toString(),query.value(2).toString(),query.value(3).toString()));
	}
	return paymenttypes;
}

PaymentType* PaymentType::Get(int id) {
PaymentType* paymenttype = new PaymentType();
if(id != 0) {
QSqlQuery query = (ErpModel::GetInstance()->qeryExec("SELECT * FROM PaymentType WHERE PaymentTypeID = '"+QString::number(id)+"' ORDER BY PaymentTypeID ASC "));
while (query.next()) {
paymenttype = new PaymentType(query.value(0).toInt(),query.value(1).toString(),query.value(2).toString(),query.value(3).toString());
 }

}
return paymenttype;
}

PaymentType* PaymentType::get(const QModelIndex &index) {
QModelIndex primaryKeyIndex = QSqlRelationalTableModel::index(index.row(), 0); 
 if(data(primaryKeyIndex).toInt() != 0) 
 return Get(data(primaryKeyIndex).toInt());
else return new PaymentType();
}

PaymentType* PaymentType::Get(QString name) {
PaymentType* paymenttype = new PaymentType();
if(name != NULL) {
QSqlQuery query = (ErpModel::GetInstance()->qeryExec("SELECT *  FROM PaymentType WHERE Description = '"+name+"'"));
while (query.next()) {
paymenttype = new PaymentType(query.value(0).toInt(),query.value(1).toString(),query.value(2).toString(),query.value(3).toString());

 }

}
return paymenttype;
 }

QList<PaymentType*> PaymentType::Search(QString keyword) {
QList<PaymentType*>list;
if(keyword != NULL) {
QSqlQuery query = (ErpModel::GetInstance()->qeryExec("SELECT *  FROM PaymentType"
"WHERE" 
"Description LIKE '%"+keyword+"%'"
"OR CreatedOn LIKE '%"+keyword+"%'"
"OR EditedOn LIKE '%"+keyword+"%'"
));
while (query.next()) {
list.append(new PaymentType(query.value(0).toInt(),query.value(1).toString(),query.value(2).toString(),query.value(3).toString()));
 }

}
return list;
 }

QList<QString> PaymentType::GetStringList() {
	QList<QString> list;
	QList<PaymentType*> paymenttypes =   QList<PaymentType*>();
paymenttypes = GetAll();
	for(int i = 0; i <paymenttypes.count(); i++){
		list.append(paymenttypes[i]->Description);
	}
	return list;
}

QList<QPair< int,QString > > PaymentType::GetPairList() {
	QList<QPair<int,QString > > list;
	QList<PaymentType*> paymenttypes =   QList<PaymentType*>();
paymenttypes = GetAll();
	for(int i = 0; i <paymenttypes.count(); i++){
		list.append(qMakePair(paymenttypes[i]->PaymentTypeID,paymenttypes[i]->Description));
	}
	return list;
}

QList<QPair< int,QString > > PaymentType::GetPairList(QList<PaymentType*> paymenttypes) {
	QList<QPair<int,QString > > list;
	for(int i = 0; i <paymenttypes.count(); i++){
		list.append(qMakePair(paymenttypes[i]->PaymentTypeID,paymenttypes[i]->Description));
	}
	return list;
}

int PaymentType::GetIndex(QString name) {
	QList<PaymentType*> paymenttypes =   QList<PaymentType*>();
paymenttypes = GetAll();
	for(int i = 0; i <paymenttypes.count(); i++){
		if(paymenttypes[i]->Description == name){
			return i;
		}
	}
	return 0;
}

QList<PaymentType*> PaymentType::QuerySelect(QString select) {
QList<PaymentType*>list;
if(select != NULL) {
QSqlQuery query = (ErpModel::GetInstance()->qeryExec("SELECT *  FROM PaymentType WHERE "+select+"" ));
while (query.next()) {
list.append(new PaymentType(query.value(0).toInt(),query.value(1).toString(),query.value(2).toString(),query.value(3).toString()));
 }

}
return list;
 }

Qt::ItemFlags PaymentType::flags(const QModelIndex &index) const {
Qt::ItemFlags flags = QSqlRelationalTableModel::flags(index);
flags ^= Qt::ItemIsEditable;
if (
index.column() == 1 || index.column() == 2 || index.column() == 3)
flags |= Qt::ItemIsEditable;
return flags;
}

bool PaymentType::setData(const QModelIndex &index, const QVariant &value, int /* role */) {
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

bool PaymentType::remove(const QModelIndex &index) {
QModelIndex primaryKeyIndex = QSqlRelationalTableModel::index(index.row(), 0);
bool ok = true;
this->PaymentTypeID = data(primaryKeyIndex).toInt();
ok = this->remove();
refresh();
return ok;
}

void PaymentType::refresh() {
if(!ErpModel::GetInstance()->db.isOpen()&&!ErpModel::GetInstance()->db.open())
qDebug() <<"Couldn't open DataBase at Refresh() PaymentType!";
this->setHeaderData(1, Qt::Horizontal, QObject::tr("Description"));
this->setHeaderData(2, Qt::Horizontal, QObject::tr("Created On"));
this->setHeaderData(3, Qt::Horizontal, QObject::tr("Edited On"));
	this->select();
//	if(ErpModel::GetInstance()->db.isOpen())
//		ErpModel::GetInstance()->db.close();
}
bool PaymentType::setDescription(int PaymentTypeID, const QString &Description) {
QSqlQuery query;
query.prepare("update PaymentType set Description = ? where PaymentTypeID = ?");
query.addBindValue(Description);
query.addBindValue(PaymentTypeID);
if( !query.exec() )
qDebug() << query.lastError().text();
return true;
}
bool PaymentType::setCreatedOn(int PaymentTypeID, const QString &CreatedOn) {
QSqlQuery query;
query.prepare("update PaymentType set CreatedOn = ? where PaymentTypeID = ?");
query.addBindValue(CreatedOn);
query.addBindValue(PaymentTypeID);
if( !query.exec() )
qDebug() << query.lastError().text();
return true;
}
bool PaymentType::setEditedOn(int PaymentTypeID, const QString &EditedOn) {
QSqlQuery query;
query.prepare("update PaymentType set EditedOn = ? where PaymentTypeID = ?");
query.addBindValue(EditedOn);
query.addBindValue(PaymentTypeID);
if( !query.exec() )
qDebug() << query.lastError().text();
return true;
}

