#include <iostream>
#include <cstring>
using namespace std;

struct Item {
    int id;
    char type[20];
    char name[30];
    char place[30];
    int time;
};

struct Node {
    Item data;
    Node* next;
};

class LostFoundList {
private:
    Node* head;
    int nextId;

public:
    LostFoundList() {
        head = nullptr;
        nextId = 1;
    }

    int addItem(Item item) {
        Node* newNode = new Node;
        newNode->data = item;
        newNode->data.id = nextId++;
        newNode->next = nullptr;

        if (head == nullptr) {
            head = newNode;
        } else {
            Node* cur = head;
            while (cur->next != nullptr) {
                cur = cur->next;
            }
            cur->next = newNode;
        }
        return newNode->data.id;
    }

    void sortByTime() {
        if (head == nullptr || head->next == nullptr) return;
        bool swapped;
        do {
            swapped = false;
            Node* cur = head;
            while (cur->next != nullptr) {
                if (cur->data.time > cur->next->data.time) {
                    Item temp = cur->data;
                    cur->data = cur->next->data;
                    cur->next->data = temp;
                    swapped = true;
                }
                cur = cur->next;
            }
        } while (swapped);
    }

    void searchByType(const char* targetType) {
        cout << "\n===== Search Results =====" << endl;
        Node* cur = head;
        bool found = false;

        while (cur != nullptr) {
            if (strcmp(cur->data.type, targetType) == 0) {
                cout << "ID: " << cur->data.id
                     << " | Type: " << cur->data.type
                     << " | Name: " << cur->data.name
                     << " | Location: " << cur->data.place
                     << " | Time: " << cur->data.time << endl;
                found = true;
            }
            cur = cur->next;
        }

        if (!found) {
            cout << "No lost items found with this type." << endl;
        }
    }

    bool deleteById(int targetId) {
        if (head == nullptr) return false;

        Node* cur = head;
        Node* pre = nullptr;

        while (cur != nullptr && cur->data.id != targetId) {
            pre = cur;
            cur = cur->next;
        }

        if (cur == nullptr) return false;

        if (pre == nullptr) {
            head = head->next;
        } else {
            pre->next = cur->next;
        }
        delete cur;
        return true;
    }

    void smartMatch(LostFoundList& foundList) {
        cout << "\n===== Smart Match Results =====" << endl;
        Node* lostCur = head;
        bool hasMatch = false;

        int lostIds[100];
        int foundIds[100];
        int matchCount = 0;

        while (lostCur != nullptr && matchCount < 100) {
            Node* foundCur = foundList.head;
            while (foundCur != nullptr && matchCount < 100) {
                if (strcmp(lostCur->data.type, foundCur->data.type) == 0 &&
                    strcmp(lostCur->data.place, foundCur->data.place) == 0 &&
                    strcmp(lostCur->data.name, foundCur->data.name) == 0) {

                    cout << "\nMatch Found!" << endl;
                    cout << "Lost Item: " << lostCur->data.name << " (ID: " << lostCur->data.id << ")" << endl;
                    cout << "Found Item: " << foundCur->data.name << " (ID: " << foundCur->data.id << ")" << endl;
                    
                    lostIds[matchCount] = lostCur->data.id;
                    foundIds[matchCount] = foundCur->data.id;
                    matchCount++;
                    hasMatch = true;

                    foundCur = foundCur->next;
                    break;
                }
                foundCur = foundCur->next;
            }
            lostCur = lostCur->next;
        }

        if (!hasMatch) {
            cout << "No matching items found." << endl;
            return;
        }

        char choice;
        cout << "\nDelete ALL " << matchCount << " matched item pairs? Y/N: ";
        cin >> choice;

        if (choice == 'Y' || choice == 'y') {
            for (int i = 0; i < matchCount; i++) {
                deleteById(lostIds[i]);
                foundList.deleteById(foundIds[i]);
            }
            cout << "All " << matchCount << " matched item pairs deleted successfully!" << endl;
        } else {
            cout << "All items kept in the list." << endl;
        }
    }

    void showAll() {
        Node* cur = head;
        if (cur == nullptr) {
            cout << "\nNo items in the list." << endl;
            return;
        }
        cout << "\n===== All Items =====" << endl;
        while (cur != nullptr) {
            cout << "ID: " << cur->data.id
                 << " | Type: " << cur->data.type
                 << " | Name: " << cur->data.name
                 << " | Location: " << cur->data.place
                 << " | Time: " << cur->data.time << endl;
            cur = cur->next;
        }
    }

    int getLength() {
        int len = 0;
        Node* cur = head;
        while (cur != nullptr) {
            len++;
            cur = cur->next;
        }
        return len;
    }
};

void showMenu() {
    cout << "\n===== Campus Lost & Found System =====" << endl;
    cout << "1. Add Lost Item" << endl;
    cout << "2. Add Found Item" << endl;
    cout << "3. View All Lost Items" << endl;
    cout << "4. View All Found Items" << endl;
    cout << "5. Run Smart Match" << endl;
    cout << "6. Sort Lost Items by Time" << endl;
    cout << "7. Search Lost Items by Type" << endl;
    cout << "8. Exit" << endl;
    cout << "Enter your choice (1-8): ";
}

Item getItemInput() {
    Item item;
    cout << "\nEnter item details:" << endl;
    cout << "Type: "; cin >> item.type;
    cout << "Name: "; cin >> item.name;
    cout << "Location: "; cin >> item.place;
    cout << "Time (number only): "; cin >> item.time;
    return item;
}

void clearCin() {
    cin.clear();
    cin.ignore(10000, '\n');
}

int main() {
    LostFoundList lostList;
    LostFoundList foundList;
    int choice;

    cout << "Welcome to Campus Lost & Found System!" << endl;

    while (true) {
        showMenu();
        cin >> choice;

        if (cin.fail()) {
            clearCin();
            cout << "Invalid input! Please enter a number." << endl;
            continue;
        }

        switch (choice) {
            case 1: {
                Item newLost = getItemInput();
                int newId = lostList.addItem(newLost);
                cout << "Lost item added successfully!" << endl;
                cout << "Auto-assigned ID: " << newId << endl;
                break;
            }
            case 2: {
                Item newFound = getItemInput();
                int newId = foundList.addItem(newFound);
                cout << "Found item added successfully!" << endl;
                cout << "Auto-assigned ID: " << newId << endl;
                break;
            }
            case 3: {
                lostList.showAll();
                break;
            }
            case 4: {
                foundList.showAll();
                break;
            }
            case 5: {
                lostList.smartMatch(foundList);
                break;
            }
            case 6: {
                lostList.sortByTime();
                cout << "Lost items sorted successfully!" << endl;
                break;
            }
            case 7: {
                char searchType[20];
                cout << "Enter item type to search (e.g., laptop): ";
                cin >> searchType;
                lostList.searchByType(searchType);
                break;
            }
            case 8: {
                cout << "\nExiting program. Thank you!" << endl;
                return 0;
            }
            default: {
                cout << "Invalid choice! Enter 1-8." << endl;
                break;
            }
        }
    }
    return 0;
}