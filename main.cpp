#include <iostream>
#include <string>
using namespace std;

// ====== CLASS: Menu Item ======
class MenuItem {
public:
    string name;
    double price;

    MenuItem() {
        name = "";
        price = 0.0;
    }

    MenuItem(string n, double p) {
        name = n;
        price = p;
    }
};

// ====== STRUCT: Linked List for Order History ======
struct OrderNode {
    string itemName;
    int quantity;
    double total;
    OrderNode* next;
};

// ====== CLASS: Stack (Undo Last Order) ======
class Stack {
private:
    string items[100];
    int top;
public:
    Stack() { top = -1; }

    void push(string item) {
        if (top < 99) {
            items[++top] = item;
        } else {
            cout << "Stack full!\n";
        }
    }

    string pop() {
        if (top >= 0)
            return items[top--];
        else {
            cout << "Nothing to undo!\n";
            return "";
        }
    }

    bool isEmpty() { return top == -1; }
};

// ====== CLASS: Queue (Delivery Queue) ======
class Queue {
private:
    string queueArray[100];
    int front, rear;
public:
    Queue() {
        front = -1;
        rear = -1;
    }

    void enqueue(string order) {
        if (rear == 99) {
            cout << "Queue full!\n";
            return;
        }
        if (front == -1) front = 0;
        queueArray[++rear] = order;
    }

    string dequeue() {
        if (front == -1 || front > rear) {
            cout << "Queue empty!\n";
            return "";
        }
        return queueArray[front++];
    }

    void display() {
        if (front == -1 || front > rear)
            cout << "No orders in delivery queue.\n";
        else {
            cout << "\nCurrent Delivery Queue:\n";
            for (int i = front; i <= rear; i++) {
                cout << "- " << queueArray[i] << endl;
            }
        }
    }
};

// ====== STRUCT: Binary Search Tree Node ======
struct TreeNode {
    MenuItem item;
    TreeNode* left;
    TreeNode* right;
};

// ====== CLASS: Menu Tree ======
class MenuTree {
public:
    TreeNode* root;

    MenuTree() { root = NULL; }

    TreeNode* insert(TreeNode* node, MenuItem item) {
        if (node == NULL) {
            node = new TreeNode();
            node->item = item;
            node->left = node->right = NULL;
        } else if (item.name < node->item.name) {
            node->left = insert(node->left, item);
        } else {
            node->right = insert(node->right, item);
        }
        return node;
    }

    bool search(TreeNode* node, string name) {
        if (node == NULL) return false;
        if (node->item.name == name) return true;
        if (name < node->item.name)
            return search(node->left, name);
        else
            return search(node->right, name);
    }
};

// ====== CLASS: Linked List (Order History) ======
class LinkedList {
public:
    OrderNode* head;
    LinkedList() { head = NULL; }

    void addOrder(string item, int qty, double total) {
        OrderNode* newNode = new OrderNode();
        newNode->itemName = item;
        newNode->quantity = qty;
        newNode->total = total;
        newNode->next = NULL;

        if (head == NULL)
            head = newNode;
        else {
            OrderNode* temp = head;
            while (temp->next != NULL)
                temp = temp->next;
            temp->next = newNode;
        }
    }

    void display() {
        if (head == NULL) {
            cout << "No past orders.\n";
            return;
        }
        cout << "\nOrder History:\n";
        OrderNode* temp = head;
        while (temp != NULL) {
            cout << "- " << temp->itemName << " x" << temp->quantity
                 << " = RM" << temp->total << endl;
            temp = temp->next;
        }
    }
};

// ====== FUNCTION: Bubble Sort ======
void sortMenu(MenuItem arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].price > arr[j + 1].price) {
                MenuItem temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// ====== MAIN PROGRAM ======
int main() {
    const int SIZE = 5;

    MenuItem foodMenu[SIZE] = {
        MenuItem("Burger", 5.00),
        MenuItem("Pizza", 8.00),
        MenuItem("Fried Rice", 6.00),
        MenuItem("Nasi Lemak", 4.50),
        MenuItem("Spaghetti", 7.00)
    };

    MenuItem drinkMenu[SIZE] = {
        MenuItem("Water", 1.00),
        MenuItem("Soda", 2.50),
        MenuItem("Coffee", 3.00),
        MenuItem("Tea", 2.00),
        MenuItem("Juice", 4.00)
    };

    MenuItem sidesMenu[SIZE] = {
        MenuItem("French Fries", 3.50),
        MenuItem("Salad", 4.00),
        MenuItem("Chicken Wings", 6.50),
        MenuItem("Onion Rings", 3.00),
        MenuItem("Garlic Bread", 2.50)
    };

    // Data structures
    Stack undoStack;
    Queue deliveryQueue;
    LinkedList history;
    MenuTree tree;

    // Insert all menus into BST
    for (int i = 0; i < SIZE; i++) {
        tree.root = tree.insert(tree.root, foodMenu[i]);
        tree.root = tree.insert(tree.root, drinkMenu[i]);
        tree.root = tree.insert(tree.root, sidesMenu[i]);
    }

    int choice, cat, itemNo, qty;
    string searchItem;

    do {
        cout << "\n========= FOOD DELIVERY SYSTEM =========\n";
        cout << "1. View Menus\n";
        cout << "2. Sort Menu (by Price)\n";
        cout << "3. Search Item\n";
        cout << "4. Place Order\n";
        cout << "5. Undo Last Order\n";
        cout << "6. View Delivery Queue\n";
        cout << "7. View Order History\n";
        cout << "8. Exit\n";
        cout << "Choose option: ";
        cin >> choice;

        if (choice == 1) {
            cout << "\nSelect Category:\n1. Food\n2. Drinks\n3. Sides\nChoice: ";
            cin >> cat;
            MenuItem* menu;
            switch (cat) {
            case 1: menu = foodMenu; break;
            case 2: menu = drinkMenu; break;
            case 3: menu = sidesMenu; break;
            default: cout << "Invalid category!\n"; continue;
            }

            cout << "\nMenu:\n";
            for (int i = 0; i < SIZE; i++)
                cout << i + 1 << ". " << menu[i].name << " - RM" << menu[i].price << endl;

        } else if (choice == 2) {
            cout << "\nSort which menu?\n1. Food\n2. Drinks\n3. Sides\nChoice: ";
            cin >> cat;
            if (cat == 1) sortMenu(foodMenu, SIZE);
            else if (cat == 2) sortMenu(drinkMenu, SIZE);
            else if (cat == 3) sortMenu(sidesMenu, SIZE);
            else cout << "Invalid!\n";
            cout << "Menu sorted!\n";

        } else if (choice == 3) {
            cout << "Enter item name to search: ";
            cin.ignore();
            getline(cin, searchItem);
            if (tree.search(tree.root, searchItem))
                cout << searchItem << " is available.\n";
            else
                cout << "Item not found.\n";

        } else if (choice == 4) {
            cout << "\nSelect Category:\n1. Food\n2. Drinks\n3. Sides\nChoice: ";
            cin >> cat;
            MenuItem* menu;
            if (cat == 1) menu = foodMenu;
            else if (cat == 2) menu = drinkMenu;
            else if (cat == 3) menu = sidesMenu;
            else { cout << "Invalid!\n"; continue; }

            cout << "\nMenu:\n";
            for (int i = 0; i < SIZE; i++)
                cout << i + 1 << ". " << menu[i].name << " - RM" << menu[i].price << endl;

            cout << "Select item number: ";
            cin >> itemNo;
            cout << "Enter quantity: ";
            cin >> qty;

            if (itemNo < 1 || itemNo > SIZE) {
                cout << "Invalid item!\n";
                continue;
            }

            double total = qty * menu[itemNo - 1].price;
            cout << "\nAdded to order: " << menu[itemNo - 1].name << " x" << qty
                 << " = RM" << total << endl;

            undoStack.push(menu[itemNo - 1].name);
            deliveryQueue.enqueue(menu[itemNo - 1].name);
            history.addOrder(menu[itemNo - 1].name, qty, total);

        } else if (choice == 5) {
            if (!undoStack.isEmpty())
                cout << "Removed last order: " << undoStack.pop() << endl;
            else
                cout << "No order to undo!\n";

        } else if (choice == 6) {
            deliveryQueue.display();

        } else if (choice == 7) {
            history.display();

        } else if (choice == 8) {
            cout << "\nThank you for using Food Delivery System!\n";
        } else {
            cout << "Invalid choice!\n";
        }

    } while (choice != 8);

    return 0;
}
