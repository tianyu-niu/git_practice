#include <iostream>
using namespace std;
struct Linkedlist {
    int data;
    Linkedlist *next;
};
void printList(Linkedlist *head) {
    Linkedlist *temp = head;
    while (temp != NULL) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}
void addAtEnd(Linkedlist **head, int value) {
    Linkedlist *newNode = new Linkedlist();
    newNode->data = value;
    newNode->next = NULL;
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Linkedlist *temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}
void addAtBeginning(Linkedlist **head, int value) {
    Linkedlist *newNode = new Linkedlist();
    newNode->data = value;
    newNode->next = *head;
    *head = newNode;
}
bool deleteNode(Linkedlist **head, int value) {
    if (*head == NULL) return false;

    bool deleted = false;
    Linkedlist *temp = *head;
    Linkedlist *prev = NULL;
    while (temp != NULL && temp->data == value) {
        *head = temp->next;
        delete temp;
        temp = *head;
        deleted = true;
    }
    while (temp != NULL) {
        while (temp != NULL && temp->data != value) {
            prev = temp;
            temp = temp->next;
        }
        if (temp == NULL) break;
        prev->next = temp->next;
        delete temp;
        temp = prev->next;
        deleted = true;
    }
    return deleted;
}
void deleteList(Linkedlist *head) {
    Linkedlist *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        delete temp;
    }
}
int main() {
    Linkedlist *head = NULL;
    addAtEnd(&head, 4);
    addAtEnd(&head, 5);
    addAtEnd(&head, 6);
    printList(head);
    addAtBeginning(&head, 3);
    addAtBeginning(&head, 2);
    addAtBeginning(&head, 1);
    printList(head);
    deleteNode(&head, 3);
    printList(head);
    deleteList(head);
    return 0;
} 