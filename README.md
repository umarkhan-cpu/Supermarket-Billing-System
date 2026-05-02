# 🛒 Supermarket Billing System

A C++ application that automates a supermarket's day-to-day operations — billing, inventory, product management, refunds, and sales reporting — through a dual-role architecture (Admin + Cashier) backed by a WinForms GUI and file-based persistence. Developed as the term project for CS1004 Object-Oriented Programming at FAST-NUCES Lahore.

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
| Muhammad Umar Khan | 25L-3089 | **Team Lead** | Category Management, Discount & Coupon System, Return & Refund Management, Session Timeout, backend integration, receipt system, bootstrap utility |
| Areesha Khurram | 25L-3007 | Member | User Management, Billing & Receipt Generation, Search & Filter Products, CAPTCHA, Password Strength |
| Mahnoor Aslam | 25L-3008 | Member | Sales Report Generation, full GUI, all UI/UX visual implementation |
| Farda Fatima | 25L-3009 | Member | Product Management, Inventory & Stock Management, Transaction History, Dark/Light Mode |

---

## ⚡ Quick Start

1. **Clone the repository** to a fresh folder:
   ```
   git clone https://github.com/umarkhan-cpu/Supermarket-Billing-System.git
   cd Supermarket-Billing-System
   ```

2. **Open the solution** in Visual Studio 2022 (Community edition or higher).

3. **Run the bootstrap utility first** to seed default user accounts:
   - Set `Supermarket-Billing-System` (the console project) as the startup project
   - Press `Ctrl+F5`
   - When prompted, choose **Option 4** — bootstraps users and runs all backend smoke tests
   - Verify that **17/17 checks pass** before launching the GUI

4. **Run the GUI:**
   - Set `supermarketui` as the startup project
   - Press `Ctrl+F5`
   - Log in using one of the demo credentials below

   💡 If login fails with a "can't open Data/users.txt" error: right-click supermarketui project → Properties → Configuration Properties → Debugging → set Working Directory to $(SolutionDir) → Apply.

### 🔑 Demo Credentials

After running the bootstrap utility (Option 1 or 4), the following accounts exist:

| Username | Password | Role |
|---|---|---|
| `Admin` | `admin123` | Admin |
| `Umar` | `umar123` | Cashier |
| `Mahnoor` | `mahnoor123` | Cashier |
| `Farda` | `farda123` | Cashier |
| `Areesha` | `areesha123` | Cashier |

> 💡 Use Admin / admin123 for admin controls, others for the cashier role.
---

## 🚀 Features

### 🔐 Admin Interface
1. **User Management** — Create, update, and delete Admin/Cashier accounts. Includes last-admin-protection, self-delete-protection, and a show-password toggle.
2. **Category Management** — Organize products into categories with full CRUD.
3. **Product Management** — Add, edit, and remove products with prices and category assignments.
4. **Inventory & Stock Management** — Track stock levels across products with low-stock alerts.
5. **Return & Refund Management** — Process partial or full refunds with proportional discount allocation. Cumulative refunds capped at the original transaction total. A customer who paid Rs 84 for a Rs 100 item (after 20% coupon) gets back exactly Rs 84.
6. **Sales Report Generation** — Revenue summary, transaction count, and refunded-item count. Revenue subtracts cumulative refunds for accuracy.

### 🧾 Cashier Interface
7. **Billing & Receipt Generation** — Cart-based POS with line-item totals, coupon application, 17% FBR sales tax, branded receipt rendering, and a Clear Cart safeguard.
8. **Discount & Coupon System** — Percentage and fixed-value coupon types with active/inactive status.
9. **Transaction History** — Sortable list of past transactions with a "View Receipt" action.
10. **Search & Filter Products** — Search by name, category, or price range.

### 🎨 UI/UX & Security Features
1. **Branded Login Screen** — FAST MART header band, gold tagline, password visibility toggle.
2. **Dark / Light Mode** — Toggle the dashboard theme at any time.
3. **Session Timeout** — Auto-logout after 5 minutes of inactivity.
4. **Password Strength Indicator** — Live strength feedback during account creation.
5. **CAPTCHA Verification** — Backend implementation included; see Known Limitations for GUI integration scope.

---

## 🧩 System Architecture

The system follows OOP principles with a **dual-perspective architecture**:

- **Abstract base class `User`** with pure-virtual `getRoleName()`, inherited by concrete `Admin` and `Cashier` classes
- **Polymorphic role dispatch** through `SessionManager` using a `User*` base pointer — the runtime decides whether to grant Admin or Cashier permissions based on the actual derived type
- **Manager pattern** — for each domain entity (Product, Category, Transaction, Refund, Discount, Inventory, User), a data class represents one record while a separate Manager class handles the collection, file I/O, and business operations
- **Receipt system** — `ReceiptRecord` + `ReceiptStore` provide structured persistence of complete sale and refund receipts, enabling proportional refund calculation against the original sale price

### Dual-Perspective Design
- **Admin Login** → Full access to manage products, categories, inventory, users, refunds, reports, and coupons
- **Cashier Login** → Access to billing, search, refunds, and transaction history

The dashboard sidebar dynamically shows only the buttons relevant to the logged-in role, with no empty gaps.

---

## 🛠️ Technologies Used

| Field | Details |
|---|---|
| Language | C++17 |
| IDE | Visual Studio 2022 |
| GUI Framework | WinForms (C++/CLI) |
| Data Storage | File Handling (CSV + structured pipe-delimited for receipts) |
| Version Control | Git & GitHub |

---

## 💡 OOP Concepts Implemented

| # | Concept | Where Demonstrated |
|---|---|---|
| 1 | Classes & Objects | All classes |
| 2 | Constructors (Default, Parameterized, Copy) | Every data class |
| 3 | Function Overloading | Search and find methods (by ID/name/code) |
| 4 | Operator Overloading | `Product::operator<` for sorting |
| 5 | Pointers & Dynamic Memory | Dynamic arrays in every Manager class with `new`/`delete` |
| 6 | Inheritance | `User` → `Admin`, `Cashier` |
| 7 | Polymorphism | Pure virtual `getRoleName()`, runtime role dispatch in SessionManager |
| 8 | Encapsulation | Private attributes with public getters/setters |
| 9 | Abstraction | `User` is abstract; refund/billing complexity hidden behind manager interfaces |
| 10 | Exception Handling | Try-catch around file parsing in Transaction, Product, UserManagement, etc. |
| 11 | Friend Functions | `Bill` and `Inventory` share product data |
| 12 | Static Members | All Manager classes use static collections + counters |
| 13 | Templates | Generic search/sort utilities |

---

## 📁 Project Structure

```
Supermarket-Billing-System/
│
├── Admin/
│   ├── Admin.{h,cpp}                    Areesha
│   ├── Category.{h,cpp}                 Umar
│   ├── CategoryManagement.{h,cpp}       Umar
│   ├── Inventory.{h,cpp}                Farda
│   ├── InventoryManagement.{h,cpp}      Farda
│   ├── Product.{h,cpp}                  Farda
│   ├── ProductManagement.{h,cpp}        Farda
│   ├── SalesReport.{h,cpp}              Mahnoor
│   └── UserManagement.{h,cpp}           Areesha
│
├── Cashier/
│   ├── Cashier.{h,cpp}                  Areesha
│   ├── Discount.{h,cpp}                 Umar
│   ├── DiscountManagement.{h,cpp}       Umar
│   ├── ReceiptAndBilling.{h,cpp}        Areesha
│   ├── ReceiptStore.{h,cpp}             Umar
│   ├── Refund.{h,cpp}                   Umar
│   ├── RefundManagement.{h,cpp}         Umar
│   ├── Transaction.{h,cpp}              Farda
│   └── TransactionManagement.{h,cpp}    Farda
│
├── Common/
│   ├── User.{h,cpp}                     Areesha
│   └── SessionManager.{h,cpp}           Umar
│
├── supermarketui/                       Mahnoor (WinForms GUI)
│   ├── MyForm.{h,cpp}                   (Login screen)
│   ├── Dashboard.{h,cpp}
│   ├── BillingForm.{h,cpp}
│   ├── ReceiptForm.{h,cpp}
│   ├── RefundForm.{h,cpp}
│   ├── UserForm.{h,cpp}
│   ├── CategoryForm.{h,cpp}
│   └── ...
│
├── Data/
│   ├── users.txt
│   ├── categories.txt
│   ├── products.txt
│   ├── transactions.txt
│   ├── receipts.txt
│   ├── coupons.txt
│   ├── refunds.txt
│   └── settings.txt
│
├── main.cpp                             (Bootstrap + smoke test utility)
└── README.md
```

---

## 📊 Progress Tracker

| # | Feature | Owner | Status |
|---|---|---|---|
| 1 | User Management | Areesha | ✅ Done |
| 2 | Category Management | Umar | ✅ Done |
| 3 | Product Management | Farda | ✅ Done |
| 4 | Inventory & Stock Management | Farda | ✅ Done |
| 5 | Return & Refund Management | Umar | ✅ Done |
| 6 | Sales Report Generation | Mahnoor | ✅ Done |
| 7 | Billing & Receipt Generation | Areesha | ✅ Done |
| 8 | Discount & Coupon System | Umar | ✅ Done |
| 9 | Transaction History | Farda | ✅ Done |
| 10 | Search & Filter Products | Areesha | ✅ Done |
| — | GUI (WinForms) | Mahnoor | ✅ Done |
| — | CAPTCHA Verification | Areesha | ⚠️ Backend only (see Known Limitations) |
| — | Password Strength Indicator | Areesha | ✅ Done |
| — | Dark / Light Mode | Farda | ✅ Done |
| — | Session Timeout | Umar | ✅ Done |

---

## 📂 Data File Formats

All persistent data lives under `Data/` and uses CSV (or pipe-delimited for the structured receipt records).

| File | Format |
|---|---|
| users.txt | `UserID, Username, PasswordHash, Role` |
| categories.txt | `CategoryID, Name, Description` |
| products.txt | `ProductID, Name, CategoryID, Price, Stock` |
| transactions.txt | `TransactionID, Date, CashierID, TotalAmount, Status` |
| receipts.txt | Pipe-delimited multi-line: `=RECEIPT=` markers, `HEADER`/`ITEM`/`TOTALS`/`END` rows |
| coupons.txt | `CouponID, Code, DiscountType, DiscountValue, Status` |
| refunds.txt | `RefundID, TransactionID, Reason, Amount, Date, ProductID, Quantity` |
| settings.txt | `theme=dark` or `theme=light` |

---

## 🧪 Backend Smoke Test

The console binary (`main.cpp`) is not just a placeholder — it's a working bootstrap and health-check utility. It offers:

1. **Bootstrap default user accounts** — idempotent, safe to run multiple times.
2. **Run full backend smoke test** — non-destructive load → count → cleanup cycle for every Manager class. Reports `[PASS]`/`[FAIL]` per check, ending with a summary like `17 / 17 checks passed`.
3. **Show data summary** — record counts across all data files.
4. **Bootstrap + smoke test** — combined; recommended before any demo run.

This utility was the foundation that let us catch crash bugs and parser issues before they reached the GUI.

---

## ⚠️ Known Limitations

We documented these honestly rather than hiding them:

1. **CAPTCHA UI not integrated.** The backend logic (`generatecaptcha`, `validatecaptcha` in `UserManagement.cpp`) is fully implemented and tested in the console flow. GUI integration was scoped out for this iteration to keep the login flow simple for the demo.
2. **No signup on the login screen.** This is intentional. Account creation is restricted to Admin via the User Management form, which mirrors how real retail POS systems handle staff accounts.
3. **Child forms use a fixed light theme.** The dashboard's dark/light toggle applies to the dashboard itself; child windows (Inventory, Categories, Refunds, etc.) were left light-themed for legibility consistency.
4. **Settings: English / PKR / Light-Dark only.** Multi-language and multi-currency support are not part of this scope.
5. **Product creation does not auto-seed inventory.** When an Admin adds a 
   product via the Inventory form's "Add" button, a Product record is created 
   with the specified initial stock, but no corresponding Inventory record. 
   This creates an asymmetry where the first stock-removal (via sale) silently 
   fails, but a subsequent refund correctly creates the Inventory record — 
   resulting in the product's stock count being off by the amount sold + refunded. 
   Workaround: after adding a product, use the "Restock" button to explicitly 
   seed inventory matching the initial stock count.

---

## 🛡️ Recovery Procedure

**If all admin accounts are lost** (e.g. accidentally deleted via User Management):

1. Open `Data/users.txt` and delete or empty the file.
2. Run the console binary (`main.cpp`).
3. Choose **Option 1: Bootstrap default user accounts**.
4. The default `Admin / admin123` account will be restored.

This is the documented disaster-recovery flow, and it's been tested.

---

## 🌿 Branching & Contribution Workflow

The repository used a feature-branch workflow. Each team member developed on their own branch, with `feature/Umar` serving as the integration branch.

| Branch | Purpose |
|---|---|
| `main` | Stable, submission-ready code (protected) |
| `feature/Umar` | Integration branch — all features merged here for testing before promotion to `main` |
| `feature/Areesha` | Areesha's individual feature work |
| `feature/Farda` | Farda's individual feature work |
| `feature/Mahnoor` | Mahnoor's individual feature work |

Final integration to `main` was done via a single Pull Request from `feature/Umar`, reviewed and merged by the Team Lead.

---

## 📄 License

This project is developed for academic purposes at FAST-NUCES Lahore under the MIT License. See [LICENSE](LICENSE) for details.
