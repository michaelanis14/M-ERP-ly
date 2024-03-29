/**************************************************************************
**   File: deliveryorderservice.cpp
**   Created on: Thu Dec 18 12:57:59 EET 2014
**   Author: Michael Bishara
**   Copyright: SphinxSolutions.
**************************************************************************/
#include "deliveryorderservice.h"
#include "erpmodel.h"

DeliveryOrderService::DeliveryOrderService()
 : QSqlRelationalTableModel(){

this->DeliveryOrderServiceID = 0 ;
this->DeliveryOrderID = 0 ;
this->ServiceID = 0 ;
this->Amount = 0 ;
this->Price = 0 ;
this->CreatedOn = "";
this->EditedOn = "";
this->setTable("DeliveryOrderService");
this->setEditStrategy(QSqlTableModel::OnManualSubmit);
this->setRelation(2, QSqlRelation("Service", "ServiceID", "Name"));
}
DeliveryOrderService::DeliveryOrderService(int DeliveryOrderServiceID,int DeliveryOrderID,int ServiceID,double Amount,double Price,QString CreatedOn,QString EditedOn) : QSqlRelationalTableModel(){
this->DeliveryOrderServiceID = DeliveryOrderServiceID ;
this->DeliveryOrderID = DeliveryOrderID ;
this->ServiceID = ServiceID ;
this->Amount = Amount ;
this->Price = Price ;
this->CreatedOn = CreatedOn ;
this->EditedOn = EditedOn ;
}

DeliveryOrderService::DeliveryOrderService(int DeliveryOrderID,int ServiceID,double Amount,double Price,QString CreatedOn,QString EditedOn) : QSqlRelationalTableModel(){
this->DeliveryOrderServiceID = 0 ;
this->DeliveryOrderID = DeliveryOrderID ;
this->ServiceID = ServiceID ;
this->Amount = Amount ;
this->Price = Price ;
this->CreatedOn = CreatedOn ;
this->EditedOn = EditedOn ;
}

bool DeliveryOrderService::Init()
{

QString table = "DeliveryOrderService";
QString query =
"(DeliveryOrderServiceID INT NOT NULL AUTO_INCREMENT, "
"PRIMARY KEY (DeliveryOrderServiceID),"
"DeliveryOrderID INT NOT NULL, "
" KEY(DeliveryOrderID),"
"FOREIGN KEY (DeliveryOrderID) REFERENCES DeliveryOrder(DeliveryOrderID)  ON DELETE CASCADE,"
"ServiceID INT NOT NULL, "
"FOREIGN KEY (ServiceID) REFERENCES Service(ServiceID)  ON DELETE CASCADE,"
"Amount DECIMAL(6,2) NOT NULL, "
"Price DECIMAL(6,2) NOT NULL, "
"CreatedOn VARCHAR(40) NOT NULL, "
"EditedOn VARCHAR(40) NOT NULL, KEY(EditedOn) )" ;

QList<QPair<QString,QString> >variables;
variables.append(qMakePair(QString(" INT"),QString("DeliveryOrderServiceID")));variables.append(qMakePair(QString(" INT"),QString("DeliveryOrderID")));variables.append(qMakePair(QString(" INT"),QString("ServiceID")));variables.append(qMakePair(QString(" DECIMAL(6,2)"),QString("Amount")));variables.append(qMakePair(QString(" DECIMAL(6,2)"),QString("Price")));variables.append(qMakePair(QString(" VARCHAR(40)"),QString("CreatedOn")));variables.append(qMakePair(QString(" VARCHAR(40)"),QString("EditedOn")));ErpModel::GetInstance()->createTable(table,query,variables);
return true;
}
DeliveryOrderService* DeliveryOrderService::p_instance = 0;
DeliveryOrderService* DeliveryOrderService::GetInstance() {
	if (p_instance == 0) {
		p_instance = new DeliveryOrderService();
		DeliveryOrderService::GetAll();
	}
return p_instance;
}
bool DeliveryOrderService::save() {
this->EditedOn = QDate::currentDate().toString();
if(DeliveryOrderServiceID== 0) {
this->CreatedOn = QDate::currentDate().toString();
ErpModel::GetInstance()->qeryExec("INSERT INTO DeliveryOrderService (DeliveryOrderID,ServiceID,Amount,Price,CreatedOn,EditedOn)"
"VALUES ('" +QString::number(this->DeliveryOrderID)+"','"+QString::number(this->ServiceID)+"','"+QString::number(this->Amount)+"','"+QString::number(this->Price)+"','"+QString(this->CreatedOn)+"','"+QString(this->EditedOn)+"')");
}else {
ErpModel::GetInstance()->qeryExec("UPDATE DeliveryOrderService SET "	"DeliveryOrderID = '"+QString::number(this->DeliveryOrderID)+"',"+"ServiceID = '"+QString::number(this->ServiceID)+"',"+"Amount = '"+QString::number(this->Amount)+"',"+"Price = '"+QString::number(this->Price)+"',"+"CreatedOn = '"+QString(this->CreatedOn)+"',"+"EditedOn = '"+QString(this->EditedOn)+"' WHERE DeliveryOrderServiceID ='"+QString::number(this->DeliveryOrderServiceID)+"'");
 }QSqlQuery query = ErpModel::GetInstance()->qeryExec("SELECT  DeliveryOrderServiceID FROM DeliveryOrderService WHERE DeliveryOrderID = "+QString::number(DeliveryOrderID)+" AND EditedOn = '"+this->EditedOn+"'"  );
while (query.next()) { 
 if(query.value(0).toInt() != 0){ 
 this->DeliveryOrderServiceID = query.value(0).toInt();	
 } 
 }
return true;
}
bool DeliveryOrderService::save(QSqlRecord &record) {
	if(ErpModel::GetInstance()->db.open()) 
 if(this->insertRowIntoTable(record)) 
 return true; 
 return false;
}

bool DeliveryOrderService::remove() {
if(DeliveryOrderServiceID!= 0) {
(ErpModel::GetInstance()->qeryExec("DELETE FROM DeliveryOrderService WHERE DeliveryOrderServiceID ="+QString::number(this->DeliveryOrderServiceID)+""));
return true;
 }
return false;
}

DeliveryOrderService* DeliveryOrderService::get() {
if(DeliveryOrderServiceID!= 0) {
QSqlQuery query = (ErpModel::GetInstance()->qeryExec("SELECT * FROM DeliveryOrderService"
"WHERE DeliveryOrderServiceID ='"+QString::number(this->DeliveryOrderServiceID)+"'"));
while (query.next()) {
return new DeliveryOrderService(query.value(0).toInt(),query.value(1).toInt(),query.value(2).toInt(),query.value(3).toInt(),query.value(4).toInt(),query.value(5).toString(),query.value(6).toString());
 }

}
return new DeliveryOrderService();
 }

QList<DeliveryOrderService*> DeliveryOrderService::GetAll() {
	QList<DeliveryOrderService*> deliveryorderservices =   QList<DeliveryOrderService*>();
	QSqlQuery query = (ErpModel::GetInstance()->qeryExec("SELECT *  FROM DeliveryOrderService ORDER BY DeliveryOrderServiceID ASC"));
	while (query.next()) {
deliveryorderservices.append(new DeliveryOrderService(query.value(0).toInt(),query.value(1).toInt(),query.value(2).toInt(),query.value(3).toInt(),query.value(4).toInt(),query.value(5).toString(),query.value(6).toString()));
	}
	return deliveryorderservices;
}

DeliveryOrderService* DeliveryOrderService::Get(int id) {
DeliveryOrderService* deliveryorderservice = new DeliveryOrderService();
if(id != 0) {
QSqlQuery query = (ErpModel::GetInstance()->qeryExec("SELECT * FROM DeliveryOrderService WHERE DeliveryOrderServiceID = '"+QString::number(id)+"' ORDER BY DeliveryOrderServiceID ASC "));
while (query.next()) {
deliveryorderservice = new DeliveryOrderService(query.value(0).toInt(),query.value(1).toInt(),query.value(2).toInt(),query.value(3).toInt(),query.value(4).toInt(),query.value(5).toString(),query.value(6).toString());
 }

}
return deliveryorderservice;
}

DeliveryOrderService* DeliveryOrderService::get(const QModelIndex &index) {
QModelIndex primaryKeyIndex = QSqlRelationalTableModel::index(index.row(), 0); 
 if(data(primaryKeyIndex).toInt() != 0) 
 return Get(data(primaryKeyIndex).toInt());
else return new DeliveryOrderService();
}

DeliveryOrderService* DeliveryOrderService::Get(QString name) {
DeliveryOrderService* deliveryorderservice = new DeliveryOrderService();
if(name != NULL) {
QSqlQuery query = (ErpModel::GetInstance()->qeryExec("SELECT *  FROM DeliveryOrderService WHERE DeliveryOrderID = QString::number("+name+")"));
while (query.next()) {
deliveryorderservice = new DeliveryOrderService(query.value(0).toInt(),query.value(1).toInt(),query.value(2).toInt(),query.value(3).toInt(),query.value(4).toInt(),query.value(5).toString(),query.value(6).toString());

 }

}
return deliveryorderservice;
 }

QList<DeliveryOrderService*> DeliveryOrderService::Search(QString keyword) {
QList<DeliveryOrderService*>list;
if(keyword != NULL) {
QSqlQuery query = (ErpModel::GetInstance()->qeryExec("SELECT *  FROM DeliveryOrderService"
"WHERE" 
"CreatedOn LIKE '%"+keyword+"%'"
"OR EditedOn LIKE '%"+keyword+"%'"
));
while (query.next()) {
list.append(new DeliveryOrderService(query.value(0).toInt(),query.value(1).toInt(),query.value(2).toInt(),query.value(3).toInt(),query.value(4).toInt(),query.value(5).toString(),query.value(6).toString()));
 }

}
return list;
 }

QList<QString> DeliveryOrderService::GetStringList() {
	QList<QString> list;
	QList<DeliveryOrderService*> deliveryorderservices =   QList<DeliveryOrderService*>();
deliveryorderservices = GetAll();
	for(int i = 0; i <deliveryorderservices.count(); i++){
	}
	return list;
}

QList<QPair< int,QString > > DeliveryOrderService::GetPairList() {
	QList<QPair<int,QString > > list;
	QList<DeliveryOrderService*> deliveryorderservices =   QList<DeliveryOrderService*>();
deliveryorderservices = GetAll();
	for(int i = 0; i <deliveryorderservices.count(); i++){
		list.append(qMakePair(deliveryorderservices[i]->DeliveryOrderServiceID,QString::number(deliveryorderservices[i]->DeliveryOrderID)));
	}
	return list;
}

QList<QPair< int,QString > > DeliveryOrderService::GetPairList(QList<DeliveryOrderService*> deliveryorderservices) {
	QList<QPair<int,QString > > list;
	for(int i = 0; i <deliveryorderservices.count(); i++){
		list.append(qMakePair(deliveryorderservices[i]->DeliveryOrderServiceID,QString::number(deliveryorderservices[i]->DeliveryOrderID)));
	}
	return list;
}

int DeliveryOrderService::GetIndex(QString name) {
	QList<DeliveryOrderService*> deliveryorderservices =   QList<DeliveryOrderService*>();
deliveryorderservices = GetAll();
	for(int i = 0; i <deliveryorderservices.count(); i++){
		if(deliveryorderservices[i]->DeliveryOrderID == name.toInt()){
			return i;
		}
	}
	return 0;
}

QList<DeliveryOrderService*> DeliveryOrderService::QuerySelect(QString select) {
QList<DeliveryOrderService*>list;
if(select != NULL) {
QSqlQuery query = (ErpModel::GetInstance()->qeryExec("SELECT *  FROM DeliveryOrderService WHERE "+select+"" ));
while (query.next()) {
list.append(new DeliveryOrderService(query.value(0).toInt(),query.value(1).toInt(),query.value(2).toInt(),query.value(3).toInt(),query.value(4).toInt(),query.value(5).toString(),query.value(6).toString()));
 }

}
return list;
 }

Qt::ItemFlags DeliveryOrderService::flags(const QModelIndex &index) const {
Qt::ItemFlags flags = QSqlRelationalTableModel::flags(index);
flags ^= Qt::ItemIsEditable;
if (
index.column() == 1 || index.column() == 2 || index.column() == 3 || index.column() == 4 || index.column() == 5 || index.column() == 6)
flags |= Qt::ItemIsEditable;
return flags;
}

bool DeliveryOrderService::setData(const QModelIndex &index, const QVariant &value, int /* role */) {
	if (index.column() < 1)
		return false;
QModelIndex primaryKeyIndex = QSqlRelationalTableModel::index(index.row(), 0);
int id = data(primaryKeyIndex).toInt();
bool ok = true;
if((data(QSqlRelationalTableModel::index(index.row(), index.column())).toString() != value.toString().toLower())){
if (index.column() == 1)
ok = setDeliveryOrderID(id, value.toString());
else if (index.column() == 2)
ok = setServiceID(id, value.toString());
else if (index.column() == 3)
ok = setAmount(id, value.toString());
else if (index.column() == 4)
ok = setPrice(id, value.toString());
else if (index.column() == 5)
ok = setCreatedOn(id, value.toString());
else if (index.column() == 6)
ok = setEditedOn(id, value.toString());
refresh();
}
return ok;
}

bool DeliveryOrderService::remove(const QModelIndex &index) {
QModelIndex primaryKeyIndex = QSqlRelationalTableModel::index(index.row(), 0);
bool ok = true;
this->DeliveryOrderServiceID = data(primaryKeyIndex).toInt();
ok = this->remove();
refresh();
return ok;
}

void DeliveryOrderService::refresh() {
if(!ErpModel::GetInstance()->db.isOpen()&&!ErpModel::GetInstance()->db.open())
qDebug() <<"Couldn't open DataBase at Refresh() DeliveryOrderService!";
this->setHeaderData(1, Qt::Horizontal, QObject::tr("Delivery Order"));
this->setHeaderData(2, Qt::Horizontal, QObject::tr("Service"));
this->setHeaderData(3, Qt::Horizontal, QObject::tr("Amount"));
this->setHeaderData(4, Qt::Horizontal, QObject::tr("Price"));
this->setHeaderData(5, Qt::Horizontal, QObject::tr("Created On"));
this->setHeaderData(6, Qt::Horizontal, QObject::tr("Edited On"));
	this->select();
//	if(ErpModel::GetInstance()->db.isOpen())
//		ErpModel::GetInstance()->db.close();
}
bool DeliveryOrderService::setDeliveryOrderID(int DeliveryOrderServiceID, const QString &DeliveryOrderID) {
QSqlQuery query;
query.prepare("update DeliveryOrderService set DeliveryOrderID = ? where DeliveryOrderServiceID = ?");
query.addBindValue(DeliveryOrderID);
query.addBindValue(DeliveryOrderServiceID);
if( !query.exec() )
qDebug() << query.lastError().text();
return true;
}
bool DeliveryOrderService::setServiceID(int DeliveryOrderServiceID, const QString &ServiceID) {
QSqlQuery query;
query.prepare("update DeliveryOrderService set ServiceID = ? where DeliveryOrderServiceID = ?");
query.addBindValue(ServiceID);
query.addBindValue(DeliveryOrderServiceID);
if( !query.exec() )
qDebug() << query.lastError().text();
return true;
}
bool DeliveryOrderService::setAmount(int DeliveryOrderServiceID, const QString &Amount) {
QSqlQuery query;
query.prepare("update DeliveryOrderService set Amount = ? where DeliveryOrderServiceID = ?");
query.addBindValue(Amount);
query.addBindValue(DeliveryOrderServiceID);
if( !query.exec() )
qDebug() << query.lastError().text();
return true;
}
bool DeliveryOrderService::setPrice(int DeliveryOrderServiceID, const QString &Price) {
QSqlQuery query;
query.prepare("update DeliveryOrderService set Price = ? where DeliveryOrderServiceID = ?");
query.addBindValue(Price);
query.addBindValue(DeliveryOrderServiceID);
if( !query.exec() )
qDebug() << query.lastError().text();
return true;
}
bool DeliveryOrderService::setCreatedOn(int DeliveryOrderServiceID, const QString &CreatedOn) {
QSqlQuery query;
query.prepare("update DeliveryOrderService set CreatedOn = ? where DeliveryOrderServiceID = ?");
query.addBindValue(CreatedOn);
query.addBindValue(DeliveryOrderServiceID);
if( !query.exec() )
qDebug() << query.lastError().text();
return true;
}
bool DeliveryOrderService::setEditedOn(int DeliveryOrderServiceID, const QString &EditedOn) {
QSqlQuery query;
query.prepare("update DeliveryOrderService set EditedOn = ? where DeliveryOrderServiceID = ?");
query.addBindValue(EditedOn);
query.addBindValue(DeliveryOrderServiceID);
if( !query.exec() )
qDebug() << query.lastError().text();
return true;
}

