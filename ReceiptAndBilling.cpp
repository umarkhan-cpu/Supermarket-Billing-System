#include "ReceiptAndBilling.h"

CartItem::CartItem() { 
    quantity = 0;
}

CartItem::CartItem(Product p, int q) : product(p), quantity(q) {
}

double CartItem::getprice() {
    return product.getPrice() * quantity;
}

Cart::Cart() { totalcount = 0; }

int Cart::itemindex(int productID) {
    for (int i = 0; i < totalcount; i++)
        if (cartItems[i].product.getId() == productID) {
            return i;
        }
    return -1;
}

void Cart::addItem(Product p, int qty) {
    int idx = itemindex(p.getId());
    if (idx != -1) {
        cartItems[idx].quantity += qty;
    }
    else {
        cartItems[totalcount++] = CartItem(p, qty);
    }
}

void Cart::removeItem(int productID) {
    int idx = itemindex(productID);
    if (idx == -1) {
        return;
    }
    for (int i = idx; i < totalcount - 1; i++) {
        cartItems[i] = cartItems[i + 1];
    }
    totalcount--;
}

void Cart::updateQuantity(int productID, int newQty) {
    int idx = itemindex(productID);
    if (idx != -1) {
        cartItems[idx].quantity = newQty;
    }
}

double Cart::getTotal() {
    double total = 0;
    for (int i = 0; i < totalcount; i++) {
        total += cartItems[i].getprice();
    }
    return total;
}

void Cart::displayCart() {
    cout << "TOTAL: " << getTotal() << endl;
}

CartStorage::CartStorage(string pFile, string cFile) {
    productsFile = pFile;
    cartFile = cFile;
}

int CartStorage::loadProducts(Product products[]) {
    ifstream in(productsFile);
    string line;
    int count = 0;

    while (getline(in, line)) {
        string token, name;
        int id, cat, stock;
        float price;

        if (line.empty()) {
            continue;
        }
        stringstream ss(line);
      
        getline(ss, token, ','); 
        id = stoi(token);
        getline(ss, name, ',');
        getline(ss, token, ',');
        cat = stoi(token);
        getline(ss, token, ','); 
        price = stof(token);
        getline(ss, token, ',');
        stock = stoi(token);

        products[count++].setData(id, name, cat, price, stock);
    }
    return count;
}

void CartStorage::saveCart(Cart& cart) {
    ofstream out(cartFile);
    for (int i = 0; i < cart.totalcount; i++) {
        out << cart.cartItems[i].product.getId() << "," << cart.cartItems[i].quantity << "\n";
    }
}

bool CartStorage::findProductById(int targetId, Product& result) {
    ifstream in(productsFile);
    string line;

    while (getline(in, line)) {
        stringstream ss(line);
        string token, name;
        int id, cat, stock;
        float price;

        getline(ss, token, ','); id = stoi(token);
        getline(ss, name, ',');
        getline(ss, token, ','); cat = stoi(token);
        getline(ss, token, ','); price = stof(token);
        getline(ss, token, ','); stock = stoi(token);

        if (id == targetId) {
            result.setData(id, name, cat, price, stock);
            return true;
        }
    }
    return false;
}

void CartStorage::loadCart(Cart& cart) {
    ifstream in(cartFile);
    string line;

    while (getline(in, line)) {
        stringstream ss(line);
        string token;
        int id, qty;

        getline(ss, token, ','); id = stoi(token);
        getline(ss, token, ','); qty = stoi(token);

        Product p;
        if (findProductById(id, p)) {
            cart.addItem(p, qty);
        }
    }
}

Bill::Bill(string n, Cart& cart, double tax, double discount)
    : customerName(n), cartReference(cart) {
    taxRate = tax;
    discountAmount = discount;
    subtotal = 0;
    totalAmount = 0;

    billID = "BILL-" + n;
    calculate();
}

void Bill::calculate() {
    subtotal = cartReference.getTotal();
    totalAmount = subtotal + (subtotal * taxRate) - discountAmount;
}

void Bill::display() const {
    cout << "TOTAL: " << totalAmount << endl;
}

void Bill::generateReceipt(Receipt& r) {
    r.receipt(*this);
}

Receipt::Receipt() { totalLines = 0; }
Receipt::Receipt(Bill& bill) { receipt(bill); }

void Receipt::addline(string line) {
    receiptLines[totalLines++] = line;
}

void Receipt::receipt(Bill& bill) {
    addline("Receipt for " + bill.customerName);
}

void Receipt::printToConsole() const {
    for (int i = 0; i < totalLines; i++)
        cout << receiptLines[i] << endl;
}

void Receipt::saveToFile(string filename) const {
    ofstream out(filename);
    for (int i = 0; i < totalLines; i++)
        out << receiptLines[i] << endl;
}

void userInputCart(Cart& cart, Product products[], int count) {
    int id, qty;

    while (true) {
        cin >> id;
        if (id == 0) {
            break;
        }

        cin >> qty;

        for (int i = 0; i < count; i++) {
            if (products[i].getId() == id) {
                cart.addItem(products[i], qty);
                break;
            }
        }
    }
}

void Bill::menu() {
    Cart cart;
    int choice;

    do {
        cout << "\n===== BILLING MENU =====" << endl;
        cout << "1. Add Item to Cart" << endl;
        cout << "2. Remove Item" << endl;
        cout << "3. Update Quantity" << endl;
        cout << "4. View Cart Total" << endl;
        cout << "5. Generate Bill" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1: {
            int id, qty;
            cout << "Enter Product ID: ";
            cin >> id;
            cout << "Enter Quantity: ";
            cin >> qty;

            Product p;
            bool found = false;

            int count = ProductManagement::getProductCount();
            for (int i = 0; i < count; i++) {
                if (ProductManagement::getProduct(i).getId() == id) {
                    p = ProductManagement::getProduct(i);
                    found = true;
                    break;
                }
            }

            if (found) {
                cart.addItem(p, qty);
                cout << "Item added." << endl;
            }
            else {
                cout << "Product not found." << endl;
            }
            break;
        }

        case 2: {
            int id;
            cout << "Enter Product ID to remove: ";
            cin >> id;
            cart.removeItem(id);
            break;
        }

        case 3: {
            int id, qty;
            cout << "Enter Product ID: ";
            cin >> id;
            cout << "Enter new quantity: ";
            cin >> qty;
            cart.updateQuantity(id, qty);
            break;
        }

        case 4:
            cart.displayCart();
            break;

        case 5: {
            string name;
            cout << "Enter Customer Name: ";
            cin >> name;

            double tax = 0.05;
            double discount = 0;

            Bill bill(name, cart, tax, discount);
            bill.display();

            Receipt r;
            bill.generateReceipt(r);

            cout << "--- RECEIPT ---" << endl;
            r.printToConsole();

            break;
        }

        case 6:
            cout << "Exiting Billing..." << endl;
            break;

        default:
            cout << "Invalid choice!" << endl;
        }

    } while (choice != 6);
}