# 🛒 Supermarket Billing System

A C++ application for managing supermarket operations including billing, inventory, product management, and sales reporting. Built with OOP principles and a GUI interface, featuring role-based access for Admin and Cashier roles. Developed as a semester project at FAST-NUCES Lahore.

---

## 📋 Project Details

| Field | Details |
|---|---|
| Course | CS1004 — Object Oriented Programming |
| Institution | FAST-NUCES, Lahore |
| Semester | 2nd Semester |
| Section | A |
| Team | Group 10 |
| Instructor | Ms. Hina Iqbal |
| TA | Syed Saad Ali |

---

## 👥 Team Members

| Name | Roll No. | Role | Responsibilities |
|---|---|---|---|
| Muhammad Umar Khan | 25L-3089 | Team Lead | Category Management, Discount & Coupon System, Return & Refund Management |
| Areesha Khurram | 25L-3007 | Member | User Management, Billing & Receipt Generation, Search & Filter Products |
| Mahnoor Aslam | 25L-3008 | Member | Sales Report Generation, GUI |
| Farda Fatima | 25L-3009 | Member | Product Management, Inventory & Stock Management, Transaction History |

---

## 🚀 Features

### 🔐 Admin Interface
1. **User Management** — Create, manage, and delete user accounts
2. **Category Management** — Organize products into categories
3. **Product Management** — Add, edit, and remove products
4. **Inventory & Stock Management** — Track stock levels and receive low stock alerts
5. **Return & Refund Management** — Process product returns and issue refunds
6. **Sales Report Generation** — View revenue summaries and top-selling products

### 🧾 Cashier Interface
7. **Billing & Receipt Generation** — Process customer purchases and generate receipts
8. **Discount & Coupon System** — Apply discount codes and offers at checkout
9. **Transaction History** — View records of past transactions
10. **Search & Filter Products** — Find products by name, category, or price

## 🔐 UI/UX & Security Features

1. **CAPTCHA Verification** — Randomly generated verification code at login to prevent unauthorized access
2. **Password Strength Indicator** — Live visual indicator during account creation to encourage secure passwords
3. **Dark / Light Mode** — Toggle between dark and light interface themes for visual comfort
4. **Session Timeout** — Automatically logs out inactive users to prevent unauthorized access
   
---

## 🛠️ Technologies Used

| Field | Details |
|---|---|
| Language | C++ |
| IDE | Visual Studio |
| GUI Framework | C++ Compatible Framework (Qt) |
| Data Storage | File Handling (CSV format) |
| Version Control | Git & GitHub |

---

## 💡 OOP Concepts Implemented

- Classes & Objects
- Constructors (Default, Parameterized, Copy)
- Function Overloading
- Operator Overloading
- Pointers & Dynamic Memory Allocation
- Inheritance
- Polymorphism
- Encapsulation & Abstraction
- Exception Handling
- Friend Functions
- Static Members
- Templates

---

## 📁 Project Structure

```
Supermarket-Billing-System/
│
├── Admin/
│   ├── CategoryManagement.h
│   ├── CategoryManagement.cpp       ← Muhammad Umar Khan
│   ├── ProductManagement.h
│   ├── ProductManagement.cpp        ← Farda Fatima
│   ├── InventoryManagement.h
│   ├── InventoryManagement.cpp      ← Farda Fatima
│   ├── SalesReport.h
│   ├── SalesReport.cpp              ← Mahnoor Aslam
│   ├── ReturnRefund.h
│   ├── ReturnRefund.cpp             ← Muhammad Umar Khan
│   ├── UserManagement.h
│   └── UserManagement.cpp           ← Areesha Khurram
│
├── Cashier/
│   ├── Billing.h
│   ├── Billing.cpp                  ← Areesha Khurram
│   ├── Discount.h
│   ├── Discount.cpp                 ← Muhammad Umar Khan
│   ├── TransactionHistory.h
│   ├── TransactionHistory.cpp       ← Farda Fatima
│   ├── SearchFilter.h
│   └── SearchFilter.cpp             ← Areesha Khurram
│
├── Data/
│   ├── products.txt
│   ├── categories.txt
│   ├── users.txt
│   ├── transactions.txt
│   ├── coupons.txt
│   ├── refunds.txt
│   └── settings.txt 
│
├── GUI/
│   └── (Mahnoor Aslam's GUI Files)
│
├── main.cpp
└── README.md
```

---

## 📂 Data File Formats

All data files use comma-separated (CSV) format:

| File | Format |
|---|---|
| users.txt | UserID, Username, Password, Role |
| categories.txt | CategoryID, CategoryName |
| products.txt | ProductID, Name, CategoryID, Price, Stock |
| transactions.txt | TransactionID, Date, CashierID, TotalAmount, Status |
| coupons.txt | CouponID, Code, DiscountType, DiscountValue, IsActive |
| refunds.txt | RefundID, TransactionID, Reason, Amount, Date |

---

## 🖥️ Dual-Perspective Architecture

The system follows a dual-perspective architecture:

- **Admin Login** → Full access to manage products, categories, inventory, users, refunds and reports
- **Cashier Login** → Access to billing, search, discounts and transaction history

---

## ⚙️ How to Run

1. Clone the repository:
```
git clone https://github.com/umarkhan17006-cpu/Supermarket-Billing-System.git
```
2. Open the project in **Visual Studio**
3. Build and run the solution
4. Login as **Admin** or **Cashier** from the main menu

---

## 📌 Development Approach

The project follows a console-first approach, with GUI integration planned after core logic is complete.

---

## 📄 License

This project is developed for academic purposes at FAST-NUCES Lahore under the MIT License.
