/**************************************************************************
**   File: errorlogger.h
**   Created on: 2025-11-18
**   Author: Claude Code Assistant
**   Copyright: SphinxSolutions.
**   Purpose: Centralized error logging and security monitoring
**************************************************************************/
#ifndef ERRORLOGGER_H
#define ERRORLOGGER_H

#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QMutex>

class ErrorLogger
{
public:
	enum LogLevel {
		DEBUG = 0,
		INFO = 1,
		WARNING = 2,
		ERROR = 3,
		CRITICAL = 4,
		SECURITY = 5
	};

	enum LogCategory {
		DATABASE,
		AUTHENTICATION,
		VALIDATION,
		BUSINESS_LOGIC,
		UI,
		SECURITY_INCIDENT,
		PERFORMANCE,
		GENERAL
	};

	static ErrorLogger* GetInstance();

	// Core logging methods
	void log(LogLevel level, LogCategory category, const QString &message);
	void logDebug(const QString &message, LogCategory category = GENERAL);
	void logInfo(const QString &message, LogCategory category = GENERAL);
	void logWarning(const QString &message, LogCategory category = GENERAL);
	void logError(const QString &message, LogCategory category = GENERAL);
	void logCritical(const QString &message, LogCategory category = GENERAL);
	void logSecurity(const QString &message, const QString &user = "", const QString &ipAddress = "");

	// Database-specific logging
	void logDatabaseError(const QString &query, const QString &error);
	void logDatabaseQuery(const QString &query, int executionTimeMs = 0);

	// Authentication logging
	void logLoginAttempt(const QString &username, bool success, const QString &ipAddress = "");
	void logLogout(const QString &username);
	void logPasswordChange(const QString &username);

	// Validation logging
	void logValidationError(const QString &field, const QString &value, const QString &error);
	void logSuspiciousInput(const QString &field, const QString &value, const QString &reason);

	// Security incident logging
	void logSQLInjectionAttempt(const QString &input, const QString &source);
	void logXSSAttempt(const QString &input, const QString &source);
	void logUnauthorizedAccess(const QString &user, const QString &resource);

	// Configuration
	void setLogLevel(LogLevel minLevel);
	void setLogFile(const QString &filePath);
	void enableConsoleOutput(bool enable);
	void enableFileOutput(bool enable);
	void setMaxLogSize(qint64 maxBytes); // Rotate log when size exceeded

	// Log management
	void clearLog();
	void rotateLogs();
	QString getLogContents(int lastNLines = 100);
	QStringList getLogFiles();

	// Statistics
	int getErrorCount(LogLevel level = ERROR);
	int getSecurityIncidentCount();
	void resetStatistics();

private:
	ErrorLogger();
	~ErrorLogger();

	static ErrorLogger* p_instance;
	static QMutex mutex;

	QString formatLogMessage(LogLevel level, LogCategory category, const QString &message);
	QString logLevelToString(LogLevel level);
	QString categoryToString(LogCategory category);
	void writeToFile(const QString &message);
	void writeToConsole(const QString &message);
	void checkAndRotateLog();

	QString logFilePath;
	LogLevel minLogLevel;
	bool consoleOutputEnabled;
	bool fileOutputEnabled;
	qint64 maxLogSizeBytes;

	// Statistics
	int errorCounts[6]; // One for each LogLevel
	int securityIncidentCount;

	QFile* logFile;
	QTextStream* logStream;
};

#endif // ERRORLOGGER_H
