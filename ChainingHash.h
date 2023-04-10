/*
 *  Separate chaining hashtable
 */

#ifndef __CHAINING_HASH_H
#define __CHAINING_HASH_H

// Standard library includes
#include <iostream>
#include <vector>
#include <list>
#include <stdexcept>

// Custom project includes
#include "Hash.h"

// Namespaces to include
using std::vector;
using std::list;
using std::pair;

using std::cout;
using std::endl;

//
// Separate chaining based hash table - derived from Hash
//
template<typename K, typename V>
class ChainingHash : public Hash<K,V> {
private:

public:
    ChainingHash(int n = 11) {
    }

    ~ChainingHash() {
        //this->clear();
    }

    bool empty() {
    }

    int size() {
    }

    V& at(const K& key) {
        throw std::out_of_range("Key not in hash");
    }

    V& operator[](const K& key) {
    }

    int count(const K& key) {
    }

    void emplace(K key, V value) {
    }

    void insert(const std::pair<K, V>& pair) {
    }

    void erase(const K& key) {
    }

    void clear() {
    }

    int bucket_count() {
    }

    int bucket_size(int n) {
    }

    int bucket(const K& key) {
    }

    float load_factor() {
    }

    void rehash() {
    }

    void rehash(int n) {
    }


private:
    int findNextPrime(int n)
    {
        while (!isPrime(n))
        {
            n++;
        }
        return n;
    }

    int isPrime(int n)
    {
        for (int i = 2; i <= sqrt(n); i++)
        {
            if (n % i == 0)
            {
                return false;
            }
        }

        return true;
    }

    int hash(const K& key) {
        return 0;       
    }

};

#endif //__CHAINING_HASH_H
