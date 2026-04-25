#ifndef CATEGORY_MANAGEMENT_H
#define CATEGORY_MANAGEMENT_H

#include "Category.h"
#include <string>
using std::string;

/*
 * CategoryManagement — static manager class for the Category collection.
 *
 * Responsibilities:
 *   - Owns the in-memory dynamic array of all loaded Category objects
 *   - Handles persistence (load/save) against Data/categories.txt
 *   - Exposes CRUD methods that operate on the collection by value
 *   - Provides a console menu (showMenu) for interactive use
 *
 * Design notes:
 *   - All members are static. There is only one conceptual "category
 *     management system" in the application, so no instances are created.
 *   - CRUD methods (addCategory, editCategory, deleteCategory) take plain
 *     data and return a bool for success/failure. They never prompt the
 *     user. This keeps them usable from both console and future GUI code.
 *   - showMenu() is the console-only driver that prompts for input and
 *     dispatches to the CRUD methods. When the GUI is introduced, it can
 *     reuse the CRUD methods directly and ignore showMenu().
 *   - Every data-modifying method calls saveToFile() automatically, so
 *     the file on disk is always consistent with the in-memory state.
 *
 * File path: Data/categories.txt (relative to the project root)
 */
class CategoryManagement {

private:
    // ----- Static data members (declared here, defined in the .cpp) -----
    static Category* categories;   // dynamic array of loaded categories
    static int count;              // number of categories currently stored
    static int capacity;           // allocated size of the array

    // ----- Private helpers -----

    // Doubles the array capacity when full. Used internally by addCategory.
    // Preserves existing elements and frees the old block.
    static void grow();

    // Returns the index of the category with the given ID, or -1 if not found.
    static int findIndexByID(int id);

    // Returns the next ID to assign to a new category (max existing + 1).
    // If the collection is empty, returns 1.
    static int nextAvailableID();

public:
    // ----- File lifecycle -----

    // Loads all categories from Data/categories.txt into the in-memory array.
    // Should be called once at program start. If the file doesn't exist,
    // starts with an empty collection (no error).
    static void loadFromFile();

    // Writes the in-memory array back to Data/categories.txt.
    // Called automatically after every add/edit/delete.
    static void saveToFile();

    // Frees the dynamic array. Should be called once before program exit
    // to release memory explicitly.
    static void cleanup();

    // ----- CRUD operations (pure data — no prompts, no output) -----

    // Creates a new Category with the given name and description and adds
    // it to the collection. The ID is auto-assigned. Returns false if the
    // input fails Category validation (e.g., empty name, comma in name).
    static bool addCategory(const string& name, const string& desc);

    // Updates the name and/or description of the category with the given ID.
    // Returns false if the ID is not found or the new values fail validation.
    static bool editCategory(int id, const string& newName, const string& newDesc);

    // Removes the category with the given ID from the collection.
    // Returns false if the ID is not found.
    static bool deleteCategory(int id);

    // ----- Read operations -----

    // Prints all categories to the console in a formatted table.
    // Read-only; safe to call at any time.
    static void viewAll();

    // Returns a copy of the category with the given ID.
    // If not found, returns a default Category (getID() == 0).
    static Category findByID(int id);

    // Returns the current number of categories (for callers that need it).
    static int getCount();

    // ----- Console driver -----

    // Interactive menu: prompts for user input and dispatches to the CRUD
    // methods. Loops until the user chooses "Back". Console-only; the GUI
    // will not call this — it will call the CRUD methods directly.
    static void showMenu();
};

#endif