/**************************************************************************
**   File: tax.h
**   Created on: Thu Dec 18 12:57:58 EET 2014
**   Author: Michael Bishara
**   Copyright: SphinxSolutions.
**************************************************************************/
#ifndef TAX_H
#define TAX_H

#include <QSqlRelationalTableModel>
#include <QSqlError>
#include <QtGui>

class Tax  : public QSqlRelationalTableModel
{
	Q_OBJECT
public:
	Tax();
	Tax(QString Title,QString CreatedOn,QString EditedOn);	int TaxID;
	QString Title;
	QString CreatedOn;
	QString EditedOn;
	static bool Init();
	bool save();
	bool save(QSqlRecord &record);
	bool remove();
	Tax* get();
	Tax* get(const QModelIndex &index);
	static Tax* Get(int id);
	static Tax* Get(QString name);
	static QList<Tax*> GetAll();
	static QList<Tax*> Search(QString keyword);
	static QList<Tax*> QuerySelect(QString select);
	static QList<QString> GetStringList();
	static QList<QPair< int,QString > > GetPairList();
	static QList<QPair< int,QString > > GetPairList(QList<Tax*> taxs);
	static int GetIndex(QString title);
	static Tax* GetInstance();
	Qt::ItemFlags flags(const QModelIndex &index) const;
	bool setData(const QModelIndex &index, const QVariant &value, int role);
	void refresh();
	bool remove(const QModelIndex &index);

private:
	Tax(int TaxID,QString Title,QString CreatedOn,QString EditedOn);	static Tax* p_instance;
	bool setTitle(int TaxID, const QString &Title);
	bool setCreatedOn(int TaxID, const QString &CreatedOn);
	bool setEditedOn(int TaxID, const QString &EditedOn);

};
#endif
