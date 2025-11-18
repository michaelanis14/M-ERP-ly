/**************************************************************************
**   File: product.h
**   Created on: Thu Dec 18 12:57:58 EET 2014
**   Author: Michael Bishara
**   Copyright: SphinxSolutions.
**************************************************************************/
#ifndef PRODUCT_H
#define PRODUCT_H

#include <QSqlRelationalTableModel>
#include <QSqlError>
#include <QtGui>
#include "productimage.h"

class Product  : public QSqlRelationalTableModel
{
	Q_OBJECT
public:
	Product();
	Product(QString Name,QString ShortDescription,int UnitID,double SellingPrice,double NetCoast,double TradeMarginRate,int TaxID,QString information,QString Barcode,int ProductCategoryID,double CriticalAmount,QString CreatedOn,QString EditedOn);	int ProductID;
	QString Name;
	QString ShortDescription;
	int UnitID;
	double SellingPrice;
	double NetCoast;
	double TradeMarginRate;
	int TaxID;
	QString information;
	QString Barcode;
	int ProductCategoryID;
	double CriticalAmount;
	QList<ProductImage*> productimages;
	QString CreatedOn;
	QString EditedOn;
	static bool Init();
	bool save();
	bool save(QSqlRecord &record);
	bool remove();
	Product* get();
	Product* get(const QModelIndex &index);
	static Product* Get(int id);
	static Product* Get(QString name);
	static QList<Product*> GetAll();
	static QList<Product*> Search(QString keyword);
	static QList<Product*> QuerySelect(QString select);
	static QList<QString> GetStringList();
	static QList<QPair< int,QString > > GetPairList();
	static QList<QPair< int,QString > > GetPairList(QList<Product*> products);
	static int GetIndex(QString title);
	static Product* GetInstance();
	Qt::ItemFlags flags(const QModelIndex &index) const;
	bool setData(const QModelIndex &index, const QVariant &value, int role);
	void refresh();
	bool remove(const QModelIndex &index);

	bool saveSecure();
	static Product* GetSecure(int id);
	static Product* GetSecure(const QString &name);
	static QList<Product*> SearchSecure(const QString &keyword);
	bool removeSecure();

private:
	Product(int ProductID,QString Name,QString ShortDescription,int UnitID,double SellingPrice,double NetCoast,double TradeMarginRate,int TaxID,QString information,QString Barcode,int ProductCategoryID,double CriticalAmount,QString CreatedOn,QString EditedOn);	static Product* p_instance;
	bool setName(int ProductID, const QString &Name);
	bool setShortDescription(int ProductID, const QString &ShortDescription);
	bool setUnitID(int ProductID, const QString &UnitID);
	bool setSellingPrice(int ProductID, const QString &SellingPrice);
	bool setNetCoast(int ProductID, const QString &NetCoast);
	bool setTradeMarginRate(int ProductID, const QString &TradeMarginRate);
	bool setTaxID(int ProductID, const QString &TaxID);
	bool setinformation(int ProductID, const QString &information);
	bool setBarcode(int ProductID, const QString &Barcode);
	bool setProductCategoryID(int ProductID, const QString &ProductCategoryID);
	bool setCriticalAmount(int ProductID, const QString &CriticalAmount);
	bool setCreatedOn(int ProductID, const QString &CreatedOn);
	bool setEditedOn(int ProductID, const QString &EditedOn);

};
#endif
