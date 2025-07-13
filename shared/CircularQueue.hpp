#ifndef CIRCULARQUEUE_HPP
#define CIRCULARQUEUE_HPP

template <typename T>
class CircularQueue {
private:
    T* array;
    int front;
    int rear;
    int capacity;
    int size;

public:
    CircularQueue(int cap);
    ~CircularQueue();
    
    void enqueue(const T& value);
    T dequeue();
    T getFront() const;
    bool isEmpty() const;
    bool isFull() const;
    int getSize() const;
    void clear();
};

#endif