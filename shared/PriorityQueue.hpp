#ifndef PRIORITYQUEUE_HPP
#define PRIORITYQUEUE_HPP

template <typename T>
class PriorityQueue {
private:
    struct Node {
        T data;
        int priority;
        Node* next;
        Node(const T& value, int prio) : data(value), priority(prio), next(nullptr) {}
    };
    
    Node* front;
    int size;

public:
    PriorityQueue();
    ~PriorityQueue();
    
    void enqueue(const T& value, int priority);
    T dequeue();
    T peek() const;
    bool isEmpty() const;
    int getSize() const;
    void clear();
};

#endif