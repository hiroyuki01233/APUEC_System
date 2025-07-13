#ifndef QUEUE_HPP
#define QUEUE_HPP

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
    Queue();
    ~Queue();
    
    void enqueue(const T& value);
    T dequeue();
    T getFront() const;
    bool isEmpty() const;
    int getSize() const;
    void clear();
};

#endif