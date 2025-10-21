/**************************************************************************
**   File: user.cpp
**   Created on: Thu Dec 18 12:57:58 EET 2014
**   Author: Michael Bishara
**   Copyright: SphinxSolutions.
**************************************************************************/
#include "user.h"
#include "erpmodel.h"
#include <QCryptographicHash>
#include <QDateTime>

User::User()
 : QSqlRelationalTableModel(){

this->UserID = 0 ;
this->Name = "";
this->UserName = "";
this->Password = "";
this->LanguageID = 0 ;
this->ContactID = 0 ;
this->CreatedOn = "";
this->EditedOn = "";
this->setTable("User");
this->setEditStrategy(QSqlTableModel::OnManualSubmit);
this->setRelation(4, QSqlRelation("Language", "LanguageID", "Title"));
this->setRelation(5, QSqlRelation("Contact", "ContactID", "Name"));
}
User::User(int UserID,QString Name,QString UserName,QString Password,int LanguageID,int ContactID,QString CreatedOn,QString EditedOn) : QSqlRelationalTableModel(){
this->UserID = UserID ;
this->Name = Name ;
this->UserName = UserName ;
this->Password = Password ;
this->LanguageID = LanguageID ;
this->ContactID = ContactID ;
this->CreatedOn = CreatedOn ;
this->EditedOn = EditedOn ;
}

User::User(QString Name,QString UserName,QString Password,int LanguageID,int ContactID,QString CreatedOn,QString EditedOn) : QSqlRelationalTableModel(){
this->UserID = 0 ;
this->Name = Name ;
this->UserName = UserName ;
this->Password = Password ;
this->LanguageID = LanguageID ;
this->ContactID = ContactID ;
this->CreatedOn = CreatedOn ;
this->EditedOn = EditedOn ;
}

bool User::Init()
{

QString table = "User";
QString query =
"(UserID INT NOT NULL AUTO_INCREMENT, "
"PRIMARY KEY (UserID),"
"Name VARCHAR(40) NOT NULL, "
" KEY(Name),"
"UserName VARCHAR(40) NOT NULL, "
"Password VARCHAR(255) NOT NULL, "
"LanguageID INT NOT NULL, "
"FOREIGN KEY (LanguageID) REFERENCES Language(LanguageID)  ON DELETE CASCADE,"
"ContactID INT NOT NULL, "
"FOREIGN KEY (ContactID) REFERENCES Contact(ContactID)  ON DELETE CASCADE,"
"CreatedOn VARCHAR(40) NOT NULL, "
"EditedOn VARCHAR(40) NOT NULL, KEY(EditedOn) )" ;

QList<QPair<QString,QString> >variables;
variables.append(qMakePair(QString(" INT"),QString("UserID")));variables.append(qMakePair(QString(" VARCHAR(40)"),QString("Name")));variables.append(qMakePair(QString(" VARCHAR(40)"),QString("UserName")));variables.append(qMakePair(QString(" VARCHAR(255)"),QString("Password")));variables.append(qMakePair(QString(" INT"),QString("LanguageID")));variables.append(qMakePair(QString(" INT"),QString("ContactID")));variables.append(qMakePair(QString(" VARCHAR(40)"),QString("CreatedOn")));variables.append(qMakePair(QString(" VARCHAR(40)"),QString("EditedOn")));ErpModel::GetInstance()->createTable(table,query,variables);
return true;
}
User* User::p_instance = 0;
User* User::GetInstance() {
	if (p_instance == 0) {
		p_instance = new User();
		User::GetAll();
	}
return p_instance;
}
bool User::save() {
this->EditedOn = QDate::currentDate().toString();
if(UserID== 0) {
this->CreatedOn = QDate::currentDate().toString();
ErpModel::GetInstance()->qeryExec("INSERT INTO User (Name,UserName,Password,LanguageID,ContactID,CreatedOn,EditedOn)"
"VALUES ('" +QString(this->Name)+"','"+QString(this->UserName)+"','"+QString(this->Password)+"','"+QString::number(this->LanguageID)+"','"+QString::number(this->ContactID)+"','"+QString(this->CreatedOn)+"','"+QString(this->EditedOn)+"')");
}else {
ErpModel::GetInstance()->qeryExec("UPDATE User SET "	"Name = '"+QString(this->Name)+"',"+"UserName = '"+QString(this->UserName)+"',"+"Password = '"+QString(this->Password)+"',"+"LanguageID = '"+QString::number(this->LanguageID)+"',"+"ContactID = '"+QString::number(this->ContactID)+"',"+"CreatedOn = '"+QString(this->CreatedOn)+"',"+"EditedOn = '"+QString(this->EditedOn)+"' WHERE UserID ='"+QString::number(this->UserID)+"'");
 }QSqlQuery query = ErpModel::GetInstance()->qeryExec("SELECT  UserID FROM User WHERE Name = '"+Name+"' AND EditedOn = '"+this->EditedOn+"'"  );
while (query.next()) { 
 if(query.value(0).toInt() != 0){ 
 this->UserID = query.value(0).toInt();	
 } 
 }
return true;
}
bool User::save(QSqlRecord &record) {
	if(ErpModel::GetInstance()->db.open()) 
 if(this->insertRowIntoTable(record)) 
 return true; 
 return false;
}

bool User::remove() {
if(UserID!= 0) {
(ErpModel::GetInstance()->qeryExec("DELETE FROM User WHERE UserID ="+QString::number(this->UserID)+""));
return true;
 }
return false;
}

User* User::get() {
if(UserID!= 0) {
QSqlQuery query = (ErpModel::GetInstance()->qeryExec("SELECT * FROM User"
"WHERE UserID ='"+QString::number(this->UserID)+"'"));
while (query.next()) {
return new User(query.value(0).toInt(),query.value(1).toString(),query.value(2).toString(),query.value(3).toString(),query.value(4).toInt(),query.value(5).toInt(),query.value(6).toString(),query.value(7).toString());
 }

}
return new User();
 }

QList<User*> User::GetAll() {
	QList<User*> users =   QList<User*>();
	QSqlQuery query = (ErpModel::GetInstance()->qeryExec("SELECT *  FROM User ORDER BY UserID ASC"));
	while (query.next()) {
users.append(new User(query.value(0).toInt(),query.value(1).toString(),query.value(2).toString(),query.value(3).toString(),query.value(4).toInt(),query.value(5).toInt(),query.value(6).toString(),query.value(7).toString()));
	}
	return users;
}

User* User::Get(int id) {
User* user = new User();
if(id != 0) {
QSqlQuery query = (ErpModel::GetInstance()->qeryExec("SELECT * FROM User WHERE UserID = '"+QString::number(id)+"' ORDER BY UserID ASC "));
while (query.next()) {
user = new User(query.value(0).toInt(),query.value(1).toString(),query.value(2).toString(),query.value(3).toString(),query.value(4).toInt(),query.value(5).toInt(),query.value(6).toString(),query.value(7).toString());
 }

}
return user;
}

User* User::get(const QModelIndex &index) {
QModelIndex primaryKeyIndex = QSqlRelationalTableModel::index(index.row(), 0); 
 if(data(primaryKeyIndex).toInt() != 0) 
 return Get(data(primaryKeyIndex).toInt());
else return new User();
}

User* User::Get(QString name) {
User* user = new User();
if(name != NULL) {
QSqlQuery query = (ErpModel::GetInstance()->qeryExec("SELECT *  FROM User WHERE Name = '"+name+"'"));
while (query.next()) {
user = new User(query.value(0).toInt(),query.value(1).toString(),query.value(2).toString(),query.value(3).toString(),query.value(4).toInt(),query.value(5).toInt(),query.value(6).toString(),query.value(7).toString());

 }

}
return user;
 }

QList<User*> User::Search(QString keyword) {
QList<User*>list;
if(keyword != NULL) {
QSqlQuery query = (ErpModel::GetInstance()->qeryExec("SELECT *  FROM User"
"WHERE" 
"Name LIKE '%"+keyword+"%'"
"OR UserName LIKE '%"+keyword+"%'"
"OR Password LIKE '%"+keyword+"%'"
"OR CreatedOn LIKE '%"+keyword+"%'"
"OR EditedOn LIKE '%"+keyword+"%'"
));
while (query.next()) {
list.append(new User(query.value(0).toInt(),query.value(1).toString(),query.value(2).toString(),query.value(3).toString(),query.value(4).toInt(),query.value(5).toInt(),query.value(6).toString(),query.value(7).toString()));
 }

}
return list;
 }

QList<QString> User::GetStringList() {
	QList<QString> list;
	QList<User*> users =   QList<User*>();
users = GetAll();
	for(int i = 0; i <users.count(); i++){
		list.append(users[i]->Name);
	}
	return list;
}

QList<QPair< int,QString > > User::GetPairList() {
	QList<QPair<int,QString > > list;
	QList<User*> users =   QList<User*>();
users = GetAll();
	for(int i = 0; i <users.count(); i++){
		list.append(qMakePair(users[i]->UserID,users[i]->Name));
	}
	return list;
}

QList<QPair< int,QString > > User::GetPairList(QList<User*> users) {
	QList<QPair<int,QString > > list;
	for(int i = 0; i <users.count(); i++){
		list.append(qMakePair(users[i]->UserID,users[i]->Name));
	}
	return list;
}

int User::GetIndex(QString name) {
	QList<User*> users =   QList<User*>();
users = GetAll();
	for(int i = 0; i <users.count(); i++){
		if(users[i]->Name == name){
			return i;
		}
	}
	return 0;
}

QList<User*> User::QuerySelect(QString select) {
QList<User*>list;
if(select != NULL) {
QSqlQuery query = (ErpModel::GetInstance()->qeryExec("SELECT *  FROM User WHERE "+select+"" ));
while (query.next()) {
list.append(new User(query.value(0).toInt(),query.value(1).toString(),query.value(2).toString(),query.value(3).toString(),query.value(4).toInt(),query.value(5).toInt(),query.value(6).toString(),query.value(7).toString()));
 }

}
return list;
 }

Qt::ItemFlags User::flags(const QModelIndex &index) const {
Qt::ItemFlags flags = QSqlRelationalTableModel::flags(index);
flags ^= Qt::ItemIsEditable;
if (
index.column() == 1 || index.column() == 2 || index.column() == 3 || index.column() == 4 || index.column() == 5 || index.column() == 6 || index.column() == 7)
flags |= Qt::ItemIsEditable;
return flags;
}

bool User::setData(const QModelIndex &index, const QVariant &value, int /* role */) {
	if (index.column() < 1)
		return false;
QModelIndex primaryKeyIndex = QSqlRelationalTableModel::index(index.row(), 0);
int id = data(primaryKeyIndex).toInt();
bool ok = true;
if((data(QSqlRelationalTableModel::index(index.row(), index.column())).toString() != value.toString().toLower())){
if (index.column() == 1)
ok = setName(id, value.toString());
else if (index.column() == 2)
ok = setUserName(id, value.toString());
else if (index.column() == 3)
ok = setPassword(id, value.toString());
else if (index.column() == 4)
ok = setLanguageID(id, value.toString());
else if (index.column() == 5)
ok = setContactID(id, value.toString());
else if (index.column() == 6)
ok = setCreatedOn(id, value.toString());
else if (index.column() == 7)
ok = setEditedOn(id, value.toString());
refresh();
}
return ok;
}

bool User::remove(const QModelIndex &index) {
QModelIndex primaryKeyIndex = QSqlRelationalTableModel::index(index.row(), 0);
bool ok = true;
this->UserID = data(primaryKeyIndex).toInt();
ok = this->remove();
refresh();
return ok;
}

void User::refresh() {
if(!ErpModel::GetInstance()->db.isOpen()&&!ErpModel::GetInstance()->db.open())
qDebug() <<"Couldn't open DataBase at Refresh() User!";
this->setHeaderData(1, Qt::Horizontal, QObject::tr("Name"));
this->setHeaderData(2, Qt::Horizontal, QObject::tr("User Name"));
this->setHeaderData(3, Qt::Horizontal, QObject::tr("Password"));
this->setHeaderData(4, Qt::Horizontal, QObject::tr("Language"));
this->setHeaderData(5, Qt::Horizontal, QObject::tr("Contact"));
this->setHeaderData(6, Qt::Horizontal, QObject::tr("Created On"));
this->setHeaderData(7, Qt::Horizontal, QObject::tr("Edited On"));
	this->select();
//	if(ErpModel::GetInstance()->db.isOpen())
//		ErpModel::GetInstance()->db.close();
}
bool User::setName(int UserID, const QString &Name) {
QSqlQuery query;
query.prepare("update User set Name = ? where UserID = ?");
query.addBindValue(Name);
query.addBindValue(UserID);
if( !query.exec() )
qDebug() << query.lastError().text();
return true;
}
bool User::setUserName(int UserID, const QString &UserName) {
QSqlQuery query;
query.prepare("update User set UserName = ? where UserID = ?");
query.addBindValue(UserName);
query.addBindValue(UserID);
if( !query.exec() )
qDebug() << query.lastError().text();
return true;
}
bool User::setPassword(int UserID, const QString &Password) {
QSqlQuery query;
query.prepare("update User set Password = ? where UserID = ?");
query.addBindValue(Password);
query.addBindValue(UserID);
if( !query.exec() )
qDebug() << query.lastError().text();
return true;
}
bool User::setLanguageID(int UserID, const QString &LanguageID) {
QSqlQuery query;
query.prepare("update User set LanguageID = ? where UserID = ?");
query.addBindValue(LanguageID);
query.addBindValue(UserID);
if( !query.exec() )
qDebug() << query.lastError().text();
return true;
}
bool User::setContactID(int UserID, const QString &ContactID) {
QSqlQuery query;
query.prepare("update User set ContactID = ? where UserID = ?");
query.addBindValue(ContactID);
query.addBindValue(UserID);
if( !query.exec() )
qDebug() << query.lastError().text();
return true;
}
bool User::setCreatedOn(int UserID, const QString &CreatedOn) {
QSqlQuery query;
query.prepare("update User set CreatedOn = ? where UserID = ?");
query.addBindValue(CreatedOn);
query.addBindValue(UserID);
if( !query.exec() )
qDebug() << query.lastError().text();
return true;
}
bool User::setEditedOn(int UserID, const QString &EditedOn) {
QSqlQuery query;
query.prepare("update User set EditedOn = ? where UserID = ?");
query.addBindValue(EditedOn);
query.addBindValue(UserID);
if( !query.exec() )
qDebug() << query.lastError().text();
return true;
}

QString User::hashPassword(const QString &password) {
	QByteArray passwordData = password.toUtf8();
	QByteArray hash = QCryptographicHash::hash(passwordData, QCryptographicHash::Sha256);
	QString salt = QDateTime::currentDateTime().toString(Qt::ISODate);
	QByteArray saltedPassword = (password + salt).toUtf8();
	QByteArray saltedHash = QCryptographicHash::hash(saltedPassword, QCryptographicHash::Sha256);
	return salt + ":" + saltedHash.toHex();
}

bool User::verifyPassword(const QString &password, const QString &hashedPassword) {
	QStringList parts = hashedPassword.split(":");
	if(parts.length() != 2) {
		return password == hashedPassword;
	}

	QString salt = parts[0];
	QString hash = parts[1];
	QByteArray saltedPassword = (password + salt).toUtf8();
	QByteArray computedHash = QCryptographicHash::hash(saltedPassword, QCryptographicHash::Sha256);

	return QString(computedHash.toHex()) == hash;
}

bool User::saveSecure() {
	this->EditedOn = QDate::currentDate().toString();

	if(UserID == 0) {
		this->CreatedOn = QDate::currentDate().toString();
		QString hashedPassword = hashPassword(this->Password);

		QVariantList values;
		values << Name << UserName << hashedPassword << LanguageID << ContactID << CreatedOn << EditedOn;

		QSqlQuery insertQuery = ErpModel::GetInstance()->execPreparedQuery(
			"INSERT INTO User (Name, UserName, Password, LanguageID, ContactID, CreatedOn, EditedOn) "
			"VALUES (?, ?, ?, ?, ?, ?, ?)",
			values
		);

		QVariantList selectValues;
		selectValues << UserName << EditedOn;
		QSqlQuery query = ErpModel::GetInstance()->execPreparedQuery(
			"SELECT UserID FROM User WHERE UserName = ? AND EditedOn = ?",
			selectValues
		);

		while (query.next()) {
			if(query.value(0).toInt() != 0){
				this->UserID = query.value(0).toInt();
			}
		}
	} else {
		QString hashedPassword = this->Password;
		if(!this->Password.contains(":")) {
			hashedPassword = hashPassword(this->Password);
		}

		QVariantList values;
		values << Name << UserName << hashedPassword << LanguageID << ContactID << CreatedOn << EditedOn << UserID;

		ErpModel::GetInstance()->execPreparedQuery(
			"UPDATE User SET Name = ?, UserName = ?, Password = ?, LanguageID = ?, "
			"ContactID = ?, CreatedOn = ?, EditedOn = ? WHERE UserID = ?",
			values
		);
	}

	return true;
}

User* User::authenticateSecure(const QString &username, const QString &password) {
	QVariantList values;
	values << username;

	QSqlQuery query = ErpModel::GetInstance()->execPreparedQuery(
		"SELECT * FROM User WHERE UserName = ?",
		values
	);

	while (query.next()) {
		QString hashedPassword = query.value(3).toString();
		if(verifyPassword(password, hashedPassword)) {
			return new User(
				query.value(0).toInt(), query.value(1).toString(), query.value(2).toString(),
				query.value(3).toString(), query.value(4).toInt(), query.value(5).toInt(),
				query.value(6).toString(), query.value(7).toString()
			);
		}
	}

	return nullptr;
}

