/**************************************************************************
**   File: invoiceperiod.h
**   Created on: Fri Dec 19 21:09:57 EET 2014
**   Author: Michael Bishara
**   Copyright: SphinxSolutions.
**************************************************************************/
#ifndef INVOICEPERIOD_H
#define INVOICEPERIOD_H

#include <QSqlRelationalTableModel>
#include <QSqlError>
#include <QtGui>

class InvoicePeriod  : public QSqlRelationalTableModel
{
	Q_OBJECT
public:
	InvoicePeriod();
	InvoicePeriod(QString Description,QString CreatedOn,QString EditedOn);	int InvoicePeriodID;
	QString Description;
	QString CreatedOn;
	QString EditedOn;
	static bool Init();
	bool save();
	bool save(QSqlRecord &record);
	bool remove();
	InvoicePeriod* get();
	InvoicePeriod* get(const QModelIndex &index);
	static InvoicePeriod* Get(int id);
	static InvoicePeriod* Get(QString name);
	static QList<InvoicePeriod*> GetAll();
	static QList<InvoicePeriod*> Search(QString keyword);
	static QList<InvoicePeriod*> QuerySelect(QString select);
	static QList<QString> GetStringList();
	static QList<QPair< int,QString > > GetPairList();
	static QList<QPair< int,QString > > GetPairList(QList<InvoicePeriod*> invoiceperiods);
	static int GetIndex(QString title);
	static InvoicePeriod* GetInstance();
	Qt::ItemFlags flags(const QModelIndex &index) const;
	bool setData(const QModelIndex &index, const QVariant &value, int role);
	void refresh();
	bool remove(const QModelIndex &index);

private:
	InvoicePeriod(int InvoicePeriodID,QString Description,QString CreatedOn,QString EditedOn);	static InvoicePeriod* p_instance;
	bool setDescription(int InvoicePeriodID, const QString &Description);
	bool setCreatedOn(int InvoicePeriodID, const QString &CreatedOn);
	bool setEditedOn(int InvoicePeriodID, const QString &EditedOn);

};
#endif
