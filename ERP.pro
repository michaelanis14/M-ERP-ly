#-------------------------------------------------
#   File: ERP.pro
#   Created on: Fri Dec 19 21:03:50 EET 2014
#   Author: Michael Bishara
#   Copyright: SphinxSolutions.
#-------------------------------------------------

QT       += core gui widgets sql printsupport
QTPLUGIN += qsqlmysql

#ifdef __APPLE__
INCLUDEPATH =/usr/local/mysql-5.6.20-osx10.8-x86_64/include
QMAKE_MAC_SDK = macosx10.9
#endif

TARGET = ERP
TEMPLATE = app

SOURCES += main.cpp \
	displays/mainwindow.cpp \
	erpdisplay.cpp \
	displays/CommonUI/erpcombobox.cpp \
	displays/CommonUI/flowlayout.cpp  \
	displays/CommonUI/erpformblock.cpp  \
	displays/CommonUI/addremovebuttons.cpp  \
	displays/CommonUI/HNavigationButtons.cpp  \
	displays/CommonUI/navigationButtons.cpp  \
	displays/CommonUI/RemovebtnWidgets.cpp  \
	displays/CommonUI/barcode.cpp  \
	displays/CommonUI/ean13.cpp  \
	displays/CommonUI/erptableview.cpp  \
	Model/erpmodel.cpp \
	Model/invoicestoreproduct.cpp \
	Model/invoiceservice.cpp \
	Model/access.cpp \
	Model/invoicedeliveryorderfreeline.cpp \
	Model/invoiceperiod.cpp \
	Model/invoiceyear.cpp \
	Model/invoicestate.cpp \
	Model/invoiceserial.cpp \
	Model/invoice.cpp \
	Model/invoicestatedate.cpp \
	Model/invoicefreeline.cpp \
	Model/returndeliveryorder.cpp \
	Model/returndeliveryorderstoreproduct.cpp \
	Model/returndeliveryorderservice.cpp \
	Model/returndeliveryorderfreeline.cpp \
	Model/deliveryorderserial.cpp \
	Model/deliveryorder.cpp \
	Model/returnpurchase.cpp \
	Model/returnpurchasefreeline.cpp \
	Model/returnpurchasestoreproduct.cpp \
	Model/purchase.cpp \
	Model/contactperson.cpp \
	Model/company.cpp \
	Model/tax.cpp \
	Model/user.cpp \
	Model/contact.cpp \
	Model/contacttelephone.cpp \
	Model/contactemail.cpp \
	Model/bankaccount.cpp \
	Model/contactclass.cpp \
	Model/contacttype.cpp \
	Model/country.cpp \
	Model/currency.cpp \
	Model/contactstatus.cpp \
	Model/fieldtype.cpp \
	Model/contactfield.cpp \
	Model/contactfielddata.cpp \
	Model/contactpersonfield.cpp \
	Model/contactpersonfielddata.cpp \
	Model/contactpersontelephone.cpp \
	Model/contactpersonemail.cpp \
	Model/projectstatus.cpp \
	Model/project.cpp \
	Model/projectfile.cpp \
	Model/projectcontactperson.cpp \
	Model/projectservice.cpp \
	Model/projectsales.cpp \
	Model/unit.cpp \
	Model/productcategory.cpp \
	Model/productimage.cpp \
	Model/product.cpp \
	Model/productfield.cpp \
	Model/productfielddata.cpp \
	Model/service.cpp \
	Model/store.cpp \
	Model/purchasestatus.cpp \
	Model/purchaseserial.cpp \
	Model/purchasestoreproduct.cpp \
	Model/purchasefreeline.cpp \
	Model/deliveryorderstatus.cpp \
	Model/deliveryorderstoreproduct.cpp \
	Model/deliveryorderservice.cpp \
	Model/deliveryorderfreeline.cpp \
	Model/paymenttype.cpp \
	Model/payment.cpp \
	Model/task.cpp \
	Model/language.cpp \
	Model/timebooking.cpp \
	Model/login.cpp \
	displays/Product/ProductStoreStateUI.cpp \ 
	 displays/Purchase/createpurchase.cpp \
	displays/InvoiceStoreProduct/invoicestoreproductindexui.cpp \
	displays/InvoiceStoreProduct/invoicestoreproductui.cpp \
	displays/InvoiceService/invoiceserviceindexui.cpp \
	displays/InvoiceService/invoiceserviceui.cpp \
	displays/Access/accessindexui.cpp \
	displays/Access/accessui.cpp \
	displays/InvoiceDeliveryOrderFreeline/invoicedeliveryorderfreelineindexui.cpp \
	displays/InvoiceDeliveryOrderFreeline/invoicedeliveryorderfreelineui.cpp \
	displays/InvoicePeriod/invoiceperiodindexui.cpp \
	displays/InvoicePeriod/invoiceperiodui.cpp \
	displays/InvoiceYear/invoiceyearindexui.cpp \
	displays/InvoiceYear/invoiceyearui.cpp \
	displays/InvoiceState/invoicestateindexui.cpp \
	displays/InvoiceState/invoicestateui.cpp \
	displays/InvoiceSerial/invoiceserialindexui.cpp \
	displays/InvoiceSerial/invoiceserialui.cpp \
	displays/Invoice/invoiceindexui.cpp \
	displays/Invoice/invoiceui.cpp \
	displays/InvoiceStateDate/invoicestatedateindexui.cpp \
	displays/InvoiceStateDate/invoicestatedateui.cpp \
	displays/InvoiceFreeline/invoicefreelineindexui.cpp \
	displays/InvoiceFreeline/invoicefreelineui.cpp \
	displays/ReturnDeliveryOrder/returndeliveryorderindexui.cpp \
	displays/ReturnDeliveryOrder/returndeliveryorderui.cpp \
	displays/ReturnDeliveryOrderStoreProduct/returndeliveryorderstoreproductindexui.cpp \
	displays/ReturnDeliveryOrderStoreProduct/returndeliveryorderstoreproductui.cpp \
	displays/ReturnDeliveryOrderService/returndeliveryorderserviceindexui.cpp \
	displays/ReturnDeliveryOrderService/returndeliveryorderserviceui.cpp \
	displays/ReturnDeliveryOrderFreeline/returndeliveryorderfreelineindexui.cpp \
	displays/ReturnDeliveryOrderFreeline/returndeliveryorderfreelineui.cpp \
	displays/DeliveryOrderSerial/deliveryorderserialindexui.cpp \
	displays/DeliveryOrderSerial/deliveryorderserialui.cpp \
	displays/DeliveryOrder/deliveryorderindexui.cpp \
	displays/DeliveryOrder/deliveryorderui.cpp \
	displays/ReturnPurchase/returnpurchaseindexui.cpp \
	displays/ReturnPurchase/returnpurchaseui.cpp \
	displays/ReturnPurchaseFreeLine/returnpurchasefreelineindexui.cpp \
	displays/ReturnPurchaseFreeLine/returnpurchasefreelineui.cpp \
	displays/ReturnPurchaseStoreProduct/returnpurchasestoreproductindexui.cpp \
	displays/ReturnPurchaseStoreProduct/returnpurchasestoreproductui.cpp \
	displays/Purchase/purchaseindexui.cpp \
	displays/Purchase/purchaseui.cpp \
	displays/ContactPerson/contactpersonindexui.cpp \
	displays/ContactPerson/contactpersonui.cpp \
	displays/Company/companyindexui.cpp \
	displays/Company/companyui.cpp \
	displays/Tax/taxindexui.cpp \
	displays/Tax/taxui.cpp \
	displays/User/userindexui.cpp \
	displays/User/userui.cpp \
	displays/Contact/contactindexui.cpp \
	displays/Contact/contactui.cpp \
	displays/ContactTelephone/contacttelephoneindexui.cpp \
	displays/ContactTelephone/contacttelephoneui.cpp \
	displays/ContactEmail/contactemailindexui.cpp \
	displays/ContactEmail/contactemailui.cpp \
	displays/BankAccount/bankaccountindexui.cpp \
	displays/BankAccount/bankaccountui.cpp \
	displays/ContactClass/contactclassindexui.cpp \
	displays/ContactClass/contactclassui.cpp \
	displays/ContactType/contacttypeindexui.cpp \
	displays/ContactType/contacttypeui.cpp \
	displays/Country/countryindexui.cpp \
	displays/Country/countryui.cpp \
	displays/Currency/currencyindexui.cpp \
	displays/Currency/currencyui.cpp \
	displays/ContactStatus/contactstatusindexui.cpp \
	displays/ContactStatus/contactstatusui.cpp \
	displays/FieldType/fieldtypeindexui.cpp \
	displays/FieldType/fieldtypeui.cpp \
	displays/ContactField/contactfieldindexui.cpp \
	displays/ContactField/contactfieldui.cpp \
	displays/ContactFieldData/contactfielddataindexui.cpp \
	displays/ContactFieldData/contactfielddataui.cpp \
	displays/ContactPersonField/contactpersonfieldindexui.cpp \
	displays/ContactPersonField/contactpersonfieldui.cpp \
	displays/ContactPersonFieldData/contactpersonfielddataindexui.cpp \
	displays/ContactPersonFieldData/contactpersonfielddataui.cpp \
	displays/ContactPersonTelephone/contactpersontelephoneindexui.cpp \
	displays/ContactPersonTelephone/contactpersontelephoneui.cpp \
	displays/ContactPersonEmail/contactpersonemailindexui.cpp \
	displays/ContactPersonEmail/contactpersonemailui.cpp \
	displays/ProjectStatus/projectstatusindexui.cpp \
	displays/ProjectStatus/projectstatusui.cpp \
	displays/Project/projectindexui.cpp \
	displays/Project/projectui.cpp \
	displays/ProjectFile/projectfileindexui.cpp \
	displays/ProjectFile/projectfileui.cpp \
	displays/ProjectContactPerson/projectcontactpersonindexui.cpp \
	displays/ProjectContactPerson/projectcontactpersonui.cpp \
	displays/ProjectService/projectserviceindexui.cpp \
	displays/ProjectService/projectserviceui.cpp \
	displays/ProjectSales/projectsalesindexui.cpp \
	displays/ProjectSales/projectsalesui.cpp \
	displays/Unit/unitindexui.cpp \
	displays/Unit/unitui.cpp \
	displays/ProductCategory/productcategoryindexui.cpp \
	displays/ProductCategory/productcategoryui.cpp \
	displays/ProductImage/productimageindexui.cpp \
	displays/ProductImage/productimageui.cpp \
	displays/Product/productindexui.cpp \
	displays/Product/productui.cpp \
	displays/ProductField/productfieldindexui.cpp \
	displays/ProductField/productfieldui.cpp \
	displays/ProductFieldData/productfielddataindexui.cpp \
	displays/ProductFieldData/productfielddataui.cpp \
	displays/Service/serviceindexui.cpp \
	displays/Service/serviceui.cpp \
	displays/Store/storeindexui.cpp \
	displays/Store/storeui.cpp \
	displays/PurchaseStatus/purchasestatusindexui.cpp \
	displays/PurchaseStatus/purchasestatusui.cpp \
	displays/PurchaseSerial/purchaseserialindexui.cpp \
	displays/PurchaseSerial/purchaseserialui.cpp \
	displays/PurchaseStoreProduct/purchasestoreproductindexui.cpp \
	displays/PurchaseStoreProduct/purchasestoreproductui.cpp \
	displays/PurchaseFreeLine/purchasefreelineindexui.cpp \
	displays/PurchaseFreeLine/purchasefreelineui.cpp \
	displays/DeliveryOrderStatus/deliveryorderstatusindexui.cpp \
	displays/DeliveryOrderStatus/deliveryorderstatusui.cpp \
	displays/DeliveryOrderStoreProduct/deliveryorderstoreproductindexui.cpp \
	displays/DeliveryOrderStoreProduct/deliveryorderstoreproductui.cpp \
	displays/DeliveryOrderService/deliveryorderserviceindexui.cpp \
	displays/DeliveryOrderService/deliveryorderserviceui.cpp \
	displays/DeliveryOrderFreeline/deliveryorderfreelineindexui.cpp \
	displays/DeliveryOrderFreeline/deliveryorderfreelineui.cpp \
	displays/PaymentType/paymenttypeindexui.cpp \
	displays/PaymentType/paymenttypeui.cpp \
	displays/Payment/paymentindexui.cpp \
	displays/Payment/paymentui.cpp \
	displays/Task/taskindexui.cpp \
	displays/Task/taskui.cpp \
	displays/Language/languageindexui.cpp \
	displays/Language/languageui.cpp \
	displays/TimeBooking/timebookingindexui.cpp \
	displays/TimeBooking/timebookingui.cpp \
	displays/Login/loginindexui.cpp \
	displays/Login/loginui.cpp

HEADERS += displays/mainwindow.h \	erpdisplay.h \
	displays/CommonUI/erpcombobox.h \
	displays/CommonUI/flowlayout.h  \
	displays/CommonUI/erpformblock.h  \
	displays/CommonUI/addremovebuttons.h  \
	displays/CommonUI/HNavigationButtons.h  \
	displays/CommonUI/navigationButtons.h  \
	displays/CommonUI/RemovebtnWidgets.h  \
	displays/CommonUI/barcode.h  \
	displays/CommonUI/ean13.h  \
	displays/CommonUI/erptableview.h  \
	Model/erpmodel.h \
	Model/invoicestoreproduct.h \
	Model/invoiceservice.h \
	Model/access.h \
	Model/invoicedeliveryorderfreeline.h \
	Model/invoiceperiod.h \
	Model/invoiceyear.h \
	Model/invoicestate.h \
	Model/invoiceserial.h \
	Model/invoice.h \
	Model/invoicestatedate.h \
	Model/invoicefreeline.h \
	Model/returndeliveryorder.h \
	Model/returndeliveryorderstoreproduct.h \
	Model/returndeliveryorderservice.h \
	Model/returndeliveryorderfreeline.h \
	Model/deliveryorderserial.h \
	Model/deliveryorder.h \
	Model/returnpurchase.h \
	Model/returnpurchasefreeline.h \
	Model/returnpurchasestoreproduct.h \
	Model/purchase.h \
	Model/contactperson.h \
	Model/company.h \
	Model/tax.h \
	Model/user.h \
	Model/contact.h \
	Model/contacttelephone.h \
	Model/contactemail.h \
	Model/bankaccount.h \
	Model/contactclass.h \
	Model/contacttype.h \
	Model/country.h \
	Model/currency.h \
	Model/contactstatus.h \
	Model/fieldtype.h \
	Model/contactfield.h \
	Model/contactfielddata.h \
	Model/contactpersonfield.h \
	Model/contactpersonfielddata.h \
	Model/contactpersontelephone.h \
	Model/contactpersonemail.h \
	Model/projectstatus.h \
	Model/project.h \
	Model/projectfile.h \
	Model/projectcontactperson.h \
	Model/projectservice.h \
	Model/projectsales.h \
	Model/unit.h \
	Model/productcategory.h \
	Model/productimage.h \
	Model/product.h \
	Model/productfield.h \
	Model/productfielddata.h \
	Model/service.h \
	Model/store.h \
	Model/purchasestatus.h \
	Model/purchaseserial.h \
	Model/purchasestoreproduct.h \
	Model/purchasefreeline.h \
	Model/deliveryorderstatus.h \
	Model/deliveryorderstoreproduct.h \
	Model/deliveryorderservice.h \
	Model/deliveryorderfreeline.h \
	Model/paymenttype.h \
	Model/payment.h \
	Model/task.h \
	Model/language.h \
	Model/timebooking.h \
	Model/login.h \
	displays/Product/ProductStoreStateUI.h \
	 displays/Purchase/createpurchase.h \
	displays/InvoiceStoreProduct/invoicestoreproductindexui.h \
	displays/InvoiceStoreProduct/invoicestoreproductui.h \
	displays/InvoiceService/invoiceserviceindexui.h \
	displays/InvoiceService/invoiceserviceui.h \
	displays/Access/accessindexui.h \
	displays/Access/accessui.h \
	displays/InvoiceDeliveryOrderFreeline/invoicedeliveryorderfreelineindexui.h \
	displays/InvoiceDeliveryOrderFreeline/invoicedeliveryorderfreelineui.h \
	displays/InvoicePeriod/invoiceperiodindexui.h \
	displays/InvoicePeriod/invoiceperiodui.h \
	displays/InvoiceYear/invoiceyearindexui.h \
	displays/InvoiceYear/invoiceyearui.h \
	displays/InvoiceState/invoicestateindexui.h \
	displays/InvoiceState/invoicestateui.h \
	displays/InvoiceSerial/invoiceserialindexui.h \
	displays/InvoiceSerial/invoiceserialui.h \
	displays/Invoice/invoiceindexui.h \
	displays/Invoice/invoiceui.h \
	displays/InvoiceStateDate/invoicestatedateindexui.h \
	displays/InvoiceStateDate/invoicestatedateui.h \
	displays/InvoiceFreeline/invoicefreelineindexui.h \
	displays/InvoiceFreeline/invoicefreelineui.h \
	displays/ReturnDeliveryOrder/returndeliveryorderindexui.h \
	displays/ReturnDeliveryOrder/returndeliveryorderui.h \
	displays/ReturnDeliveryOrderStoreProduct/returndeliveryorderstoreproductindexui.h \
	displays/ReturnDeliveryOrderStoreProduct/returndeliveryorderstoreproductui.h \
	displays/ReturnDeliveryOrderService/returndeliveryorderserviceindexui.h \
	displays/ReturnDeliveryOrderService/returndeliveryorderserviceui.h \
	displays/ReturnDeliveryOrderFreeline/returndeliveryorderfreelineindexui.h \
	displays/ReturnDeliveryOrderFreeline/returndeliveryorderfreelineui.h \
	displays/DeliveryOrderSerial/deliveryorderserialindexui.h \
	displays/DeliveryOrderSerial/deliveryorderserialui.h \
	displays/DeliveryOrder/deliveryorderindexui.h \
	displays/DeliveryOrder/deliveryorderui.h \
	displays/ReturnPurchase/returnpurchaseindexui.h \
	displays/ReturnPurchase/returnpurchaseui.h \
	displays/ReturnPurchaseFreeLine/returnpurchasefreelineindexui.h \
	displays/ReturnPurchaseFreeLine/returnpurchasefreelineui.h \
	displays/ReturnPurchaseStoreProduct/returnpurchasestoreproductindexui.h \
	displays/ReturnPurchaseStoreProduct/returnpurchasestoreproductui.h \
	displays/Purchase/purchaseindexui.h \
	displays/Purchase/purchaseui.h \
	displays/ContactPerson/contactpersonindexui.h \
	displays/ContactPerson/contactpersonui.h \
	displays/Company/companyindexui.h \
	displays/Company/companyui.h \
	displays/Tax/taxindexui.h \
	displays/Tax/taxui.h \
	displays/User/userindexui.h \
	displays/User/userui.h \
	displays/Contact/contactindexui.h \
	displays/Contact/contactui.h \
	displays/ContactTelephone/contacttelephoneindexui.h \
	displays/ContactTelephone/contacttelephoneui.h \
	displays/ContactEmail/contactemailindexui.h \
	displays/ContactEmail/contactemailui.h \
	displays/BankAccount/bankaccountindexui.h \
	displays/BankAccount/bankaccountui.h \
	displays/ContactClass/contactclassindexui.h \
	displays/ContactClass/contactclassui.h \
	displays/ContactType/contacttypeindexui.h \
	displays/ContactType/contacttypeui.h \
	displays/Country/countryindexui.h \
	displays/Country/countryui.h \
	displays/Currency/currencyindexui.h \
	displays/Currency/currencyui.h \
	displays/ContactStatus/contactstatusindexui.h \
	displays/ContactStatus/contactstatusui.h \
	displays/FieldType/fieldtypeindexui.h \
	displays/FieldType/fieldtypeui.h \
	displays/ContactField/contactfieldindexui.h \
	displays/ContactField/contactfieldui.h \
	displays/ContactFieldData/contactfielddataindexui.h \
	displays/ContactFieldData/contactfielddataui.h \
	displays/ContactPersonField/contactpersonfieldindexui.h \
	displays/ContactPersonField/contactpersonfieldui.h \
	displays/ContactPersonFieldData/contactpersonfielddataindexui.h \
	displays/ContactPersonFieldData/contactpersonfielddataui.h \
	displays/ContactPersonTelephone/contactpersontelephoneindexui.h \
	displays/ContactPersonTelephone/contactpersontelephoneui.h \
	displays/ContactPersonEmail/contactpersonemailindexui.h \
	displays/ContactPersonEmail/contactpersonemailui.h \
	displays/ProjectStatus/projectstatusindexui.h \
	displays/ProjectStatus/projectstatusui.h \
	displays/Project/projectindexui.h \
	displays/Project/projectui.h \
	displays/ProjectFile/projectfileindexui.h \
	displays/ProjectFile/projectfileui.h \
	displays/ProjectContactPerson/projectcontactpersonindexui.h \
	displays/ProjectContactPerson/projectcontactpersonui.h \
	displays/ProjectService/projectserviceindexui.h \
	displays/ProjectService/projectserviceui.h \
	displays/ProjectSales/projectsalesindexui.h \
	displays/ProjectSales/projectsalesui.h \
	displays/Unit/unitindexui.h \
	displays/Unit/unitui.h \
	displays/ProductCategory/productcategoryindexui.h \
	displays/ProductCategory/productcategoryui.h \
	displays/ProductImage/productimageindexui.h \
	displays/ProductImage/productimageui.h \
	displays/Product/productindexui.h \
	displays/Product/productui.h \
	displays/ProductField/productfieldindexui.h \
	displays/ProductField/productfieldui.h \
	displays/ProductFieldData/productfielddataindexui.h \
	displays/ProductFieldData/productfielddataui.h \
	displays/Service/serviceindexui.h \
	displays/Service/serviceui.h \
	displays/Store/storeindexui.h \
	displays/Store/storeui.h \
	displays/PurchaseStatus/purchasestatusindexui.h \
	displays/PurchaseStatus/purchasestatusui.h \
	displays/PurchaseSerial/purchaseserialindexui.h \
	displays/PurchaseSerial/purchaseserialui.h \
	displays/PurchaseStoreProduct/purchasestoreproductindexui.h \
	displays/PurchaseStoreProduct/purchasestoreproductui.h \
	displays/PurchaseFreeLine/purchasefreelineindexui.h \
	displays/PurchaseFreeLine/purchasefreelineui.h \
	displays/DeliveryOrderStatus/deliveryorderstatusindexui.h \
	displays/DeliveryOrderStatus/deliveryorderstatusui.h \
	displays/DeliveryOrderStoreProduct/deliveryorderstoreproductindexui.h \
	displays/DeliveryOrderStoreProduct/deliveryorderstoreproductui.h \
	displays/DeliveryOrderService/deliveryorderserviceindexui.h \
	displays/DeliveryOrderService/deliveryorderserviceui.h \
	displays/DeliveryOrderFreeline/deliveryorderfreelineindexui.h \
	displays/DeliveryOrderFreeline/deliveryorderfreelineui.h \
	displays/PaymentType/paymenttypeindexui.h \
	displays/PaymentType/paymenttypeui.h \
	displays/Payment/paymentindexui.h \
	displays/Payment/paymentui.h \
	displays/Task/taskindexui.h \
	displays/Task/taskui.h \
	displays/Language/languageindexui.h \
	displays/Language/languageui.h \
	displays/TimeBooking/timebookingindexui.h \
	displays/TimeBooking/timebookingui.h \
	displays/Login/loginindexui.h \
	displays/Login/loginui.h 

TRANSLATIONS = erp_ar.ts
FORMS	+= mainwindow.ui

RESOURCES +=Resources.qrc
