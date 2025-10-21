# Security Policy

## Supported Versions

| Version | Supported          |
| ------- | ------------------ |
| 1.1.x   | :white_check_mark: |
| 1.0.x   | :x:                |

## Security Improvements (v1.1)

### 1. SQL Injection Prevention

**Problem**: All legacy model methods use string concatenation to build SQL queries, making them vulnerable to SQL injection attacks.

**Example of Vulnerable Code**:
```cpp
// VULNERABLE - Do not use!
QSqlQuery query = ErpModel::GetInstance()->qeryExec(
    "SELECT * FROM Contact WHERE Name = '" + userInput + "'"
);
```

**Solution**: Use parameterized queries with the new secure methods:
```cpp
// SECURE - Use this instead!
QVariantList values;
values << userInput;
QSqlQuery query = ErpModel::GetInstance()->execPreparedQuery(
    "SELECT * FROM Contact WHERE Name = ?",
    values
);
```

**Status**:
- ✅ Core `ErpModel` updated with `execPreparedQuery()` methods
- ✅ `Contact` model includes secure example methods
- ✅ `User` model includes secure authentication
- ⚠️ **70+ other models still need migration**

### 2. Password Security

**Problem**: Passwords were stored in plain text in the database.

**Solution**: Implemented SHA-256 password hashing with salt:

```cpp
// Hash password
QString hashedPassword = User::hashPassword("myPassword");

// Verify password
bool isValid = User::verifyPassword("inputPassword", hashedPassword);

// Secure authentication
User* user = User::authenticateSecure("username", "password");
```

**Status**:
- ✅ Password hashing implemented
- ✅ `User::saveSecure()` hashes passwords automatically
- ✅ `User::authenticateSecure()` verifies hashed passwords
- ⚠️ Legacy users still have plain-text passwords (backward compatible)
- 📝 **Recommendation**: Force password reset on next login

### 3. Database Connection Pooling

**Problem**: Database connections were opened and closed for every query, causing:
- Performance degradation
- Connection overhead
- Potential connection exhaustion

**Solution**: Implemented connection pooling with `ensureConnection()`:

```cpp
bool ErpModel::ensureConnection() {
    if (!db.isOpen()) {
        if (!db.open()) {
            return false;
        }
    }
    return true;
}
```

**Status**: ✅ Complete - all queries now reuse connections

## Known Vulnerabilities

### Critical Severity

#### 1. SQL Injection in Legacy Methods

**Affected Code**: All model classes except `Contact` and `User` secure methods

**Vulnerable Methods**:
- `save()` - INSERT/UPDATE with string concatenation
- `Get(int id)` - SELECT with string concatenation
- `Get(QString name)` - SELECT with string concatenation
- `Search(QString keyword)` - LIKE queries with string concatenation
- `remove()` - DELETE with string concatenation
- `QuerySelect(QString select)` - Direct query execution

**Example Attack**:
```cpp
// Attacker input: "'; DROP TABLE Contact; --"
Contact* contact = Contact::Get(attackerInput);
// Executes: SELECT * FROM Contact WHERE Name = ''; DROP TABLE Contact; --'
```

**Impact**:
- Data theft
- Data manipulation
- Data deletion
- Privilege escalation

**Mitigation**:
1. Use `*Secure()` methods where available
2. Migrate remaining models to parameterized queries
3. Input validation and sanitization
4. Principle of least privilege for database user

**Timeline**: High priority - should be addressed in next release

#### 2. Plain-Text Password Storage (Legacy Users)

**Affected**: Users created with `save()` instead of `saveSecure()`

**Impact**:
- Password exposure in database dumps
- Password exposure if database is compromised
- No protection against rainbow table attacks

**Mitigation**:
1. Force password reset for all existing users
2. Use only `saveSecure()` for user creation/updates
3. Consider adding password complexity requirements

**Timeline**: Should be addressed immediately

### High Severity

#### 3. No Session Timeout

**Problem**: User sessions never expire

**Impact**: Unauthorized access if workstation left unattended

**Recommendation**: Implement automatic session timeout (15-30 minutes of inactivity)

#### 4. No Failed Login Attempt Limiting

**Problem**: No protection against brute force attacks

**Impact**: Attackers can attempt unlimited login attempts

**Recommendation**:
- Implement account lockout after 5 failed attempts
- Add CAPTCHA after 3 failed attempts
- Log failed login attempts

#### 5. Weak Password Policy

**Problem**: No password complexity requirements

**Impact**: Users can set weak passwords like "123" or "password"

**Recommendation**:
- Minimum 8 characters
- Require uppercase, lowercase, numbers, and special characters
- Password strength indicator in UI

### Medium Severity

#### 6. No Audit Trail

**Problem**: No logging of data modifications

**Impact**: Cannot track who changed what and when (forensics impossible)

**Recommendation**: Add audit logging for:
- User login/logout
- Data creation/modification/deletion
- Access control changes
- Configuration changes

#### 7. Insufficient Input Validation

**Problem**: Limited validation of user inputs

**Impact**:
- Data corruption
- Application crashes
- Unexpected behavior

**Recommendation**: Add validation layer:
```cpp
class InputValidator {
public:
    static bool validateEmail(const QString &email);
    static bool validatePhone(const QString &phone);
    static bool validateTaxNumber(const QString &taxNumber);
    static QString sanitizeInput(const QString &input);
};
```

#### 8. Database Credentials in Source Code

**Problem**: Database credentials hardcoded in `erpmodel.cpp`

```cpp
db.setUserName("root");
db.setPassword("root");  // Hardcoded!
```

**Impact**:
- Credentials exposed in version control
- Cannot change without recompiling

**Recommendation**:
- Use configuration file (encrypted)
- Environment variables
- Secure credential storage

### Low Severity

#### 9. No HTTPS/TLS for Remote Database

**Problem**: If MySQL is configured for remote access, connection is not encrypted

**Impact**: Credentials and data transmitted in plain text

**Recommendation**:
- Use SSL/TLS for MySQL connections
- Configure Qt to use encrypted connections:
```cpp
db.setConnectOptions("MYSQL_OPT_SSL_KEY=client-key.pem;"
                     "MYSQL_OPT_SSL_CERT=client-cert.pem;"
                     "MYSQL_OPT_SSL_CA=ca-cert.pem");
```

#### 10. Default Admin Credentials

**Problem**: Default admin account with well-known credentials (`admin`/`admin`)

**Impact**: Easy unauthorized access if not changed

**Recommendation**:
- Force password change on first login
- Display warning until default password is changed
- Consider removing default admin account from init

## Secure Coding Guidelines

### For Developers

#### 1. Always Use Parameterized Queries

**DO**:
```cpp
QVariantList values;
values << userInput;
QSqlQuery query = ErpModel::GetInstance()->execPreparedQuery(
    "SELECT * FROM Table WHERE Field = ?", values
);
```

**DON'T**:
```cpp
QSqlQuery query = ErpModel::GetInstance()->qeryExec(
    "SELECT * FROM Table WHERE Field = '" + userInput + "'"
);
```

#### 2. Hash All Passwords

**DO**:
```cpp
User* user = new User("Name", "username", "password", 1, 1, "", "");
user->saveSecure();  // Hashes password automatically
```

**DON'T**:
```cpp
User* user = new User("Name", "username", "password", 1, 1, "", "");
user->save();  // Stores plain-text password!
```

#### 3. Validate All User Input

**DO**:
```cpp
QString sanitizedInput = input.trimmed();
if (sanitizedInput.isEmpty() || sanitizedInput.length() > 255) {
    QMessageBox::warning(0, "Validation Error", "Invalid input");
    return false;
}
// Use sanitizedInput
```

**DON'T**:
```cpp
// Directly use user input without validation
contact->Name = ui->nameLineEdit->text();
```

#### 4. Use Secure Methods

**DO**:
```cpp
Contact* contact = Contact::GetSecure(contactId);
contact->saveSecure();
```

**DON'T**:
```cpp
Contact* contact = Contact::Get(contactId);
contact->save();
```

#### 5. Implement Error Handling

**DO**:
```cpp
QSqlQuery query = ErpModel::GetInstance()->execPreparedQuery(queryStr, values);
if (query.lastError().isValid()) {
    qDebug() << "Query failed:" << query.lastError().text();
    return false;
}
```

**DON'T**:
```cpp
// Ignore errors
QSqlQuery query = ErpModel::GetInstance()->execPreparedQuery(queryStr, values);
// Continue without checking
```

## Migration Checklist

To fully secure the application, complete these tasks:

### Phase 1: Critical (Immediate)
- [ ] Migrate all `save()` methods to use parameterized queries
- [ ] Migrate all `Get()` methods to use parameterized queries
- [ ] Migrate all `remove()` methods to use parameterized queries
- [ ] Force password reset for existing users
- [ ] Change default admin password
- [ ] Add input validation layer

### Phase 2: High Priority (This Quarter)
- [ ] Implement session timeout
- [ ] Add failed login attempt limiting
- [ ] Implement password policy
- [ ] Add audit logging
- [ ] Move database credentials to config file
- [ ] Migrate all `Search()` methods to parameterized queries

### Phase 3: Medium Priority (Next Quarter)
- [ ] Add SSL/TLS for database connections
- [ ] Implement comprehensive error handling
- [ ] Add data sanitization utilities
- [ ] Create security unit tests
- [ ] Perform penetration testing
- [ ] Code security review

## Reporting a Vulnerability

If you discover a security vulnerability, please:

1. **DO NOT** create a public GitHub issue
2. Email security details to: [security contact email]
3. Include:
   - Description of the vulnerability
   - Steps to reproduce
   - Potential impact
   - Suggested fix (if available)

We will respond within 48 hours and provide a timeline for fix deployment.

## Security Update Policy

- **Critical vulnerabilities**: Patched within 24-48 hours
- **High severity**: Patched within 1 week
- **Medium severity**: Patched in next release
- **Low severity**: Addressed in quarterly updates

## Acknowledgments

Thank you to everyone who has contributed to improving the security of M-ERP-ly.

## References

- [OWASP SQL Injection Prevention](https://cheatsheetseries.owasp.org/cheatsheets/SQL_Injection_Prevention_Cheat_Sheet.html)
- [OWASP Password Storage Cheat Sheet](https://cheatsheetseries.owasp.org/cheatsheets/Password_Storage_Cheat_Sheet.html)
- [Qt SQL Security](https://doc.qt.io/qt-5/sql-programming.html#database-security)
- [CWE-89: SQL Injection](https://cwe.mitre.org/data/definitions/89.html)
- [CWE-259: Use of Hard-coded Password](https://cwe.mitre.org/data/definitions/259.html)

---

**Last Updated**: 2025-10-21
**Next Security Review**: 2025-11-21
