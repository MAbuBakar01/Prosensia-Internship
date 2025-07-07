#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;

struct Item {
    int id;
    char name[50];
    int quantity;
    float price;
};
const char* FILENAME = "inventory.txt";
// Function Prototypes
void menu();
void addItem();
void viewAllItems();
void searchItemByID();
void updateQuantity();
void deleteItem();
bool idExists(int id);
// Main Menu
int main() {
    int choice;
    do {
        menu();
        cin >> choice;
        switch(choice) {
            case 1: addItem(); break;
            case 2: viewAllItems(); break;
            case 3: searchItemByID(); break;
            case 4: updateQuantity(); break;
            case 5: deleteItem(); break;
            case 6: cout << "Exiting...\n"; break;
            default: cout << "Invalid option!\n";
        }
    } while(choice != 6);
    return 0;
}
// Menu display
void menu() {
    cout << "\nInventory Management System\n";
    cout << "1. Add Item\n2. View All Items\n3. Search by ID\n4. Update Quantity\n5. Delete Item\n6. Exit\n";
    cout << "Enter your choice: ";
}

// Add Item (with ID validation)
void addItem() {
    Item item;
    cout << "Enter Item ID: ";
    cin >> item.id;

    if(idExists(item.id)) {
        cout << "Error: Item with this ID already exists.\n";
        return;
    }
    cout << "Enter Item Name: ";
    cin.ignore();
    cin.getline(item.name, 50);
    cout << "Enter Quantity: ";
    cin >> item.quantity;
    cout << "Enter Price: ";
    cin >> item.price;
    ofstream file(FILENAME, ios::app);
    file << item.id << "|" << item.name << "|" << item.quantity << "|" << item.price << "\n";
    file.close();
    cout << "Item added successfully!\n";
}
// View All Items
void viewAllItems() {
    ifstream file(FILENAME);
    Item item;
    char line[200];
    cout << "\nID\tName\t\tQty\tPrice\n";
    while(file.getline(line, 200)) {
        sscanf(line, "%d|%[^|]|%d|%f", &item.id, item.name, &item.quantity, &item.price);
        cout << item.id << "\t" << item.name << "\t\t" << item.quantity << "\t" << item.price << "\n";
    }
    file.close();
}
// Search by ID
void searchItemByID() {
    int searchID;
    cout << "Enter Item ID to search: ";
    cin >> searchID;

    ifstream file(FILENAME);
    Item item;
    char line[200];
    bool found = false;

    while(file.getline(line, 200)) {
        sscanf(line, "%d|%[^|]|%d|%f", &item.id, item.name, &item.quantity, &item.price);
        if(item.id == searchID) {
            cout << "Item Found: " << item.name << ", Qty: " << item.quantity << ", Price: " << item.price << "\n";
            found = true;
            break;
        }
    }
    file.close();
    if(!found) cout << "Item not found.\n";
}
// Update Quantity
void updateQuantity() {
    int searchID, newQty;
    cout << "Enter Item ID to update quantity: ";
    cin >> searchID;
   cout << "Enter new quantity: ";
    cin >> newQty;
    ifstream file(FILENAME);
    ofstream temp("temp.txt");
    Item item;
    char line[200];
    bool found = false;
    while(file.getline(line, 200)) {
        sscanf(line, "%d|%[^|]|%d|%f", &item.id, item.name, &item.quantity, &item.price);
        if(item.id == searchID) {
            item.quantity = (newQty < 0) ? 0 : newQty;
            found = true;
        }
        temp << item.id << "|" << item.name << "|" << item.quantity << "|" << item.price << "\n";
    }
    file.close();
    temp.close();
    remove(FILENAME);
    rename("temp.txt", FILENAME);
    if(found) cout << "Quantity updated.\n";
    else cout << "Item not found.\n";
}
// Delete Item
void deleteItem() {
    int deleteID;
    cout << "Enter Item ID to delete: ";
    cin >> deleteID;
    ifstream file(FILENAME);
    ofstream temp("temp.txt");
    Item item;
    char line[200];
    bool deleted = false;
    while(file.getline(line, 200)) {
        sscanf(line, "%d|%[^|]|%d|%f", &item.id, item.name, &item.quantity, &item.price);
        if(item.id != deleteID)
            temp << item.id << "|" << item.name << "|" << item.quantity << "|" << item.price << "\n";
        else
            deleted = true;
    }
    file.close();
    temp.close();
    remove(FILENAME);
    rename("temp.txt", FILENAME);
    if(deleted) cout << "Item deleted.\n";
    else cout << "Item not found.\n";
}
// Check if ID exists
bool idExists(int id) {
    ifstream file(FILENAME);
    Item item;
    char line[200];
    while(file.getline(line, 200)) {
        sscanf(line, "%d|%[^|]|%d|%f", &item.id, item.name, &item.quantity, &item.price);
        if(item.id == id) {
            file.close();
            return true;
        }   }
    file.close();
    return false;
}