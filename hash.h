//hash.h
//hash data structure for program 3
//Caden McFate
//COSC 2
#ifndef HASH_
#define HASH_
#include <iostream>

template <class T>
class myHash {
private:
    const static int HASHSIZE = 266351; //smallest prime number that is at least twice the size of the dictionary
    T* hash;
    int size;
public:
    myHash();
    ~myHash();
    void insert(T item);
    int find(T item);
    int getSize() { return size; }
    bool isEmpty() { return size == 0; }
    long int findhash(T word);
};

template <class T> //constructor
myHash<T>::myHash() {
    hash = new T[HASHSIZE];
    size = 0;
    for (int i =0; i<HASHSIZE; i++) {
        hash[i] = "";
    }
}

template <class T> //destructor
myHash<T>::~myHash() {
    delete [] hash;
}

template <class T>
void myHash<T>::insert(T item) {
    long int key = findhash(item);
    bool entered = false;
    int attempts = 1;
    while (!entered) {
        if (hash[key].empty()) {
            hash[key] = item; //found a free spot for the word
            size++;
            return;
        }
        else { //spot was already taken
            key += attempts * attempts; //quadratic probing
            if (key >= HASHSIZE) { key = key % HASHSIZE; } //keep hash value within bounds of the array
            attempts++;
        }
    }
}

template <class T>
int myHash<T>::find(T item) {
    int key = findhash(item);
    int compares = 0;
    bool found = false;
    int attempts = 1;
    while (!found) {
        if (item.length() == hash[key].length() && (int)item[0] == (int)hash[key][0]) { //only .compare() when the words are the same length and start with the same letter.
            compares++;
            if (hash[key].compare(item) == 0) {
                found = true;
                return compares; //found
            }
        } else if (hash[key].empty()) {
            return compares *= -1; //word not in dictionary
        }
        key += attempts * attempts; //quadratic probing
        if (key >= HASHSIZE) { key = key % HASHSIZE; } //keep values within the bounds of the array
        attempts++;
    }
    return 0;
}

template <class T>
long int myHash<T>::findhash(T item) {
    int i; long int key = 1;
    for (i = 0; i < item.length(); i++) {
        key += (int)item[i] * (i+1)*(i+1)*(i+1); //adding 1 to i so words of length 1 don't all collide at 0.
    }
    return key % HASHSIZE;
}

#endif
