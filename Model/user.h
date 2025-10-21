/**************************************************************************
**   File: user.h
**   Created on: Thu Dec 18 12:57:58 EET 2014
**   Author: Michael Bishara
**   Copyright: SphinxSolutions.
**************************************************************************/
#ifndef USER_H
#define USER_H

#include <QSqlRelationalTableModel>
#include <QSqlError>
#include <QtGui>

class User  : public QSqlRelationalTableModel
{
	Q_OBJECT
public:
	User();
	User(QString Name,QString UserName,QString Password,int LanguageID,int ContactID,QString CreatedOn,QString EditedOn);	int UserID;
	QString Name;
	QString UserName;
	QString Password;
	int LanguageID;
	int ContactID;
	QString CreatedOn;
	QString EditedOn;
	static bool Init();
	bool save();
	bool save(QSqlRecord &record);
	bool remove();
	User* get();
	User* get(const QModelIndex &index);
	static User* Get(int id);
	static User* Get(QString name);
	static QList<User*> GetAll();
	static QList<User*> Search(QString keyword);
	static QList<User*> QuerySelect(QString select);
	static QList<QString> GetStringList();
	static QList<QPair< int,QString > > GetPairList();
	static QList<QPair< int,QString > > GetPairList(QList<User*> users);
	static int GetIndex(QString title);
	static User* GetInstance();
	Qt::ItemFlags flags(const QModelIndex &index) const;
	bool setData(const QModelIndex &index, const QVariant &value, int role);
	void refresh();
	bool remove(const QModelIndex &index);

	static QString hashPassword(const QString &password);
	static bool verifyPassword(const QString &password, const QString &hashedPassword);
	bool saveSecure();
	static User* authenticateSecure(const QString &username, const QString &password);

private:
	User(int UserID,QString Name,QString UserName,QString Password,int LanguageID,int ContactID,QString CreatedOn,QString EditedOn);	static User* p_instance;
	bool setName(int UserID, const QString &Name);
	bool setUserName(int UserID, const QString &UserName);
	bool setPassword(int UserID, const QString &Password);
	bool setLanguageID(int UserID, const QString &LanguageID);
	bool setContactID(int UserID, const QString &ContactID);
	bool setCreatedOn(int UserID, const QString &CreatedOn);
	bool setEditedOn(int UserID, const QString &EditedOn);

};
#endif
