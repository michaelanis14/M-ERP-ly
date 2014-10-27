﻿/*************************************
**   Created on:  10/8/2014
**   Author: michaelbishara
**   Copyright: Bishara©.
**************************************/

#include "erpformblock.h"
#include <QPushButton>

ERPFormBlock::ERPFormBlock(QWidget *parent) :
	QWidget(parent)
{

	this->setObjectName("ERPFormBlock");
	QWidget * widget = new QWidget();
	boxLayout = new QVBoxLayout();
	formLayout = new QFormLayout(widget);

	formLayout->setObjectName("formPanelk");
	this->setContentsMargins(0,0,0,0);
	//	formLayout->setContentsMargins(5,2,5,2);
	//	formLayout->setRowWrapPolicy(QFormLayout::WrapLongRows);
	//	formLayout->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
	formLayout->setLabelAlignment(Qt::AlignLeft);
	this->setAutoFillBackground(true);
	formLayout->setRowWrapPolicy(QFormLayout::WrapAllRows);
	//this->setMinimumWidth(190);
	//this->setMinimumHeight(190);
	//formLayout->setFieldGrowthPolicy(QFormLayout::FieldsStayAtSizeHint);

	boxLayout->addWidget(widget);
	boxLayout->addStretch(1);
	this->setLayout(boxLayout);
}

void ERPFormBlock::addRow(const QString &labelText, QWidget *field){

	formLayout->addRow(labelText,field);
	//this->repaint();
}
void ERPFormBlock::addWidget(QWidget *widget){

	boxLayout->addWidget(widget);
	boxLayout->addStretch(1);
}
