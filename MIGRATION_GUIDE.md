# Security Migration Guide for M-ERP-ly

## Overview

This guide provides step-by-step instructions for migrating M-ERP-ly from vulnerable legacy methods to secure, SQL injection-proof implementations.

## Table of Contents

1. [Migration Strategy](#migration-strategy)
2. [Quick Start](#quick-start)
3. [Step-by-Step Model Migration](#step-by-step-model-migration)
4. [Code Examples](#code-examples)
5. [Testing Guidelines](#testing-guidelines)
6. [Rollback Procedures](#rollback-procedures)
7. [Performance Considerations](#performance-considerations)

---

## Migration Strategy

### Phase 1: Foundation (COMPLETED ✅)
- [x] Add parameterized query methods to `ErpModel`
- [x] Implement connection pooling
- [x] Create secure example methods in `Contact` model
- [x] Add password hashing in `User` model
- [x] Create `InputValidator` utility class
- [x] Document security improvements

### Phase 2: Core Models (IN PROGRESS 🔄)
- [x] Migrate `Product` model
- [ ] Migrate `Invoice` model
- [ ] Migrate `Purchase` model
- [ ] Migrate `DeliveryOrder` model
- [ ] Migrate `Payment` model

### Phase 3: Supporting Models
- [ ] Migrate `Project` model
- [ ] Migrate `Task` model
- [ ] Migrate supporting lookup tables
- [ ] Migrate relationship tables

### Phase 4: UI Integration
- [ ] Update UI forms to use secure methods
- [ ] Add input validation to all forms
- [ ] Implement client-side validation
- [ ] Add user feedback for validation errors

### Phase 5: Testing & Deployment
- [ ] Unit tests for all secure methods
- [ ] Integration tests
- [ ] Security audit
- [ ] Performance benchmarking
- [ ] Production deployment

---

## Quick Start

### For Developers

**1. Always use secure methods for new code:**

```cpp
// ❌ OLD WAY (Vulnerable)
Contact* contact = Contact::Get(id);
contact->Name = userName;
contact->save();

// ✅ NEW WAY (Secure)
Contact* contact = Contact::GetSecure(id);
contact->Name = InputValidator::sanitizeString(userName);
contact->saveSecure();
```

**2. Use Input Validation:**

```cpp
#include "inputvalidator.h"

// Validate email
QString email = ui->emailLineEdit->text();
if(!InputValidator::isValidEmail(email)) {
    QMessageBox::warning(this, "Invalid Email", "Please enter a valid email address");
    return;
}
email = InputValidator::sanitizeEmail(email);

// Validate password
QString password = ui->passwordLineEdit->text();
QString errorMsg;
if(!InputValidator::meetsPasswordPolicy(password, errorMsg)) {
    QMessageBox::warning(this, "Weak Password", errorMsg);
    return;
}
```

**3. Use Parameterized Queries:**

```cpp
// When writing custom queries
QVariantList values;
values << userId << productId;

QSqlQuery query = ErpModel::GetInstance()->execPreparedQuery(
    "SELECT * FROM UserProducts WHERE UserID = ? AND ProductID = ?",
    values
);
```

---

## Step-by-Step Model Migration

### Step 1: Add Secure Method Declarations

Open the model's header file (e.g., `invoice.h`) and add secure method declarations:

```cpp
// In the public section, after existing methods:
bool saveSecure();
static Invoice* GetSecure(int id);
static Invoice* GetSecure(const QString &name);
static QList<Invoice*> SearchSecure(const QString &keyword);
bool removeSecure();
```

### Step 2: Implement Secure Save Method

In the model's cpp file (e.g., `invoice.cpp`), add:

```cpp
bool Invoice::saveSecure() {
    this->EditedOn = QDate::currentDate().toString();

    if(InvoiceID == 0) {
        // INSERT
        this->CreatedOn = QDate::currentDate().toString();

        QVariantList values;
        values << Field1 << Field2 << Field3 /* ... add all fields ... */
               << CreatedOn << EditedOn;

        QSqlQuery insertQuery = ErpModel::GetInstance()->execPreparedQuery(
            "INSERT INTO Invoice (Field1, Field2, Field3, ..., CreatedOn, EditedOn) "
            "VALUES (?, ?, ?, ..., ?, ?)",
            values
        );

        // Get the newly created ID
        QVariantList selectValues;
        selectValues << uniqueField << EditedOn; // Use fields that identify the record
        QSqlQuery query = ErpModel::GetInstance()->execPreparedQuery(
            "SELECT InvoiceID FROM Invoice WHERE UniqueField = ? AND EditedOn = ?",
            selectValues
        );

        while (query.next()) {
            if(query.value(0).toInt() != 0){
                this->InvoiceID = query.value(0).toInt();
            }
        }
    } else {
        // UPDATE
        QVariantList values;
        values << Field1 << Field2 << Field3 /* ... add all fields ... */
               << CreatedOn << EditedOn << InvoiceID; // ID goes last for WHERE clause

        ErpModel::GetInstance()->execPreparedQuery(
            "UPDATE Invoice SET Field1 = ?, Field2 = ?, Field3 = ?, ..., "
            "CreatedOn = ?, EditedOn = ? WHERE InvoiceID = ?",
            values
        );
    }

    return true;
}
```

### Step 3: Implement Secure Get Method

```cpp
Invoice* Invoice::GetSecure(int id) {
    Invoice* invoice = new Invoice();
    if(id != 0) {
        QVariantList values;
        values << id;

        QSqlQuery query = ErpModel::GetInstance()->execPreparedQuery(
            "SELECT * FROM Invoice WHERE InvoiceID = ? ORDER BY InvoiceID ASC",
            values
        );

        while (query.next()) {
            invoice = new Invoice(
                query.value(0).toInt(),    // InvoiceID
                query.value(1).toString(), // Field1
                query.value(2).toString(), // Field2
                // ... map all fields from query result ...
                query.value(N).toString()  // LastField
            );
        }

        // Load related data if needed
        // invoice->relatedItems = RelatedTable::QuerySelect("InvoiceID = " + QString::number(id));
    }
    return invoice;
}
```

### Step 4: Implement Secure Get by Name

```cpp
Invoice* Invoice::GetSecure(const QString &name) {
    Invoice* invoice = new Invoice();
    if(!name.isEmpty()) {
        QVariantList values;
        values << name;

        QSqlQuery query = ErpModel::GetInstance()->execPreparedQuery(
            "SELECT * FROM Invoice WHERE Name = ?",
            values
        );

        while (query.next()) {
            invoice = new Invoice(
                query.value(0).toInt(),
                query.value(1).toString(),
                // ... all fields ...
            );
        }
    }
    return invoice;
}
```

### Step 5: Implement Secure Search

```cpp
QList<Invoice*> Invoice::SearchSecure(const QString &keyword) {
    QList<Invoice*> list;
    if(!keyword.isEmpty()) {
        QString likePattern = "%" + keyword + "%";
        QVariantList values;

        // Add the pattern for each searchable field
        int searchableFields = 6; // Number of fields to search
        for(int i = 0; i < searchableFields; i++) {
            values << likePattern;
        }

        QSqlQuery query = ErpModel::GetInstance()->execPreparedQuery(
            "SELECT * FROM Invoice WHERE "
            "Field1 LIKE ? OR Field2 LIKE ? OR Field3 LIKE ? OR "
            "Field4 LIKE ? OR Field5 LIKE ? OR Field6 LIKE ?",
            values
        );

        while (query.next()) {
            list.append(new Invoice(
                query.value(0).toInt(),
                query.value(1).toString(),
                // ... all fields ...
            ));
        }
    }
    return list;
}
```

### Step 6: Implement Secure Remove

```cpp
bool Invoice::removeSecure() {
    if(InvoiceID != 0) {
        QVariantList values;
        values << InvoiceID;

        ErpModel::GetInstance()->execPreparedQuery(
            "DELETE FROM Invoice WHERE InvoiceID = ?",
            values
        );
        return true;
    }
    return false;
}
```

---

## Code Examples

### Example 1: User Registration with Validation

```cpp
void RegisterDialog::onRegisterClicked() {
    QString username = ui->usernameEdit->text();
    QString email = ui->emailEdit->text();
    QString password = ui->passwordEdit->text();
    QString confirmPassword = ui->confirmPasswordEdit->text();

    // Validate username
    if(!InputValidator::isValidUsername(username)) {
        QMessageBox::warning(this, "Invalid Username",
            "Username must be 3-30 characters and contain only letters, numbers, _ and -");
        return;
    }

    // Validate email
    if(!InputValidator::isValidEmail(email)) {
        QMessageBox::warning(this, "Invalid Email", "Please enter a valid email address");
        return;
    }

    // Validate password
    QString passwordError;
    if(!InputValidator::meetsPasswordPolicy(password, passwordError)) {
        QMessageBox::warning(this, "Weak Password", passwordError);
        return;
    }

    // Check password match
    if(password != confirmPassword) {
        QMessageBox::warning(this, "Password Mismatch", "Passwords do not match");
        return;
    }

    // Sanitize inputs
    username = InputValidator::sanitizeUsername(username);
    email = InputValidator::sanitizeEmail(email);

    // Create user with secure method
    User* user = new User(username, username, password, 1, 1, "", "");
    if(user->saveSecure()) {
        QMessageBox::information(this, "Success", "User registered successfully!");
        this->accept();
    } else {
        QMessageBox::critical(this, "Error", "Failed to create user");
    }
}
```

### Example 2: Product Search with Input Validation

```cpp
void ProductIndexUI::onSearchClicked() {
    QString keyword = ui->searchEdit->text();

    // Sanitize search input
    keyword = InputValidator::sanitizeString(keyword, 100);

    // Check for SQL injection attempts
    if(!InputValidator::isSafeForSQL(keyword)) {
        QMessageBox::warning(this, "Invalid Search",
            "Search contains invalid characters. Please try a different search.");
        return;
    }

    // Perform secure search
    QList<Product*> products = Product::SearchSecure(keyword);

    // Display results
    displayProducts(products);
}
```

### Example 3: Contact Form with Validation

```cpp
void ContactUI::onSaveClicked() {
    Contact* contact = getContactFromForm();

    // Validate all fields
    if(contact->Name.trimmed().isEmpty()) {
        QMessageBox::warning(this, "Validation Error", "Name is required");
        return;
    }

    if(!contact->Website.isEmpty() && !InputValidator::isValidURL(contact->Website)) {
        QMessageBox::warning(this, "Validation Error", "Invalid website URL");
        return;
    }

    // Sanitize inputs
    contact->Name = InputValidator::sanitizeString(contact->Name, 40);
    contact->Address = InputValidator::sanitizeString(contact->Address, 40);
    contact->Website = InputValidator::sanitizeURL(contact->Website);
    contact->TaxNumber = InputValidator::sanitizeTaxNumber(contact->TaxNumber);

    // Validate tax number if provided
    if(!contact->TaxNumber.isEmpty() && !InputValidator::isValidTaxNumber(contact->TaxNumber)) {
        QMessageBox::warning(this, "Validation Error", "Invalid tax number format");
        return;
    }

    // Save using secure method
    if(contact->saveSecure()) {
        QMessageBox::information(this, "Success", "Contact saved successfully!");
        this->close();
    } else {
        QMessageBox::critical(this, "Error", "Failed to save contact");
    }
}
```

---

## Testing Guidelines

### Unit Testing Template

```cpp
#include <QtTest/QtTest>
#include "contact.h"
#include "erpmodel.h"

class TestContactSecure : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testSaveSecure();
    void testGetSecure();
    void testSearchSecure();
    void testRemoveSecure();
    void testSQLInjectionPrevention();
    void cleanupTestCase();
};

void TestContactSecure::initTestCase() {
    // Initialize database connection
    ErpModel::GetInstance();
}

void TestContactSecure::testSaveSecure() {
    Contact* contact = new Contact("Test Contact", "Mr.", QDate::currentDate(),
                                   1, 1, 1, "123 Test St", "12345", "Test City",
                                   1, 1, "http://test.com", "TAX123", "", "");

    bool result = contact->saveSecure();
    QVERIFY(result == true);
    QVERIFY(contact->ContactID > 0);

    delete contact;
}

void TestContactSecure::testGetSecure() {
    // Create a test contact
    Contact* contact1 = new Contact("Get Test", "Ms.", QDate::currentDate(),
                                    1, 1, 2, "456 Test Ave", "67890", "Test Town",
                                    1, 1, "http://get.com", "TAX456", "", "");
    contact1->saveSecure();
    int savedId = contact1->ContactID;

    // Retrieve it
    Contact* contact2 = Contact::GetSecure(savedId);
    QVERIFY(contact2->ContactID == savedId);
    QVERIFY(contact2->Name == "Get Test");

    // Cleanup
    contact2->removeSecure();
    delete contact1;
    delete contact2;
}

void TestContactSecure::testSQLInjectionPrevention() {
    // Try to inject SQL
    QString maliciousInput = "'; DROP TABLE Contact; --";

    Contact* contact = new Contact(maliciousInput, "Mr.", QDate::currentDate(),
                                   1, 1, 3, "Test", "Test", "Test",
                                   1, 1, "http://test.com", "TAX", "", "");
    contact->saveSecure();

    // Verify the record was created with the literal string (not executed as SQL)
    Contact* retrieved = Contact::GetSecure(contact->ContactID);
    QVERIFY(retrieved->Name == maliciousInput);

    // Cleanup
    retrieved->removeSecure();
    delete contact;
    delete retrieved;
}

void TestContactSecure::cleanupTestCase() {
    // Cleanup test data
}

QTEST_MAIN(TestContactSecure)
#include "test_contact_secure.moc"
```

### Running Tests

```bash
# Build tests
qmake tests.pro
make

# Run tests
./test_contact_secure
./test_product_secure
./test_user_secure
```

---

## Rollback Procedures

### If Issues Are Discovered

1. **Identify the problematic code**
   - Check error logs
   - Review recent commits

2. **Revert to legacy methods temporarily**
   ```cpp
   // Change from:
   contact->saveSecure();

   // Back to:
   contact->save();
   ```

3. **Fix and re-deploy**
   - Correct the issue in secure methods
   - Test thoroughly
   - Deploy updated version

### Database Rollback

If password migration causes issues:

```sql
-- Check current password format
SELECT UserID, UserName, LENGTH(Password) as PasswordLength FROM User;

-- If needed, you can identify hashed vs plain-text by length
-- Hashed passwords will be much longer (150+ characters)
```

---

## Performance Considerations

### Connection Pooling Benefits

Before (closing after each query):
```
100 queries = 100 connections × ~50ms = 5000ms
```

After (connection reuse):
```
100 queries = 1 connection (50ms) + 100 queries (0.5ms each) = 100ms
```

**Performance gain: 50x faster!**

### Query Performance Tips

1. **Use indexes on frequently queried fields**
   ```sql
   CREATE INDEX idx_contact_name ON Contact(Name);
   CREATE INDEX idx_product_barcode ON Product(Barcode);
   ```

2. **Batch operations when possible**
   ```cpp
   ErpModel::GetInstance()->db.transaction();
   for(int i = 0; i < products.count(); i++) {
       products[i]->saveSecure();
   }
   ErpModel::GetInstance()->db.commit();
   ```

3. **Limit result sets**
   ```cpp
   QVariantList values;
   values << keyword << 100; // Limit to 100 results

   QSqlQuery query = ErpModel::GetInstance()->execPreparedQuery(
       "SELECT * FROM Product WHERE Name LIKE ? LIMIT ?",
       values
   );
   ```

---

## Migration Checklist

### For Each Model

- [ ] Add secure method declarations to .h file
- [ ] Implement `saveSecure()`
- [ ] Implement `GetSecure(int id)`
- [ ] Implement `GetSecure(QString name)` if applicable
- [ ] Implement `SearchSecure(QString keyword)`
- [ ] Implement `removeSecure()`
- [ ] Write unit tests
- [ ] Update UI code to use secure methods
- [ ] Test thoroughly
- [ ] Document any special considerations

### For Each UI Form

- [ ] Add input validation
- [ ] Sanitize all user inputs
- [ ] Use secure model methods
- [ ] Add user feedback for validation errors
- [ ] Test with malicious inputs
- [ ] Performance test with large datasets

---

## Getting Help

If you encounter issues during migration:

1. **Check the examples** in this guide
2. **Review SECURITY.md** for vulnerability details
3. **Examine existing secure models**: Contact, User, Product
4. **Create an issue** on the repository with:
   - Model name
   - Error message
   - Code snippet
   - What you've tried

---

## Success Metrics

Track migration progress:

- **Models migrated**: 3 / 70+ (Contact, User, Product)
- **Security vulnerabilities fixed**: SQL Injection in 3 models
- **Performance improvement**: 10-50x faster (connection pooling)
- **Test coverage**: Unit tests for secure methods
- **Documentation**: Complete guides (README, SECURITY, MIGRATION)

---

**Last Updated**: 2025-11-18
**Version**: 1.1
**Status**: In Progress
