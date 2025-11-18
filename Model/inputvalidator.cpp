/**************************************************************************
**   File: inputvalidator.cpp
**   Created on: 2025-11-18
**   Author: Claude Code Assistant
**   Copyright: SphinxSolutions.
**   Purpose: Input validation and sanitization utilities implementation
**************************************************************************/
#include "inputvalidator.h"
#include <QRegExp>
#include <QStringList>

// Initialize static regex patterns
const QRegExp InputValidator::emailRegex("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
const QRegExp InputValidator::phoneRegex("^[+]?[0-9\\s\\-\\(\\)]{7,20}$");
const QRegExp InputValidator::urlRegex("^https?://[a-zA-Z0-9\\-._~:/?#\\[\\]@!$&'()*+,;=]+$");
const QRegExp InputValidator::usernameRegex("^[a-zA-Z0-9_\\-]{3,30}$");

InputValidator::InputValidator() {
}

// Email validation
bool InputValidator::isValidEmail(const QString &email) {
	if(email.trimmed().isEmpty()) return false;
	return emailRegex.exactMatch(email.trimmed());
}

QString InputValidator::sanitizeEmail(const QString &email) {
	return email.trimmed().toLower();
}

// Phone number validation
bool InputValidator::isValidPhone(const QString &phone) {
	if(phone.trimmed().isEmpty()) return false;
	return phoneRegex.exactMatch(phone.trimmed());
}

QString InputValidator::sanitizePhone(const QString &phone) {
	QString sanitized = phone.trimmed();
	// Remove all non-numeric characters except + and spaces
	sanitized.replace(QRegExp("[^0-9+\\s\\-()]"), "");
	return sanitized;
}

// Tax number validation (basic - can be customized per country)
bool InputValidator::isValidTaxNumber(const QString &taxNumber) {
	QString clean = taxNumber.trimmed();
	if(clean.isEmpty()) return false;
	// Basic validation: alphanumeric, 5-20 characters
	QRegExp taxRegex("^[A-Z0-9\\-]{5,20}$");
	return taxRegex.exactMatch(clean.toUpper());
}

QString InputValidator::sanitizeTaxNumber(const QString &taxNumber) {
	return taxNumber.trimmed().toUpper().replace(QRegExp("[^A-Z0-9\\-]"), "");
}

// Barcode validation (EAN-13)
bool InputValidator::isValidEAN13(const QString &barcode) {
	QString clean = barcode.trimmed();
	if(clean.length() != 13) return false;

	// Check if all characters are digits
	for(int i = 0; i < clean.length(); i++) {
		if(!clean[i].isDigit()) return false;
	}

	// Calculate checksum
	int sum = 0;
	for(int i = 0; i < 12; i++) {
		int digit = QString(clean[i]).toInt();
		sum += (i % 2 == 0) ? digit : digit * 3;
	}

	int checksum = (10 - (sum % 10)) % 10;
	return checksum == QString(clean[12]).toInt();
}

QString InputValidator::sanitizeBarcode(const QString &barcode) {
	return barcode.trimmed().replace(QRegExp("[^0-9]"), "");
}

// String sanitization
QString InputValidator::sanitizeString(const QString &input, int maxLength) {
	QString sanitized = input.trimmed();

	// Remove control characters
	sanitized.replace(QRegExp("[\\x00-\\x1F\\x7F]"), "");

	// Truncate to max length
	if(sanitized.length() > maxLength) {
		sanitized = sanitized.left(maxLength);
	}

	return sanitized;
}

QString InputValidator::sanitizeSQLString(const QString &input) {
	QString sanitized = input;

	// Escape single quotes
	sanitized.replace("'", "''");

	// Remove or escape other dangerous characters
	sanitized.replace("\\", "\\\\");
	sanitized.replace("\0", "");

	return sanitized;
}

QString InputValidator::removeHTMLTags(const QString &input) {
	QString clean = input;
	clean.replace(QRegExp("<[^>]*>"), "");
	return clean;
}

QString InputValidator::escapeSpecialCharacters(const QString &input) {
	QString escaped = input;
	escaped.replace("&", "&amp;");
	escaped.replace("<", "&lt;");
	escaped.replace(">", "&gt;");
	escaped.replace("\"", "&quot;");
	escaped.replace("'", "&#39;");
	return escaped;
}

// Numeric validation
bool InputValidator::isValidInteger(const QString &input) {
	bool ok;
	input.toInt(&ok);
	return ok;
}

bool InputValidator::isValidDecimal(const QString &input) {
	bool ok;
	input.toDouble(&ok);
	return ok;
}

bool InputValidator::isValidPrice(const QString &input) {
	bool ok;
	double value = input.toDouble(&ok);
	return ok && value >= 0 && value < 1000000;
}

bool InputValidator::isInRange(double value, double min, double max) {
	return value >= min && value <= max;
}

// Date validation
bool InputValidator::isValidDate(const QString &dateString, const QString &format) {
	QDate date = QDate::fromString(dateString, format);
	return date.isValid();
}

bool InputValidator::isDateInRange(const QDate &date, const QDate &min, const QDate &max) {
	return date >= min && date <= max;
}

// Password validation
bool InputValidator::isStrongPassword(const QString &password) {
	if(password.length() < 8) return false;

	bool hasUpper = false;
	bool hasLower = false;
	bool hasDigit = false;
	bool hasSpecial = false;

	for(int i = 0; i < password.length(); i++) {
		QChar ch = password[i];
		if(ch.isUpper()) hasUpper = true;
		if(ch.isLower()) hasLower = true;
		if(ch.isDigit()) hasDigit = true;
		if(!ch.isLetterOrNumber()) hasSpecial = true;
	}

	return hasUpper && hasLower && hasDigit && hasSpecial;
}

QString InputValidator::getPasswordStrength(const QString &password) {
	if(password.length() < 6) return "Weak";
	if(password.length() < 8) return "Fair";

	int score = 0;
	if(password.length() >= 12) score++;
	if(password.contains(QRegExp("[A-Z]"))) score++;
	if(password.contains(QRegExp("[a-z]"))) score++;
	if(password.contains(QRegExp("[0-9]"))) score++;
	if(password.contains(QRegExp("[^A-Za-z0-9]"))) score++;

	if(score >= 5) return "Very Strong";
	if(score >= 4) return "Strong";
	if(score >= 3) return "Good";
	return "Fair";
}

bool InputValidator::meetsPasswordPolicy(const QString &password, QString &errorMessage) {
	if(password.length() < 8) {
		errorMessage = "Password must be at least 8 characters long";
		return false;
	}

	if(!password.contains(QRegExp("[A-Z]"))) {
		errorMessage = "Password must contain at least one uppercase letter";
		return false;
	}

	if(!password.contains(QRegExp("[a-z]"))) {
		errorMessage = "Password must contain at least one lowercase letter";
		return false;
	}

	if(!password.contains(QRegExp("[0-9]"))) {
		errorMessage = "Password must contain at least one number";
		return false;
	}

	if(!password.contains(QRegExp("[^A-Za-z0-9]"))) {
		errorMessage = "Password must contain at least one special character";
		return false;
	}

	errorMessage = "";
	return true;
}

// Username validation
bool InputValidator::isValidUsername(const QString &username) {
	return usernameRegex.exactMatch(username.trimmed());
}

QString InputValidator::sanitizeUsername(const QString &username) {
	QString sanitized = username.trimmed().toLower();
	sanitized.replace(QRegExp("[^a-z0-9_\\-]"), "");
	return sanitized;
}

// URL validation
bool InputValidator::isValidURL(const QString &url) {
	return urlRegex.exactMatch(url.trimmed());
}

QString InputValidator::sanitizeURL(const QString &url) {
	QString sanitized = url.trimmed();
	// Basic sanitization - remove dangerous protocols
	if(sanitized.startsWith("javascript:", Qt::CaseInsensitive) ||
	   sanitized.startsWith("data:", Qt::CaseInsensitive) ||
	   sanitized.startsWith("file:", Qt::CaseInsensitive)) {
		return "";
	}
	return sanitized;
}

// Credit card validation (Luhn algorithm)
bool InputValidator::isValidCreditCard(const QString &cardNumber) {
	QString clean = cardNumber;
	clean.replace(QRegExp("[^0-9]"), "");

	if(clean.length() < 13 || clean.length() > 19) return false;

	int sum = 0;
	bool alternate = false;

	for(int i = clean.length() - 1; i >= 0; i--) {
		int digit = QString(clean[i]).toInt();

		if(alternate) {
			digit *= 2;
			if(digit > 9) digit -= 9;
		}

		sum += digit;
		alternate = !alternate;
	}

	return (sum % 10 == 0);
}

// IBAN validation (basic)
bool InputValidator::isValidIBAN(const QString &iban) {
	QString clean = iban.toUpper();
	clean.replace(QRegExp("[^A-Z0-9]"), "");

	if(clean.length() < 15 || clean.length() > 34) return false;

	// Basic format check (2 letters, 2 digits, then alphanumeric)
	QRegExp ibanRegex("^[A-Z]{2}[0-9]{2}[A-Z0-9]+$");
	return ibanRegex.exactMatch(clean);
}

// General validation
bool InputValidator::isEmpty(const QString &input) {
	return input.trimmed().isEmpty();
}

bool InputValidator::hasLength(const QString &input, int minLength, int maxLength) {
	int len = input.trimmed().length();
	return len >= minLength && len <= maxLength;
}

bool InputValidator::containsOnly(const QString &input, const QString &allowedChars) {
	for(int i = 0; i < input.length(); i++) {
		if(!allowedChars.contains(input[i])) {
			return false;
		}
	}
	return true;
}

bool InputValidator::matches(const QString &input, const QString &pattern) {
	QRegExp regex(pattern);
	return regex.exactMatch(input);
}

// SQL Injection prevention
bool InputValidator::containsSQLKeywords(const QString &input) {
	QString upper = input.toUpper();
	QStringList sqlKeywords;
	sqlKeywords << "SELECT" << "INSERT" << "UPDATE" << "DELETE" << "DROP"
	            << "CREATE" << "ALTER" << "EXEC" << "EXECUTE" << "UNION"
	            << "DECLARE" << "CAST" << "CONVERT" << "SCRIPT" << "--"
	            << "/*" << "*/" << "XP_" << "SP_" << "0x";

	foreach(QString keyword, sqlKeywords) {
		if(upper.contains(keyword)) {
			return true;
		}
	}

	return false;
}

bool InputValidator::isSafeForSQL(const QString &input) {
	// Check for SQL injection patterns
	if(containsSQLKeywords(input)) return false;

	// Check for suspicious patterns
	QStringList dangerousPatterns;
	dangerousPatterns << "'" << "\"" << ";" << "--" << "/*" << "*/"
	                  << "=" << "OR" << "AND" << "1=1" << "' OR '" << "';";

	foreach(QString pattern, dangerousPatterns) {
		if(input.contains(pattern, Qt::CaseInsensitive)) {
			return false;
		}
	}

	return true;
}

// XSS prevention
bool InputValidator::containsXSSPatterns(const QString &input) {
	QString lower = input.toLower();
	QStringList xssPatterns;
	xssPatterns << "<script" << "</script>" << "javascript:" << "onerror="
	            << "onload=" << "onclick=" << "<iframe" << "<embed" << "<object"
	            << "eval(" << "alert(" << "document.cookie";

	foreach(QString pattern, xssPatterns) {
		if(lower.contains(pattern)) {
			return true;
		}
	}

	return false;
}

QString InputValidator::escapeHTML(const QString &input) {
	QString escaped = input;
	escaped.replace("&", "&amp;");
	escaped.replace("<", "&lt;");
	escaped.replace(">", "&gt;");
	escaped.replace("\"", "&quot;");
	escaped.replace("'", "&#x27;");
	escaped.replace("/", "&#x2F;");
	return escaped;
}
