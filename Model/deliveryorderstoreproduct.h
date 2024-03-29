/**************************************************************************
**   File: deliveryorderstoreproduct.h
**   Created on: Thu Dec 18 12:57:59 EET 2014
**   Author: Michael Bishara
**   Copyright: SphinxSolutions.
**************************************************************************/
#ifndef DELIVERYORDERSTOREPRODUCT_H
#define DELIVERYORDERSTOREPRODUCT_H

#include <QSqlRelationalTableModel>
#include <QSqlError>
#include <QtGui>

class DeliveryOrderStoreProduct  : public QSqlRelationalTableModel
{
	Q_OBJECT
public:
	DeliveryOrderStoreProduct();
	DeliveryOrderStoreProduct(int DeliveryOrderID,int StoreID,int ProductID,double Amount,double Price,QString CreatedOn,QString EditedOn);	int DeliveryOrderStoreProductID;
	int DeliveryOrderID;
	int StoreID;
	int ProductID;
	double Amount;
	double Price;
	QString CreatedOn;
	QString EditedOn;
	static bool Init();
	bool save();
	bool save(QSqlRecord &record);
	bool remove();
	DeliveryOrderStoreProduct* get();
	DeliveryOrderStoreProduct* get(const QModelIndex &index);
	static DeliveryOrderStoreProduct* Get(int id);
	static DeliveryOrderStoreProduct* Get(QString name);
	static QList<DeliveryOrderStoreProduct*> GetAll();
	static QList<DeliveryOrderStoreProduct*> Search(QString keyword);
	static QList<DeliveryOrderStoreProduct*> QuerySelect(QString select);
	static QList<QString> GetStringList();
	static QList<QPair< int,QString > > GetPairList();
	static QList<QPair< int,QString > > GetPairList(QList<DeliveryOrderStoreProduct*> deliveryorderstoreproducts);
	static int GetIndex(QString title);
	static DeliveryOrderStoreProduct* GetInstance();
	Qt::ItemFlags flags(const QModelIndex &index) const;
	bool setData(const QModelIndex &index, const QVariant &value, int role);
	void refresh();
	bool remove(const QModelIndex &index);

private:
	DeliveryOrderStoreProduct(int DeliveryOrderStoreProductID,int DeliveryOrderID,int StoreID,int ProductID,double Amount,double Price,QString CreatedOn,QString EditedOn);	static DeliveryOrderStoreProduct* p_instance;
	bool setDeliveryOrderID(int DeliveryOrderStoreProductID, const QString &DeliveryOrderID);
	bool setStoreID(int DeliveryOrderStoreProductID, const QString &StoreID);
	bool setProductID(int DeliveryOrderStoreProductID, const QString &ProductID);
	bool setAmount(int DeliveryOrderStoreProductID, const QString &Amount);
	bool setPrice(int DeliveryOrderStoreProductID, const QString &Price);
	bool setCreatedOn(int DeliveryOrderStoreProductID, const QString &CreatedOn);
	bool setEditedOn(int DeliveryOrderStoreProductID, const QString &EditedOn);

};
#endif
