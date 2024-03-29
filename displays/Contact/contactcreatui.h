/**************************************************************************
**   File: contactcreatui.h
**   Created on: Wed Dec 17 18:31:01 EET 2014
**   Author: Michael Bishara
**   Copyright: SphinxSolutions.
**************************************************************************/

#ifndef CONTACTUI_H
#define CONTACTUI_H
#include "../../erpdisplay.h"
#include "contactui.h"
#include "../CommonUI/erpformblock.h"
#include "../CommonUI/erpcombobox.h"
#include "../CommonUI/addremovebuttons.h"
#include "../CommonUI/RemovebtnWidgets.h"
#include "../../Model/contact.h"
#include "../../Model/erpmodel.h"
#include "../../Model/contact.h"
#include "../../Model/contacttype.h"
#include "../../Model/contactclass.h"
#include "../../Model/country.h"
#include "../../Model/contactstatus.h"

#include "../ContactTelephone/contacttelephoneui.h"
#include "../ContactEmail/contactemailui.h"
#include "../BankAccount/bankaccountui.h"

#include <QWidget>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QCompleter>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QDateEdit>
class ContactCreatUI : public ERPDisplay
{
	Q_OBJECT
public:
	explicit ContactCreatUI(QWidget *parent = 0);
	static void ShowUI();
	static ContactCreatUI* GetUI();
	ERPFormBlock* block0Layout;
	ContactTelephoneUI* ContactTelephoneui;
	QList<ContactTelephoneUI*> ContactTelephones;
	AddRemoveButtons* addremoveContactTelephoneBtn;
	ContactEmailUI* ContactEmailui;
	QList<ContactEmailUI*> ContactEmails;
	AddRemoveButtons* addremoveContactEmailBtn;
	BankAccountUI* BankAccountui;
	QList<BankAccountUI*> BankAccounts;
	AddRemoveButtons* addremoveBankAccountBtn;
	ERPTableView *tabel; 
	QStandardItemModel *model; 
	QPushButton *remove; 
	ERPFormBlock *tabelLayout;
	QLineEdit*name;
	QLineEdit*salutation;
	QDateEdit*birthdateordateoffoundation;
	ERPComboBox*contacttype;
	ERPComboBox*contactclass;
	QLineEdit*serial;
	QLineEdit*address;
	QLineEdit*postalcode;
	QLineEdit*city;
	ERPComboBox*country;
	ERPComboBox*contactstatus;
	QLineEdit*website;
	QLineEdit*taxnumber;
	void fill(Contact* contact);
Contact* contact;
private:
	static ERPDisplay* p_instance;
	void refreshTabel();
private slots:
	void addContactTelephone();
	void addContactTelephone(ContactTelephone* ContactTelephone);
	void removeContactTelephone(QWidget* widget);
	void addContactEmail();
	void addContactEmail(ContactEmail* ContactEmail);
	void removeContactEmail(QWidget* widget);
	void addBankAccount();
	void addBankAccount(BankAccount* BankAccount);
	void removeBankAccount(QWidget* widget);
	void selectContact();
	void cancel();
	void clear();
	void removeRow();
public slots:
	bool save();
	bool updateModel();
	void onSelectionChanged();
protected:
void showEvent(QShowEvent * event);
};
#endif
