/**************************************************************************
**   File: deliveryorder.h
**   Created on: Fri Dec 19 13:01:03 EET 2014
**   Author: Michael Bishara
**   Copyright: SphinxSolutions.
**************************************************************************/
#ifndef DELIVERYORDER_H
#define DELIVERYORDER_H

#include <QSqlRelationalTableModel>
#include <QSqlError>
#include <QtGui>
#include "deliveryorderstoreproduct.h"
#include "deliveryorderservice.h"
#include "deliveryorderfreeline.h"

class DeliveryOrder  : public QSqlRelationalTableModel
{
	Q_OBJECT
public:
	DeliveryOrder();
	DeliveryOrder(int Serial,int DeliveryOrderSerialID,int DeliveryOrderStatusID,int ContactID,int ProjectID,QDate CreationDate,QDate DeliveryDate,QString Note,QString Header,QString Footer,QString DeliveryAddress,QString CreatedOn,QString EditedOn);	int DeliveryOrderID;
	int Serial;
	int DeliveryOrderSerialID;
	int DeliveryOrderStatusID;
	int ContactID;
	int ProjectID;
	QDate CreationDate;
	QDate DeliveryDate;
	QString Note;
	QString Header;
	QString Footer;
	QString DeliveryAddress;
	QList<DeliveryOrderStoreProduct*> deliveryorderstoreproducts;
	QList<DeliveryOrderService*> deliveryorderservices;
	QList<DeliveryOrderFreeline*> deliveryorderfreelines;
	QString CreatedOn;
	QString EditedOn;
	static bool Init();
	bool save();
	bool save(QSqlRecord &record);
	bool remove();
	DeliveryOrder* get();
	DeliveryOrder* get(const QModelIndex &index);
	static DeliveryOrder* Get(int id);
	static DeliveryOrder* Get(QString name);
	static QList<DeliveryOrder*> GetAll();
	static QList<DeliveryOrder*> Search(QString keyword);
	static QList<DeliveryOrder*> QuerySelect(QString select);
	static QList<QString> GetStringList();
	static QList<QPair< int,QString > > GetPairList();
	static QList<QPair< int,QString > > GetPairList(QList<DeliveryOrder*> deliveryorders);
	static int GetIndex(QString title);
	static DeliveryOrder* GetInstance();
	Qt::ItemFlags flags(const QModelIndex &index) const;
	bool setData(const QModelIndex &index, const QVariant &value, int role);
	void refresh();
	bool remove(const QModelIndex &index);

private:
	DeliveryOrder(int DeliveryOrderID,int Serial,int DeliveryOrderSerialID,int DeliveryOrderStatusID,int ContactID,int ProjectID,QDate CreationDate,QDate DeliveryDate,QString Note,QString Header,QString Footer,QString DeliveryAddress,QString CreatedOn,QString EditedOn);	static DeliveryOrder* p_instance;
	bool setSerial(int DeliveryOrderID, const QString &Serial);
	bool setDeliveryOrderSerialID(int DeliveryOrderID, const QString &DeliveryOrderSerialID);
	bool setDeliveryOrderStatusID(int DeliveryOrderID, const QString &DeliveryOrderStatusID);
	bool setContactID(int DeliveryOrderID, const QString &ContactID);
	bool setProjectID(int DeliveryOrderID, const QString &ProjectID);
	bool setCreationDate(int DeliveryOrderID, const QString &CreationDate);
	bool setDeliveryDate(int DeliveryOrderID, const QString &DeliveryDate);
	bool setNote(int DeliveryOrderID, const QString &Note);
	bool setHeader(int DeliveryOrderID, const QString &Header);
	bool setFooter(int DeliveryOrderID, const QString &Footer);
	bool setDeliveryAddress(int DeliveryOrderID, const QString &DeliveryAddress);
	bool setCreatedOn(int DeliveryOrderID, const QString &CreatedOn);
	bool setEditedOn(int DeliveryOrderID, const QString &EditedOn);

};
#endif
