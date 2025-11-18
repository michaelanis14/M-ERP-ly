/**************************************************************************
**   File: product.cpp
**   Created on: Thu Dec 18 12:57:58 EET 2014
**   Author: Michael Bishara
**   Copyright: SphinxSolutions.
**************************************************************************/
#include "product.h"
#include "erpmodel.h"

Product::Product()
 : QSqlRelationalTableModel(){

this->ProductID = 0 ;
this->Name = "";
this->ShortDescription = "";
this->UnitID = 0 ;
this->SellingPrice = 0 ;
this->NetCoast = 0 ;
this->TradeMarginRate = 0 ;
this->TaxID = 0 ;
this->information = "";
this->Barcode = "";
this->ProductCategoryID = 0 ;
this->CriticalAmount = 0 ;
this->CreatedOn = "";
this->EditedOn = "";
this->setTable("Product");
this->setEditStrategy(QSqlTableModel::OnManualSubmit);
this->setRelation(3, QSqlRelation("Unit", "UnitID", "Description"));
this->setRelation(7, QSqlRelation("Tax", "TaxID", "Title"));
this->setRelation(10, QSqlRelation("ProductCategory", "ProductCategoryID", "Description"));
}
Product::Product(int ProductID,QString Name,QString ShortDescription,int UnitID,double SellingPrice,double NetCoast,double TradeMarginRate,int TaxID,QString information,QString Barcode,int ProductCategoryID,double CriticalAmount,QString CreatedOn,QString EditedOn) : QSqlRelationalTableModel(){
this->ProductID = ProductID ;
this->Name = Name ;
this->ShortDescription = ShortDescription ;
this->UnitID = UnitID ;
this->SellingPrice = SellingPrice ;
this->NetCoast = NetCoast ;
this->TradeMarginRate = TradeMarginRate ;
this->TaxID = TaxID ;
this->information = information ;
this->Barcode = Barcode ;
this->ProductCategoryID = ProductCategoryID ;
this->CriticalAmount = CriticalAmount ;
this->CreatedOn = CreatedOn ;
this->EditedOn = EditedOn ;
}

Product::Product(QString Name,QString ShortDescription,int UnitID,double SellingPrice,double NetCoast,double TradeMarginRate,int TaxID,QString information,QString Barcode,int ProductCategoryID,double CriticalAmount,QString CreatedOn,QString EditedOn) : QSqlRelationalTableModel(){
this->ProductID = 0 ;
this->Name = Name ;
this->ShortDescription = ShortDescription ;
this->UnitID = UnitID ;
this->SellingPrice = SellingPrice ;
this->NetCoast = NetCoast ;
this->TradeMarginRate = TradeMarginRate ;
this->TaxID = TaxID ;
this->information = information ;
this->Barcode = Barcode ;
this->ProductCategoryID = ProductCategoryID ;
this->CriticalAmount = CriticalAmount ;
this->CreatedOn = CreatedOn ;
this->EditedOn = EditedOn ;
}

bool Product::Init()
{

QString table = "Product";
QString query =
"(ProductID INT NOT NULL AUTO_INCREMENT, "
"PRIMARY KEY (ProductID),"
"Name VARCHAR(40) NOT NULL, "
" KEY(Name),"
"ShortDescription VARCHAR(40) NOT NULL, "
"UnitID INT NOT NULL, "
"FOREIGN KEY (UnitID) REFERENCES Unit(UnitID)  ON DELETE CASCADE,"
"SellingPrice DECIMAL(6,2) NOT NULL, "
"NetCoast DECIMAL(6,2) NOT NULL, "
"TradeMarginRate DECIMAL(6,2) NOT NULL, "
"TaxID INT NOT NULL, "
"FOREIGN KEY (TaxID) REFERENCES Tax(TaxID)  ON DELETE CASCADE,"
"information VARCHAR(40) NOT NULL, "
"Barcode VARCHAR(40) NOT NULL, "
"ProductCategoryID INT NOT NULL, "
"FOREIGN KEY (ProductCategoryID) REFERENCES ProductCategory(ProductCategoryID)  ON DELETE CASCADE,"
"CriticalAmount DECIMAL(6,2) NOT NULL, "
"CreatedOn VARCHAR(40) NOT NULL, "
"EditedOn VARCHAR(40) NOT NULL, KEY(EditedOn) )" ;

QList<QPair<QString,QString> >variables;
variables.append(qMakePair(QString(" INT"),QString("ProductID")));variables.append(qMakePair(QString(" VARCHAR(40)"),QString("Name")));variables.append(qMakePair(QString(" VARCHAR(40)"),QString("ShortDescription")));variables.append(qMakePair(QString(" INT"),QString("UnitID")));variables.append(qMakePair(QString(" DECIMAL(6,2)"),QString("SellingPrice")));variables.append(qMakePair(QString(" DECIMAL(6,2)"),QString("NetCoast")));variables.append(qMakePair(QString(" DECIMAL(6,2)"),QString("TradeMarginRate")));variables.append(qMakePair(QString(" INT"),QString("TaxID")));variables.append(qMakePair(QString(" VARCHAR(40)"),QString("information")));variables.append(qMakePair(QString(" VARCHAR(40)"),QString("Barcode")));variables.append(qMakePair(QString(" INT"),QString("ProductCategoryID")));variables.append(qMakePair(QString(" DECIMAL(6,2)"),QString("CriticalAmount")));variables.append(qMakePair(QString(" VARCHAR(40)"),QString("CreatedOn")));variables.append(qMakePair(QString(" VARCHAR(40)"),QString("EditedOn")));ErpModel::GetInstance()->createTable(table,query,variables);
return true;
}
Product* Product::p_instance = 0;
Product* Product::GetInstance() {
	if (p_instance == 0) {
		p_instance = new Product();
		Product::GetAll();
	}
return p_instance;
}
bool Product::save() {
this->EditedOn = QDate::currentDate().toString();
if(ProductID== 0) {
this->CreatedOn = QDate::currentDate().toString();
ErpModel::GetInstance()->qeryExec("INSERT INTO Product (Name,ShortDescription,UnitID,SellingPrice,NetCoast,TradeMarginRate,TaxID,information,Barcode,ProductCategoryID,CriticalAmount,CreatedOn,EditedOn)"
"VALUES ('" +QString(this->Name)+"','"+QString(this->ShortDescription)+"','"+QString::number(this->UnitID)+"','"+QString::number(this->SellingPrice)+"','"+QString::number(this->NetCoast)+"','"+QString::number(this->TradeMarginRate)+"','"+QString::number(this->TaxID)+"','"+QString(this->information)+"','"+QString(this->Barcode)+"','"+QString::number(this->ProductCategoryID)+"','"+QString::number(this->CriticalAmount)+"','"+QString(this->CreatedOn)+"','"+QString(this->EditedOn)+"')");
}else {
ErpModel::GetInstance()->qeryExec("UPDATE Product SET "	"Name = '"+QString(this->Name)+"',"+"ShortDescription = '"+QString(this->ShortDescription)+"',"+"UnitID = '"+QString::number(this->UnitID)+"',"+"SellingPrice = '"+QString::number(this->SellingPrice)+"',"+"NetCoast = '"+QString::number(this->NetCoast)+"',"+"TradeMarginRate = '"+QString::number(this->TradeMarginRate)+"',"+"TaxID = '"+QString::number(this->TaxID)+"',"+"information = '"+QString(this->information)+"',"+"Barcode = '"+QString(this->Barcode)+"',"+"ProductCategoryID = '"+QString::number(this->ProductCategoryID)+"',"+"CriticalAmount = '"+QString::number(this->CriticalAmount)+"',"+"CreatedOn = '"+QString(this->CreatedOn)+"',"+"EditedOn = '"+QString(this->EditedOn)+"' WHERE ProductID ='"+QString::number(this->ProductID)+"'");
 }QSqlQuery query = ErpModel::GetInstance()->qeryExec("SELECT  ProductID FROM Product WHERE Name = '"+Name+"' AND EditedOn = '"+this->EditedOn+"'"  );
while (query.next()) {
 if(query.value(0).toInt() != 0){
 this->ProductID = query.value(0).toInt();
 }
 }
return true;
}
bool Product::save(QSqlRecord &record) {
	if(ErpModel::GetInstance()->db.open())
 if(this->insertRowIntoTable(record))
 return true;
 return false;
}

bool Product::remove() {
if(ProductID!= 0) {
(ErpModel::GetInstance()->qeryExec("DELETE FROM Product WHERE ProductID ="+QString::number(this->ProductID)+""));
return true;
 }
return false;
}

Product* Product::get() {
if(ProductID!= 0) {
QSqlQuery query = (ErpModel::GetInstance()->qeryExec("SELECT * FROM Product"
"WHERE ProductID ='"+QString::number(this->ProductID)+"'"));
while (query.next()) {
return new Product(query.value(0).toInt(),query.value(1).toString(),query.value(2).toString(),query.value(3).toInt(),query.value(4).toInt(),query.value(5).toInt(),query.value(6).toInt(),query.value(7).toInt(),query.value(8).toString(),query.value(9).toString(),query.value(10).toInt(),query.value(11).toInt(),query.value(12).toString(),query.value(13).toString());
 }

}
return new Product();
 }

QList<Product*> Product::GetAll() {
	QList<Product*> products =   QList<Product*>();
	QSqlQuery query = (ErpModel::GetInstance()->qeryExec("SELECT *  FROM Product ORDER BY ProductID ASC"));
	while (query.next()) {
products.append(new Product(query.value(0).toInt(),query.value(1).toString(),query.value(2).toString(),query.value(3).toInt(),query.value(4).toInt(),query.value(5).toInt(),query.value(6).toInt(),query.value(7).toInt(),query.value(8).toString(),query.value(9).toString(),query.value(10).toInt(),query.value(11).toInt(),query.value(12).toString(),query.value(13).toString()));
	}
	return products;
}

Product* Product::Get(int id) {
Product* product = new Product();
if(id != 0) {
QSqlQuery query = (ErpModel::GetInstance()->qeryExec("SELECT * FROM Product WHERE ProductID = '"+QString::number(id)+"' ORDER BY ProductID ASC "));
while (query.next()) {
product = new Product(query.value(0).toInt(),query.value(1).toString(),query.value(2).toString(),query.value(3).toInt(),query.value(4).toInt(),query.value(5).toInt(),query.value(6).toInt(),query.value(7).toInt(),query.value(8).toString(),query.value(9).toString(),query.value(10).toInt(),query.value(11).toInt(),query.value(12).toString(),query.value(13).toString());
 }
product->productimages = ProductImage::QuerySelect("ProductID = " + QString::number(id));

}
return product;
}

Product* Product::get(const QModelIndex &index) {
QModelIndex primaryKeyIndex = QSqlRelationalTableModel::index(index.row(), 0);
 if(data(primaryKeyIndex).toInt() != 0)
 return Get(data(primaryKeyIndex).toInt());
else return new Product();
}

Product* Product::Get(QString name) {
Product* product = new Product();
if(name != NULL) {
QSqlQuery query = (ErpModel::GetInstance()->qeryExec("SELECT *  FROM Product WHERE Name = '"+name+"'"));
while (query.next()) {
product = new Product(query.value(0).toInt(),query.value(1).toString(),query.value(2).toString(),query.value(3).toInt(),query.value(4).toInt(),query.value(5).toInt(),query.value(6).toInt(),query.value(7).toInt(),query.value(8).toString(),query.value(9).toString(),query.value(10).toInt(),query.value(11).toInt(),query.value(12).toString(),query.value(13).toString());

 }
product->productimages = ProductImage::QuerySelect("ProductID = " +QString::number(product->ProductID));

}
return product;
 }

QList<Product*> Product::Search(QString keyword) {
QList<Product*>list;
if(keyword != NULL) {
QSqlQuery query = (ErpModel::GetInstance()->qeryExec("SELECT *  FROM Product"
"WHERE"
"Name LIKE '%"+keyword+"%'"
"OR ShortDescription LIKE '%"+keyword+"%'"
"OR information LIKE '%"+keyword+"%'"
"OR Barcode LIKE '%"+keyword+"%'"
"OR CreatedOn LIKE '%"+keyword+"%'"
"OR EditedOn LIKE '%"+keyword+"%'"
));
while (query.next()) {
list.append(new Product(query.value(0).toInt(),query.value(1).toString(),query.value(2).toString(),query.value(3).toInt(),query.value(4).toInt(),query.value(5).toInt(),query.value(6).toInt(),query.value(7).toInt(),query.value(8).toString(),query.value(9).toString(),query.value(10).toInt(),query.value(11).toInt(),query.value(12).toString(),query.value(13).toString()));
 }

}
return list;
 }

QList<QString> Product::GetStringList() {
	QList<QString> list;
	QList<Product*> products =   QList<Product*>();
products = GetAll();
	for(int i = 0; i <products.count(); i++){
		list.append(products[i]->Name);
	}
	return list;
}

QList<QPair< int,QString > > Product::GetPairList() {
	QList<QPair<int,QString > > list;
	QList<Product*> products =   QList<Product*>();
products = GetAll();
	for(int i = 0; i <products.count(); i++){
		list.append(qMakePair(products[i]->ProductID,products[i]->Name));
	}
	return list;
}

QList<QPair< int,QString > > Product::GetPairList(QList<Product*> products) {
	QList<QPair<int,QString > > list;
	for(int i = 0; i <products.count(); i++){
		list.append(qMakePair(products[i]->ProductID,products[i]->Name));
	}
	return list;
}

int Product::GetIndex(QString name) {
	QList<Product*> products =   QList<Product*>();
products = GetAll();
	for(int i = 0; i <products.count(); i++){
		if(products[i]->Name == name){
			return i;
		}
	}
	return 0;
}

QList<Product*> Product::QuerySelect(QString select) {
QList<Product*>list;
if(select != NULL) {
QSqlQuery query = (ErpModel::GetInstance()->qeryExec("SELECT *  FROM Product WHERE "+select+"" ));
while (query.next()) {
list.append(new Product(query.value(0).toInt(),query.value(1).toString(),query.value(2).toString(),query.value(3).toInt(),query.value(4).toInt(),query.value(5).toInt(),query.value(6).toInt(),query.value(7).toInt(),query.value(8).toString(),query.value(9).toString(),query.value(10).toInt(),query.value(11).toInt(),query.value(12).toString(),query.value(13).toString()));
 }

}
return list;
 }

Qt::ItemFlags Product::flags(const QModelIndex &index) const {
Qt::ItemFlags flags = QSqlRelationalTableModel::flags(index);
flags ^= Qt::ItemIsEditable;
if (
index.column() == 1 || index.column() == 2 || index.column() == 3 || index.column() == 4 || index.column() == 5 || index.column() == 6 || index.column() == 7 || index.column() == 8 || index.column() == 9 || index.column() == 10 || index.column() == 11 || index.column() == 13 || index.column() == 14)
flags |= Qt::ItemIsEditable;
return flags;
}

bool Product::setData(const QModelIndex &index, const QVariant &value, int /* role */) {
	if (index.column() < 1)
		return false;
QModelIndex primaryKeyIndex = QSqlRelationalTableModel::index(index.row(), 0);
int id = data(primaryKeyIndex).toInt();
bool ok = true;
if((data(QSqlRelationalTableModel::index(index.row(), index.column())).toString() != value.toString().toLower())){
if (index.column() == 1)
ok = setName(id, value.toString());
else if (index.column() == 2)
ok = setShortDescription(id, value.toString());
else if (index.column() == 3)
ok = setUnitID(id, value.toString());
else if (index.column() == 4)
ok = setSellingPrice(id, value.toString());
else if (index.column() == 5)
ok = setNetCoast(id, value.toString());
else if (index.column() == 6)
ok = setTradeMarginRate(id, value.toString());
else if (index.column() == 7)
ok = setTaxID(id, value.toString());
else if (index.column() == 8)
ok = setinformation(id, value.toString());
else if (index.column() == 9)
ok = setBarcode(id, value.toString());
else if (index.column() == 10)
ok = setProductCategoryID(id, value.toString());
else if (index.column() == 11)
ok = setCriticalAmount(id, value.toString());
else if (index.column() == 13)
ok = setCreatedOn(id, value.toString());
else if (index.column() == 14)
ok = setEditedOn(id, value.toString());
refresh();
}
return ok;
}

bool Product::remove(const QModelIndex &index) {
QModelIndex primaryKeyIndex = QSqlRelationalTableModel::index(index.row(), 0);
bool ok = true;
this->ProductID = data(primaryKeyIndex).toInt();
ok = this->remove();
refresh();
return ok;
}

void Product::refresh() {
if(!ErpModel::GetInstance()->db.isOpen()&&!ErpModel::GetInstance()->db.open())
qDebug() <<"Couldn't open DataBase at Refresh() Product!";
this->setHeaderData(1, Qt::Horizontal, QObject::tr("Name"));
this->setHeaderData(2, Qt::Horizontal, QObject::tr("Short Description"));
this->setHeaderData(3, Qt::Horizontal, QObject::tr("Unit"));
this->setHeaderData(4, Qt::Horizontal, QObject::tr("Selling Price"));
this->setHeaderData(5, Qt::Horizontal, QObject::tr("Net Coast"));
this->setHeaderData(6, Qt::Horizontal, QObject::tr("Trade Margin Rate"));
this->setHeaderData(7, Qt::Horizontal, QObject::tr("Tax"));
this->setHeaderData(8, Qt::Horizontal, QObject::tr("information"));
this->setHeaderData(9, Qt::Horizontal, QObject::tr("Barcode"));
this->setHeaderData(10, Qt::Horizontal, QObject::tr("Product Category"));
this->setHeaderData(11, Qt::Horizontal, QObject::tr("Critical Amount"));
this->setHeaderData(13, Qt::Horizontal, QObject::tr("Created On"));
this->setHeaderData(14, Qt::Horizontal, QObject::tr("Edited On"));
	this->select();
//	if(ErpModel::GetInstance()->db.isOpen())
//		ErpModel::GetInstance()->db.close();
}
bool Product::setName(int ProductID, const QString &Name) {
QSqlQuery query;
query.prepare("update Product set Name = ? where ProductID = ?");
query.addBindValue(Name);
query.addBindValue(ProductID);
if( !query.exec() )
qDebug() << query.lastError().text();
return true;
}
bool Product::setShortDescription(int ProductID, const QString &ShortDescription) {
QSqlQuery query;
query.prepare("update Product set ShortDescription = ? where ProductID = ?");
query.addBindValue(ShortDescription);
query.addBindValue(ProductID);
if( !query.exec() )
qDebug() << query.lastError().text();
return true;
}
bool Product::setUnitID(int ProductID, const QString &UnitID) {
QSqlQuery query;
query.prepare("update Product set UnitID = ? where ProductID = ?");
query.addBindValue(UnitID);
query.addBindValue(ProductID);
if( !query.exec() )
qDebug() << query.lastError().text();
return true;
}
bool Product::setSellingPrice(int ProductID, const QString &SellingPrice) {
QSqlQuery query;
query.prepare("update Product set SellingPrice = ? where ProductID = ?");
query.addBindValue(SellingPrice);
query.addBindValue(ProductID);
if( !query.exec() )
qDebug() << query.lastError().text();
return true;
}
bool Product::setNetCoast(int ProductID, const QString &NetCoast) {
QSqlQuery query;
query.prepare("update Product set NetCoast = ? where ProductID = ?");
query.addBindValue(NetCoast);
query.addBindValue(ProductID);
if( !query.exec() )
qDebug() << query.lastError().text();
return true;
}
bool Product::setTradeMarginRate(int ProductID, const QString &TradeMarginRate) {
QSqlQuery query;
query.prepare("update Product set TradeMarginRate = ? where ProductID = ?");
query.addBindValue(TradeMarginRate);
query.addBindValue(ProductID);
if( !query.exec() )
qDebug() << query.lastError().text();
return true;
}
bool Product::setTaxID(int ProductID, const QString &TaxID) {
QSqlQuery query;
query.prepare("update Product set TaxID = ? where ProductID = ?");
query.addBindValue(TaxID);
query.addBindValue(ProductID);
if( !query.exec() )
qDebug() << query.lastError().text();
return true;
}
bool Product::setinformation(int ProductID, const QString &information) {
QSqlQuery query;
query.prepare("update Product set information = ? where ProductID = ?");
query.addBindValue(information);
query.addBindValue(ProductID);
if( !query.exec() )
qDebug() << query.lastError().text();
return true;
}
bool Product::setBarcode(int ProductID, const QString &Barcode) {
QSqlQuery query;
query.prepare("update Product set Barcode = ? where ProductID = ?");
query.addBindValue(Barcode);
query.addBindValue(ProductID);
if( !query.exec() )
qDebug() << query.lastError().text();
return true;
}
bool Product::setProductCategoryID(int ProductID, const QString &ProductCategoryID) {
QSqlQuery query;
query.prepare("update Product set ProductCategoryID = ? where ProductID = ?");
query.addBindValue(ProductCategoryID);
query.addBindValue(ProductID);
if( !query.exec() )
qDebug() << query.lastError().text();
return true;
}
bool Product::setCriticalAmount(int ProductID, const QString &CriticalAmount) {
QSqlQuery query;
query.prepare("update Product set CriticalAmount = ? where ProductID = ?");
query.addBindValue(CriticalAmount);
query.addBindValue(ProductID);
if( !query.exec() )
qDebug() << query.lastError().text();
return true;
}
bool Product::setCreatedOn(int ProductID, const QString &CreatedOn) {
QSqlQuery query;
query.prepare("update Product set CreatedOn = ? where ProductID = ?");
query.addBindValue(CreatedOn);
query.addBindValue(ProductID);
if( !query.exec() )
qDebug() << query.lastError().text();
return true;
}
bool Product::setEditedOn(int ProductID, const QString &EditedOn) {
QSqlQuery query;
query.prepare("update Product set EditedOn = ? where ProductID = ?");
query.addBindValue(EditedOn);
query.addBindValue(ProductID);
if( !query.exec() )
qDebug() << query.lastError().text();
return true;
}

bool Product::saveSecure() {
	this->EditedOn = QDate::currentDate().toString();

	if(ProductID == 0) {
		this->CreatedOn = QDate::currentDate().toString();

		QVariantList values;
		values << Name << ShortDescription << UnitID << SellingPrice << NetCoast
		       << TradeMarginRate << TaxID << information << Barcode
		       << ProductCategoryID << CriticalAmount << CreatedOn << EditedOn;

		QSqlQuery insertQuery = ErpModel::GetInstance()->execPreparedQuery(
			"INSERT INTO Product (Name, ShortDescription, UnitID, SellingPrice, NetCoast, "
			"TradeMarginRate, TaxID, information, Barcode, ProductCategoryID, CriticalAmount, "
			"CreatedOn, EditedOn) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)",
			values
		);

		QVariantList selectValues;
		selectValues << Name << EditedOn;
		QSqlQuery query = ErpModel::GetInstance()->execPreparedQuery(
			"SELECT ProductID FROM Product WHERE Name = ? AND EditedOn = ?",
			selectValues
		);

		while (query.next()) {
			if(query.value(0).toInt() != 0){
				this->ProductID = query.value(0).toInt();
			}
		}
	} else {
		QVariantList values;
		values << Name << ShortDescription << UnitID << SellingPrice << NetCoast
		       << TradeMarginRate << TaxID << information << Barcode
		       << ProductCategoryID << CriticalAmount << CreatedOn << EditedOn << ProductID;

		ErpModel::GetInstance()->execPreparedQuery(
			"UPDATE Product SET Name = ?, ShortDescription = ?, UnitID = ?, SellingPrice = ?, "
			"NetCoast = ?, TradeMarginRate = ?, TaxID = ?, information = ?, Barcode = ?, "
			"ProductCategoryID = ?, CriticalAmount = ?, CreatedOn = ?, EditedOn = ? "
			"WHERE ProductID = ?",
			values
		);
	}

	return true;
}

Product* Product::GetSecure(int id) {
	Product* product = new Product();
	if(id != 0) {
		QVariantList values;
		values << id;

		QSqlQuery query = ErpModel::GetInstance()->execPreparedQuery(
			"SELECT * FROM Product WHERE ProductID = ? ORDER BY ProductID ASC",
			values
		);

		while (query.next()) {
			product = new Product(
				query.value(0).toInt(), query.value(1).toString(), query.value(2).toString(),
				query.value(3).toInt(), query.value(4).toDouble(), query.value(5).toDouble(),
				query.value(6).toDouble(), query.value(7).toInt(), query.value(8).toString(),
				query.value(9).toString(), query.value(10).toInt(), query.value(11).toDouble(),
				query.value(12).toString(), query.value(13).toString()
			);
		}

		product->productimages = ProductImage::QuerySelect("ProductID = " + QString::number(id));
	}
	return product;
}

Product* Product::GetSecure(const QString &name) {
	Product* product = new Product();
	if(!name.isEmpty()) {
		QVariantList values;
		values << name;

		QSqlQuery query = ErpModel::GetInstance()->execPreparedQuery(
			"SELECT * FROM Product WHERE Name = ?",
			values
		);

		while (query.next()) {
			product = new Product(
				query.value(0).toInt(), query.value(1).toString(), query.value(2).toString(),
				query.value(3).toInt(), query.value(4).toDouble(), query.value(5).toDouble(),
				query.value(6).toDouble(), query.value(7).toInt(), query.value(8).toString(),
				query.value(9).toString(), query.value(10).toInt(), query.value(11).toDouble(),
				query.value(12).toString(), query.value(13).toString()
			);
		}

		product->productimages = ProductImage::QuerySelect("ProductID = " + QString::number(product->ProductID));
	}
	return product;
}

QList<Product*> Product::SearchSecure(const QString &keyword) {
	QList<Product*> list;
	if(!keyword.isEmpty()) {
		QString likePattern = "%" + keyword + "%";
		QVariantList values;
		for(int i = 0; i < 6; i++) {
			values << likePattern;
		}

		QSqlQuery query = ErpModel::GetInstance()->execPreparedQuery(
			"SELECT * FROM Product WHERE "
			"Name LIKE ? OR ShortDescription LIKE ? OR information LIKE ? OR "
			"Barcode LIKE ? OR CreatedOn LIKE ? OR EditedOn LIKE ?",
			values
		);

		while (query.next()) {
			list.append(new Product(
				query.value(0).toInt(), query.value(1).toString(), query.value(2).toString(),
				query.value(3).toInt(), query.value(4).toDouble(), query.value(5).toDouble(),
				query.value(6).toDouble(), query.value(7).toInt(), query.value(8).toString(),
				query.value(9).toString(), query.value(10).toInt(), query.value(11).toDouble(),
				query.value(12).toString(), query.value(13).toString()
			));
		}
	}
	return list;
}

bool Product::removeSecure() {
	if(ProductID != 0) {
		QVariantList values;
		values << ProductID;

		ErpModel::GetInstance()->execPreparedQuery(
			"DELETE FROM Product WHERE ProductID = ?",
			values
		);
		return true;
	}
	return false;
}

