/*************************************
**   Created on:  9/11/2014
**   Author: michaelbishara
**   Copyright: Bishara©.
**************************************/

#ifndef ERPMODEL_H
#define ERPMODEL_H
#include "user.h"
#include "access.h"

#include <QSqlQuery>
#include <QPair>


class ErpModel
{
public:
	ErpModel();
	QSqlDatabase db;
	User* LoggedUser;
	QList<QString> toStringList(QList<QPair<int, QString> > pairList);
	QList<Access*> UserAccessList;
	static ErpModel* GetInstance();
	QSqlQuery qeryExec(QString q);
	QSqlQuery execPreparedQuery(const QString &queryStr, const QVariantList &bindValues);
	QSqlQuery execPreparedQuery(const QString &queryStr, const QMap<QString, QVariant> &bindValues);
	bool createTable(QString table,QString query,QList<QPair<QString,QString> >variables);
	bool init();
	bool ensureConnection();
private:
	static ErpModel* p_instance;
};

#endif // ERPMODEL_H
