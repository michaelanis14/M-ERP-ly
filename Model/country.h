/**************************************************************************
**   File: country.h
**   Created on: Sat Oct 18 13:10:05 EET 2014
**   Author: Michael Bishara
**   Copyright: SphinxSolutions.
**************************************************************************/
#ifndef COUNTRY_H
#define COUNTRY_H

#include <QtGui>

class Country
{
public:
	Country();
	Country(QString Name);	int CountryID;
	QString Name;
	QList<Country*> countrys;
	static bool init();
	bool save();
	bool remove();
	Country* get();
	static Country* get(int id);
	static Country* get(QString name);
	static QList<Country*> getAll();
	static QList<Country*> search(QString keyword);
	static QList<Country*> select(QString select);
	static QList<QString> GetStringList();
	static int GetIndex(QString title);
	static Country* GetInstance();

private:
	Country(int CountryID,QString Name);
	static Country* p_instance;

};
#endif
