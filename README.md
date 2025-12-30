# 🏦 Bank Management System - Extended Edition | Level 7

This project is a **functional extension** of the first Bank Project in Level 7. The system has evolved from a simple data storage tool into an interactive banking application capable of managing financial transactions with built-in logic validation.

---

## 🔗 Quick Links
* **Previous Project:** [Bank System (V1)](https://github.com/ammmrrr18-cloud/07-Algorithms-Level-3-Bank-Project)

---

## 🔄 What's New in this Version? (Enhancements)

In this extension, I upgraded the project with professional features:

### 1️⃣ Nested Menus System (Sub-Menus)
* **Addition:** Introduced a new option in the Main Menu called **`Transactions`**, which opens a completely separate sub-menu for financial operations.
* **Technical Objective:** Demonstrating control flow management using multiple `Enums` and smooth navigation between different program layers.

### 2️⃣ Financial Transaction Operations
* **Deposit:** Added a feature to increase a client's balance and instantly sync changes with the `Clients.text` file.
* **Withdraw:** Integrated a withdrawal feature linked to immediate balance verification.

### 3️⃣ Smart Validation Logic
* **Overdraft Prevention:** The program is now "intelligent" enough to reject any withdrawal exceeding the client's current balance, displaying the warning: `Amount Exceeds the balance`.
* **Technical Objective:** Applying **Error Handling** concepts to ensure financial data integrity.

### 4️⃣ Liquidity Reporting (Total Balances)
* **Addition:** A dedicated screen that displays a summary of all clients and their balances, concluding with the **Total Bank Balances**.
* **Technical Objective:** Iterating through `Vectors` to perform cumulative calculations and presenting data in a formatted report.

---

## 🛠️ Technical Toolkit
* **Vectors & Structs:** Used for dynamic and flexible data management in memory.
* **File Handling (fstream):** Ensuring every financial transaction (Deposit/Withdraw) is permanently saved.
* **Advanced Enums:** For professional menu control and cleaner code maintenance.
* **iomanip:** To format financial outputs into professional, aligned tables.

---

## 📁 Repository Structure
* **My-Solution:** My enhanced implementation featuring Transactions and balance validation.
* **Instructor-Solution:** The model solution by Dr. Mohammed Abu-Hadhoud for technical reference and comparison.

---
*📌 "Strong software isn't just about storing data; it's about managing it intelligently and protecting it from errors."*
