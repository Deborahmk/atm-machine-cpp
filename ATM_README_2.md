# 🏧 Simple ATM Machine — C++ OOP Project

**Author:** Deborah Musuamba  
**GitHub:** [github.com/Deborahmk](https://github.com/Deborahmk)  
**Language:** C++

---

## 📌 Overview

A console-based ATM simulation built with C++ demonstrating core Object-Oriented Programming concepts including classes, objects, encapsulation, vectors, loops, and functions.

---

## 🚀 Features

- 🔐 Secure PIN-based login with 3 attempt limit
- 💰 Check account balance
- 📥 Deposit funds
- 📤 Withdraw funds (with insufficient funds validation)
- 🔄 Transfer between accounts
- 📋 Transaction history (last 5 transactions)
- 🚪 Logout

---

## 🧠 OOP Concepts Used

| Concept | Where Used |
|---------|------------|
| Classes | `Account`, `Transaction`, `ATM` |
| Objects | Multiple account instances |
| Encapsulation | Private members with public getters |
| Vectors | Transaction history, account list |
| Constructors | Account and Transaction initialization |
| Pointers | Current account tracking |
| Loops | Menu navigation, login attempts |
| Conditionals | Validation and error handling |

---

## ▶️ How to Run

### Requirements
- C++ compiler (g++ recommended)
- Terminal/Command Prompt

### Compile
```bash
g++ -o atm atm.cpp
```

### Run
```bash
./atm        # Mac/Linux
atm.exe      # Windows
```

### Sample Accounts
| Account Number | PIN | Owner | Balance |
|---------------|-----|-------|---------|
| ACC001 | 1234 | Deborah Musuamba | $5,000.00 |
| ACC002 | 5678 | John Smith | $2,500.00 |
| ACC003 | 9012 | Sarah Johnson | $7,800.00 |

---

## 📊 Sample Session

```
  ╔══════════════════════════════════════╗
  ║        WELCOME TO DM BANK ATM        ║
  ╚══════════════════════════════════════╝

  Enter account number: ACC001
  Enter PIN: 1234
  ✅ Login successful! Welcome, Deborah Musuamba!

  ATM MAIN MENU
  1. Check Balance
  2. Deposit
  3. Withdraw
  4. Transfer
  5. Transaction History
  6. Logout

  Enter choice: 3
  Enter withdrawal amount: $500
  ✅ Withdrawal successful!
  Amount withdrawn : $500.00
  Remaining balance: $4500.00
```

---

## 🔭 Future Enhancements

- [ ] File-based data persistence (save accounts to file)
- [ ] Admin panel to create/delete accounts
- [ ] Interest calculation
- [ ] Multiple currency support
- [ ] GUI interface

---

## 📄 License

MIT License — Copyright 2026 Deborah Musuamba
