#ifndef PRIORITYQUEUE_HPP
#define PRIORITYQUEUE_HPP

#include <stdexcept>

template <typename T>
class PriorityQueue {
private:
    struct HeapNode {
        T data;
        int priority;
        HeapNode() : data(T()), priority(0) {}
        HeapNode(const T& value, int prio) : data(value), priority(prio) {}
    };
    
    HeapNode* heap;
    int capacity;
    int size;
    
    void resize() {
        capacity *= 2;
        HeapNode* newHeap = new HeapNode[capacity];
        for (int i = 0; i < size; i++) {
            newHeap[i] = heap[i];
        }
        delete[] heap;
        heap = newHeap;
    }
    
    void heapifyUp(int index) {
        if (index == 0) return;
        
        int parentIndex = (index - 1) / 2;
        if (heap[index].priority < heap[parentIndex].priority) {
            swap(index, parentIndex);
            heapifyUp(parentIndex);
        }
    }
    
    void heapifyDown(int index) {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        int smallest = index;
        
        if (leftChild < size && heap[leftChild].priority < heap[smallest].priority) {
            smallest = leftChild;
        }
        
        if (rightChild < size && heap[rightChild].priority < heap[smallest].priority) {
            smallest = rightChild;
        }
        
        if (smallest != index) {
            swap(index, smallest);
            heapifyDown(smallest);
        }
    }
    
    void swap(int i, int j) {
        HeapNode temp = heap[i];
        heap[i] = heap[j];
        heap[j] = temp;
    }

public:
    PriorityQueue() : capacity(10), size(0) {
        heap = new HeapNode[capacity];
    }
    
    ~PriorityQueue() {
        delete[] heap;
    }
    
    void enqueue(const T& value, int priority) {
        if (size >= capacity) {
            resize();
        }
        
        heap[size] = HeapNode(value, priority);
        heapifyUp(size);
        size++;
    }
    
    T dequeue() {
        if (isEmpty()) {
            throw std::runtime_error("Priority queue is empty");
        }
        
        T result = heap[0].data;
        heap[0] = heap[size - 1];
        size--;
        
        if (size > 0) {
            heapifyDown(0);
        }
        
        return result;
    }
    
    T peek() const {
        if (isEmpty()) {
            throw std::runtime_error("Priority queue is empty");
        }
        return heap[0].data;
    }
    
    bool isEmpty() const {
        return size == 0;
    }
    
    int getSize() const {
        return size;
    }
    
    void clear() {
        size = 0;
    }
    
    // Copy constructor
    PriorityQueue(const PriorityQueue& other) : capacity(other.capacity), size(other.size) {
        heap = new HeapNode[capacity];
        for (int i = 0; i < size; i++) {
            heap[i] = other.heap[i];
        }
    }
    
    // Assignment operator
    PriorityQueue& operator=(const PriorityQueue& other) {
        if (this != &other) {
            delete[] heap;
            capacity = other.capacity;
            size = other.size;
            heap = new HeapNode[capacity];
            for (int i = 0; i < size; i++) {
                heap[i] = other.heap[i];
            }
        }
        return *this;
    }
};

#endif