#ifndef STACK_HPP
#define STACK_HPP

#include <stdexcept>

template <typename T>
class Stack {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };
    
    Node* top;
    int size;

public:
    Stack();
    ~Stack();
    
    void push(const T& value);
    T pop();
    T peek() const;
    bool isEmpty() const;
    int getSize() const;
    void clear();
    
    Stack(const Stack& other);
    Stack& operator=(const Stack& other);
};

template <typename T>
Stack<T>::Stack() : top(nullptr), size(0) {}

template <typename T>
Stack<T>::~Stack() {
    clear();
}

template <typename T>
void Stack<T>::push(const T& value) {
    Node* newNode = new Node(value);
    newNode->next = top;
    top = newNode;
    size++;
}

template <typename T>
T Stack<T>::pop() {
    if (isEmpty()) {
        throw std::runtime_error("Stack is empty");
    }
    
    Node* temp = top;
    T value = top->data;
    top = top->next;
    delete temp;
    size--;
    
    return value;
}

template <typename T>
T Stack<T>::peek() const {
    if (isEmpty()) {
        throw std::runtime_error("Stack is empty");
    }
    return top->data;
}

template <typename T>
bool Stack<T>::isEmpty() const {
    return top == nullptr;
}

template <typename T>
int Stack<T>::getSize() const {
    return size;
}

template <typename T>
void Stack<T>::clear() {
    while (!isEmpty()) {
        Node* temp = top;
        top = top->next;
        delete temp;
    }
    size = 0;
}

template <typename T>
Stack<T>::Stack(const Stack& other) : top(nullptr), size(0) {
    if (other.isEmpty()) {
        return;
    }
    
    Node* current = other.top;
    Stack<T> temp;
    
    while (current != nullptr) {
        temp.push(current->data);
        current = current->next;
    }
    
    while (!temp.isEmpty()) {
        push(temp.pop());
    }
}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack& other) {
    if (this != &other) {
        clear();
        
        if (!other.isEmpty()) {
            Node* current = other.top;
            Stack<T> temp;
            
            while (current != nullptr) {
                temp.push(current->data);
                current = current->next;
            }
            
            while (!temp.isEmpty()) {
                push(temp.pop());
            }
        }
    }
    return *this;
}

#endif