#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include <stdexcept>

template <typename T>
class LinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };
    
    Node* head;
    Node* tail;
    int size;

    // Merge Sort helper functions
    Node* getMid(Node* head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }
        
        Node* slow = head;
        Node* fast = head->next;
        
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }
        
        return slow;
    }
    
    Node* merge(Node* left, Node* right, bool (*compare)(const T&, const T&)) {
        if (left == nullptr) return right;
        if (right == nullptr) return left;
        
        if (compare(left->data, right->data)) {
            left->next = merge(left->next, right, compare);
            return left;
        } else {
            right->next = merge(left, right->next, compare);
            return right;
        }
    }
    
    Node* mergeSort(Node* head, bool (*compare)(const T&, const T&)) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }
        
        Node* mid = getMid(head);
        Node* midNext = mid->next;
        mid->next = nullptr;
        
        Node* left = mergeSort(head, compare);
        Node* right = mergeSort(midNext, compare);
        
        return merge(left, right, compare);
    }
    
    void updateTail() {
        if (head == nullptr) {
            tail = nullptr;
        } else {
            Node* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            tail = current;
        }
    }

public:
    LinkedList();
    ~LinkedList();
    
    void pushBack(const T& value);
    void pushFront(const T& value);
    void insert(int index, const T& value);
    
    T& get(int index);
    const T& get(int index) const;
    T& operator[](int index);
    const T& operator[](int index) const;
    
    void remove(int index);
    void removeValue(const T& value);
    void clear();
    
    int getSize() const;
    bool isEmpty() const;
    int indexOf(const T& value) const;
    bool contains(const T& value) const;
    
    T* toArray() const;
    
    // New merge sort method
    void mergeSort(bool (*compare)(const T&, const T&)) {
        if (size <= 1) return;
        
        head = mergeSort(head, compare);
        updateTail();
    }
    
    class Iterator {
    private:
        Node* current;
    public:
        Iterator(Node* node) : current(node) {}
        
        T& operator*() { return current->data; }
        Iterator& operator++() { 
            current = current->next; 
            return *this; 
        }
        bool operator!=(const Iterator& other) const { 
            return current != other.current; 
        }
        bool operator==(const Iterator& other) const { 
            return current == other.current; 
        }
    };
    
    Iterator begin() { return Iterator(head); }
    Iterator end() { return Iterator(nullptr); }
    
    LinkedList(const LinkedList& other);
    LinkedList& operator=(const LinkedList& other);
};

template <typename T>
LinkedList<T>::LinkedList() : head(nullptr), tail(nullptr), size(0) {}

template <typename T>
LinkedList<T>::~LinkedList() {
    clear();
}

template <typename T>
void LinkedList<T>::pushBack(const T& value) {
    Node* newNode = new Node(value);
    if (isEmpty()) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
    size++;
}

template <typename T>
void LinkedList<T>::pushFront(const T& value) {
    Node* newNode = new Node(value);
    if (isEmpty()) {
        head = tail = newNode;
    } else {
        newNode->next = head;
        head = newNode;
    }
    size++;
}

template <typename T>
void LinkedList<T>::insert(int index, const T& value) {
    if (index < 0 || index > size) {
        throw std::out_of_range("Index out of range");
    }
    
    if (index == 0) {
        pushFront(value);
        return;
    }
    
    if (index == size) {
        pushBack(value);
        return;
    }
    
    Node* newNode = new Node(value);
    Node* prev = nullptr;
    Node* current = head;
    
    for (int i = 0; i < index; i++) {
        prev = current;
        current = current->next;
    }
    
    prev->next = newNode;
    newNode->next = current;
    size++;
}

template <typename T>
T& LinkedList<T>::get(int index) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of range");
    }
    
    Node* current = head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    
    return current->data;
}

template <typename T>
const T& LinkedList<T>::get(int index) const {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of range");
    }
    
    Node* current = head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    
    return current->data;
}

template <typename T>
T& LinkedList<T>::operator[](int index) {
    return get(index);
}

template <typename T>
const T& LinkedList<T>::operator[](int index) const {
    return get(index);
}

template <typename T>
void LinkedList<T>::remove(int index) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of range");
    }
    
    Node* toDelete;
    
    if (index == 0) {
        toDelete = head;
        head = head->next;
        if (head == nullptr) {
            tail = nullptr;
        }
    } else {
        Node* prev = nullptr;
        Node* current = head;
        
        for (int i = 0; i < index; i++) {
            prev = current;
            current = current->next;
        }
        
        toDelete = current;
        prev->next = current->next;
        
        if (current == tail) {
            tail = prev;
        }
    }
    
    delete toDelete;
    size--;
}

template <typename T>
void LinkedList<T>::removeValue(const T& value) {
    int index = indexOf(value);
    if (index != -1) {
        remove(index);
    }
}

template <typename T>
void LinkedList<T>::clear() {
    while (!isEmpty()) {
        remove(0);
    }
}

template <typename T>
int LinkedList<T>::getSize() const {
    return size;
}

template <typename T>
bool LinkedList<T>::isEmpty() const {
    return size == 0;
}

template <typename T>
int LinkedList<T>::indexOf(const T& value) const {
    Node* current = head;
    for (int i = 0; i < size; i++) {
        if (current->data == value) {
            return i;
        }
        current = current->next;
    }
    return -1;
}

template <typename T>
bool LinkedList<T>::contains(const T& value) const {
    return indexOf(value) != -1;
}

template <typename T>
T* LinkedList<T>::toArray() const {
    if (isEmpty()) {
        return nullptr;
    }
    
    T* array = new T[size];
    Node* current = head;
    for (int i = 0; i < size; i++) {
        array[i] = current->data;
        current = current->next;
    }
    return array;
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList& other) : head(nullptr), tail(nullptr), size(0) {
    Node* current = other.head;
    while (current != nullptr) {
        pushBack(current->data);
        current = current->next;
    }
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList& other) {
    if (this != &other) {
        clear();
        Node* current = other.head;
        while (current != nullptr) {
            pushBack(current->data);
            current = current->next;
        }
    }
    return *this;
}

#endif