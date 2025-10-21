# M-ERP-ly

A comprehensive desktop Enterprise Resource Planning (ERP) system built with C++ and Qt Framework.

## Overview

M-ERP-ly is a full-featured business management application designed for small to medium-sized enterprises. It provides integrated modules for managing contacts, inventory, purchases, deliveries, invoicing, projects, and payments through a unified desktop interface.

## Features

### Core Modules

- **Contact Management (CRM)** - Comprehensive customer and supplier database with contact persons, emails, phones, and bank accounts
- **Product & Inventory Management** - Product catalog with categories, pricing, barcodes (EAN-13), and multi-warehouse support
- **Purchase Management** - Purchase orders with status tracking, returns, and supplier management
- **Delivery Management** - Delivery order creation, tracking, and return processing
- **Invoicing & Financial Management** - Invoice creation, serial numbering, periods, and financial tracking
- **Payment Management** - Payment recording with multiple payment types (Cash, Credit)
- **Project Management** - Project tracking with files, services, sales, and time booking
- **User Management** - Role-based access control with granular permissions

### Technical Features

- Multi-language support (Arabic included, extensible)
- Barcode generation and recognition (EAN-13)
- Print support for documents and invoices
- Database auto-migration and schema management
- Relational data model with foreign key constraints
- UTF-8 encoding for international character support

## Technology Stack

- **Language**: C++ (C++11 or later recommended)
- **Framework**: Qt 4.x/5.x (Qt 6.x compatible with minor updates)
- **Database**: MySQL 5.6+
- **Build System**: QMake
- **UI**: Qt Widgets
- **Modules Used**: QtCore, QtGui, QtWidgets, QtSql, QtPrintSupport

## Prerequisites

### Required Software

1. **Qt Framework** (5.x or later recommended)
   - Download from: https://www.qt.io/download
   - Required modules: Core, Gui, Widgets, Sql, PrintSupport

2. **MySQL Server** (5.6 or later)
   - Download from: https://dev.mysql.com/downloads/mysql/
   - Must be running on localhost (default configuration)

3. **MySQL Client Libraries**
   - Required for Qt's QMYSQL driver
   - Usually included with MySQL installation

4. **C++ Compiler**
   - Linux: GCC 4.8+ or Clang 3.4+
   - Windows: MinGW or MSVC 2015+
   - macOS: Xcode Command Line Tools

### Optional Software

- **Qt Creator** - Recommended IDE for development
- **Git** - For version control

## Installation

### 1. Clone the Repository

```bash
git clone <repository-url>
cd M-ERP-ly
```

### 2. Configure MySQL

Ensure MySQL is running and accessible:

```bash
# Start MySQL service (Linux)
sudo systemctl start mysql

# Or (macOS with Homebrew)
brew services start mysql
```

**Default Database Configuration:**
- Host: `localhost`
- Database: `testqt` (auto-created on first run)
- Username: `root`
- Password: `` (empty on Linux) or `root` (on Windows)

To change these settings, edit `Model/erpmodel.cpp`:

```cpp
db.setHostName("localhost");      // Change if MySQL is on different host
db.setUserName("root");            // Change to your MySQL username
#ifdef Q_OS_WIN32
    db.setPassword("root");        // Change Windows password
#endif
```

### 3. Install Qt MySQL Driver

Verify Qt MySQL plugin is installed:

```bash
# Find Qt plugins directory
find /usr -name "libqsqlmysql.so" 2>/dev/null
# Or on macOS
find /usr -name "libqsqlmysql.dylib" 2>/dev/null
```

If not found, install it:

**Ubuntu/Debian:**
```bash
sudo apt-get install libqt5sql5-mysql
```

**Fedora/RHEL:**
```bash
sudo dnf install qt5-qtbase-mysql
```

**macOS (with Homebrew):**
```bash
brew install qt
brew link qt --force
```

### 4. Build the Project

#### Using Qt Creator (Recommended)

1. Open Qt Creator
2. File → Open File or Project
3. Select `ERP.pro`
4. Configure project with desired kit
5. Build → Build Project "ERP"
6. Run → Run

#### Using Command Line

```bash
# Generate Makefile
qmake ERP.pro

# Build
make

# Run
./ERP
```

**Windows (MinGW):**
```cmd
qmake ERP.pro
mingw32-make
ERP.exe
```

**Windows (MSVC):**
```cmd
qmake ERP.pro
nmake
ERP.exe
```

### 5. First Run

On first startup, the application will:
1. Create the `testqt` database automatically
2. Initialize all tables with proper schema
3. Populate default data:
   - Default users: `admin`/`admin` and `super`/`Ma12345`
   - Sample contact types and classes
   - Default invoice periods and years
   - Sample countries, currencies, and units
   - Default warehouse and payment types

**Default Login Credentials:**
- Username: `admin`
- Password: `admin`

**IMPORTANT**: Change the default password immediately after first login for security reasons!

## Security Improvements (Recent Updates)

### New Secure Methods

This version includes new secure methods to prevent SQL injection attacks and implement password hashing:

#### 1. Parameterized Queries

The `ErpModel` class now includes secure query execution methods:

```cpp
// Using positional parameters (?)
QVariantList values;
values << contactId;
QSqlQuery query = ErpModel::GetInstance()->execPreparedQuery(
    "SELECT * FROM Contact WHERE ContactID = ?",
    values
);

// Using named parameters (:name)
QMap<QString, QVariant> values;
values[":id"] = contactId;
QSqlQuery query = ErpModel::GetInstance()->execPreparedQuery(
    "SELECT * FROM Contact WHERE ContactID = :id",
    values
);
```

#### 2. Secure Model Methods

Example secure methods in `Contact` model:

- `Contact::saveSecure()` - Save with parameterized queries
- `Contact::GetSecure(int id)` - Retrieve by ID securely
- `Contact::GetSecure(const QString &name)` - Retrieve by name securely
- `Contact::SearchSecure(const QString &keyword)` - Secure search
- `Contact::removeSecure()` - Secure delete

#### 3. Password Hashing

The `User` model now includes password hashing:

```cpp
// Hash a password (SHA-256 with salt)
QString hashedPassword = User::hashPassword("myPassword");

// Verify a password
bool isValid = User::verifyPassword("myPassword", hashedPassword);

// Save user with hashed password
User* user = new User("John Doe", "john", "password123", 1, 1, "", "");
user->saveSecure();  // Password will be hashed automatically

// Authenticate user securely
User* authenticatedUser = User::authenticateSecure("john", "password123");
if(authenticatedUser) {
    // Login successful
}
```

#### 4. Connection Pooling

Database connections are now pooled and reused instead of opening/closing for each query. This significantly improves performance.

### Migration Guide

To migrate existing code to use secure methods:

**Before (Vulnerable):**
```cpp
Contact* contact = Contact::Get(contactId);
contact->Name = userInput;  // Vulnerable to SQL injection
contact->save();
```

**After (Secure):**
```cpp
Contact* contact = Contact::GetSecure(contactId);
contact->Name = userInput;  // Safe - uses parameterized queries
contact->saveSecure();
```

## Project Structure

```
M-ERP-ly/
├── Model/                  # Data layer (70+ model classes)
│   ├── erpmodel.h/cpp      # Core database manager (singleton)
│   ├── contact*.h/cpp      # Contact-related models
│   ├── product*.h/cpp      # Product catalog models
│   ├── invoice*.h/cpp      # Invoicing models
│   ├── purchase*.h/cpp     # Purchase management models
│   ├── delivery*.h/cpp     # Delivery order models
│   ├── payment*.h/cpp      # Payment models
│   ├── project*.h/cpp      # Project management models
│   ├── user.h/cpp          # User authentication
│   └── access.h/cpp        # Access control
│
├── displays/               # UI layer (76 display modules)
│   ├── mainwindow.h/cpp    # Main application window
│   ├── CommonUI/           # Reusable UI components
│   │   ├── erpcombobox.*   # Custom combo box
│   │   ├── erptableview.*  # Custom table view
│   │   ├── barcode.*       # Barcode generation
│   │   └── printview.*     # Print functionality
│   └── [Module]/           # One folder per business entity
│       ├── *indexui.*      # List/grid view
│       └── *ui.*           # Detail/edit form
│
├── Resources/              # Images, icons, and resources
├── ERP.pro                 # Qt project file
├── main.cpp                # Application entry point
├── erp_ar.ts/qm           # Arabic translations
└── README.md              # This file
```

## Development

### Adding a New Module

1. Create model class in `Model/` directory
2. Implement CRUD operations
3. Create UI classes in `displays/[ModuleName]/`
4. Add to main window navigation
5. Initialize in `ErpModel::init()`

### Code Conventions

- Model classes use singleton pattern: `ModelName::GetInstance()`
- All models inherit from `QSqlRelationalTableModel`
- UI classes inherit from `ERPDisplay` base class
- Use signals/slots for event handling
- Follow Qt naming conventions (camelCase for methods, PascalCase for classes)

### Building for Different Platforms

**Linux:**
```bash
qmake ERP.pro
make
```

**Windows:**
```cmd
qmake ERP.pro
mingw32-make   # or nmake for MSVC
```

**macOS:**
```bash
qmake ERP.pro
make
```

## Database Schema

The application automatically creates and manages 70+ database tables including:

- **Master Data**: Contact, Product, Company, Tax, Currency, Country, Language
- **Transactions**: Invoice, Purchase, DeliveryOrder, Payment
- **Configuration**: ContactType, ProductCategory, PaymentType, InvoiceState
- **Relationships**: InvoiceStoreProduct, ProjectContactPerson, etc.

All tables include:
- Auto-incrementing primary keys
- Foreign key constraints with cascading deletes
- Creation and modification timestamps
- Indexed fields for performance

## Localization

### Adding a New Language

1. Create translation file:
```bash
lupdate ERP.pro -ts erp_[language_code].ts
```

2. Translate strings using Qt Linguist:
```bash
linguist erp_[language_code].ts
```

3. Compile translation:
```bash
lrelease erp_[language_code].ts
```

4. Add language to database via UI or directly:
```cpp
Language* language = new Language("French", ":/erp_fr.qm", "", "");
language->save();
```

## Troubleshooting

### MySQL Connection Failed

**Error**: "BataBase Issue: Something went Wrong: QMYSQL driver not loaded"

**Solution**: Install Qt MySQL plugin (see Installation step 3)

### Database Not Created

**Error**: "Unknown database 'testqt'"

**Solution**: Ensure MySQL is running and root user has permissions:
```sql
GRANT ALL PRIVILEGES ON testqt.* TO 'root'@'localhost';
FLUSH PRIVILEGES;
```

### Build Errors

**Error**: "Cannot find -lmysqlclient"

**Solution**: Install MySQL development libraries:
```bash
# Ubuntu/Debian
sudo apt-get install libmysqlclient-dev

# Fedora/RHEL
sudo dnf install mysql-devel
```

### Missing Qt Modules

**Error**: "Project ERROR: Unknown module(s) in QT: printsupport"

**Solution**: Install complete Qt development package:
```bash
sudo apt-get install qt5-default qtbase5-dev
```

## Performance Tips

1. **Indexes**: The application automatically indexes key fields, but you can add custom indexes for frequently queried fields
2. **Connection Pooling**: Now implemented - connections are reused
3. **Batch Operations**: For bulk imports, use transactions:
```cpp
db.transaction();
// ... perform multiple operations
db.commit();
```

## Contributing

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## Known Issues & Limitations

1. **SQL Injection**: Legacy methods (non-Secure) are vulnerable. Migrate to `*Secure()` methods.
2. **Password Storage**: Legacy users have plain-text passwords. Use `saveSecure()` for new users.
3. **Single Database**: Currently supports one database instance. Multi-tenancy requires code modification.
4. **Screen Resolution**: Some UI elements use fixed pixel values and may not scale on high-DPI displays.

## Future Roadmap

- [ ] Complete migration to secure parameterized queries for all models
- [ ] PDF export for invoices and reports
- [ ] Advanced reporting and analytics dashboard
- [ ] REST API for mobile/web integration
- [ ] Email integration for invoices and notifications
- [ ] Audit trail and activity logging
- [ ] Data backup and restore functionality
- [ ] Multi-company support
- [ ] Cloud deployment option
- [ ] Web-based companion interface

## License

Copyright © Bishara. All rights reserved.

See LICENSE file for details.

## Support

For issues, questions, or contributions:
- Create an issue in the repository
- Contact: [Your contact information]

## Acknowledgments

- Built with Qt Framework (https://www.qt.io)
- Uses MySQL database (https://www.mysql.com)
- Barcode generation based on EAN-13 standard

## Version History

### v1.1 (Current - Security Update)
- Added parameterized query support
- Implemented password hashing (SHA-256)
- Fixed connection pooling issues
- Added secure methods to Contact and User models
- Updated documentation

### v1.0 (Initial Release)
- Core ERP functionality
- 70+ models, 76 UI modules
- Multi-language support
- Basic access control
