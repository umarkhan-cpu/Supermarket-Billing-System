#include "ReceiptAndBilling.h"
#include <sstream>
#include <iomanip>
using namespace std;

static string fmt(double v) { //converts a double value into a string
    ostringstream out; //stores output in a string 

    out << fixed << setprecision(2) << v;// setprecision keeps only 2 digits after decimal while fixed forces decimal format
    return out.str();
}


CartItem::CartItem() : quantity(0) {
}

CartItem::CartItem(Product p, int q) : product(p), quantity(q) {
}

double CartItem::getPrice() const {
    return product.getPrice() * quantity;  
}

Cart::Cart() : totalcount(0) {
}

int Cart::itemIndex(int productID) const {
    for (int i = 0; i < totalcount; i++) {
        if (cartItems[i].product.getID() == productID) {
            return i;  
        }
    }
    return -1; 
}

void Cart::addItem(Product p, int quant) {
    int index = itemIndex(p.getID());

    if (index != -1) { // if product already exists in cart
        cartItems[index].quantity += quant;// increase quantity

    } else {
        cartItems[totalcount++] = CartItem(p, quant); // Add new item in next free position
    }
}

void Cart::removeItem(int productID) {
    int index = itemIndex(productID);
    if (index == -1) {
        return;
    }
    for (int i = index; i < totalcount - 1; i++) { //shift to left
        cartItems[i] = cartItems[i + 1];
    }
    totalcount--;
}

void Cart::updateQuantity(int productID, int newQuan) {
    int index = itemIndex(productID);
    if (index != -1)
        cartItems[idx].quantity = newQuan;
}

double Cart::getTotal() const {
    double total = 0;
    for (int i = 0; i < totalcount; i++) {
        total += cartItems[i].getPrice(); //adds all prices
    }
    return total;
}

void Cart::displayCart() const {

    cout << left << setw(4)  << "ID" << setw(20) << "Name" << setw(6)  << "Qty" << setw(10) << "Price" << endl;
    cout << string(40, '-') << endl;
    for (int i = 0; i < totalcount; i++) {
        const CartItem& item = cartItems[i];
        cout << left << setw(4)  << item.product.getID() << setw(20) << item.product.getName() << setw(6)  << item.quantity << setw(10) << fmt(item.getPrice()) << endl;
    }
    cout << string(40, '-') << endl;

    cout << "TOTAL: " << fmt(getTotal()) << endl;
}

CartStorage::CartStorage(string file) : cartFile(file) {}

void CartStorage::saveCart(const Cart& cart) const {
    ofstream out(cartFile);
    for (int i = 0; i < cart.totalcount; i++) {// Save each cart item as CSV line
        out << cart.cartItems[i].product.getID() << "," << cart.cartItems[i].quantity << endl;
    }
}

void CartStorage::loadCart(Cart& cart) const {
    string line;
    ifstream in(cartFile);

    if (!in) {
        return;
    }

    while (getline(in, line)) {
        stringstream ss(line);
        string token;
        int id, quantity;

        if (line.empty()) {
            continue;
        }

        getline(ss, token, ','); //product ID
        id = stoi(token);

        getline(ss, token, ','); //quantity
        quantity = stoi(token);

        // Find product in ProductManagement
        for (int i = 0; i < ProductManagement::getCount(); i++) {
            if (ProductManagement::getAt(i).getID() == id) { //gives product at index i
                cart.addItem(ProductManagement::getAt(i), quantity);
                break;
            }
        }
    }
}

Bill::Bill(const string& name, Cart& cart, double tax, const string& couponCode)
    : customerName(name), cartReference(cart), taxRate(tax), discountAmount(0), subtotal(0), totalAmount(0)
{
    billID = "BILL-" + name;

    if (!couponCode.empty()) {
        subtotal = cart.getTotal();// calculate subtotal first
        discountAmount = DiscountManagement::applyCoupon(couponCode, subtotal);
    }
    calculate();
}

void Bill::calculate() {
    subtotal = cartReference.getTotal();
    totalAmount = subtotal + (subtotal * taxRate) - discountAmount; //subtotal + tax - discount
    if (totalAmount < 0) {
        totalAmount = 0;
    }
}

void Bill::display() const {
    cout << "~~BILL~~" << endl;
    cout << "Customer : " << customerName << endl;
    cout << "Bill ID  : " << billID << endl;

    cartReference.displayCart(); // shows cart details

    cout << "Subtotal : " << fmt(subtotal) << endl; //shows calculations
    cout << "Tax (" << (taxRate * 100) << "%): " << fmt(subtotal * taxRate) << endl;
    cout << "Discount : " << fmt(discountAmount) << endl;
    cout << "TOTAL    : " << fmt(totalAmount) << endl;
}

void Bill::generateReceipt(Receipt& r) { // Sends bill data to receipt generator
    r.receipt(*this);
}

Receipt::Receipt() : totalLines(0) {
}

Receipt::Receipt(Bill& bill) : totalLines(0) {
    receipt(bill); //builds receipt directly from bill
}

void Receipt::addLine(const string& line) {
    if (totalLines < MAX_RECEIPT_LINES) {
        receiptLines[totalLines++] = line;
    }
}

void Receipt::receipt(Bill& bill) {

    addLine("================================");
    addLine("           RECEIPT              ");
    addLine("================================");
    addLine("Bill ID  : " + bill.billID);
    addLine("Customer : " + bill.customerName);
    addLine("--------------------------------");

    // Each cart item line
    for (int i = 0; i < bill.cartReference.totalcount; i++) {
        const CartItem& item = bill.cartReference.cartItems[i];

        string itemLine = item.product.getName() + " x " + to_string(item.quantity) +"  =  " + fmt(item.getPrice());
        addLine(itemLine);
    }

    addLine("--------------------------------");
    addLine("Subtotal : " + fmt(bill.subtotal));
    addLine("Tax      : " + fmt(bill.subtotal * bill.taxRate));
    addLine("Discount : " + fmt(bill.discountAmount));
    addLine("TOTAL    : " + fmt(bill.totalAmount));
    addLine("================================");
    addLine("     Thank you for shopping :) !    ");
    addLine("================================");
}

void Receipt::printToConsole() const {
    for (int i = 0; i < totalLines; i++) {
        cout << receiptLines[i] << endl;
    }
}

void Receipt::saveToFile(const string& filename) const {
    ofstream out(filename);

    for (int i = 0; i < totalLines; i++) {
        out << receiptLines[i] << "\n";
    }
}

void Bill::menu() {
    Cart cart;
    int choice;

    do {
        cout << "===== BILLING MENU =====" << endl;
        cout << "1. Add Item to Cart" << endl;
        cout << "2. Remove Item" << endl;
        cout << "3. Update Quantity" << endl;
        cout << "4. View Cart" << endl;
        cout << "5. Generate Bill & Receipt" << endl;
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

            bool found = false;

            for (int i = 0; i < ProductManagement::getCount(); i++) {
                if (ProductManagement::getAt(i).getID() == id) {
                    cart.addItem(ProductManagement::getAt(i), qty);
                    cout << "Item added." << endl;
                    found = true;
                    break;
                }
            }

            if (!found)
                cout << "Product not found." << endl;

            break;
        }

        case 2: {
            int id;
            cout << "Enter Product ID to remove: ";
            cin >> id;
            cart.removeItem(id);
            cout << "Item removed!" << endl;
            break;
        }

        // Update quantity
        case 3: {
            int id, qty;
            cout << "Enter Product ID: ";
            cin >> id;
            cout << "Enter new quantity: ";
            cin >> qty;
            cart.updateQuantity(id, qty);
            break;
        }

        // Show cart
        case 4:
            cart.displayCart();
            break;

        // Generate bill + receipt
        case 5: {
            string name, coupon;
            cout << "Enter Customer Name: ";
            cin >> name;

            cout << "Enter coupon code (or press Enter to skip): ";
            cin.ignore();
            getline(cin, coupon);

            Bill bill(name, cart, 0.05, coupon);
            bill.display();

            Receipt r;
            bill.generateReceipt(r);

            cout << "\n--- RECEIPT ---" << endl;
            r.printToConsole();

            Transaction t;
            t.setData(0,getCurrentDate(),0,bill.totalAmount,"Completed")
            TransactionManagement::addTransaction(t)
            cout << "Transaction recorded." << endl;
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