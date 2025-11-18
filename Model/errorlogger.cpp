/**************************************************************************
**   File: errorlogger.cpp
**   Created on: 2025-11-18
**   Author: Claude Code Assistant
**   Copyright: SphinxSolutions.
**   Purpose: Centralized error logging implementation
**************************************************************************/
#include "errorlogger.h"
#include <QDir>
#include <QDebug>
#include <QFileInfo>

ErrorLogger* ErrorLogger::p_instance = nullptr;
QMutex ErrorLogger::mutex;

ErrorLogger::ErrorLogger() {
	logFilePath = "logs/erp.log";
	minLogLevel = INFO;
	consoleOutputEnabled = true;
	fileOutputEnabled = true;
	maxLogSizeBytes = 10 * 1024 * 1024; // 10 MB default
	logFile = nullptr;
	logStream = nullptr;
	securityIncidentCount = 0;

	for(int i = 0; i < 6; i++) {
		errorCounts[i] = 0;
	}

	// Create logs directory if it doesn't exist
	QDir().mkpath("logs");

	// Open log file
	logFile = new QFile(logFilePath);
	if(logFile->open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
		logStream = new QTextStream(logFile);
	}
}

ErrorLogger::~ErrorLogger() {
	if(logStream) {
		delete logStream;
		logStream = nullptr;
	}
	if(logFile) {
		logFile->close();
		delete logFile;
		logFile = nullptr;
	}
}

ErrorLogger* ErrorLogger::GetInstance() {
	if(!p_instance) {
		mutex.lock();
		if(!p_instance) {
			p_instance = new ErrorLogger();
		}
		mutex.unlock();
	}
	return p_instance;
}

void ErrorLogger::log(LogLevel level, LogCategory category, const QString &message) {
	if(level < minLogLevel) {
		return;
	}

	QString formattedMessage = formatLogMessage(level, category, message);

	mutex.lock();

	// Update statistics
	if(level >= 0 && level < 6) {
		errorCounts[level]++;
	}
	if(category == SECURITY_INCIDENT) {
		securityIncidentCount++;
	}

	// Write to outputs
	if(fileOutputEnabled) {
		writeToFile(formattedMessage);
	}
	if(consoleOutputEnabled) {
		writeToConsole(formattedMessage);
	}

	// Check if log rotation is needed
	checkAndRotateLog();

	mutex.unlock();
}

void ErrorLogger::logDebug(const QString &message, LogCategory category) {
	log(DEBUG, category, message);
}

void ErrorLogger::logInfo(const QString &message, LogCategory category) {
	log(INFO, category, message);
}

void ErrorLogger::logWarning(const QString &message, LogCategory category) {
	log(WARNING, category, message);
}

void ErrorLogger::logError(const QString &message, LogCategory category) {
	log(ERROR, category, message);
}

void ErrorLogger::logCritical(const QString &message, LogCategory category) {
	log(CRITICAL, category, message);
}

void ErrorLogger::logSecurity(const QString &message, const QString &user, const QString &ipAddress) {
	QString fullMessage = message;
	if(!user.isEmpty()) {
		fullMessage += " | User: " + user;
	}
	if(!ipAddress.isEmpty()) {
		fullMessage += " | IP: " + ipAddress;
	}
	log(SECURITY, SECURITY_INCIDENT, fullMessage);
}

void ErrorLogger::logDatabaseError(const QString &query, const QString &error) {
	QString message = "Database Error: " + error + " | Query: " + query;
	log(ERROR, DATABASE, message);
}

void ErrorLogger::logDatabaseQuery(const QString &query, int executionTimeMs) {
	if(executionTimeMs > 1000) {
		// Log slow queries
		QString message = "Slow Query (" + QString::number(executionTimeMs) + "ms): " + query;
		log(WARNING, PERFORMANCE, message);
	} else if(minLogLevel == DEBUG) {
		QString message = "Query (" + QString::number(executionTimeMs) + "ms): " + query;
		log(DEBUG, DATABASE, message);
	}
}

void ErrorLogger::logLoginAttempt(const QString &username, bool success, const QString &ipAddress) {
	QString message = success ? "Login successful: " : "Login failed: ";
	message += username;
	if(!ipAddress.isEmpty()) {
		message += " from " + ipAddress;
	}

	LogLevel level = success ? INFO : WARNING;
	log(level, AUTHENTICATION, message);
}

void ErrorLogger::logLogout(const QString &username) {
	log(INFO, AUTHENTICATION, "User logged out: " + username);
}

void ErrorLogger::logPasswordChange(const QString &username) {
	log(INFO, AUTHENTICATION, "Password changed for user: " + username);
}

void ErrorLogger::logValidationError(const QString &field, const QString &value, const QString &error) {
	QString message = "Validation failed for field '" + field + "': " + error;
	log(WARNING, VALIDATION, message);
}

void ErrorLogger::logSuspiciousInput(const QString &field, const QString &value, const QString &reason) {
	QString message = "Suspicious input in field '" + field + "': " + reason + " | Value: " + value;
	log(SECURITY, VALIDATION, message);
}

void ErrorLogger::logSQLInjectionAttempt(const QString &input, const QString &source) {
	QString message = "SQL Injection attempt detected from " + source + " | Input: " + input;
	log(SECURITY, SECURITY_INCIDENT, message);
}

void ErrorLogger::logXSSAttempt(const QString &input, const QString &source) {
	QString message = "XSS attempt detected from " + source + " | Input: " + input;
	log(SECURITY, SECURITY_INCIDENT, message);
}

void ErrorLogger::logUnauthorizedAccess(const QString &user, const QString &resource) {
	QString message = "Unauthorized access attempt by " + user + " to resource: " + resource;
	log(SECURITY, SECURITY_INCIDENT, message);
}

void ErrorLogger::setLogLevel(LogLevel minLevel) {
	minLogLevel = minLevel;
}

void ErrorLogger::setLogFile(const QString &filePath) {
	mutex.lock();

	// Close existing file
	if(logStream) {
		delete logStream;
		logStream = nullptr;
	}
	if(logFile) {
		logFile->close();
		delete logFile;
		logFile = nullptr;
	}

	// Open new file
	logFilePath = filePath;
	QFileInfo fileInfo(filePath);
	QDir().mkpath(fileInfo.absolutePath());

	logFile = new QFile(logFilePath);
	if(logFile->open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
		logStream = new QTextStream(logFile);
	}

	mutex.unlock();
}

void ErrorLogger::enableConsoleOutput(bool enable) {
	consoleOutputEnabled = enable;
}

void ErrorLogger::enableFileOutput(bool enable) {
	fileOutputEnabled = enable;
}

void ErrorLogger::setMaxLogSize(qint64 maxBytes) {
	maxLogSizeBytes = maxBytes;
}

void ErrorLogger::clearLog() {
	mutex.lock();

	if(logStream) {
		delete logStream;
		logStream = nullptr;
	}
	if(logFile) {
		logFile->close();
		delete logFile;
	}

	// Truncate file
	logFile = new QFile(logFilePath);
	if(logFile->open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
		logStream = new QTextStream(logFile);
	}

	mutex.unlock();
}

void ErrorLogger::rotateLogs() {
	mutex.lock();

	// Close current log
	if(logStream) {
		delete logStream;
		logStream = nullptr;
	}
	if(logFile) {
		logFile->close();
		delete logFile;
		logFile = nullptr;
	}

	// Rename old logs
	for(int i = 9; i >= 1; i--) {
		QString oldName = logFilePath + "." + QString::number(i);
		QString newName = logFilePath + "." + QString::number(i + 1);
		if(QFile::exists(oldName)) {
			QFile::remove(newName);
			QFile::rename(oldName, newName);
		}
	}

	// Rename current log to .1
	if(QFile::exists(logFilePath)) {
		QFile::rename(logFilePath, logFilePath + ".1");
	}

	// Create new log file
	logFile = new QFile(logFilePath);
	if(logFile->open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
		logStream = new QTextStream(logFile);
	}

	mutex.unlock();
}

QString ErrorLogger::getLogContents(int lastNLines) {
	QFile file(logFilePath);
	if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		return "";
	}

	QStringList lines;
	QTextStream in(&file);
	while(!in.atEnd()) {
		lines.append(in.readLine());
	}
	file.close();

	// Return last N lines
	if(lastNLines > 0 && lines.count() > lastNLines) {
		return lines.mid(lines.count() - lastNLines).join("\n");
	}

	return lines.join("\n");
}

QStringList ErrorLogger::getLogFiles() {
	QStringList files;
	QDir logDir(QFileInfo(logFilePath).absolutePath());

	QStringList filters;
	filters << QFileInfo(logFilePath).fileName() + "*";

	foreach(QString file, logDir.entryList(filters, QDir::Files, QDir::Name)) {
		files.append(logDir.absoluteFilePath(file));
	}

	return files;
}

int ErrorLogger::getErrorCount(LogLevel level) {
	if(level >= 0 && level < 6) {
		return errorCounts[level];
	}
	return 0;
}

int ErrorLogger::getSecurityIncidentCount() {
	return securityIncidentCount;
}

void ErrorLogger::resetStatistics() {
	for(int i = 0; i < 6; i++) {
		errorCounts[i] = 0;
	}
	securityIncidentCount = 0;
}

QString ErrorLogger::formatLogMessage(LogLevel level, LogCategory category, const QString &message) {
	QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss.zzz");
	QString levelStr = logLevelToString(level);
	QString categoryStr = categoryToString(category);

	return QString("[%1] [%2] [%3] %4")
		.arg(timestamp)
		.arg(levelStr)
		.arg(categoryStr)
		.arg(message);
}

QString ErrorLogger::logLevelToString(LogLevel level) {
	switch(level) {
		case DEBUG: return "DEBUG   ";
		case INFO: return "INFO    ";
		case WARNING: return "WARNING ";
		case ERROR: return "ERROR   ";
		case CRITICAL: return "CRITICAL";
		case SECURITY: return "SECURITY";
		default: return "UNKNOWN ";
	}
}

QString ErrorLogger::categoryToString(LogCategory category) {
	switch(category) {
		case DATABASE: return "DATABASE  ";
		case AUTHENTICATION: return "AUTH      ";
		case VALIDATION: return "VALIDATION";
		case BUSINESS_LOGIC: return "BUSINESS  ";
		case UI: return "UI        ";
		case SECURITY_INCIDENT: return "SECURITY  ";
		case PERFORMANCE: return "PERF      ";
		case GENERAL: return "GENERAL   ";
		default: return "UNKNOWN   ";
	}
}

void ErrorLogger::writeToFile(const QString &message) {
	if(logStream) {
		*logStream << message << "\n";
		logStream->flush();
	}
}

void ErrorLogger::writeToConsole(const QString &message) {
	qDebug() << message;
}

void ErrorLogger::checkAndRotateLog() {
	if(logFile && logFile->size() > maxLogSizeBytes) {
		rotateLogs();
	}
}
