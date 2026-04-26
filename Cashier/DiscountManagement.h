#ifndef DISCOUNT_MANAGEMENT_H
#define DISCOUNT_MANAGEMENT_H

#include "Discount.h"
#include <string>
using std::string;

/*
 * DiscountManagement - static manager class for the Discount collection.
 * Belongs to: Muhammad Umar Khan (lead)
 *
 * Responsibilities:
 *   - Owns the in-memory dynamic array of all loaded Discount objects
 *   - Handles persistence (load/save) against Data/coupons.txt
 *   - Exposes CRUD methods that operate on the collection by value
 *   - Exposes applyCoupon() - the one method other features (Billing) call
 *   - Provides a console menu (showMenu) for interactive use
 *
 * Design notes:
 *   - All members are static. There is only one conceptual "discount system"
 *     in the application, so no instances are created.
 *   - CRUD methods take plain data and return a bool for success/failure.
 *     They never prompt the user, keeping them GUI-compatible.
 *   - applyCoupon is the integration contract used by the Billing feature:
 *         float discount = DiscountManagement::applyCoupon(code, subtotal);
 *         float final    = subtotal - discount;
 *   - showMenu() is the console-only driver, kept as a debug/fallback tool.
 *   - Every data-modifying method calls saveToFile() automatically, so the
 *     file on disk is always consistent with the in-memory state.
 *
 * File path: Data/coupons.txt (relative to the project root)
 */
class DiscountManagement {

private:
    // ----- Static data members (declared here, defined in the .cpp) -----
    static Discount* discounts;    // dynamic array of loaded discounts
    static int count;              // number of discounts currently stored
    static int capacity;           // allocated size of the array

    // ----- Private helpers -----

    // Doubles the array capacity when full. Used internally by addCoupon.
    static void grow();

    // Returns the index of the discount with the given ID, or -1 if not found.
    static int findIndexByID(int id);

    // Returns the index of the discount with the given code, or -1 if not found.
    // Used by applyCoupon - cashiers identify coupons by code, not ID.
    static int findIndexByCode(const string& code);

    // Returns the next ID to assign to a new discount (max existing + 1).
    static int nextAvailableID();

public:
    // ----- File lifecycle -----

    static void loadFromFile();
    static void saveToFile();
    static void cleanup();

    // ----- CRUD operations (pure data - no prompts, no output) -----

    // Creates a new Discount with the given code/type/value and adds it.
    // The ID is auto-assigned, isActive defaults to true. Returns false if
    // the input fails validation (e.g., duplicate code, invalid type).
    static bool addCoupon(const string& code, const string& type, float value);

    // Updates the type and/or value of the discount with the given ID.
    // The code itself is not editable (changing a code is conceptually
    // creating a new coupon - admins should delete + add).
    static bool editCoupon(int id, const string& newType, float newValue);

    // Removes the discount with the given ID from the collection.
    static bool deleteCoupon(int id);

    // Activates or deactivates a discount without deleting it.
    // Useful for temporarily disabling a coupon (e.g., out-of-season promo).
    static bool setActive(int id, bool active);

    // ----- The integration method (called by Billing) -----

    // Looks up the coupon by code and returns the discount amount in rupees.
    // Returns 0 if:
    //   - The code doesn't exist
    //   - The coupon is inactive
    //   - The coupon's type is unknown (defensive)
    // The returned amount is what Billing should subtract from the subtotal:
    //     float final = subtotal - DiscountManagement::applyCoupon(code, subtotal);
    static float applyCoupon(const string& code, float subtotal);

    // ----- Read operations -----

    static void viewAll();
    static Discount findByID(int id);
    static int getCount();

    // ----- Console driver -----

    static void showMenu();
};

#endif
