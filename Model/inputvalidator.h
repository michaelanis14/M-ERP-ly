/**************************************************************************
**   File: inputvalidator.h
**   Created on: 2025-11-18
**   Author: Claude Code Assistant
**   Copyright: SphinxSolutions.
**   Purpose: Input validation and sanitization utilities
**************************************************************************/
#ifndef INPUTVALIDATOR_H
#define INPUTVALIDATOR_H

#include <QString>
#include <QRegExp>
#include <QDate>
#include <QValidator>

class InputValidator
{
public:
	InputValidator();

	// Email validation
	static bool isValidEmail(const QString &email);
	static QString sanitizeEmail(const QString &email);

	// Phone number validation
	static bool isValidPhone(const QString &phone);
	static QString sanitizePhone(const QString &phone);

	// Tax number validation
	static bool isValidTaxNumber(const QString &taxNumber);
	static QString sanitizeTaxNumber(const QString &taxNumber);

	// Barcode validation (EAN-13)
	static bool isValidEAN13(const QString &barcode);
	static QString sanitizeBarcode(const QString &barcode);

	// String sanitization
	static QString sanitizeString(const QString &input, int maxLength = 255);
	static QString sanitizeSQLString(const QString &input);
	static QString removeHTMLTags(const QString &input);
	static QString escapeSpecialCharacters(const QString &input);

	// Numeric validation
	static bool isValidInteger(const QString &input);
	static bool isValidDecimal(const QString &input);
	static bool isValidPrice(const QString &input);
	static bool isInRange(double value, double min, double max);

	// Date validation
	static bool isValidDate(const QString &dateString, const QString &format = "yyyy-MM-dd");
	static bool isDateInRange(const QDate &date, const QDate &min, const QDate &max);

	// Password validation
	static bool isStrongPassword(const QString &password);
	static QString getPasswordStrength(const QString &password);
	static bool meetsPasswordPolicy(const QString &password, QString &errorMessage);

	// Username validation
	static bool isValidUsername(const QString &username);
	static QString sanitizeUsername(const QString &username);

	// URL validation
	static bool isValidURL(const QString &url);
	static QString sanitizeURL(const QString &url);

	// Credit card validation (basic Luhn algorithm)
	static bool isValidCreditCard(const QString &cardNumber);

	// IBAN validation (basic)
	static bool isValidIBAN(const QString &iban);

	// General validation
	static bool isEmpty(const QString &input);
	static bool hasLength(const QString &input, int minLength, int maxLength);
	static bool containsOnly(const QString &input, const QString &allowedChars);
	static bool matches(const QString &input, const QString &pattern);

	// SQL Injection prevention
	static bool containsSQLKeywords(const QString &input);
	static bool isSafeForSQL(const QString &input);

	// XSS prevention
	static bool containsXSSPatterns(const QString &input);
	static QString escapeHTML(const QString &input);

private:
	static const QRegExp emailRegex;
	static const QRegExp phoneRegex;
	static const QRegExp urlRegex;
	static const QRegExp usernameRegex;
};

#endif // INPUTVALIDATOR_H
