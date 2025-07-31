#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <stdexcept>

template <typename T>
class Queue {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };
    
    Node* front;
    Node* rear;
    int size;

public:
    Queue() : front(nullptr), rear(nullptr), size(0) {}

    ~Queue() {
        clear();
    }

    void enqueue(const T& value) {
        Node* newNode = new Node(value);
        if (isEmpty()) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
        size++;
    }

    T dequeue() {
        if (isEmpty()) throw std::runtime_error("Queue is empty");
        Node* temp = front;
        T value = front->data;
        front = front->next;
        delete temp;
        size--;
        if (size == 0) rear = nullptr;
        return value;
    }

    T getFront() const {
        if (isEmpty()) throw std::runtime_error("Queue is empty");
        return front->data;
    }

    bool isEmpty() const {
        return size == 0;
    }

    int getSize() const {
        return size;
    }

    void clear() {
        while (!isEmpty()) {
            dequeue();
        }
    }
};

#endif
