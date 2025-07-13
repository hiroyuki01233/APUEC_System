#ifndef HASHMAP_HPP
#define HASHMAP_HPP

#include "LinkedList.hpp"
#include <string>
#include <functional>

template <typename K, typename V>
class HashMap {
private:
    struct KeyValuePair {
        K key;
        V value;
        
        KeyValuePair() {}
        KeyValuePair(const K& k, const V& v) : key(k), value(v) {}
        
        bool operator==(const KeyValuePair& other) const {
            return key == other.key;
        }
    };
    
    static const int DEFAULT_CAPACITY = 16;
    LinkedList<KeyValuePair>* buckets;
    int capacity;
    int size;
    
    int hash(const K& key) const;
    void resize();

public:
    HashMap(int initialCapacity = DEFAULT_CAPACITY);
    ~HashMap();
    
    void put(const K& key, const V& value);
    V get(const K& key) const;
    V& operator[](const K& key);
    bool contains(const K& key) const;
    void remove(const K& key);
    void clear();
    
    int getSize() const;
    bool isEmpty() const;
    
    LinkedList<K> keys() const;
    LinkedList<V> values() const;
    
    HashMap(const HashMap& other);
    HashMap& operator=(const HashMap& other);
};

template <typename K, typename V>
HashMap<K, V>::HashMap(int initialCapacity) : capacity(initialCapacity), size(0) {
    buckets = new LinkedList<KeyValuePair>[capacity];
}

template <typename K, typename V>
HashMap<K, V>::~HashMap() {
    delete[] buckets;
}

template <typename K, typename V>
int HashMap<K, V>::hash(const K& key) const {
    std::hash<K> hasher;
    return hasher(key) % capacity;
}

template <typename K, typename V>
void HashMap<K, V>::put(const K& key, const V& value) {
    int index = hash(key);
    LinkedList<KeyValuePair>& bucket = buckets[index];
    
    for (int i = 0; i < bucket.getSize(); i++) {
        if (bucket[i].key == key) {
            bucket[i].value = value;
            return;
        }
    }
    
    bucket.pushBack(KeyValuePair(key, value));
    size++;
    
    if (size > capacity * 0.75) {
        resize();
    }
}

template <typename K, typename V>
V HashMap<K, V>::get(const K& key) const {
    int index = hash(key);
    const LinkedList<KeyValuePair>& bucket = buckets[index];
    
    for (int i = 0; i < bucket.getSize(); i++) {
        if (bucket[i].key == key) {
            return bucket[i].value;
        }
    }
    
    throw std::runtime_error("Key not found");
}

template <typename K, typename V>
V& HashMap<K, V>::operator[](const K& key) {
    int index = hash(key);
    LinkedList<KeyValuePair>& bucket = buckets[index];
    
    for (int i = 0; i < bucket.getSize(); i++) {
        if (bucket[i].key == key) {
            return bucket[i].value;
        }
    }
    
    bucket.pushBack(KeyValuePair(key, V()));
    size++;
    
    if (size > capacity * 0.75) {
        resize();
        index = hash(key);
        LinkedList<KeyValuePair>& newBucket = buckets[index];
        for (int i = 0; i < newBucket.getSize(); i++) {
            if (newBucket[i].key == key) {
                return newBucket[i].value;
            }
        }
    }
    
    return bucket[bucket.getSize() - 1].value;
}

template <typename K, typename V>
bool HashMap<K, V>::contains(const K& key) const {
    int index = hash(key);
    const LinkedList<KeyValuePair>& bucket = buckets[index];
    
    for (int i = 0; i < bucket.getSize(); i++) {
        if (bucket[i].key == key) {
            return true;
        }
    }
    
    return false;
}

template <typename K, typename V>
void HashMap<K, V>::remove(const K& key) {
    int index = hash(key);
    LinkedList<KeyValuePair>& bucket = buckets[index];
    
    for (int i = 0; i < bucket.getSize(); i++) {
        if (bucket[i].key == key) {
            bucket.remove(i);
            size--;
            return;
        }
    }
}

template <typename K, typename V>
void HashMap<K, V>::clear() {
    for (int i = 0; i < capacity; i++) {
        buckets[i].clear();
    }
    size = 0;
}

template <typename K, typename V>
int HashMap<K, V>::getSize() const {
    return size;
}

template <typename K, typename V>
bool HashMap<K, V>::isEmpty() const {
    return size == 0;
}

template <typename K, typename V>
LinkedList<K> HashMap<K, V>::keys() const {
    LinkedList<K> keyList;
    for (int i = 0; i < capacity; i++) {
        const LinkedList<KeyValuePair>& bucket = buckets[i];
        for (int j = 0; j < bucket.getSize(); j++) {
            keyList.pushBack(bucket[j].key);
        }
    }
    return keyList;
}

template <typename K, typename V>
LinkedList<V> HashMap<K, V>::values() const {
    LinkedList<V> valueList;
    for (int i = 0; i < capacity; i++) {
        const LinkedList<KeyValuePair>& bucket = buckets[i];
        for (int j = 0; j < bucket.getSize(); j++) {
            valueList.pushBack(bucket[j].value);
        }
    }
    return valueList;
}

template <typename K, typename V>
void HashMap<K, V>::resize() {
    int newCapacity = capacity * 2;
    LinkedList<KeyValuePair>* newBuckets = new LinkedList<KeyValuePair>[newCapacity];
    
    LinkedList<KeyValuePair>* oldBuckets = buckets;
    int oldCapacity = capacity;
    
    buckets = newBuckets;
    capacity = newCapacity;
    size = 0;
    
    for (int i = 0; i < oldCapacity; i++) {
        LinkedList<KeyValuePair>& bucket = oldBuckets[i];
        for (int j = 0; j < bucket.getSize(); j++) {
            put(bucket[j].key, bucket[j].value);
        }
    }
    
    delete[] oldBuckets;
}

template <typename K, typename V>
HashMap<K, V>::HashMap(const HashMap& other) : capacity(other.capacity), size(0) {
    buckets = new LinkedList<KeyValuePair>[capacity];
    for (int i = 0; i < other.capacity; i++) {
        const LinkedList<KeyValuePair>& bucket = other.buckets[i];
        for (int j = 0; j < bucket.getSize(); j++) {
            put(bucket[j].key, bucket[j].value);
        }
    }
}

template <typename K, typename V>
HashMap<K, V>& HashMap<K, V>::operator=(const HashMap& other) {
    if (this != &other) {
        delete[] buckets;
        capacity = other.capacity;
        size = 0;
        buckets = new LinkedList<KeyValuePair>[capacity];
        
        for (int i = 0; i < other.capacity; i++) {
            const LinkedList<KeyValuePair>& bucket = other.buckets[i];
            for (int j = 0; j < bucket.getSize(); j++) {
                put(bucket[j].key, bucket[j].value);
            }
        }
    }
    return *this;
}

#endif