#include <iostream>
#include <string>
#include <queue>
#include <cstdlib> // for system("cls")
#include <iomanip>
using namespace std;

// ================== CLEAR SCREEN ==================
void clearScreen() {
    system("cls"); // For Windows CMD
}

// ================== CLASS DEFINITIONS ==================
class MenuItem {
public:
    string name;
    double price;
    string category;
};

// Linked List Node for Order History
struct OrderHistory {
    int orderID;
    string customerName;
    string itemsOrdered;
    double totalPrice;
    OrderHistory* next;
};

// Node for Binary Search Tree (for searching menu)
struct TreeNode {
    string name;
    double price;
    TreeNode* left;
    TreeNode* right;
};

// ================== GLOBAL VARIABLES ==================
MenuItem food[5] = {
    {"Burger", 8.50, "Food"},
    {"Pizza", 12.00, "Food"},
    {"Pasta", 9.00, "Food"},
    {"Fried Rice", 7.00, "Food"},
    {"Chicken Chop", 10.00, "Food"}
};

MenuItem drinks[5] = {
    {"Cola", 3.00, "Drink"},
    {"Iced Tea", 3.50, "Drink"},
    {"Lemon Juice", 4.00, "Drink"},
    {"Milkshake", 5.00, "Drink"},
    {"Mineral Water", 2.00, "Drink"}
};

MenuItem sides[5] = {
    {"French Fries", 4.50, "Sides"},
    {"Garlic Bread", 3.00, "Sides"},
    {"Mashed Potato", 4.00, "Sides"},
    {"Soup", 3.50, "Sides"},
    {"Salad", 5.00, "Sides"}
};

queue<string> deliveryQueue;
OrderHistory* historyHead = NULL;
int orderCounter = 1000; // Order ID starts from 1000

// ================== FUNCTION DECLARATIONS ==================
void showMenu(MenuItem arr[], int size);
void sortMenu(MenuItem arr[], int size);
TreeNode* insertTree(TreeNode* root, string name, double price);
void searchTree(TreeNode* root, string name);
void addToHistory(int id, string name, string items, double total);
void viewHistory();
void placeOrder();
void processDelivery();
void mainMenu();

// ================== DISPLAY FUNCTIONS ==================
void showMenu(MenuItem arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << setw(2) << i + 1 << ". " << setw(15) << left << arr[i].name
             << " RM " << fixed << setprecision(2) << arr[i].price << endl;
    }
}

void sortMenu(MenuItem arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j].price > arr[j + 1].price) {
                MenuItem temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    cout << "\nMenu sorted by price (low to high):\n";
    showMenu(arr, size);
}

// ================== TREE FUNCTIONS ==================
TreeNode* insertTree(TreeNode* root, string name, double price) {
    if (root == NULL) {
        root = new TreeNode;
        root->name = name;
        root->price = price;
        root->left = root->right = NULL;
        return root;
    }
    if (name < root->name)
        root->left = insertTree(root->left, name, price);
    else
        root->right = insertTree(root->right, name, price);
    return root;
}

void searchTree(TreeNode* root, string name) {
    if (root == NULL) {
        cout << "Item not found!\n";
        return;
    }
    if (root->name == name) {
        cout << "Found " << root->name << " - RM " << root->price << endl;
    } else if (name < root->name) {
        searchTree(root->left, name);
    } else {
        searchTree(root->right, name);
    }
}

// ================== LINKED LIST FUNCTIONS ==================
void addToHistory(int id, string name, string items, double total) {
    OrderHistory* newNode = new OrderHistory;
    newNode->orderID = id;
    newNode->customerName = name;
    newNode->itemsOrdered = items;
    newNode->totalPrice = total;
    newNode->next = NULL;

    if (historyHead == NULL)
        historyHead = newNode;
    else {
        OrderHistory* temp = historyHead;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newNode;
    }
}

void viewHistory() {
    if (historyHead == NULL) {
        cout << "No order history.\n";
        return;
    }
    cout << "\n===== Order History =====\n";
    OrderHistory* temp = historyHead;
    while (temp != NULL) {
        cout << "Order ID: " << temp->orderID << endl;
        cout << "Customer: " << temp->customerName << endl;
        cout << "Items: " << temp->itemsOrdered << endl;
        cout << "Total: RM " << fixed << setprecision(2) << temp->totalPrice << endl;
        cout << "-----------------------------\n";
        temp = temp->next;
    }
}

// ================== ORDERING FUNCTIONS ==================
void placeOrder() {
    string customerName;
    clearScreen();
    cout << "Enter your name: ";
    cin.ignore();
    getline(cin, customerName);

    double totalPrice = 0.0;
    string orderedItems = "";
    int categoryChoice, itemChoice, quantity;
    char more;

    do {
        clearScreen();
        cout << "\nSelect Category:\n1. Food\n2. Drinks\n3. Sides\nChoice: ";
        cin >> categoryChoice;

        MenuItem* chosenArray = NULL;
        int size = 5;

        if (categoryChoice == 1)
            chosenArray = food;
        else if (categoryChoice == 2)
            chosenArray = drinks;
        else if (categoryChoice == 3)
            chosenArray = sides;
        else {
            cout << "Invalid choice.\n";
            return;
        }

        clearScreen();
        showMenu(chosenArray, size);
        cout << "Select item number: ";
        cin >> itemChoice;

        if (itemChoice < 1 || itemChoice > size) {
            cout << "Invalid item.\n";
            return;
        }

        cout << "Enter quantity: ";
        cin >> quantity;

        string itemName = chosenArray[itemChoice - 1].name;
        double itemPrice = chosenArray[itemChoice - 1].price * quantity;

        totalPrice += itemPrice;
        orderedItems += itemName + " x" + to_string(quantity) + ", ";

        cout << itemName << " added!\n";
        cout << "Add more? (y/n): ";
        cin >> more;

    } while (more == 'y' || more == 'Y');

    // Remove last comma
    if (orderedItems.size() > 2)
        orderedItems = orderedItems.substr(0, orderedItems.size() - 2);

    int orderID = ++orderCounter;
    addToHistory(orderID, customerName, orderedItems, totalPrice);
    deliveryQueue.push(orderedItems);

    clearScreen();
    cout << "\n===== ORDER SUMMARY =====\n";
    cout << "Order ID: " << orderID << endl;
    cout << "Customer: " << customerName << endl;
    cout << "Items: " << orderedItems << endl;
    cout << "Total Price: RM " << fixed << setprecision(2) << totalPrice << endl;
    cout << "=========================\n";
    cout << "Your order has been added to the delivery queue.\n";
}

// ================== DELIVERY QUEUE ==================
void processDelivery() {
    if (deliveryQueue.empty()) {
        cout << "No orders in queue.\n";
    } else {
        cout << "Delivering: " << deliveryQueue.front() << endl;
        deliveryQueue.pop();
    }
}

// ================== MAIN MENU ==================
void mainMenu() {
    int choice;
    TreeNode* root = NULL;

    for (int i = 0; i < 5; i++) {
        root = insertTree(root, food[i].name, food[i].price);
        root = insertTree(root, drinks[i].name, drinks[i].price);
        root = insertTree(root, sides[i].name, sides[i].price);
    }

    do {
        clearScreen();
        cout << "\n========= FOOD DELIVERY SYSTEM =========\n";
        cout << "1. View Menu\n";
        cout << "2. Sort Menu (by Price)\n";
        cout << "3. Search Item\n";
        cout << "4. Place Order\n";
        cout << "5. Process Delivery\n";
        cout << "6. View Order History\n";
        cout << "7. Exit\n";
        cout << "Choose option: ";
        cin >> choice;

        clearScreen();
        switch (choice) {
            case 1:
                cout << "\n--- FOOD MENU ---\n";
                showMenu(food, 5);
                cout << "\n--- DRINKS MENU ---\n";
                showMenu(drinks, 5);
                cout << "\n--- SIDES MENU ---\n";
                showMenu(sides, 5);
                break;

            case 2:
                cout << "\nSort which category?\n1. Food\n2. Drinks\n3. Sides\nChoice: ";
                int sortChoice;
                cin >> sortChoice;
                clearScreen();
                if (sortChoice == 1) sortMenu(food, 5);
                else if (sortChoice == 2) sortMenu(drinks, 5);
                else if (sortChoice == 3) sortMenu(sides, 5);
                else cout << "Invalid category.\n";
                break;

            case 3: {
                string searchName;
                cout << "Enter item name to search: ";
                cin.ignore();
                getline(cin, searchName);
                searchTree(root, searchName);
                break;
            }

            case 4:
                placeOrder();
                break;

            case 5:
                processDelivery();
                break;

            case 6:
                viewHistory();
                break;

            case 7:
                cout << "Thank you for using Food Delivery System!\n";
                break;

            default:
                cout << "Invalid choice!\n";
        }

        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();

    } while (choice != 7);
}

// ================== MAIN FUNCTION ==================
int main() {
    mainMenu();
    return 0;
}
