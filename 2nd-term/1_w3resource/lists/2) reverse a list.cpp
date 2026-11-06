// Reverse a list on a place.

#include <iostream>

// 1. Читерим при помощи stl
// 2. Пишем свой список, как на литкоде, и работаем с ним вручную

struct Node { 
    int data; 
    struct Node* next; 
    Node(int data) 
    { 
        this->data = data; 
        next = NULL; 
    } 
}; 
  
struct LinkedList { 
    Node* head; 
    LinkedList() { head = NULL; } 
  
    /* Function to reverse the linked list */
    void reverse() 
    { 
        // Initialize current, previous and next pointers 
        Node* current = head; 
        Node *prev = NULL, *next = NULL; 
  
        while (current != NULL) { 
            // Store next 
            next = current->next; 
            // Reverse current node's pointer 
            current->next = prev; 
            // Move pointers one position ahead. 
            prev = current; 
            current = next; 
        } 
        head = prev; 
    }
};


int main () {
    
}