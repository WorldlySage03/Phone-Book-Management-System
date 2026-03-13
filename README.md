# 📒 Phone Book Management System

A console-based **Phone Book Management System** written in C++ that allows users to store, manage, and organize contacts efficiently. Contacts are maintained in a **sorted linked list** and support tagging, CSV import/export, and file-based persistence.

---

## 📋 Table of Contents

- [Features](#-features)
- [Data Structure](#-data-structure)
- [Getting Started](#-getting-started)
  - [Prerequisites](#prerequisites)
  - [Compilation](#compilation)
  - [Running](#running)
- [Usage](#-usage)
- [File Formats](#-file-formats)
- [Project Structure](#-project-structure)

---

## ✨ Features

| Feature | Description |
|---|---|
| ➕ Add Contact | Add a contact with name, phone number, and tag |
| 🔍 Search Contact | Search by name or phone number |
| ✏️ Edit Contact | Update name, phone, or tag for an existing contact |
| 🗑️ Delete Contact | Remove a contact by name or phone number |
| 📋 Display Contacts | View all contacts alphabetically or grouped by tag |
| 🔢 Contact Count | Display the total number of stored contacts |
| 📤 Import/Export CSV | Import contacts from or export to a `.csv` file |
| 💾 Save/Load File | Persist contacts to and load from a custom file format |

---

## 🏗️ Data Structure

Contacts are stored using a **singly linked list**, where each node holds:
- `name` — Contact's full name
- `phone` — Phone number
- `tag` — Category label (e.g., Family, Friend, Work)

New contacts are inserted in **sorted (alphabetical) order** using the `sortedInsert()` function, so the list is always kept ordered by name.

---

## 🚀 Getting Started

### Prerequisites

- A C++ compiler supporting **C++11** or later (e.g., `g++`, `clang++`)
- Windows OS (the `clearScreen()` function uses `system("cls")`)

> **Note for Linux/macOS users:** Replace `system("cls")` with `system("clear")` in the `clearScreen()` function before compiling.

### Compilation

```bash
g++ -o PhoneBook PhoneBook.cpp -std=c++11
```

### Running

```bash
./PhoneBook
```

Or on Windows, you can run the pre-compiled executable directly:

```bash
PhoneBook.exe
```

---

## 🖥️ Usage

Once launched, the program displays an interactive menu:

```
========= Phone Book Menu =========
1. Add Contact
2. Search Contact
3. Edit Contact
4. Delete Contact
5. Display All Contacts
6. Show Total Contact Number
7. Import/Export Contacts (CSV)
8. Save/Load from File
0. Exit
===================================
```

Enter the number corresponding to the action you want to perform and follow the on-screen prompts.

---

## 📁 File Formats

### CSV Format (Import/Export)

Used with option **7 – Import/Export Contacts**. The file must have a header row:

```
Name,Phone,Tag
Anika Uddin,+880 1758-193452,Friend
Rahim Khan,+880 1823-456789,Work
```

A sample file `Data.csv` is included in the repository with 100 pre-loaded contacts.

### Custom Save Format (Save/Load)

Used with option **8 – Save/Load from File**. Fields are pipe-separated (`|`):

```
Anika Uddin|+880 1758-193452|Friend
Rahim Khan|+880 1823-456789|Work
```

---

## 📂 Project Structure

```
Phone-Book-Management-System/
├── PhoneBook.cpp      # Main source file (all logic)
├── PhoneBook.exe      # Pre-compiled Windows executable
├── Data.csv           # Sample dataset with 100 contacts
└── README.md          # Project documentation
```
